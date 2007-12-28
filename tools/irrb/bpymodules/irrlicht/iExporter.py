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
import Blender,iMesh,iMeshBuffer,bpy,iFilename,iScene

#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               d o E x p o r t
    #-----------------------------------------------------------------------------
    def __init__(self,SceneDir, MeshDir, MeshPath, TexDir, TexPath, TexExtension, CreateScene, \
            SelectedMeshesOnly, CopyTextures, Debug):
        
        if len(MeshDir):
            if MeshDir[len(MeshDir)-1] != Blender.sys.sep:
                MeshDir += Blender.sys.sep
        if len(TexDir):
            if TexDir[len(TexDir)-1] != Blender.sys.sep:
                TexDir += Blender.sys.sep
                
        self.gMeshDir = MeshDir
        self.gMeshPath = MeshPath
        self.gTexDir = TexDir
        self.gTexPath = TexPath
        self.gSceneDir = SceneDir
        self.gTexExtension = TexExtension
        self.gCreateScene = CreateScene
        self.gSelectedMeshesOnly = SelectedMeshesOnly
        self.gCopyTextures = CopyTextures
        self.gDebug = Debug
        self.gScene = None
        self.gRootNodes = []
        self.gMeshFileName = ''
        self.nodeLevel = 0
        self.iScene = None
        self.sfile = None


    #-----------------------------------------------------------------------------
    #                              g e t T e x P a t h
    #-----------------------------------------------------------------------------
    def getTexPath(self):
        return self.gTexPath

    #-----------------------------------------------------------------------------
    #                              g e t T e x E x t
    #-----------------------------------------------------------------------------
    def getTexExt(self):
        return self.gTexExtension

    #-----------------------------------------------------------------------------
    #                              d o E x p o r t
    #-----------------------------------------------------------------------------
    def doExport(self):

    
        print 'iExport.doExport()'

        # exit edit mode if necessary
        editMode = Blender.Window.EditMode()
        if editMode:
            Blender.Window.EditMode(0)


        #
        # extract the correct nodes from the current scene
        #
        self.gScene = Blender.Scene.GetCurrent()
        print 'Current Scene Name: "%s"' % (self.gScene.getName())

        #
        # initialize .irr scene file if requested
        #
        if self.gCreateScene:
            try:
                sfname = self.gSceneDir + Blender.sys.sep + self.gScene.getName() + '.irr'
                self.sfile = open(sfname,'w')
                self.iScene = iScene.Scene(self)
                self.iScene.writeHeader(self.sfile)
            except IOError,(errno, strerror):
                self.sfile = None
                errmsg = "IO Error #%s: %s" % (errno, strerror)
            
                
        gso = self.gScene.objects.selected
        print '*******gso',gso
        for o in gso:
            print 'type(o)',o

        if self.gSelectedMeshesOnly == 1:
            self.gRootNodes = self.gScene.objects.selected 
            print 'Selected Only Root Nodes:', len(self.gRootNodes)
        
        else: 
            for node in self.gScene.objects:
                pNode = node.parent
                if pNode is None:
                    self.gRootNodes.append(node)
            print 'All Root Nodes:', len(self.gRootNodes)
        

        if self.gDebug == 1:
            idx = 0
            for bNode in self.gRootNodes:
                type = bNode.getType()
                print 'Node (%d): Name=%s, Type=%s' % (idx,bNode.getName(),type)
                idx += 1

        self.nodeLevel = 0
        for bNode in self.gRootNodes:
            self._exportNode(bNode)


        if self.sfile != None:
            self.iScene.writeFooter(self.sfile)
            self.sfile.close()
            self.sfile = None


        if editMode:
            Blender.Window.EditMode(1)

    #-----------------------------------------------------------------------------
    #                            _ g e t C h i l d r e n
    #-----------------------------------------------------------------------------
    def _getChildren(self,obj):	
        obs = self.gScene.objects
        return [ ob for ob in obs if ob.parent == obj ]	

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t N o d e
    #-----------------------------------------------------------------------------
    def _exportNode(self,bNode):
        type = bNode.getType()
        if type == 'Mesh':
            if (self.gSelectedMeshesOnly == 0) or bNode.sel:
                self._exportMesh(bNode)

        self.nodeLevel += 1
        cnodes = self._getChildren(bNode)
        for cnode in cnodes:
            self._exportNode(cnode)
        self.nodeLevel -= 1

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h 
    #-----------------------------------------------------------------------------
    def _exportMesh(self,bNode):


        self.gMeshFileName = self.gMeshDir + Blender.sys.sep + bNode.getName() + '.irrmesh'

        #
        # write scene node data to scene (.irr) file
        #
        if self.sfile != None:
            self.iScene.writeMeshNode(self.sfile,bNode,self.nodeLevel)
        

        print 'Creating Mesh:', self.gMeshFileName
        try:
            file = open(self.gMeshFileName,'w')
        except IOError,(errno, strerror):
            errmsg = "IO Error #%s: %s" % (errno, strerror)
    
        print '[Export Mesh - %s]' % (bNode.getName())

        # get Mesh
        mesh = bNode.getData(False,True)

        # sticky UV's?
        bHasStickyUV = mesh.vertexUV

        # face UV's
        bHasFaceUV = mesh.faceUV

        uvLayerNames = mesh.getUVLayerNames()

        faces = mesh.faces

        print 'mesh materials count:', len(mesh.materials)
        for mat in mesh.materials:
            print 'Material Type:', type(mat)
            if mat != None:
                print 'Material:', mat.getName()


        irrMesh = iMesh.Mesh(bNode,self,True)
        irrMesh.createBuffers()
        irrMesh.write(file)

        self.copiedImages = []
        if self.gCopyTextures:
            # write image(s) if any
            for k,v in irrMesh.getMaterials().iteritems():
                if v.getMaterialType() == 'UVMaterial':
                    mat = v.getMaterial()
                    image = mat.getImage()
                    self._copyImage(image)
                    image = mat.getLMImage()
                    if image != None:
                        self._copyImage(image)
                
        file.close()
        file = None

        print 'Export Done'

        

    #-----------------------------------------------------------------------------
    #                           _ c o p y I m a g e
    #-----------------------------------------------------------------------------
    def _copyImage(self,bImage):
        
        filename = bImage.getFilename()
        if filename == 'Untitled':
            filename = bImage.getName()


        if filename in self.copiedImages:
            return

        self.copiedImages.append(filename)

        size = bImage.getSize()

        nimage = bpy.data.images.new('temp',size[0],size[1])
        print 'depth', nimage.depth, bImage.depth


        for y in range(size[1]):
            for x in range(size[0]):
                nimage.setPixelI(x,y,bImage.getPixelI(x,y))

        fn = iFilename.Filename(filename)
        filename = self.gTexDir + fn.getBaseName() + self.gTexExtension

        print 'copyImage filename',filename

        nimage.setFilename(filename)
        nimage.save()

        nimage = None
