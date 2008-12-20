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
import Blender, iGUI 
import iMaterials, iMeshBuffer, iUtils, time


#-----------------------------------------------------------------------------
#                                 d e b u g
#-----------------------------------------------------------------------------
def debug(msg):
    iUtils.debug(msg)
    
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
        self.bKeyBlocks = None
        self.armatures = []
        self.shapes = []

        # get 'Mesh' - not deprecated 'NMesh'
        self.bMesh =  bNode.getData(False,True)

        # get mesh shape keys
        self.bKey = self.bMesh.key
        if self.bKey:
            self.bKeyBlocks = self.bKey.blocks

        # get mesh armatures
        mods = self.bNode.modifiers
        if mods:
            for mod in mods:
                if self._getModType(mod) == 'Armature':
                    armature = mod[Blender.Modifier.Settings.OBJECT].getData()
                    self.armatures.append(armature)
            
        self.meshBuffers = []

        # dict of {mangled material name, MeshBuffer()}
        self.materials = {}
        self.hasFaceUV = self.bMesh.faceUV
        self.uvLayerNames = self.bMesh.getUVLayerNames()
        self.activeUVLayer = self.bMesh.activeUVLayer
        self.debug = debug

        self.uvMatName = None                # Irrlicht material name
        self.findMatName()

    #-------------------------------------------------------------------------
    #                        f i n d M a t N a m e
    #-------------------------------------------------------------------------
    def findMatName(self):
        if len(self.uvLayerNames) == 0:
            return

        #
        # search for matching Irrlicht material name
        #
        for lname in self.uvLayerNames:
            if iMaterials.getIrrMaterial(lname) != None:
                self.uvMatName = lname
                break

        #
        # if not found look for custom name: '$' prefix
        #
        for lname in self.uvLayerNames:
            if lname[0] == '$':
                self.uvMatName = lname
                break;

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
    #                     _ g e t F a c e I m a g e N a m e s
    #-------------------------------------------------------------------------
    def _getFaceImageNames(self,face):
        names = ''
        for uvlayer in self.uvLayerNames:
            self.bMesh.activeUVLayer = uvlayer
            if face.image == None:
                names += 'none:'
            else:
                names += (face.image.getName() + ':')
        self.bMesh.activeUVLayer = self.activeUVLayer
        if names == '':
            names = 'none:'
        return names

    #-------------------------------------------------------------------------
    #                        _ g e t M o d T y p e
    #-------------------------------------------------------------------------
    def _getModType(self,mod):
        result = 'unknown'

        if mod.type == Blender.Modifier.Types.ARMATURE:
            result = 'Armature'
        elif mod.type == Blender.Modifier.Types.ARRAY:
            result = 'Array'
        elif mod.type == Blender.Modifier.Types.BOOLEAN:
            result = 'Boolean'
        elif mod.type == Blender.Modifier.Types.BUILD:
            result = 'Build'
        elif mod.type == Blender.Modifier.Types.CURVE:
            result = 'Curve'
        elif mod.type == Blender.Modifier.Types.MIRROR:
            result = 'Mirror'
        elif mod.type == Blender.Modifier.Types.DECIMATE:
            result = 'Decimate'
        elif mod.type == Blender.Modifier.Types.LATTICE:
            result = 'Lattice'
        elif mod.type == Blender.Modifier.Types.SUBSURF:
            result = 'Suburf'
        elif mod.type == Blender.Modifier.Types.WAVE:
            result = 'Wave'
        elif mod.type == Blender.Modifier.Types.EDGESPLIT:
            result = 'EdgeSplit'
        elif mod.type == Blender.Modifier.Types.DISPLACE:
            result = 'Displace'
        elif mod.type == Blender.Modifier.Types.SMOOTH:
            result = 'Smooth'
        elif mod.type == Blender.Modifier.Types.CAST:
            result = 'Cast'

        return result

    #-------------------------------------------------------------------------
    #                         c r e a t e B u f f e r s
    #-------------------------------------------------------------------------
    def createBuffers(self):
        if self.debug:
            lnames = ''
            for name in self.uvLayerNames:
                if len(lnames):
                    lnames += ', '
                lnames += name
            debug('UV Layers (%d): %s' % (len(self.uvLayerNames), lnames))
            mname = 'None'
            if self.uvMatName != None:
                mname = self.uvMatName
            debug('Primary UV Layer: '  + mname)
            val = 'False'
            if (self.bMesh.mode & Blender.Mesh.Modes['TWOSIDED']):
                val = 'True'
            debug('Double Sided: ' + val)

            #
            # dump shape keys
            #
            if self.bKey:
                debug('Mesh Key: True')
                debug('Mesh Key Blocks Count: %d' % len(self.bKeyBlocks))
                i = 1
                for block in self.bKeyBlocks:
                    debug('   Block %d, Name: %s, Length: %d' % (i,block.name,
                        len(block.data)))
                    i += 1
                debug('Mesh Key IPO: %s' % str(self.bKey.ipo))
            else:
                debug('Mesh Key: None')

            #
            # dump ipo's
            #
            ipos = self.bNode.ipo
            if ipos:
                debug('Mesh ipo: %s' % str(ipos))
            else:
                debug('Mesh ipo: None')

            #
            # dump modifiers
            #
            mods = self.bNode.modifiers
            if mods:
                debug('Modifiers:')
                for mod in mods:
                    stype = self._getModType(mod)
                    debug('   Name: %s, Type: %s' % (mod.name,stype))
            else:
                debug('Modifiers: None')

            #
            # dump armatures
            #
            if len(self.armatures) > 0:
                debug('Armatures:')
                for arm in self.armatures:
                    debug('   Name: %s, Bone Count: %d' %
                            (arm.name,len(arm.bones)))
            else:
                debug('Armatures: None')

            #
            # dump actions
            #
            '''
            act = self.bNode.action
            print 'bNode.action', act, type(act)
            if act != None:
                print '   Action Name', act.name

            strips = self.bNode.actionStrips
            print 'bNode.actionstrips', strips, type(strips)
            if strips != None:
                print '   ActionStrips size: ', len(strips)
                print '   ActionStrips __len__: ', strips.__len__()
            '''

        #
        # Loop through faces and create a new meshBuffer for each unique 
        # material used.  Also add face/vertex info into the meshBuffer.
        #
        result = True
        faces = self.bMesh.faces
        materials = self.bMesh.materials
        mCount = 0

        #
        # the face attributes will be extracted from the uvMatName uvlayer
        #
        if (self.uvMatName != None) and (self.uvMatName != 
                self.activeUVLayer):
            self.bMesh.activeUVLayer = self.uvMatName


        fcount = 0
        tfaces = len(faces)
        mcount = 100
            
        for face in faces:

            if iGUI.exportCancelled():
                break;

            fcount += 1
            if (fcount % mcount) == 0:
                iGUI.updateStatus('Analyzing Mesh Faces: %s, (%d of %d)' % 
                        (self.bMesh.name, fcount, tfaces))

            try:
                bMaterial = self.bMesh.materials[face.mat]
            except:
                bMaterial = None


            # UV Material (game engine)?
            if self.hasFaceUV and (face.mode & 
                    Blender.Mesh.FaceModes['TEX']):
                #
                # UV/game materials allow options (two-sided, lighting, 
                # alpha etc.) per face. This is why we include these 
                # settings in the material name - differing options will 
                # create seperate mesh buffers..
                #
                stwosided = '0'

                if ((self.bMesh.mode & Blender.Mesh.Modes['TWOSIDED']) or  
                    (face.mode & Blender.Mesh.FaceModes['TWOSIDE'])):
                    stwosided = '1'
                
                slighting = '0'
                if (face.mode & Blender.Mesh.FaceModes['LIGHT']):
                    slighting = '1'

                salpha = '0'
                if (face.transp & Blender.Mesh.FaceTranspModes['ALPHA']):
                    salpha = '1'

                faceImageName = self._getFaceImageNames(face)

                matName = ('uvmat:' + faceImageName + stwosided + 
                        slighting + salpha)

                material = iMaterials.UVMaterial(self, self.bNode,matName,
                        self.exporter,self.properties,face)
            # Blender Material
            elif bMaterial != None:
                matName = 'blender:' + bMaterial.getName()
                material = iMaterials.BlenderMaterial(self.bNode,matName, 
                        self.exporter,self.properties,bMaterial)
            # Unassigned Material
            else:
                matName = 'unassigned'
                material = iMaterials.DefaultMaterial(self.bNode,matName,
                        self.exporter,self.properties)

            if self.materials.has_key(matName):
                meshBuffer = self.materials[matName]
            else:
                meshBuffer = iMeshBuffer.MeshBuffer(self.bMesh, material,
                        self.uvMatName,len(self.meshBuffers))
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)


            meshBuffer.addFace(face,self.bKeyBlocks)
            if len(meshBuffer.faces) > 65535:
                result = False
                s = ('Mesh "%s" exceeds buffer index limit: %d' % 
                        (meshBuffer.bMesh.name,len(meshBuffer.faces)))
                self.exporter.gFatalError = s
                debug('**** Fatal Error: ' + s)
                return False
                
        iGUI.updateStatus('Analyzing Mesh Faces: %s, Done.' % 
                        (self.bMesh.name))
        if self.debug:
            debug('\n[Buffers]')
            debug('Count: %d' % len(self.materials))
            for key,val in self.materials.iteritems():
                debug('   ' + key + ' : ' + val.getMaterialType())

        #
        # restore the active uv layer if necessary
        #
        if self.activeUVLayer != self.bMesh.activeUVLayer:
            self.bMesh.activeUVLayer = self.activeUVLayer

        return result

    #-------------------------------------------------------------------------
    #                               w r i t e 
    #-------------------------------------------------------------------------
    def write(self, file):

        file.write('<?xml version="1.0"?>\n')
        file.write('<mesh xmlns="http://irrlicht.sourceforge.net/' + 
            'IRRMESH_09_2007" version="1.0">\n')
        dateTime = (iUtils.datetime2str(time.localtime()), 
                    iUtils.getversion())
        createString = ('<!-- Created %s by irrb %s - ' + 
                '"Irrlicht/Blender Exporter" -->\n')
        file.write(createString % dateTime)

        for buffer in self.meshBuffers:
            buffer.write(file)

        file.write('</mesh>\n')
        
        
