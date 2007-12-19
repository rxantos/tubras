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
import iMaterials, iMeshBuffer


#-----------------------------------------------------------------------------
#                                M e s h
#-----------------------------------------------------------------------------
class Mesh:
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, name, bMesh, debug):
        self.name = name
        self.mesh = bMesh
        self.meshBuffers = []

        # dict of {mangled material name, MeshBuffer()}
        self.materials = {}
        self.hasFaceUV = self.mesh.faceUV        
        self.debug = debug

    #-------------------------------------------------------------------------
    #                         c r e a t e B u f f e r s
    #-------------------------------------------------------------------------
    def createBuffers(self):

        #
        # Loop through faces and create a new meshBuffer for each unique 
        # material used.  Also add face info into the meshBuffer.
        #
        faces = self.mesh.faces
        materials = self.mesh.materials
        mCount = 0

        for face in faces:

            try:
                bMaterial = self.mesh.materials[face.mat]
            except:
                bMaterial = None

            # UV Material?
            if self.hasFaceUV and (face.mode & Blender.Mesh.FaceModes['TEX']):
                matName = 'image:' + face.image.getName()
                material = iMaterials.ImageMaterial(face.image)
            # Blender Material
            elif bMaterial != None:
                matName = 'blender:' + bMaterial.getName()
                material = iMaterials.BlenderMaterial(bMaterial)
            else:
                matName = 'unassigned'
                material = iMaterials.DefaultMaterial()

            if self.materials.has_key(matName):
                meshBuffer = self.materials[matName]
            else:
                meshBuffer = iMeshBuffer.MeshBuffer(material)
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)

            meshBuffer.addFace(face)
            
        if self.debug:
            print '\n---------------------------'
            print 'Mesh: ', self.name
            print 'MeshBuffer(s) created: %d' % len(self.materials)
            for key,val in self.materials.iteritems():
                print '   ',key,val.getMaterialType()

    #-------------------------------------------------------------------------
    #                               w r i t e 
    #-------------------------------------------------------------------------
    def write(self, file):

        file.write('<?xml version="1.0"?>\n')
        file.write('<mesh xmlns="http://irrlicht.sourceforge.net/IRRMESH_09_2007" version="1.0">\n')
        file.write('<!-- Created by Birr - Blender/Irrlicht Export Script. -->\n')

        for buffer in self.meshBuffers:
            buffer.write(file)

        file.write('</mesh>\n')
	    #<boundingBox minEdge="-5.617457 -0.369465 -5.400124" maxEdge="5.400123 7.758770 5.617457" />
	    #<buffer>

        
