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
import Blender

#-----------------------------------------------------------------------------
#                               M e s h B u f f e r
#-----------------------------------------------------------------------------
class MeshBuffer:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,material):
        self.material = material
        self.vertices = []
        self.faces = []
        
    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getMaterialType(self):
        return self.material.getType()

    #-------------------------------------------------------------------------
    #                               a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self,bFace):
        self.faces.append(bFace)

    #-------------------------------------------------------------------------
    #                                 w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('   <buffer>\n')

        self.material.write(file)
        
        file.write('      <vertices type="standard" vertexCount="%d">\n' % (len(self.vertices)))
        file.write('      </vertices>\n')
        
        file.write('      <indices indexCount="%d">\n' % len(self.faces))
        file.write('      </indices>\n')

        file.write('   </buffer>\n')
        

