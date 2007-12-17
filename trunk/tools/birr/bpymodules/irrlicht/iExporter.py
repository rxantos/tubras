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

gExportDir = ''
gCreateScene = 0
gSelectedMeshesOnly = 0
gDebug = 0
gScene = None
gRootNodes = []
gChildNodes = []
gMeshFileName = ''

#-----------------------------------------------------------------------------
#                            w r i t e X M L H e a d e r
#-----------------------------------------------------------------------------
def writeXMLHeader(file):
    file.write('<?xml version="1.0"?>\n')

#-----------------------------------------------------------------------------
#                              w r i t e M e s h
#-----------------------------------------------------------------------------
def writeMesh(file,mesh):
    file.write('<mesh xmlns="http://irrlicht.sourceforge.net/IRRMESH_09_2007" version="1.0">\n')
    file.write('<!-- Created by Birr - Blender/Irrlicht Export Script. -->\n')

    writeMeshBuffer(file,mesh)

    file.write('</mesh>\n')
	#<boundingBox minEdge="-5.617457 -0.369465 -5.400124" maxEdge="5.400123 7.758770 5.617457" />
	#<buffer>
    
#-----------------------------------------------------------------------------
#                        w r i t e M e s h B u f f e r
#-----------------------------------------------------------------------------
def writeMeshBuffer(file,mesh):
    file.write('    <buffer>\n')

    writeMeshMaterial(file,mesh)

    writeMeshVertexData(file,mesh)

    writeMeshFaceData(file,mesh)

    file.write('    </buffer>\n')

#-----------------------------------------------------------------------------
#                       w r i t e M e s h M a t e r i a l
#-----------------------------------------------------------------------------
def writeMeshMaterial(file,mesh):
    file.write('        <material>\n');


    file.write('        </material>\n')

#-----------------------------------------------------------------------------
#                     w r i t e M e s h V e r t e x D a t a
#-----------------------------------------------------------------------------
def writeMeshVertexData(file,mesh):
    file.write('        <vertices type="standard" vertexCount="%d">\n' % (len(mesh.verts)))


    file.write('        </vertices>\n')

#-----------------------------------------------------------------------------
#                      w r i t e M e s h F a c e D a t a
#-----------------------------------------------------------------------------
def writeMeshFaceData(file,mesh):
    indexCount = 0

    #
    # we'll convert quads to triangles laters
    #
    for face in mesh.faces:
        vcount = len(face.verts)
        if vcount == 3:
            indexCount += 1
        elif vcount == 4:
            indexCount += 2
        else:
            print 'Warning Mesh contains NGon Face. Face Skipped...'

    file.write('        <indices indexCount="%d">\n' % indexCount)

    file.write('        </indices>\n')

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
    if Blender.Window.EditMode():
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



    # returns "NMesh"
    nMesh = bNode.getData(False,False)
    print 'data type',type(nMesh)

    # returns faster "Mesh"
    mesh = bNode.getData(False,True)
    print 'data type',type(mesh)

    writeXMLHeader(file)
    

    bHasUV = mesh.vertexUV
    print 'HasUV', bHasUV

    uvLayerNames = mesh.getUVLayerNames()
    print 'UVLayers', uvLayerNames

    verts = mesh.verts
    print 'len(verts)', len(verts)

    for vert in verts:
        print vert


    faces = mesh.faces
    print 'len(faces)',len(faces)

    for face in faces:
        print face


    writeMesh(file,mesh)


    file.close()
        



