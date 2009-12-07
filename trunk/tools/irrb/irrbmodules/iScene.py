#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import Blender
import iUtils
import iMaterials
import time
import math

#-----------------------------------------------------------------------------
#                           w r i t e U s e r D a t a
#-----------------------------------------------------------------------------
def writeUserData(file,i1,i2,bObject,writeClose=True):

    props = bObject.properties

    if type(props) != Blender.Types.IDGroupType:
        return

    file.write(i1 + '<userData>\n')
    file.write(i2 + '<attributes>\n')
    i3 = i2 + '   '

    # extract from irrb:userAttributes namespace
    if 'irrb' in props and 'userAttributes' in props['irrb']:
        userAttributes = props['irrb']['userAttributes']
        keys = userAttributes.keys()
        keys.sort()
        for name in keys:
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
                
            if name.lower().find('color') >= 0:
                stype = 'colorf'

            if stype != None:
                pout = '<%s name="%s" value="%s"/>\n' % (stype,name,svalue)
                file.write(i3 + pout)

    #
    # write game properties
    #
    try:
        gprops = bObject.getAllProperties()
        for p in gprops:
            dtype = p.getType()
            name = p.getName()
            data = p.getData()

            stype = None
            svalue = ''
            if dtype == 'STRING':
                stype = 'string'
                svalue = data
            elif dtype == 'INT':
                stype = 'int'
                svalue = str(data)
            elif dtype == 'BOOL':
                stype = 'bool'
                svalue = 'false'
                if data == True:
                    svalue = 'true'
            elif dtype == 'FLOAT':
                stype = 'float'
                svalue = iUtils.float2str(data)
            if stype != None:
                pout = '<%s name="%s" value="%s"/>\n' % (stype,name,svalue)
                file.write(i3 + pout)
    except:
        pass

    if writeClose:
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
    #                       w r i t e S c e n e H e a d e r
    #-------------------------------------------------------------------------
    def writeSceneHeader(self,file,scene, physicsEnabled):

        world = Blender.World.GetCurrent()
        amb = world.getAmb()
        scolor = '%.6f, %.6f, %.6f %.6f' % (amb[0],amb[1],amb[2],1.0)

        file.write('<?xml version="1.0"?>\n')
        datetime = (iUtils.datetime2str(time.localtime()), 
                     iUtils.getversion())
        file.write(('<!-- Created %s by irrb %s - "Irrlicht/Blender ' + 
                'Exporter" -->\n') % datetime)
        file.write('<irr_scene>\n')
        file.write('   <attributes>\n')
        file.write('      <string name="Name" value="root"/>\n')
        file.write('      <int name="Id" value="-1"/>\n')
        file.write('      <vector3d name="Position" value="0.000000, ' + 
                '0.000000, 0.000000"/>\n')
        file.write('      <vector3d name="Rotation" value="0.000000, ' + 
                '0.000000, 0.000000"/>\n')
        file.write('      <vector3d name="Scale" value="1.000000, ' 
                + '1.000000, 1.000000"/>\n')
        file.write('      <colorf name="AmbientLight" value="%s"/>\n' % (scolor))
        file.write('      <bool name="AutomaticCulling" value="true"/>\n')
        file.write('      <bool name="DebugDataVisible" value="false"/>\n')
        file.write('      <bool name="IsDebugObject" value="false"/>\n')
        file.write('      <bool name="Visible" value="true"/>\n')
        
        # mist/fog enabled
        mode = world.getMode()
        if(mode & 1):
            mist = world.getMist()
            mistType = world.getMistype()
            if mistType == 0:
                sMistType = 'FogExp'
            elif mistType == 1:
                sMistType = 'FogLinear'
            else:
                sMistType = 'FogExp2'
            file.write('      <enum name="FogType" value="%s"/>\n' % (sMistType))
            file.write('      <float name="FogStart" value="%.6f"/>\n' % (mist[1]))
            file.write('      <float name="FogEnd" value="%.6f"/>\n' % (mist[2]))
            file.write('      <float name="FogHeight" value="%.6f"/>\n' % (mist[3]))
            file.write('      <float name="FogDensity" value="%.6f"/>\n' % (mist[0]))
            fcolor = world.getHor()
            scolor = '%.6f, %.6f, %.6f, %.6f' % (fcolor[0],fcolor[1],fcolor[2],1.0)
            file.write('      <colorf name="FogColor" value="%s"/>\n' % (scolor))
            file.write('      <bool name="FogPixel" value="false"/>\n')
            file.write('      <bool name="FogRange" value="false"/>\n')

        file.write('   </attributes>\n')

        if not 'irrb' in scene.properties:
            scene.properties['irrb'] = {'userAttributes': iUtils.defSceneAttributes}

        try:
            scene.properties['irrb']['userAttributes']['Gravity'] = -world.gravity
        except:
            pass

        scene.properties['irrb']['userAttributes']['Physics.Enabled'] = physicsEnabled

        writeUserData(file, '   ', 2*'   ', scene)

    #-------------------------------------------------------------------------
    #                      w r i t e S c e n e F o o t e r
    #-------------------------------------------------------------------------
    def writeSceneFooter(self,file):
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
        sa.inheritFromObject(bObject);
        
        file.write(i2 + '<string name="Name" value="%s"/>\n' % 
                (bObject.getName()))

        self._iwrite(file,'int','Id',sa.attributes['Id'],i2)

        file.write(i2 + '<vector3d name="Position" value="%s"/>\n' % 
                (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s"/>\n' % 
                (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s"/>\n' % 
                (sscale))
        self._iwrite(file,'bool','Visible',sa.attributes['Visible'],i2)
        self._iwrite(file,'enum','AutomaticCulling',sa.attributes['AutomaticCulling'],i2)
        self._iwrite(file,'bool','DebugDataVisible',sa.attributes['DebugDataVisible'],i2)
        self._iwrite(file,'bool','IsDebugObject',sa.attributes['IsDebugObject'],i2)
        self._iwrite(file,'bool','ReadOnlyMaterials',sa.attributes['ReadOnlyMaterials'],i2)


    #-------------------------------------------------------------------------
    #                       w r i t e M e s h O b j e c t
    #-------------------------------------------------------------------------
    def writeMeshObject(self, file, meshFileName, bObject, level, physicsEnabled):

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

        file.write(i2 + '<string name="Mesh" value="%s"/>\n' % 
                (iUtils.flattenPath(meshFileName)))
        file.write(i1 + '</attributes>\n')

        if physicsEnabled == 0:
            writeUserData(file,i1,i2,bObject, True)
            return

        writeUserData(file,i1,i2,bObject, False)
        ctype = 'none'
        response = False
        hasBounds = False
        rbFlags = bObject.rbFlags

        # from DNA_Object_types.h
        OB_OCCLUDER		= 0x40000
        OB_SENSOR		= 0x80000

        addMass = False
        if (rbFlags & 0x10000) == 0x10000:
            ctype = 'static'
            if rbFlags & Blender.Object.RBFlags['DYNAMIC']:
                addMass = True
                ctype = 'dynamic'
            if rbFlags & Blender.Object.RBFlags['RIGIDBODY']:
                addMass = True
                ctype = 'rigid'
            if rbFlags & Blender.Object.RBFlags['COLLISION_RESPONSE']:
                response = True
            if rbFlags & Blender.Object.RBFlags['BOUNDS']:
                hasBounds = True
            if bObject.isSoftBody:
                ctype = 'soft'
            if rbFlags & OB_SENSOR:
                ctype = 'trigger'
            if rbFlags & OB_OCCLUDER:
                ctype = 'occluder'

        if ctype == 'static':
            addMass = False

        i3 = i2 + '   '
        sout = '<string name="Physics.BodyType" value="%s"/>\n' % ctype
        file.write(i3 + sout)

        sShapeType = 'concavemesh' #default shape - concave mesh
        if hasBounds:
            ShapeType = bObject.rbShapeBoundType
            if ShapeType == 0:      # OB_BOUND_BOX - "Box"
                sShapeType = 'box'
            elif ShapeType == 1:    # OB_BOUND_SPHERE - "Sphere"
                sShapeType = 'sphere'
            elif ShapeType == 2:    # OB_BOUND_CYLINDER - "Cylinder"
                sShapeType = 'cylinder'
            elif ShapeType == 3:    # OB_BOUND_CONE - "Cone"
                sShapeType = 'cone'
            elif ShapeType == 4:    # OB_BOUND_POLYH - "Concave TriangleMesh"
                sShapeType = 'concavemesh'
            elif ShapeType == 5:    # OB_BOUND_POLYT - "Convex Hull"
                sShapeType = 'convexmesh'
            if rbFlags & Blender.Object.RBFlags['CHILD']:
                sout = '<bool name="Physics.Compound" value="true"/>\n'
                file.write(i3 + sout)
        sout = '<string name="Physics.BodyShape" value="%s"/>\n' % sShapeType
        file.write(i3 + sout)
        
        if bObject.restrictRender:
            sout = '<bool name="Physics.Visible" value="false"/>\n'
        else:
            sout = '<bool name="Physics.Visible" value="true"/>\n'
        file.write(i3 + sout)

        if addMass:
            sout = '<float name="Physics.Mass" value="%.2f"/>\n' % bObject.rbMass
            file.write(i3 + sout)

        if sShapeType == 'sphere':
            sout = '<float name="Physics.Radius" value="%.2f"/>\n' % bObject.rbRadius
            file.write(i3 + sout)


        if rbFlags & Blender.Object.RBFlags['GHOST']:
            sout = '<bool name="Physics.Ghost" value="true"/>\n'
            file.write(i3 + sout)

        if rbFlags & Blender.Object.RBFlags['ACTOR']:
            sout = '<bool name="Physics.Actor" value="true"/>\n'
            file.write(i3 + sout)

        if rbFlags & Blender.Object.RBFlags['MAINACTOR']:
            sout = '<bool name="Physics.MainActor" value="true"/>\n'
            file.write(i3 + sout)

        if rbFlags & Blender.Object.RBFlags['COLLISION_RESPONSE']:
            sout = '<bool name="Physics.CollisionResponse" value="true"/>\n'
            file.write(i3 + sout)

        # extract friction & restitution from 1st material
        mesh =  bObject.getData(False,True)
        if (mesh.materials != None) and (len(mesh.materials) > 0):
            mat = mesh.materials[0]
            if mat != None:
                sout = '<float name="Physics.Friction" value="%.2f"/>\n' % mat.rbFriction
                file.write(i3 + sout)

                sout = '<float name="Physics.Restitution" value="%.2f"/>\n' % mat.rbRestitution
                file.write(i3 + sout)

        file.write(i2 + '</attributes>\n')
        file.write(i1 + '</userData>\n')

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
    
        writeUserData(file,i1,i2,bObject)

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

        file.write(i2 + '<enum name="LightType" value="%s"/>\n' % 
                lightType)

        diffuse = '%.6f, %.6f, %.6f %.6f' % (light.R,light.G,light.B,1.0)

        file.write(i2 + '<colorf name="AmbientColor" value="0.000000,' + 
                '0.000000, 0.000000, 1.000000"/>\n')
        file.write(i2 + '<colorf name="DiffuseColor" value="%s"/>\n' % 
                diffuse)
        file.write(i2 + '<colorf name="SpecularColor" value="1.000000,' + 
                '1.000000, 1.000000, 1.000000"/>\n')

        attvalue = 0.0
        if light.energy != 0.000000:
            attvalue = 0.5 / light.energy
        satt = '0.000000 %.6f 0.000000' % attvalue
        file.write(i2 + '<vector3d name="Attenuation" value="%s"/>\n' % 
                (satt))
        
        file.write(i2 + '<float name="Radius" value="%.2f"/>\n' % 
                (light.dist * 2.0))
        file.write(i2 + '<bool name="CastShadows" value="true"/>\n')
        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject)
        
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

        prop = iUtils.getProperty('fov',bObject)
        if prop != None and type(prop) == float:
            fov = prop

        prop = iUtils.getProperty('aspect',bObject)
        if prop != None and type(prop) == float:
            aspect = prop
    
        file.write(i2 + '<vector3d name="Target" value="%s"/>\n' % (starget))
        file.write(i2 + '<vector3d name="UpVector" value="0.000000,' + 
                ' 1.000000, 0.000000"/>\n')
        file.write(i2 + '<float name="Fovy" value="%.6f"/>\n' % fov)
        file.write(i2 + '<float name="Aspect" value="%.6f"/>\n' % aspect)
        file.write(i2 + '<float name="ZNear" value="%.2f"/>\n' % 
                camera.clipStart)
        file.write(i2 + '<float name="ZFar" value="%.2f"/>\n' % 
                camera.clipEnd)

        file.write(i1 + '</attributes>\n')

        writeUserData(file,i1,i2,bObject)

    #-------------------------------------------------------------------------
    #                              _ i w r i t e
    #-------------------------------------------------------------------------
    def _iwrite(self,file,tag,name,value,indent):
        svalue = '?enum?'
        if tag == 'enum':
            svalue = value
        elif tag == 'color':
            svalue = iUtils.del2SColor(value)
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
    def _writeSBImageAttributes(self,file,indent,mat,matType,bImage,bObject,lightingOverride=None):

        i2 = indent + '    '
        imageName = self.exporter.getImageFileName(bObject.getData().name,bImage,0)
        file.write(indent + '<attributes>\n')
        self._iwrite(file,'enum','Type',matType, i2)
        self._iwrite(file,'color','Ambient',mat.attributes['AmbientColor'],i2)
        self._iwrite(file,'color','Diffuse',mat.attributes['DiffuseColor'],i2)
        self._iwrite(file,'color','Emissive',mat.attributes['EmissiveColor'],i2)
        self._iwrite(file,'color','Specular',mat.attributes['SpecularColor'],i2)
        self._iwrite(file,'float','Shininess',mat.attributes['Shininess'],i2)
        self._iwrite(file,'float','Param1',mat.attributes['MaterialTypeParam'],i2)
        self._iwrite(file,'float','Param2',mat.attributes['MaterialTypeParam2'],i2)
        self._iwrite(file,'bool','Wireframe',mat.attributes['WireFrame'],i2)
        self._iwrite(file,'bool','GouraudShading',mat.attributes['GouraudShading'],i2)
        if lightingOverride == None:
            self._iwrite(file,'bool','Lighting',mat.attributes['Lighting'],i2)
        else:
            self._iwrite(file,'bool','Lighting',lightingOverride,i2)
            
        self._iwrite(file,'bool','ZWriteEnable',mat.attributes['ZWriteEnable'],i2)
        self._iwrite(file,'int','ZBuffer',mat.attributes['ZBuffer'],i2)
        self._iwrite(file,'bool','BackfaceCulling',mat.attributes['BackfaceCulling'],i2)
        self._iwrite(file,'bool','FogEnable',mat.attributes['FogEnable'],i2)
        self._iwrite(file,'bool','NormalizeNormals',mat.attributes['NormalizeNormals'],i2)
        self._iwrite(file,'int','ColorMask',mat.attributes['ColorMask'],i2)
        self._iwrite(file,'int','AntiAliasing',mat.attributes['AntiAliasing'],i2)
        
        self._iwrite(file,'texture','Texture1',iUtils.flattenPath(imageName),i2)
        self._iwrite(file,'enum','TextureWrap1','texture_clamp_clamp',i2)
        self._iwrite(file,'bool','BilinearFilter1',mat.attributes['Layer1']['BilinearFilter'],i2)
        self._iwrite(file,'bool','TrilinearFilter1',mat.attributes['Layer1']['TrilinearFilter'],i2)
        if self.exporter.gIrrlichtVersion >= 16:
            self._iwrite(file,'int','AnisotropicFilter1',mat.attributes['Layer1']['AnisotropicFilter'],i2)
        else:
            self._iwrite(file,'bool','AnisotropicFilter1',mat.attributes['Layer1']['AnisotropicFilter'],i2)
        file.write(indent + '</attributes>\n')

    #-----------------------------------------------------------------------------
    #                     w r i t e S k y B o x N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeSkyBoxNodeData(self,file,bObject,sImages,level):

        if bObject.getType() != 'Mesh':
            return

        mesh = bObject.getData(False, True)
        bMaterial = mesh.materials[0]
        material = iMaterials.DefaultMaterial(bObject,'skybox',
                self.exporter,bMaterial) 

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

        self._writeSBImageAttributes(file, i2, material, 'solid',
                frontImage, bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', rightImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', backImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', leftImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', topImage,
                bObject, False)
        self._writeSBImageAttributes(file, i2, material,'solid', botImage,
                bObject, False)

        file.write(i1 + '</materials>\n')
        
    #-----------------------------------------------------------------------------
    #                   w r i t e B i l l b o a r d N o d e D a t a
    #-----------------------------------------------------------------------------
    def writeBillboardNodeData(self,file,bObject,bbImage,level):

        if bObject.getType() != 'Mesh':
            return

        bMaterial = None
        mesh = bObject.getData(False, True)
        if len(mesh.materials) > 0:
            bMaterial = mesh.materials[0]
        
        material = iMaterials.DefaultMaterial(bObject,'billboard',
                self.exporter,bMaterial)
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bObject.getMatrix('localspace')

        ipos = iUtils.b2iPosition(localSpace, bObject)
        iscale = iUtils.b2iVector(localSpace.scalePart())
    
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)
        srot = '%.6f, %.6f, %.6f' % (0.0, 0.0, 0.0)
        sscale = '%.6f, %.6f, %.6f' % (1.0, 1.0, 1.0)

        self.writeSTDAttributes(file,i1,i2,bObject,spos,srot,sscale,'false')

        # billboard quad vertex positions: ul:3, ur:0, lr:1, ll:2
        
        ul = mesh.verts[3].co
        ur = mesh.verts[0].co
        lr = mesh.verts[1].co

        scale = bObject.getSize()
        dx = (ul.x - ur.x) * scale[0]
        dy = (ul.y - ur.y) * scale[1]
        dz = (ul.z - ur.z) * scale[2]
        width = math.fabs(math.sqrt((dx * dx) + (dy * dy) + (dz * dz)))

        dx = (ur.x - lr.x) * scale[0]
        dy = (ur.y - lr.y) * scale[1]
        dz = (ur.z - lr.z) * scale[2]
        height = math.fabs(math.sqrt((dx * dx) + (dy * dy) + (dz * dz)))

        file.write(i2 + '<int name="Width" value="%.6f" />\n' % width)
        file.write(i2 + '<int name="Height" value="%.6f" />\n' % height)
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

        self._writeSBImageAttributes(file, i2, material, irrMatInfo[0], bbImage,
                bObject)

        file.write(i1 + '</materials>\n')
        
