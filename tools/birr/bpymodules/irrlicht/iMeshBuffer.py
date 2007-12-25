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
import Blender, iUtils

#-----------------------------------------------------------------------------
#                                  V e r t e x
#-----------------------------------------------------------------------------
class Vertex:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,bVertex, irrIdx):
        self.bVertex = bVertex
        self.irrIdx = irrIdx
        self.UV = [Blender.Mathutils.Vector(0.0,0.0,0.0)]

    #-------------------------------------------------------------------------
    #                               s e t U V
    #-------------------------------------------------------------------------
    def setUV(self,bUV):
        self.UV[0] = bUV
        
    #-------------------------------------------------------------------------
    #                           g e t I r r I n d e x
    #-------------------------------------------------------------------------
    def getIrrIndex(self):
        return self.irrIdx

    #-------------------------------------------------------------------------
    #                           g e t P o s i t i o n
    #-------------------------------------------------------------------------
    def getPosition(self):
        v = self.bVertex.co
        return Blender.Mathutils.Vector(v.x,v.z,v.y)
        
    #-------------------------------------------------------------------------
    #                            g e t N o r m a l
    #-------------------------------------------------------------------------
    def getNormal(self):
        n = self.bVertex.no
        return Blender.Mathutils.Vector(n.x,n.z,n.y)

    #-------------------------------------------------------------------------
    #                            g e t C o l o u r
    #-------------------------------------------------------------------------
    def getColour(self):
        return 0xFFFF0000

    #-------------------------------------------------------------------------
    #                               g e t U V
    #-------------------------------------------------------------------------
    def getUV(self):
        return self.UV[0]
        
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
        self.vertices = []  # list of vertices 
        self.faces = []     # list of irr indexes {{i0,i1,i2},{},...}
        self.vertDict = {}  # blender vert index : internal Vertex()
        self.hasFaceUV = bMesh.faceUV
        
    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l T y p e
    #-------------------------------------------------------------------------
    def getMaterialType(self):
        return self.material.getType()


    #-------------------------------------------------------------------------
    #                            g e t M a t e r i a l
    #-------------------------------------------------------------------------
    def getMaterial(self):
        return self.material
    
    #-------------------------------------------------------------------------
    #                             a d d V e r t e x
    #-------------------------------------------------------------------------
    def addVertex(self, bVertex):

        vertex = Vertex(bVertex)

        self.vertices.append(vertex)

        # return our index
        return len(self.vertices)

    #-------------------------------------------------------------------------
    #                             g e t V e r t e x
    #-------------------------------------------------------------------------
    def getVertex(self,bFace,idx):

        bVertex = bFace.v[idx]

        # if uv's present - every vertex is unique.  should check for 
        # equal uv's...
        if self.hasFaceUV:
            vertex = Vertex(bVertex,len(self.vertices))
            vertex.setUV(bFace.uv[idx])
            self.vertices.append(vertex)
        else:
            if self.vertDict.has_key(bVertex.index):
                vertex = self.vertDict[bVertex.index]
            else:
                vertex = Vertex(bVertex,len(self.vertices))
                self.vertDict[bVertex.index] = vertex
                self.vertices.append(vertex)

        return vertex

    #-------------------------------------------------------------------------
    #                              a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self,bFace):

        if (len(bFace.v) == 3):
            v1 = self.getVertex(bFace,0)
            v2 = self.getVertex(bFace,1)
            v3 = self.getVertex(bFace,2)
            self.faces.append((v1.getIrrIndex(), v2.getIrrIndex(), v3.getIrrIndex()))
        elif (len(bFace.v) == 4):
            v1 = self.getVertex(bFace,0)
            v2 = self.getVertex(bFace,1)
            v3 = self.getVertex(bFace,2)
            v4 = self.getVertex(bFace,3)
            self.faces.append((v1.getIrrIndex(), v2.getIrrIndex(), v3.getIrrIndex()))
            self.faces.append((v1.getIrrIndex(), v3.getIrrIndex(), v4.getIrrIndex()))
        else:
            print 'Ignored face with %d edges.' % len(bFace.v)


    #-------------------------------------------------------------------------
    #                        _ w r i t e V e r t e x
    #-------------------------------------------------------------------------
    def _writeVertex(self, file, vert):
        pos = vert.getPosition()
        normal = vert.getNormal()        
        colour = vert.getColour()
        uv = vert.getUV()

        spos = '%.6f %.6f %.6f ' % (pos.x, pos.y, pos.z)
        snormal = '%.6f %.6f %.6f ' % (normal.x, normal.y, normal.z)
        scolour = iUtils.rgb2str(self.material.getDiffuse()) + ' '
        suv = '%.6f %.6f' % (uv.x, 1-uv.y)
        #suv = '%.6f %.6f' % (uv.x, uv.y)
        file.write('         ' + spos + snormal + scolour + suv + '\n')

    #-------------------------------------------------------------------------
    #                       _ w r i t e V e r t i c e s
    #-------------------------------------------------------------------------
    def _writeVertices(self, file):
        file.write('      <vertices type="standard" vertexCount="%d">\n' % (len(self.vertices)))
        for vert in self.vertices:
            self._writeVertex(file, vert)
        file.write('      </vertices>\n')        

    #-------------------------------------------------------------------------
    #                         _ w r i t e F a c e s
    #-------------------------------------------------------------------------
    def _writeFaces(self, file):
        file.write('      <indices indexCount="%d">\n' % (len(self.faces)*3))
        line = '        '
        iCount = 0
        for face in self.faces:
            line += (' %d %d %d' % (face[2], face[1], face[0]))
            iCount += 1
            if iCount == 12:
                line += '\n'
                file.write(line)
                line = '        '
                iCount = 0

        if iCount > 0:
            line += '\n'
            file.write(line)

        file.write('      </indices>\n')
    
    #-------------------------------------------------------------------------
    #                               w r i t e
    #-------------------------------------------------------------------------
    def write(self, file):
        file.write('   <buffer>\n')

        self.material.write(file)

        self._writeVertices(file)

        self._writeFaces(file)
        
        file.write('   </buffer>\n')
        

