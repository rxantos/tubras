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
import iMaterials, iMeshBuffer, iUtils, time


#-----------------------------------------------------------------------------
#                                M e s h
#-----------------------------------------------------------------------------
class Mesh:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bNode, exporter, debug):
        self.bNode = bNode
        self.name = bNode.getName()
        self.exporter = exporter
        self.properties = bNode.getAllProperties()

        # get 'Mesh' - not deprecated 'NMesh'
        self.bMesh =  bNode.getData(False,True)
        self.meshBuffers = []

        # dict of {mangled material name, MeshBuffer()}
        self.materials = {}
        self.hasFaceUV = self.bMesh.faceUV
        self.uvLayerNames = self.bMesh.getUVLayerNames()
        self.debug = debug


    #-------------------------------------------------------------------------
    #                         g e t M a t e r i a l s
    #-------------------------------------------------------------------------
    def getMaterials(self):
        return self.materials

    #-------------------------------------------------------------------------
    #                       g e t V e r t e x C o u n t
    #-------------------------------------------------------------------------
    def getVertexCount(self):
        count = 0

        for buf in self.meshBuffers:
            count += len(buf.vertices)

        return count

    #-------------------------------------------------------------------------
    #                          g e t F a c e C o u n t
    #-------------------------------------------------------------------------
    def getFaceCount(self):
        count = 0
        for buf in self.meshBuffers:
            count += len(buf.faces)

        return count

    #-------------------------------------------------------------------------
    #                         c r e a t e B u f f e r s
    #-------------------------------------------------------------------------
    def createBuffers(self):

        #
        # Loop through faces and create a new meshBuffer for each unique 
        # material used.  Also add face/vertex info into the meshBuffer.
        #
        result = True
        faces = self.bMesh.faces
        materials = self.bMesh.materials
        mCount = 0

        for face in faces:

            try:
                bMaterial = self.bMesh.materials[face.mat]
            except:
                bMaterial = None


            # UV Material (game engine)?
            if self.hasFaceUV and (face.mode & Blender.Mesh.FaceModes['TEX']):
                #
                # UV/game materials allow options (two-sided, lighting, alpha
                # etc.) per face. This is why we include these settings in the
                # material name - differing options will create seperate mesh
                # buffers..
                #
                stwosided = '0'
                if (face.mode & Blender.Mesh.FaceModes['TWOSIDE']):
                    stwosided = '1'
                
                slighting = '0'
                if (face.mode & Blender.Mesh.FaceModes['LIGHT']):
                    slighting = '1'

                salpha = '0'
                if (face.transp & Blender.Mesh.FaceTranspModes['ALPHA']):
                    salpha = '1'

                matName = 'uvmat:' + face.image.getName() + ':' + stwosided + slighting + salpha

                material = iMaterials.UVMaterial(self.bNode,matName,self.exporter,self.properties,face)
            # Blender Material
            elif bMaterial != None:
                matName = 'blender:' + bMaterial.getName()
                material = iMaterials.BlenderMaterial(self.bNode,matName,self.exporter,self.properties,bMaterial)
            # Unassigned Material
            else:
                matName = 'unassigned'
                material = iMaterials.DefaultMaterial(self.bNode,matName,self.exporter,self.properties)

            if self.materials.has_key(matName):
                meshBuffer = self.materials[matName]
            else:
                meshBuffer = iMeshBuffer.MeshBuffer(self.bMesh, material)
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)

            meshBuffer.addFace(face)

        for buf in self.meshBuffers:
            if len(buf.faces) > 65535:
                result = False
                s = 'Mesh "%s" exceeds index limit: %d' % (buf.bMesh.name,len(buf.faces))
                self.exporter.gFatalError = s
                if self.debug:
                    print '\n** Error **'
                    print s
            
        if self.debug:
            print '\n---------------------------'
            print 'Mesh: ', self.name
            print 'MeshBuffer(s) created: %d' % len(self.materials)
            for key,val in self.materials.iteritems():
                print '   ',key,val.getMaterialType()

        return result

    #-------------------------------------------------------------------------
    #                               w r i t e 
    #-------------------------------------------------------------------------
    def write(self, file):

        file.write('<?xml version="1.0"?>\n')
        file.write('<mesh xmlns="http://irrlicht.sourceforge.net/IRRMESH_09_2007" version="1.0">\n')

        file.write('<!-- Created %s by irrb %s - "Irrlicht/Blender Exporter" -->\n' \
                 % (iUtils.datetime2str(time.localtime()), iUtils.getversion()))

        for buffer in self.meshBuffers:
            buffer.write(file)

        file.write('</mesh>\n')
        
        #<boundingBox minEdge="-5.617457 -0.369465 -5.400124" maxEdge="5.400123 7.758770 5.617457" />
	    #<buffer>

        
