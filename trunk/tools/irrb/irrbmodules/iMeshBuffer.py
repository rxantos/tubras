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
import Blender, iUtils, iMaterials, iGUI

#-----------------------------------------------------------------------------
#                                  V e r t e x
#-----------------------------------------------------------------------------
class Vertex:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bVertex, irrIdx, bKeyBlocks):
        self.bVertex = bVertex
        self.index = bVertex.index
        self.irrIdx = irrIdx
        self.UV = [Blender.Mathutils.Vector(0.0,0.0,0.0), \
                Blender.Mathutils.Vector(0.0,0.0,0.0)]
        v = self.bVertex.co
        #
        # if shape keys exist, use the position from the "basis" key.
        #
        self.pos = []
        if bKeyBlocks != None:
            self.pos = []
            for i in range(len(bKeyBlocks)):
                v = bKeyBlocks[i].data[bVertex.index]
                self.pos.append(v)
        else:
            self.pos.append(v)
        n = self.bVertex.no
        self.normal = Blender.Mathutils.Vector(n.x,n.y,n.z)

    #-------------------------------------------------------------------------
    #                               s e t U V
    #-------------------------------------------------------------------------
    def setUV(self,bUV,idx):
        self.UV[idx] = bUV
        
    #-------------------------------------------------------------------------
    #                           g e t I r r I n d e x
    #-------------------------------------------------------------------------
    def getIrrIndex(self):
        return self.irrIdx

    #-------------------------------------------------------------------------
    #                           g e t P o s i t i o n
    #-------------------------------------------------------------------------
    def getPosition(self,idx=0):
        return self.pos[idx]
        
    #-------------------------------------------------------------------------
    #                            g e t N o r m a l
    #-------------------------------------------------------------------------
    def getNormal(self):
        return self.normal

    #-------------------------------------------------------------------------
    #                            g e t C o l o u r
    #-------------------------------------------------------------------------
    def getColour(self):
        return 0xFFFF0000

    #-------------------------------------------------------------------------
    #                               g e t U V
    #-------------------------------------------------------------------------
    def getUV(self,idx):
        return self.UV[idx]
        
#-----------------------------------------------------------------------------
#                               M e s h B u f f e r
#-----------------------------------------------------------------------------
class MeshBuffer:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bMesh, material, uvMatName, bufNumber):
        self.bMesh = bMesh

        self.bKey = self.bMesh.key
        self.bKeyBlocks = None
        if self.bKey:
            self.bKeyBlocks = self.bKey.blocks

        self.bufNumber = bufNumber

        self.material = material
        self.uvMatName = uvMatName
        self.vertices = []  # list of vertices 
        self.faces = []     # list of irr indexes {{i0,i1,i2},{},...}
        self.vertDict = {}  # blender vert index : internal Vertex()
        self.hasFaceUV = bMesh.faceUV
        self.uvLayers = bMesh.getUVLayerNames()
        self.activeUVLayer = bMesh.activeUVLayer
        
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
    def getVertex(self,bFace,idx,bKeyBlocks):

        #
        # extract the Blender vertex data
        #
        bVertex = bFace.v[idx]

        # if uv's present - every vertex is unique.  should check for 
        # equal uv's...
        if self.hasFaceUV and (bFace.mode & Blender.Mesh.FaceModes['TEX']):
            uvLayerNames = self.bMesh.getUVLayerNames()
            vertex = Vertex(bVertex,len(self.vertices),bKeyBlocks)
            self.bMesh.activeUVLayer = uvLayerNames[0]
            vertex.setUV(bFace.uv[idx],0)
            if len(uvLayerNames) > 1:
               self.bMesh.activeUVLayer = uvLayerNames[1]
               vertex.setUV(bFace.uv[idx],1)
               self.bMesh.activeUVLayer = self.activeUVLayer

            self.vertices.append(vertex)
        else:
            if self.vertDict.has_key(bVertex.index):
                vertex = self.vertDict[bVertex.index]
            else:
                vertex = Vertex(bVertex,len(self.vertices),bKeyBlocks)
                self.vertDict[bVertex.index] = vertex
                self.vertices.append(vertex)

        #
        # fix up vertex coords with basis shape if it exists
        #
        #adjust vertex coords if keyblock exists
        #if bKeyBlocks:
        #   bVertex = bKeyBlocks[0].data[idx]

        return vertex

    #-------------------------------------------------------------------------
    #                              a d d F a c e
    #-------------------------------------------------------------------------
    def addFace(self, bFace, bKeyBlocks):

        if (len(bFace.v) == 3):
            v1 = self.getVertex(bFace,0,bKeyBlocks)
            v2 = self.getVertex(bFace,1,bKeyBlocks)
            v3 = self.getVertex(bFace,2,bKeyBlocks)
            self.faces.append((v1.getIrrIndex(), v2.getIrrIndex(),
                v3.getIrrIndex()))
        elif (len(bFace.v) == 4):
            v1 = self.getVertex(bFace,0,bKeyBlocks)
            v2 = self.getVertex(bFace,1,bKeyBlocks)
            v3 = self.getVertex(bFace,2,bKeyBlocks)
            v4 = self.getVertex(bFace,3,bKeyBlocks)
            self.faces.append((v1.getIrrIndex(), v2.getIrrIndex(),
                v3.getIrrIndex()))
            self.faces.append((v1.getIrrIndex(), v3.getIrrIndex(),
                v4.getIrrIndex()))
        else:
            print 'Ignored face with %d edges.' % len(bFace.v)

    #-------------------------------------------------------------------------
    #                        _ w r i t e V e r t e x
    #-------------------------------------------------------------------------
    def _writeVertex(self, file, vert, idx=0):
        pos = vert.getPosition(idx)
        normal = vert.getNormal()
        colour = vert.getColour()
        uv = vert.getUV(0)
        uv2 = vert.getUV(1)

        spos = '%.6f %.6f %.6f ' % (pos.x, pos.z, pos.y)
        snormal = '%.6f %.6f %.6f ' % (normal.x, normal.z, normal.y)
        scolour = iUtils.rgb2str(self.material.getDiffuse()) + ' '
        suv = '%.6f %.6f ' % (uv.x, 1-uv.y)
        suv2 = '%.6f %.6f' % (uv2.x, 1-uv2.y)
        file.write('         ' + spos + snormal + scolour + suv + suv2 + '\n')

    #-------------------------------------------------------------------------
    #                       _ w r i t e V e r t i c e s
    #-------------------------------------------------------------------------
    def _writeVertices(self, file):
        file.write('      <vertices type="2tcoords" vertexCount="%d">\n' % 
                (len(self.vertices)))

        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return
            
            self._writeVertex(file, vert)
            vcount += 1
            if (vcount % mcount) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing vertices(%d of %d)' % 
                        (meshName, bnum, vcount, tverts))
        file.write('      </vertices>\n')        

    #-------------------------------------------------------------------------
    #                         _ w r i t e F a c e s
    #-------------------------------------------------------------------------
    def _writeFaces(self, file):
        file.write('      <indices indexCount="%d">\n' % (len(self.faces)*3))
        line = '        '
        iCount = 0

        meshName = self.bMesh.name
        tfaces = len(self.faces)
        fcount = 0
        bnum = self.bufNumber
        for face in self.faces:
            if iGUI.exportCancelled():
                return
            line += (' %d %d %d' % (face[2], face[1], face[0]))
            iCount += 1
            if iCount == 12:
                line += '\n'
                file.write(line)
                line = '        '
                iCount = 0
            fcount += 1
            if (fcount % 100) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing faces(%d of %d)' % 
                        (meshName, bnum, fcount, tfaces))


        if iCount > 0:
            line += '\n'
            file.write(line)

        file.write('      </indices>\n')

    #-------------------------------------------------------------------------
    #                       _ w r i t e S h a p e K e y
    #-------------------------------------------------------------------------
    def _writeShapeKey(self, file, idx):
        block = self.bKeyBlocks[idx]

        #
        # first, count the number of vertices we'll be writing
        #

        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.getPosition(0)
            pos = vert.getPosition(idx)

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                vidx += 1


        file.write('      <shapekey name="%s" vertexCount="%d">\n' % (block.name,vidx))
        line = '        '
        iCount = 0


        meshName = self.bMesh.name
        tverts = len(self.vertices)
        vcount = 0
        mcount = 100
        bnum = self.bufNumber
        if tverts > 10000:
            mcount = 1000
        vidx = 0
        for vert in self.vertices:
            if iGUI.exportCancelled():
                return

            bvert = vert.getPosition(0)
            
            pos = vert.getPosition(idx)

            if (bvert.x != pos.x) or (bvert.y != pos.y) or (bvert.z != pos.z):
                spos = '%d %.6f %.6f %.6f ' % (vidx, pos.x, pos.z, pos.y)
                file.write('         ' + spos + '\n')
            vidx += 1
            vcount += 1
            if (vcount % mcount) == 0:
                iGUI.updateStatus('Exporting Mesh: %s, buf: %d writing vertices(%d of %d)' % 
                        (meshName, bnum, vcount, tverts))

        file.write('      </shapekey>\n')
    
    #-------------------------------------------------------------------------
    #                              w r i t e
    #-------------------------------------------------------------------------
    def write(self, file):
        file.write('   <buffer>\n')

        self.material.write(file)

        self._writeVertices(file)

        self._writeFaces(file)

        if self.bKeyBlocks:
            for i in range(1,len(self.bKeyBlocks)):
                self._writeShapeKey(file,i)
        
        file.write('   </buffer>\n')
        
