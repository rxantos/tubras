#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import Blender
import iGUI
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
        self.name = bObject.getName()
        self.exporter = exporter
        self.bKeyBlocks = None
        self.armatures = []
        self.shapes = []

        # get 'Mesh' - not deprecated 'NMesh'
        self.bMesh =  bObject.getData(False,True)

        # get mesh shape keys
        self.bKey = self.bMesh.key
        if self.bKey:
            self.bKeyBlocks = self.bKey.blocks

        # get mesh armatures
        mods = self.bObject.modifiers
        if mods:
            for mod in mods:
                if self._getModType(mod) == 'Armature':
                    try:
                        armature = mod[Blender.Modifier.Settings.OBJECT].getData()
                        self.armatures.append(armature)
                    except:
                        pass
            
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
                return

        #
        # if not found look for custom name: '$' prefix
        #
        for lname in self.uvLayerNames:
            if lname[0] == '$':
                self.uvMatName = lname
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
            debug('Restrict Display: ' + str(self.bObject.restrictDisplay))
            debug('Restrict Render: ' + str(self.bObject.restrictRender))

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

            psystems = self.bObject.getParticleSystems()
            pnames = ''
            for psys in psystems:
                if len(pnames):
                    pnames += ', '
                pnames += psys.getName()
            debug('Particle Systems (%d): %s' % (len(psystems), pnames))


            val = 'False'
            if (self.bMesh.mode & Blender.Mesh.Modes['TWOSIDED']):
                val = 'True'
            debug('Double Sided: ' + val)

            if self.bMesh.vertexColors:
                val = 'True'
            else:
                val = 'False'
            debug('Mesh VertexColors: ' + val)

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
            ipos = self.bObject.ipo
            if ipos:
                debug('Mesh ipo: %s' % str(ipos))
            else:
                debug('Mesh ipo: None')

            #
            # dump modifiers
            #
            mods = self.bObject.modifiers
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
            OB_OCCLUDER		= 0x40000
            OB_SENSOR		= 0x80000
            pflags = []
            rbFlags = self.bObject.rbFlags
            showMass = False
            if not (rbFlags & 0x10000): # shhhh :)
                pflags.append('NO COLLISION')
            else:
                if rbFlags & Blender.Object.RBFlags['ACTOR']:
                    pflags.append('ACTOR')
                if rbFlags & Blender.Object.RBFlags['PROP']:
                    pflags.append('PROP')
                if rbFlags & Blender.Object.RBFlags['DYNAMIC']:
                    showMass = True
                    pflags.append('DYNAMIC')
                if rbFlags & Blender.Object.RBFlags['GHOST']:
                    pflags.append('GHOST')
                if rbFlags & Blender.Object.RBFlags['RIGIDBODY']:
                    showMass = True
                    pflags.append('RIGIDBODY')
                if rbFlags & Blender.Object.RBFlags['COLLISION_RESPONSE']:
                    pflags.append('RESPONSE')
                if rbFlags & Blender.Object.RBFlags['BOUNDS']:
                    pflags.append('BOUNDS')
                if rbFlags & Blender.Object.RBFlags['CHILD']:
                    pflags.append('COMPOUND')
                if rbFlags & OB_OCCLUDER:
                    pflags.append('OCCLUDER')
                if rbFlags & OB_SENSOR:
                    pflags.append('SENSOR')

            debug('rbflags:'  + ('%x' % rbFlags))
            debug('pflags: ' + str(pflags))
            debug('isSoftBody: ' + str(self.bObject.isSB()))

            if rbFlags & Blender.Object.RBFlags['BOUNDS']:
                ShapeType = self.bObject.rbShapeBoundType
                if ShapeType == 0:
                    sShapeType = 'box'
                elif ShapeType == 1:
                    sShapeType = 'sphere'
                elif ShapeType == 2:
                    sShapeType = 'cylinder'
                elif ShapeType == 3:
                    sShapeType = 'cone'
                elif ShapeType == 4:
                    sShapeType = 'trimesh'
                elif ShapeType == 5:
                    sShapeType = 'convexhull'

                debug('bound shape: ' + sShapeType);

            if showMass:
                debug('mass: %.2f' % self.bObject.rbMass)
                debug('radius: %.2f' % self.bObject.rbRadius)

            #
            # dump constraints
            #
            constraints = self.bObject.constraints
            for constraint in constraints:
                if constraint.type == Blender.Constraint.Type['RIGIDBODYJOINT']:
                    rbcType =constraint[Blender.Constraint.Settings['CONSTR_RB_TYPE']]

                    #rbcType isn't matching these constants...
                    #print(Blender.Constraint.Settings['CONSTR_RB_FLAG'])
                    #print(Blender.Constraint.Settings['CONSTR_RB_HINGE'])
                    #print(Blender.Constraint.Settings['CONSTR_RB_BALL'])
                    #print(Blender.Constraint.Settings['CONSTR_RB_GENERIC6DOF'])

                    # from DNA_constraint_types.h
                    CONSTRAINT_RB_BALL          = 1
                    CONSTRAINT_RB_HINGE         = 2
                    CONSTRAINT_RB_CONETWIST     = 4
                    CONSTRAINT_RB_VEHICLE       = 11
                    CONSTRAINT_RB_GENERIC6DOF   = 12
                    
                    srbcType = '6dof'
                    if rbcType == CONSTRAINT_RB_BALL:
                        srbcType = 'Hinge'
                    elif rbcType == CONSTRAINT_RB_HINGE:
                        srbcType = 'Ball'

                    pivot = (constraint[Blender.Constraint.Settings['CONSTR_RB_PIVX']],
                        constraint[Blender.Constraint.Settings['CONSTR_RB_PIVY']],
                        constraint[Blender.Constraint.Settings['CONSTR_RB_PIVZ']])

                    axisrot = (constraint[Blender.Constraint.Settings['CONSTR_RB_AXX']],
                        constraint[Blender.Constraint.Settings['CONSTR_RB_AXY']],
                        constraint[Blender.Constraint.Settings['CONSTR_RB_AXZ']])

                    debug('rb const: %s' % constraint.name)
                    debug('    type: %d %s' % (rbcType, srbcType))
                    debug('   pivot: %s' % str(pivot))
                    debug('     rot: %s' % str(axisrot))

        #
        # Loop through faces and create a new meshBuffer for each unique 
        # material used.  Also add face/vertex info into the meshBuffer.
        #
        result = True
        faces = self.bMesh.faces

        #
        # the face attributes will be extracted from the uvMatName uvlayer
        #
        if (self.uvMatName != None) and (self.uvMatName != 
                self.activeUVLayer):
            self.bMesh.activeUVLayer = self.uvMatName


        fcount = 0
        tfaces = len(faces)
        mcount = 100

        tangents = self.bMesh.getTangents()

        for face in faces:

            if iGUI.exportCancelled():
                break;

            fcount += 1
            if (fcount % mcount) == 0:
                iGUI.updateStatus('Analyzing Mesh Faces: %s, (%d of %d)' % 
                        (self.bMesh.name, fcount, tfaces))

            # Get the Blender "Procedural" Material for this face.  Will be used 
            # for vertex color if a UV texture isn't assigned.  Will also be used 
            # in the material name.
            try:
                bMaterial = self.bMesh.materials[face.mat]
            except:
                bMaterial = None


            matType = 0
            # UV Material (game engine)?
            if self.hasFaceUV and (face.mode & iUtils.B_MESH_FACEMODE_TEX):
                matType = 1
                #
                # UV/game materials allow options (two-sided, lighting, 
                # alpha etc.) per face. This is why we include these 
                # settings in the material name - differing options will 
                # create seperate mesh buffers..
                #
                stwosided = '0'

                # mesh "Double Sided"
                if ((self.bMesh.mode & iUtils.B_MESH_MODE_TWOSIDED) or
                    (face.mode & iUtils.B_MESH_FACEMODE_TWOSIDE)):
                    stwosided = '1'
                
                # face "light"
                slighting = '0'
                if (face.mode & iUtils.B_MESH_FACEMODE_LIGHT):
                    slighting = '1'

                # face "alpha"
                salpha = '0'
                if (face.transp & iUtils.B_MESH_FACETRANSPMODE_ALPHA):
                    salpha = '1'

                # face uvlayer image names 
                faceImageName = self._getFaceImageNames(face)

                # face blender material index
                if bMaterial == None:
                    sBlenderMat = '00'
                else:
                    sBlenderMat = '%02d' % face.mat

                matName = ('uvmat:' + faceImageName + sBlenderMat + stwosided + 
                        slighting + salpha)

            # Blender Material
            elif bMaterial != None:
                matType = 2
                matName = 'blender:' + bMaterial.getName() + (':%02d' % face.mat)
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
                meshBuffer = iMeshBuffer.MeshBuffer(self.bMesh, material,
                        self.uvMatName,len(self.meshBuffers))
                self.materials[matName] = meshBuffer
                self.meshBuffers.append(meshBuffer)


            meshBuffer.addFace(face, tangents[face.index], self.bKeyBlocks)
                
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
        