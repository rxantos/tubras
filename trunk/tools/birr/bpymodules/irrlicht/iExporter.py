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
import Blender,iMesh,iMeshBuffer

gExportDir = ''
gCreateScene = 0
gSelectedMeshesOnly = 0
gDebug = 0
gScene = None
gRootNodes = []
gChildNodes = []
gMeshFileName = ''

#-----------------------------------------------------------------------------
#                              d o E x p o r t
#-----------------------------------------------------------------------------
def doExport(ExportDir, CreateScene, SelectedMeshesOnly, Debug):
    global gExportDir, gCreateScene, gSelectedMeshesOnly
    global gRootNodes, gChildNodes

    print 'iExport.doExport()'

    gExportDir = ExportDir
    gCreateScene = CreateScene
    gSelectedMeshesOnly = SelectedMeshesOnly
    gDebug = Debug

    # exit edit mode if necessary
    editMode = Blender.Window.EditMode()
    if editMode:
        Blender.Window.EditMode(0)

    #
    # extract the correct nodes from the current scene
    #
    gScene = Blender.Scene.GetCurrent()
    print 'Current Scene Name: "%s"' % (gScene.getName())

    if gSelectedMeshesOnly == 1:
        gRootNodes = Blender.Object.GetSelected()
        gChildNodes = []
        print 'Selected Only Root Nodes:', len(gRootNodes)
        
    else: 
        for node in gScene.objects:
            pNode = node.parent
            if pNode is None:
                gRootNodes.append(node)
            else:
                try:
                    gChildNodes[pNode.name].append(node)
                except:
                    gChildNodes[pNode.name] = [node]
        print 'All Root Nodes:', len(gRootNodes)
        

    if gDebug == 1:
        idx = 0
        for bNode in gRootNodes:
            type = bNode.getType()
            print 'Node (%d): Name=%s, Type=%s' % (idx,bNode.getName(),type)
            idx += 1

    for bNode in gRootNodes:
        type = bNode.getType()
        if type == 'Mesh':
            exportMesh(bNode)


    if editMode:
        Blender.Window.EditMode(1)



#-----------------------------------------------------------------------------
#                             e x p o r t M e s h 
#-----------------------------------------------------------------------------
def exportMesh(bNode):

    global gMeshFileName

    gMeshFileName = gExportDir + Blender.sys.sep + bNode.getName() + '.irrmesh'

    print 'Creating Mesh:', gMeshFileName
    try:
        file = open(gMeshFileName,'w')
    except IOError,(errno, strerror):
        errmsg = "IO Error #%s: %s" % (errno, strerror)
    
    print '[Export Mesh - %s]' % (bNode.getName())



    # returns a deprecated "NMesh"
    nMesh = bNode.getData(False,False)
    print 'data type',type(nMesh)

    # returns faster "Mesh"
    mesh = bNode.getData(False,True)
    print 'data type',type(mesh)

    # sticky UV's?
    bHasUV = mesh.vertexUV
    print 'vertexUV', bHasUV

    # face UV's
    bHasFaceUV = mesh.faceUV
    print 'faceUV', bHasFaceUV

    uvLayerNames = mesh.getUVLayerNames()
    print 'UVLayers', uvLayerNames

    verts = mesh.verts
    print 'len(verts)', len(verts)

    for vert in verts:
        print 'vert',vert
        if bHasUV:
            print 'vert uvco', vert.uvco


    faces = mesh.faces
    print 'len(faces)',len(faces)

    for face in faces:
        print 'face:', face, 'mat idx:', face.mat
        if bHasFaceUV:
            print 'face uv:', face.uv
            print 'face image:', face.image

    print 'mesh materials count:', len(mesh.materials)
    for mat in mesh.materials:
        print 'Material Type:', type(mat)
        if mat != None:
            print 'Material:', mat.getName()


    irrMesh = iMesh.Mesh(bNode,True)
    irrMesh.createBuffers()
    irrMesh.write(file)

    file.close()
        



