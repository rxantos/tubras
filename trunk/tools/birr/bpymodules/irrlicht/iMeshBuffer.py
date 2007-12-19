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
#                                  V e r t e x
#-----------------------------------------------------------------------------
class Vertex:
    def __init__(self,bVertex):
        self.bVertext = bVertex


#-----------------------------------------------------------------------------
#                                   F a c e
#-----------------------------------------------------------------------------
class Face:
    def __init__(self,bFace):
        self.bFace = bFace
        
#-----------------------------------------------------------------------------
#                               M e s h B u f f e r
#-----------------------------------------------------------------------------
class MeshBuffer:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bMesh, material):
        self.bMesh = bMesh
        self.material = material
        self.vertices = []
        self.faces = []
        
    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l T y p e
    #-------------------------------------------------------------------------
    def getMaterialType(self):
        return self.material.getType()


    #-------------------------------------------------------------------------
    #                             a d d V e r t e x
    #-------------------------------------------------------------------------
    def addVertex(self, bVertex):

        vertex = Vertex(bVertex)

        self.vertices.append(vertex)

        # return our index
        return len(self.vertices)

    #-------------------------------------------------------------------------
    #                              a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self,bFace):
        face = Face(bFace)        

        self.faces.append(face)

    #-------------------------------------------------------------------------
    #                       _ w r i t e V e r t i c e s
    #-------------------------------------------------------------------------
    def _writeVertices(self, file):
        file.write('      <vertices type="standard" vertexCount="%d">\n' % (len(self.vertices)))
        file.write('      </vertices>\n')        

    #-------------------------------------------------------------------------
    #                         _ w r i t e F a c e s
    #-------------------------------------------------------------------------
    def _writeFaces(self, file):
        file.write('      <indices indexCount="%d">\n' % len(self.faces))
        file.write('      </indices>\n')
    
    #-------------------------------------------------------------------------
    #                               w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('   <buffer>\n')

        self.material.write(file)

        self._writeVertices(file)

        self._writeFaces(file)
        
        file.write('   </buffer>\n')
        

