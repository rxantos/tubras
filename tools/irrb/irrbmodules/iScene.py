#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import Blender,iUtils,iMaterials,time,math

#-----------------------------------------------------------------------------
#                           w r i t e U s e r D a t a
#-----------------------------------------------------------------------------
def writeUserData(file,i1,i2,props):

    if type(props) != Blender.Types.IDGroupType:
        return

    file.write(i1 + '<userData>\n')
    file.write(i2 + '<attributes>\n')
    i3 = i2 + '   '

    # extract from irrb:userAttributes namespace
    if 'irrb' in props and 'userAttributes' in props['irrb']:
        userAttributes = props['irrb']['userAttributes']
        for name in userAttributes:
            data = userAttributes[name]
            dtype = type(data)
            stype = None
            if dtype == int:
                stype = 'int'
                svalue = str(data)
            elif dtype == str:
                stype = 'string'
                svalue = data
            elif dtype == float:
                stype = 'float'
                svalue = iUtils.float2str(data)

            if stype != None:
                pout = '<%s name="%s" value="%s" />\n' % (stype,name,svalue)
                file.write(i3 + pout)

    file.write(i2 + '</attributes>\n')
    file.write(i1 + '</userData>\n')



#-----------------------------------------------------------------------------
#                                 S c e n e
#-----------------------------------------------------------------------------
class Scene:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,exporter):
        self.exporter = exporter


    #-------------------------------------------------------------------------
    #                            w r i t e H e a d e r
    #-------------------------------------------------------------------------
    def writeHeader(self,file):

        file.write('<?xml version="1.0"?>\n')
        datetime = (iUtils.datetime2str(time.localtime()), 
                     iUtils.getversion())
        file.write(('<!-- Created %s by irrb %s - "Irrlicht/Blender ' + 
                'Exporter" -->\n') % datetime)
        file.write('<irr_scene>\n')
        file.write('   <attributes>\n')
        file.write('      <string name="Name" value="root" />\n')
        file.write('      <int name="Id" value="-1" />\n')
        file.write('      <vector3d name="Position" value="0.000000, ' + 
                '0.000000, 0.000000" />\n')
        file.write('      <vector3d name="Rotation" value="0.000000, ' + 
                '0.000000, 0.000000" />\n')
        file.write('      <vector3d name="Scale" value="1.000000, ' 
                + '1.000000, 1.000000" />\n')
        file.write('      <bool name="Visible" value="true" />\n')
        file.write('      <bool name="AutomaticCulling" value="true" />\n')
        file.write('      <bool name="DebugDataVisible" value="false" />\n')
        file.write('      <bool name="IsDebugObject" value="false" />\n')
        file.write('   </attributes>\n')

        file.write('   <userData>\n')
        file.write('      <attributes>\n')
        file.write('         <bool name="OccludesLight" value="false" />\n')
        file.write('      </attributes>\n')
        file.write('   </userData>\n')

    #-------------------------------------------------------------------------
    #                            w r i t e F o o t e r
    #-------------------------------------------------------------------------
    def writeFooter(self,file):
        file.write('</irr_scene>\n')


    #-------------------------------------------------------------------------
    #                     w r i t e S T D A t t r i b u t e s
    #-------------------------------------------------------------------------
    def writeSTDAttributes(self,file,i1,i2,bObject,spos,srot,sscale,cullDefault='frustum_box'):
        
        file.write(i1 + '<attributes>\n')

        props = bObject.properties

        #
        # std attribute defaults
        #
        sa = iUtils.StdAttributes()
        sa.AutomaticCulling = cullDefault
        sa.updateFromObject(bObject);
        

        file.write(i2 + '<string name="Name" value="%s" />\n' % 
                (bObject.getName()))
        file.write(i2 + '<int name="Id" value="%d" />\n' % sa.id)
        file.write(i2 + '<vector3d name="Position" value="%s" />\n' % 
                (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s" />\n' % 
                (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s" />\n' % 
                (sscale))
        file.write(i2 + '<bool name="Visible" value="%s" />\n' % 
                sa.Visible)
        file.write(i2 + '<enum name="AutomaticCulling" value="%s" />\n' % 
                sa.AutomaticCulling)
        file.write(i2 + '<bool name="DebugDataVisible" value="%s" />\n' % 
                sa.DebugDataVisible)
        file.write(i2 + '<bool name="IsDebugObject" value="%s" />\n' % 
                sa.IsDebugObject)
        file.write(i2 + '<bool name="ReadOnlyMaterials" value="%s" />\n' % 
                sa.ReadOnlyMaterials)


    #-------------------------------------------------------------------------
    #                       w r i t e M e s h O b j e c t
    #-------------------------------------------------------------------------
    def writeMeshObject(self, file, meshFileName, bObject, level):

        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        irot = iUtils.b2iRotation(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())
        
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)
        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        file.write(i2 + '<string name="Mesh" value="%s" />\n' % 
                (meshFileName))
        file.write(i1 + '</attributes>\n')
    
        writeUserData(file,i1,i2,bObject.properties)

    #-------------------------------------------------------------------------
    #                       w r i t e E m p t y O b j e c t
    #-------------------------------------------------------------------------
    def writeEmptyObject(self,file,bObject,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        irot = iUtils.b2iRotation(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())
                
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)

        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)
        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        file.write(i1 + '</attributes>\n')
    
        writeUserData(file,i1,i2,bObject.getAllProperties())

    #-------------------------------------------------------------------------
    #                     w r i t e N o d e H e a d
    #-------------------------------------------------------------------------
    def writeNodeHead(self,file,level,ntype):
        indent = iUtils.getIndent(level)
        file.write(indent + ('<node type="%s">\n') % ntype)

    #-------------------------------------------------------------------------
    #                     w r i t e N o d e T a i l
    #-------------------------------------------------------------------------
    def writeNodeTail(self,file,level):
        indent = iUtils.getIndent(level)
        file.write(indent + '</node>\n')

    #-------------------------------------------------------------------------
    #                      w r i t e L i g h t N o d e D a t a
    #-------------------------------------------------------------------------
    def writeLightNodeData(self,file,bObject,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        irot = iUtils.b2iRotation(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())

        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)

        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)
        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)
    

        light = bObject.getData()

        lightType = 'Point'
        if light.type == Blender.Lamp.Types['Lamp']:
            lightType = 'Point'
        if light.type == Blender.Lamp.Types['Area']:
            lightType = 'Directional'
        if light.type == Blender.Lamp.Types['Spot']:
            lightType = 'Spot'
        if light.type == Blender.Lamp.Types['Sun']:
            lightType = 'Directional'
        if light.type == Blender.Lamp.Types['Hemi']:
            lightType = 'Directional'

        file.write(i2 + '<enum name="LightType" value="%s" />\n' % 
                lightType)

        diffuse = '%.6f, %.6f, %.6f %.6f' % (light.R,light.G,light.B,1.0)

        file.write(i2 + '<colorf name="AmbientColor" value="0.000000,' + 
                '0.000000, 0.000000, 1.000000" />\n')
        file.write(i2 + '<colorf name="DiffuseColor" value="%s" />\n' % 
                diffuse)
        file.write(i2 + '<colorf name="SpecularColor" value="1.000000,' + 
                '1.000000, 1.000000, 1.000000" />\n')

        attvalue = 0.0
        if light.energy != 0.000000:
            attvalue = 0.5 / light.energy
        satt = '0.000000 %.6f 0.000000' % attvalue
        file.write(i2 + '<vector3d name="Attenuation" value="%s" />\n' % 
                (satt))
        
        file.write(i2 + '<float name="Radius" value="%.2f" />\n' % 
                (light.dist * 2.0))
        file.write(i2 + '<bool name="CastShadows" value="true" />\n')
        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject.getAllProperties())        
        
    #-------------------------------------------------------------------------
    #                      w r i t e C a m e r a N o d e D a t a
    #-------------------------------------------------------------------------
    def writeCameraNodeData(self,file,bObject,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        irot = iUtils.b2iRotation(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())
    
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)
        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)    

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale)

        camera = bObject.getData()

        #
        # calculate target based on x,z rotation 
        #
        
        target = Blender.Mathutils.Vector(0.0,0.0,0.0)
        #target.normalize()
        #target = target * 100.0

        rpos = Blender.Mathutils.Vector(ipos.x,ipos.y,ipos.z)
        #target = target + rpos

        starget = '%.6f, %.6f, %.6f' % (target.x, target.z, target.y)

        #
        # override fov & aspect with logic properties if defined
        #
        fov = 2 * math.atan(16.0 / camera.lens )
        aspect = 1.25

        cprops = bObject.properties

        prop = iUtils.getProperty('fov',cprops)
        if prop != None and type(prop) == float:
            fov = prop

        prop = iUtils.getProperty('aspect',cprops)
        if prop != None and type(prop) == float:
            aspect = prop
    

        file.write(i2 + '<vector3d name="Target" value="%s" />\n' % (starget))
        file.write(i2 + '<vector3d name="UpVector" value="0.000000,' + 
                ' 1.000000, 0.000000" />\n')
        file.write(i2 + '<float name="Fovy" value="%.6f" />\n' % fov)
        file.write(i2 + '<float name="Aspect" value="%.6f" />\n' % aspect)
        file.write(i2 + '<float name="ZNear" value="%.2f" />\n' % 
                camera.clipStart)
        file.write(i2 + '<float name="ZFar" value="%.2f" />\n' % 
                camera.clipEnd)

        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject.getAllProperties())

    #-------------------------------------------------------------------------
    #                              _ i w r i t e
    #-------------------------------------------------------------------------
    def _iwrite(self,file,tag,name,value,indent):
        svalue = '?enum?'
        if tag == 'enum':
            svalue = value
        elif tag == 'color':
            svalue = iUtils.colour2str(value)
        elif tag == 'float':
            svalue = iUtils.float2str(value)
        elif tag == 'texture':
            svalue = value
        elif tag == 'int':
            svalue = iUtils.int2str(value)
        elif tag == 'bool':
            svalue = iUtils.bool2str(value)

        out = indent + '<%s name="%s" value="%s"/>\n' % (tag,name,svalue)
        file.write(out)  

    #-----------------------------------------------------------------------------
    #                    _ w r i t e S B I m a g e A t t r i b u t e s
    #-----------------------------------------------------------------------------
    def _writeSBImageAttributes(self,file,indent,matType,bImage,bObject):

        i2 = indent + '    '
        imageName = self.exporter.getImageFileName(bObject.getData().name,bImage,0)
        file.write(indent + '<attributes>\n')
        self._iwrite(file,'enum','Type',matType, i2)
        self._iwrite(file,'color','Ambient',0xFFFFFFFF,i2)
        self._iwrite(file,'color','Diffuse',0xFFFFFFFF,i2)
        self._iwrite(file,'color','Emissive',0,i2)
        self._iwrite(file,'color','Specular',0xFFFFFFFF,i2)
        self._iwrite(file,'float','Shininess',0.0,i2)
        self._iwrite(file,'float','Param1',0.0,i2)
        self._iwrite(file,'float','Param2',0.0,i2)
        self._iwrite(file,'texture','Texture1',imageName,i2)
        self._iwrite(file,'bool','Wireframe',False,i2)
        self._iwrite(file,'bool','GouraudShading',True,i2)
        self._iwrite(file,'bool','Lighting',False,i2)
        self._iwrite(file,'bool','ZWriteEnable',False,i2)
        self._iwrite(file,'int','ZBuffer',0,i2)
        self._iwrite(file,'bool','BackfaceCulling',False,i2)
        self._iwrite(file,'bool','FogEnable',False,i2)
        self._iwrite(file,'bool','NormalizeNormals',False,i2)
        self._iwrite(file,'bool','BilinearFilter1',False,i2)
        self._iwrite(file,'bool','TrilinearFilter1',False,i2)
        if self.exporter.gIrrlichtVersion >= 16:
            self._iwrite(file,'int','AnisotropicFilter1',0,i2)
        else:
            self._iwrite(file,'bool','AnisotropicFilter1',False,i2)
        self._iwrite(file,'enum','TextureWrap1','texture_clamp_clamp',i2)
        file.write(indent + '</attributes>\n')

    #-----------------------------------------------------------------------------
    #                     w r i t e S k y B o x N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeSkyBoxNodeData(self,file,bObject,sImages,level):

        topImage = sImages[0]
        botImage = sImages[1]
        leftImage = sImages[2]
        rightImage = sImages[3]
        frontImage = sImages[4]
        backImage = sImages[5]

        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        spos = '%.6f, %.6f, %.6f' % (0.0, 0.0, 0.0)
        srot = '%.6f, %.6f, %.6f' % (0.0, 0.0, 0.0)
        sscale = '%.6f, %.6f, %.6f' % (1.0, 1.0, 1.0)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale,'false')

        file.write(i1 + '</attributes>\n')
        file.write(i1 + '<materials>\n')

        self._writeSBImageAttributes(file, i2, 'solid', frontImage, bObject)
        self._writeSBImageAttributes(file, i2, 'solid', rightImage, bObject)
        self._writeSBImageAttributes(file, i2, 'solid', backImage, bObject)
        self._writeSBImageAttributes(file, i2, 'solid', leftImage, bObject)
        self._writeSBImageAttributes(file, i2, 'solid', topImage, bObject)
        self._writeSBImageAttributes(file, i2, 'solid', botImage, bObject)

        file.write(i1 + '</materials>\n')
        
    #-----------------------------------------------------------------------------
    #                   w r i t e B i l l b o a r d N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeBillboardNodeData(self,file,bObject,bbImage,level):

        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())
    
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)
        srot = '%.6f, %.6f, %.6f' % (0.0, 0.0, 0.0)
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)    

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale,'false')

        file.write(i2 + '<int name="Width" value="%.6f" />\n' % iscale.x)
        file.write(i2 + '<int name="Height" value="%.6f" />\n' % iscale.z)
        file.write(i2 + '<color name="Shade_Top" value="ffffffff" />\n')
        file.write(i2 + '<color name="Shade_Down" value="ffffffff" />\n')

        file.write(i1 + '</attributes>\n')
        file.write(i1 + '<materials>\n')

        # extract material type based on irrb UV layer rules
        bMesh = bObject.getData(False,True)
        uvLayerNames = bMesh.getUVLayerNames()
        irrMatInfo = None
        for name in uvLayerNames:
            irrMatInfo = iMaterials.getIrrMaterial(name)
            if irrMatInfo != None:
                break
        if irrMatInfo == None:
            irrMatInfo = ('solid',1)

        self._writeSBImageAttributes(file, i2, irrMatInfo[0], bbImage,
                bObject)

        file.write(i1 + '</materials>\n')
        
