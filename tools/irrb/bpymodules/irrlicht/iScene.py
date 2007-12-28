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
    #                          w r i t e M e s h H e a d
    #-------------------------------------------------------------------------
    def writeMeshNodeHead(self,file,level):
        indent = iUtils.getIndent(level)
        file.write(indent + '<node type="mesh">\n')


    #-------------------------------------------------------------------------
    #                          w r i t e M e s h T a i l
    #-------------------------------------------------------------------------
    def writeMeshNodeTail(self,file,level):
        indent = iUtils.getIndent(level)
        file.write(indent + '</node>\n')

    #-------------------------------------------------------------------------
    #                          w r i t e M e s h N o d e
    #-------------------------------------------------------------------------
    def writeMeshNodeData(self,file,meshFileName,bNode,level):
        i1 = iUtils.getIndent(level,3)
        i2 = iUtils.getIndent(level,6)

        matrix = bNode.getMatrix('worldspace')
        pos = matrix.translationPart()
        spos = '%.6f, %.6f, %.6f' % (pos.x, pos.z, pos.y)

        rot = matrix.toEuler()
        srot = '%.6f, %.6f, %.6f' % (rot.x, rot.z, rot.y)
        
        scale = matrix.scalePart()
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

        
