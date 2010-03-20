#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import bpy
import Mathutils
# import iGUI // for status updates.
import iMaterials
import iMeshBuffer
import iUtils
import time

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
    def __init__(self, bObject, exporter, debug):
        self.bObject = bObject
        self.name = bObject.name
        self.exporter = exporter
        self.gui = exporter.gGUI
        self.bKeyBlocks = None
        self.armatures = []
        self.shapes = []

        # get 'Mesh' - not deprecated 'NMesh'
        self.bMesh =  bObject.data

        # get mesh shape keys
        self.bKey = self.bMesh.shape_keys
        if self.bKey:
            self.bKeyBlocks = self.bKey.keys

        # get mesh armatures
        mods = self.bObject.modifiers
        if mods:
            for mod in mods:
                if mod.type == 'ARMATURE':
                    try:
                        armature = mod.object
                        self.armatures.append(armature)
                    except:
                        pass
            
        self.meshBuffers = []

        # dict of {mangled material name, MeshBuffer()}
        self.materials = {}
        self.hasFaceUV = len(self.bMesh.uv_textures) > 0
        self.debug = debug

        self.uvMatName = None                # Irrlicht material name
        self.findMatName()

    #-------------------------------------------------------------------------
    #                        f i n d M a t N a m e
    #-------------------------------------------------------------------------
    def findMatName(self):
        if len(self.bMesh.uv_textures) == 0:
            return

        #
        # search for matching Irrlicht material name
        #
        for uv in self.bMesh.uv_textures:
            if iMaterials.getIrrMaterial(uv.name) != None:
                self.uvMatName = uv.name
                return

        #
        # if not found look for custom name: '$' prefix
        #
        for uv in self.bMesh.uv_textures:
            if uv.name[0] == '$':
                self.uvMatName = uv.name
                return

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
        for uvlayer in self.bMesh.uv_textures:
            
            if uvlayer.data[face.index].image == None:
                names += 'none:'
            else:
                names += (uvlayer.data[face.index].image.name + ':')
        if names == '':
            names = 'none:'
        return names

    #-------------------------------------------------------------------------
    #                    c r e a t e M e s h B u f f e r s
    #-------------------------------------------------------------------------
    def createMeshBuffers(self):
        if self.debug:
            if self.bObject.parent == None:
                debug('Parent: None')
            else:
                debug('Parent: {0}'.format(self.bObject.parent.name))

            debug('Rotation Euler: {0}'.format(self.bObject.rotation_euler))
                
            debug('Restrict View: ' + str(self.bObject.restrict_view))
            debug('Restrict Render: ' + str(self.bObject.restrict_render))

            lnames = ''
            for uv in self.bMesh.uv_textures:
                if len(uv.name):
                    lnames += ', '
                lnames += uv.name
            debug('UV Layers (%d): %s' % (len(self.bMesh.uv_textures), lnames))
            mname = 'None'
            if self.uvMatName != None:
                mname = self.uvMatName
            debug('Primary UV Layer: '  + mname)
            val = 'False'
            if self.bMesh.double_sided:
                val = 'True'
            debug('Double Sided: ' + val)

            if len(self.bMesh.vertex_colors) > 0:
                val = 'True'
            else:
                val = 'False'
            debug('Mesh VertexColors: ' + val)

            #
            # dump shape keys
            #
            #if self.bKey:
            #    debug('Mesh Key: True')
            #    debug('Mesh Key Blocks Count: %d' % len(self.bKeyBlocks))
            #    i = 1
            #    for block in self.bKeyBlocks:
            #        debug('   Block %d, Name: %s, Length: %d' % (i,block.name,
            #            len(block.data)))
            #        i += 1
            #    debug('Mesh Key IPO: %s' % str(self.bKey.ipo))
            #else:
            #    debug('Mesh Key: None')

            #
            # dump ipo's
            #
            #ipos = self.bObject.ipo
            #if ipos:
            #    debug('Mesh ipo: %s' % str(ipos))
            #else:
            #    debug('Mesh ipo: None')

            #
            # dump modifiers
            #
            if len(self.bObject.modifiers) > 0:
                debug('Modifiers:')
                for mod in self.bObject.modifiers:
                    debug('   Name: %s, Type: %s' % (mod.name,mod.type))
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
            act = self.bObject.action
            print 'bObject.action', act, type(act)
            if act != None:
                print '   Action Name', act.name

            strips = self.bObject.actionStrips
            print 'bObject.actionstrips', strips, type(strips)
            if strips != None:
                print '   ActionStrips size: ', len(strips)
                print '   ActionStrips __len__: ', strips.__len__()
            '''

            #
            # dump physics
            #
            debug('physics_type: ' + self.bObject.game.physics_type)
            debug('collision_bounds: ' + self.bObject.game.collision_bounds)

            debug('mass: %.2f' % self.bObject.game.mass)
            debug('radius: %.2f' % self.bObject.game.radius)

        #
        # Loop through faces and create a new "MeshBuffer" class for each unique
        # material assigned to a face.  Also add the corresponding face/vertex
        # info into the MeshBuffer.
        #
        result = True
        faces = self.bMesh.faces
        hasUVTexture = len(self.bMesh.uv_textures) > 0

        fcount = 0
        tfaces = len(faces)
        mcount = 100

        #tangents = self.bMesh.getTangents()

        for face in faces:

            if self.gui.isExportCanceled():
                break;

            fcount += 1
            if (fcount % mcount) == 0:
                self.gui.updateStatus('Analyzing Mesh Faces: %s, (%d of %d)' %
                        (self.bMesh.name, fcount, tfaces))

            # Get the Blender "Procedural" Material for this face.  Will be used 
            # for vertex color if a UV texture isn't assigned.  Will also be used 
            # in the material name.
            try:
                bMaterial = self.bMesh.materials[face.material_index]
            except:
                bMaterial = None


            matType = 0
            # UV Material (game engine)?
            if hasUVTexture:
                matType = 1
                #
                # UV/game materials allow options (two-sided, lighting, 
                # alpha etc.) per face. This is why we include these 
                # settings in the material name - differing options will 
                # create seperate mesh buffers..
                #
                stwosided = '0'
                # face "light"
                slighting = '0'
                # face "alpha"
                salpha = '0'
                # face blender material index
                sBlenderMat = '00'

                # mesh "Double Sided"
                if self.bMesh.double_sided:
                    stwosided = '1'
                
                if (bMaterial != None):
                    # face blender material index
                    sBlenderMat = '%02d' % face.material_index

                    # face "light"
                    if bMaterial.shadeless == False:
                        slighting = '1'

                    # face "alpha"
                    if bMaterial.transparency:
                        salpha = '1'

                # face uvlayer image names 
                faceImageName = self._getFaceImageNames(face)


                matName = ('uvmat:' + faceImageName + sBlenderMat + stwosided + 
                        slighting + salpha)

            # Blender Material
            elif bMaterial != None:
                matType = 2
                matName = 'blender:' + bMaterial.name + (':%02d' % face.material_index)
            # Unassigned Material
            else:
                matType = 3
                matName = 'unassigned'

            if matName in self.materials:
                meshBuffer = self.materials[matName]
            else:
                # create the material and mesh buffer
                if matType == 1:    # uv material
                    material = iMaterials.UVMaterial(self, self.bObject,matName,
                            self.exporter,face,bMaterial)
                elif matType == 2:  # blender material
                    material = iMaterials.BlenderMaterial(self.bObject,matName, 
                            self.exporter,bMaterial)
                else:               # unassigned / default material
                    material = iMaterials.DefaultMaterial(self.bObject,matName,
                            self.exporter,bMaterial)                    
                
                # create the meshbuffer and update the material dict & mesh
                # buffer list
                meshBuffer = iMeshBuffer.MeshBuffer(self.exporter, self.bMesh, material,
                        self.uvMatName,len(self.meshBuffers))
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)


            #meshBuffer.addFace(face, tangents[face.index], self.bKeyBlocks)
            #todo - figure if tangents exist or need to be calculated
            tangent = Mathutils.Vector(0.0, 0.0, 0.0)
            tangents = [tangent, tangent, tangent, tangent]
            meshBuffer.addFace(face, tangents, self.bKeyBlocks)
                
        self.gui.updateStatus('Analyzing Mesh Faces: %s, Done.' %
                        (self.bMesh.name))
        if self.debug:
            debug('\n[Buffers]')
            debug('Count: %d' % len(self.materials))
            for key,val in self.materials.items():
                debug('   ' + key + ' : ' + val.getMaterialType())

        #
        # restore the active uv layer if necessary
        #
        #if self.activeUVLayer != self.bMesh.activeUVLayer:
        #    self.bMesh.activeUVLayer = self.activeUVLayer

        return result

    #-------------------------------------------------------------------------
    #                       w r i t e M e s h D a t a
    #-------------------------------------------------------------------------
    def writeMeshData(self, file):

        file.write('<?xml version="1.0"?>\n')
        file.write('<mesh xmlns="http://irrlicht.sourceforge.net/' + 
            'IRRMESH_09_2007" version="1.0">\n')
        dateTime = (iUtils.datetime2str(time.localtime()), 
                    iUtils.getversion())
        createString = ('<!-- Created %s by irrb %s - ' + 
                '"Irrlicht/Blender Exporter" -->\n')
        file.write(createString % dateTime)

        for buffer in self.meshBuffers:
            buffer.writeBufferData(file)

        file.write('</mesh>\n')
        