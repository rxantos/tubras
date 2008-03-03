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
import Blender,iUtils,time


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
        file.write('<!-- Created %s by irrb %s - "Irrlicht/Blender Exporter" -->\n' \
                 % (iUtils.datetime2str(time.localtime()), iUtils.getversion()))
        file.write('<irr_scene>\n')
        file.write('   <attributes>\n')
        file.write('      <string name="Name" value="root" />\n')
        file.write('      <int name="Id" value="-1" />\n')
        file.write('      <vector3d name="Position" value="0.000000, 0.000000, 0.000000" />\n')
        file.write('      <vector3d name="Rotation" value="0.000000, 0.000000, 0.000000" />\n')
        file.write('      <vector3d name="Scale" value="1.000000, 1.000000, 1.000000" />\n')
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
    #                      w r i t e M e s h N o d e D a t a
    #-------------------------------------------------------------------------
    def writeMeshNodeData(self,file,meshFileName,bNode,level):
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

        srot = '%.6f, %.6f, %.6f' % (-rot.x, -rot.z, -rot.y)
        
        sscale = '%.6f, %.6f, %.6f' % (scale.x, scale.z, scale.y)

        file.write(i1 + '<attributes>\n')

        file.write(i2 + '<string name="Name" value="%s" />\n' % (bNode.getName()))
        file.write(i2 + '<int name="Id" value="-1" />\n')
        file.write(i2 + '<vector3d name="Position" value="%s" />\n' % (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s" />\n' % (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s" />\n' % (sscale))
        file.write(i2 + '<bool name="Visible" value="true" />\n')
        file.write(i2 + '<bool name="AutomaticCulling" value="true" />\n')
        file.write(i2 + '<bool name="DebugDataVisible" value="false" />\n')
        file.write(i2 + '<bool name="IsDebugObject" value="false" />\n')
        file.write(i2 + '<string name="Mesh" value="%s" />\n' % (meshFileName))
        file.write(i2 + '<bool name="ReadOnlyMaterials" value="false" />\n')

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

        transWld = bNode.getMatrix('worldspace').translationPart()
        transLoc =  bNode.getMatrix('localspace').translationPart()
        transDiff = transLoc - transWld

        pos = transWld + transDiff

        spos = '%.6f, %.6f, %.6f' % (pos.x, pos.z, pos.y)

        srot = '%.6f, %.6f, %.6f' % (0.0,0.0,0.0)
        
        sscale = '%.6f, %.6f, %.6f' % (1.0,1.0,1.0)

        file.write(i1 + '<attributes>\n')

        file.write(i2 + '<string name="Name" value="%s" />\n' % (bNode.getName()))
        file.write(i2 + '<int name="Id" value="-1" />\n')
        file.write(i2 + '<vector3d name="Position" value="%s" />\n' % (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s" />\n' % (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s" />\n' % (sscale))
        file.write(i2 + '<bool name="Visible" value="true" />\n')
        file.write(i2 + '<bool name="AutomaticCulling" value="false" />\n')
        file.write(i2 + '<bool name="DebugDataVisible" value="true" />\n')
        file.write(i2 + '<bool name="IsDebugObject" value="false" />\n')

        light = bNode.getData()
        diffuse = '%.6f, %.6f, %.6f %.6f' % (light.R,light.G,light.B,1.0)

        file.write(i2 + '<colorf name="AmbientColor" value="0.000000,0.000000, 0.000000, 1.000000" />\n')
        file.write(i2 + '<colorf name="DiffuseColor" value="%s" />\n' % diffuse)
        file.write(i2 + '<colorf name="SpecularColor" value="1.000000,1.000000, 1.000000, 1.000000" />\n')
        file.write(i2 + '<float name="Radius" value="50.000000" />\n')
        file.write(i2 + '<bool name="CastShadows" value="true" />\n')
        file.write(i2 + '<enum name="LightType" value="Point" />\n')        
        file.write(i1 + '</attributes>\n')
        
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

        srot = '%.6f, %.6f, %.6f' % (-rot.x, -rot.z, 0.0)
        
        sscale = '%.6f, %.6f, %.6f' % (1.0,1.0,1.0)

        file.write(i1 + '<attributes>\n')

        file.write(i2 + '<string name="Name" value="%s" />\n' % (bNode.getName()))
        file.write(i2 + '<int name="Id" value="-1" />\n')
        file.write(i2 + '<vector3d name="Position" value="%s" />\n' % (spos))
        file.write(i2 + '<vector3d name="Rotation" value="%s" />\n' % (srot))
        file.write(i2 + '<vector3d name="Scale" value="%s" />\n' % (sscale))
        file.write(i2 + '<bool name="Visible" value="true" />\n')
        file.write(i2 + '<bool name="AutomaticCulling" value="false" />\n')
        file.write(i2 + '<bool name="DebugDataVisible" value="true" />\n')
        file.write(i2 + '<bool name="IsDebugObject" value="false" />\n')

        camera = bNode.getData()

        #
        # calculate target based on x,z rotation 
        #
        
        target = Blender.Mathutils.Vector(0.0,rot.z,0.0)
        #target.normalize()
        #target = target * 100.0

        rpos = Blender.Mathutils.Vector(pos.x,pos.z,pos.y)
        #target = target + rpos

        starget = '%.6f, %.6f, %.6f' % (target.x, target.z, target.y)

        file.write(i2 + '<vector3d name="Target" value="%s" />\n' % (starget))
        file.write(i2 + '<vector3d name="UpVector" value="0.000000, 1.000000, 0.000000" />\n')
        file.write(i2 + '<float name="Fovy" value="1.256637" />\n')
        file.write(i2 + '<float name="Aspect" value="1.250000" />\n')
        file.write(i2 + '<float name="ZNear" value="1.000000" />\n')
        file.write(i2 + '<float name="ZFar" value="3000.000000" />\n')

        file.write(i1 + '</attributes>\n')
        
        
