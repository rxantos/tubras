#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
#
# Copyright (C) 2008 Keith Murray -- <pc0de@tubras.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# this export script is assumed to be used with the latest blender version.
#-----------------------------------------------------------------------------
import Blender,iUtils,time,math

STDATTRIBUTES=('id','automaticculling','visible','debugdatavisible',
        'isdebugobject','readonlymaterials')
CULLINGSTATES=('false','box','frustum_box','frustum_shpere')

#-----------------------------------------------------------------------------
#                           w r i t e U s e r D a t a
#-----------------------------------------------------------------------------
def writeUserData(file,i1,i2,props):

    if len(props) == 0:
        return

    file.write(i1 + '<userData>\n')
    file.write(i2 + '<attributes>\n')
    i3 = i2 + '   '

    for p in props:
        name = p.getName()
        type = p.getType()
        data = p.getData()   
        stype = '????'
        svalue = '?'
        if type == 'BOOL':
            stype = 'bool'
            svalue = 'false'
            if data:
                svalue = 'true'
        elif type == 'INT':
            stype = 'int'
            svalue = str(data)
        elif type == 'FLOAT':
            stype = 'float'
            svalue = iUtils.float2str(data)
        elif type == 'STRING':
            stype = 'string'
            svalue = data
        elif type == 'TIME': # not supported
            continue

        # bypass standard attributes
        if name.lower() in STDATTRIBUTES:
            continue

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
    def writeSTDAttributes(self,file,i1,i2,bNode,spos,srot,sscale):
        
        file.write(i1 + '<attributes>\n')

        cprops = bNode.getAllProperties()

        #
        # std attribute defaults
        #
        pid = -1
        pAutomaticCulling = 'frustum_box'
        pVisible = 'true'
        pDebugDataVisible = 'false'
        pIsDebugObject = 'false'
        pReadOnlyMaterials = 'false'

        #
        # look for overrides
        ##
        prop = iUtils.getProperty('id',cprops)
        if prop != None and prop.getType() == 'INT':
            pid = prop.getData()

        prop = iUtils.getProperty('automaticculling',cprops)
        if prop != None and prop.getType() == 'STRING':
            cullType = prop.getData()
            if cullType in CULLINGSTATES:
                pAutomaticCulling = cullType
        
        prop = iUtils.getProperty('visible',cprops)
        if prop != None and prop.getType() == 'BOOL':
            if not prop.getData():
                pVisible = 'false'

        prop = iUtils.getProperty('debugdatavisible',cprops)
        if prop != None and prop.getType() == 'BOOL':
            if prop.getData():
                pDebugDataVisible = 'true'

        prop = iUtils.getProperty('isdebugobject',cprops)
        if prop != None and prop.getType() == 'BOOL':
            if prop.getData():
                pIsDebugObject = 'true'

        prop = iUtils.getProperty('readonlymaterials',cprops)
        if prop != None and prop.getType() == 'BOOL':
            if prop.getData():
                pReadOnlyMaterials = 'true'

        file.write(i2 + '<string name="Name" value="%s" />\n' % 
                (bNode.getName()))
        file.write(i2 + '<int name="Id" value="%d" />\n' % pid)
        file.write(i2 + '<vector3d name="Position" value="%s" />\n' % 
                (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s" />\n' % 
                (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s" />\n' % 
                (sscale))
        file.write(i2 + '<bool name="Visible" value="%s" />\n' % 
                pVisible)
        file.write(i2 + '<enum name="AutomaticCulling" value="%s" />\n' % 
                pAutomaticCulling)
        file.write(i2 + '<bool name="DebugDataVisible" value="%s" />\n' % 
                pDebugDataVisible)
        file.write(i2 + '<bool name="IsDebugObject" value="%s" />\n' % 
                pIsDebugObject)
        file.write(i2 + '<bool name="ReadOnlyMaterials" value="%s" />\n' % 
                pReadOnlyMaterials)


    #-------------------------------------------------------------------------
    #                      w r i t e M e s h N o d e D a t a
    #-------------------------------------------------------------------------
    def writeMeshNodeData(self,file,meshFileName,bNode,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bNode.getMatrix('localspace')

        lpos = localSpace.translationPart()
        lscale = localSpace.scalePart()
        lrot = localSpace.toEuler()

        ipos = iUtils.b2iVector(lpos)
        irot = iUtils.b2iEuler(lrot)
        iscale = iUtils.b2iVector(lscale)
        
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)

        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)
        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bNode,spos,srot,sscale)

        file.write(i2 + '<string name="Mesh" value="%s" />\n' % 
                (meshFileName))
        file.write(i1 + '</attributes>\n')
    
        writeUserData(file,i1,i2,bNode.getAllProperties())

    #-------------------------------------------------------------------------
    #                      w r i t e E m p t y N o d e D a t a
    #-------------------------------------------------------------------------
    def writeEmptyNodeData(self,file,bNode,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        localSpace = bNode.getMatrix('localspace')

        lpos = localSpace.translationPart()
        lscale = localSpace.scalePart()
        lrot = localSpace.toEuler()

        ipos = iUtils.b2iVector(lpos)
        irot = iUtils.b2iEuler(lrot)
        iscale = iUtils.b2iVector(lscale)
        
        spos = '%.6f, %.6f, %.6f' % (ipos.x, ipos.y, ipos.z)

        srot = '%.6f, %.6f, %.6f' % (irot.x, irot.y, irot.z)
        
        sscale = '%.6f, %.6f, %.6f' % (iscale.x, iscale.y, iscale.z)

        self.writeSTDAttributes(file,i1,i2,bNode,spos,srot,sscale)

        file.write(i1 + '</attributes>\n')
    
        writeUserData(file,i1,i2,bNode.getAllProperties())

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
    def writeLightNodeData(self,file,bNode,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        worldSpace = bNode.getMatrix('worldspace')
        localSpace = bNode.getMatrix('localspace')
        transWld = worldSpace.translationPart()
        transLoc =  localSpace.translationPart()
        transDiff = transLoc - transWld

        pos = transWld + transDiff
        scale = worldSpace.scalePart()
        rot = worldSpace.toEuler()

        spos = '%.6f, %.6f, %.6f' % (pos.x, pos.z, pos.y)

        srot = '%.6f, %.6f, %.6f' % (90.0-rot.x, 90.0-rot.z, 0.0)
        
        sscale = '%.6f, %.6f, %.6f' % (scale.x, scale.z, scale.y)

        self.writeSTDAttributes(file,i1,i2,bNode,spos,srot,sscale)
    

        light = bNode.getData()

        lightType = 'Point'
        if light.type == Blender.Lamp.Types['Lamp']:
            lightType = 'Point'
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

        writeUserData(file,i1,i2,bNode.getAllProperties())        
        
    #-------------------------------------------------------------------------
    #                      w r i t e C a m e r a N o d e D a t a
    #-------------------------------------------------------------------------
    def writeCameraNodeData(self,file,bNode,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        worldSpace = bNode.getMatrix('worldspace')
        transWld = bNode.getMatrix('worldspace').translationPart()
        transLoc =  bNode.getMatrix('localspace').translationPart()
        transDiff = transLoc - transWld

        pos = transWld + transDiff
        rot = worldSpace.toEuler()        

        spos = '%.6f, %.6f, %.6f' % (pos.x, pos.z, pos.y)

        xrot = 90 - rot.x
        srot = '%.6f, %.6f, %.6f' % (xrot, -rot.z, 0.0)
        
        sscale = '%.6f, %.6f, %.6f' % (1.0,1.0,1.0)

        self.writeSTDAttributes(file,i1,i2,bNode,spos,srot,sscale)

        camera = bNode.getData()

        #
        # calculate target based on x,z rotation 
        #
        
        target = Blender.Mathutils.Vector(0.0,0.0,0.0)
        #target.normalize()
        #target = target * 100.0

        rpos = Blender.Mathutils.Vector(pos.x,pos.z,pos.y)
        #target = target + rpos

        starget = '%.6f, %.6f, %.6f' % (target.x, target.z, target.y)

        #
        # override fov & aspect with logic properties if defined
        #
        fov = 2 * math.atan(16.0 / camera.lens )
        aspect = 1.25

        cprops = bNode.getAllProperties()

        prop = iUtils.getProperty('fov',cprops)
        if prop != None and prop.getType() == 'FLOAT':
            fov = prop.getData()

        prop = iUtils.getProperty('aspect',cprops)
        if prop != None and prop.getType() == 'FLOAT':
            aspect = prop.getData()
    

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

        writeUserData(file,i1,i2,bNode.getAllProperties())
        
        
        
