#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import bpy
import os
import irrbmodules.iExporter as iExporter

__author__ = ['Keith Murray (pc0de)']
__version__ = '0.6'
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
    'irrb, http://code.google.com/p/tubras/wiki/irrb']
__bpydoc__ = """\
Exports selected objects to Irrlicht.

Read the script manual for further information.
"""

gVersionList = (0, '1.6', '1.7')
gIrrlichtVersion = 2
sVersionList = "1.6 %x1|1.7 %x2"


#-----------------------------------------------------------------------------
#                                   w r i t e
#-----------------------------------------------------------------------------
def write(filename, context, OutDirectory, CreateSceneFile, SelectedOnly,
    ExportLights, ExportCameras, ExportPhysics, ExportBinary, Debug,
    IrrlichtVersion):

    reload(iExporter)

    scene = context.scene

    if not filename.lower().endswith('.irr'):
        filename += '.irr'
	
    #file = open(filename, 'w')
    #file.close()

    print('filename: ' + filename)

    print('len(scene.objects): {0}'.format(len(scene.objects)))

    for object in scene.objects:
        print(object)
        print('object(type-name): {0}-{1}'.format(object.type,object.name))
        print('          visible: {0}'.format(object.is_visible()))
        print('         selected: {0}'.format(object.selected))
        print('\n')


    SceneDirectory = ''
    MeshDirectory = ''
    ImageDirectory = ''

    exporter = iExporter.Exporter(context, CreateSceneFile, OutDirectory,
                SceneDirectory, MeshDirectory, ImageDirectory,
                SelectedOnly,
                ExportLights, ExportCameras, ExportPhysics,
                ExportBinary, Debug, gVersionList[IrrlichtVersion])

    # exporter.doExport()

    print('irrb Export Done')

	

from bpy.props import *
#-----------------------------------------------------------------------------
#                                E x p o r t I r r 
#-----------------------------------------------------------------------------
class ExportIrr(bpy.types.Operator):
    '''Export scene and object info to the native Irrlicht scene (.irr) and mesh (.irrmesh) formats'''
    bl_idname = "export.irr"
    bl_label = "Export IRR"
	
    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    path = StringProperty(name="File Path", description="File path used for exporting the .irr file", maxlen= 1024, default= "")
    exportScene = BoolProperty(name="Export Scene", description="Export Scene", default=True)
    exportSelected = BoolProperty(name="Selected Object(s) Only", description="Export Selected Object(s) Only", default=False)
    exportLights = BoolProperty(name="Export Light(s)", description="Export Lights", default=True)
    exportCameras = BoolProperty(name="Export Camera(s)", description="Export Cameras", default=True)
    exportPhysics = BoolProperty(name="Export Collision/Physics Data", description="Export Collision/Physics Data", default=True)
    exportBinary = BoolProperty(name="Generate Binary Mesh Data", description="Generate Binary Mesh Data (.irrbmesh)", default=True)
    debug = BoolProperty(name="Generate Debug Data", description="Generate Debug Data in irrb.log", default=True)

    # rna complains if these aren't defined... (1/6)
    filename = StringProperty(name="File Name")
    directory = StringProperty(name="File Directory")
    	
    def poll(self, context):
        return {'PASS_THROUGH'}
	
    def execute(self, context):
        if not self.properties.path:
            raise Exception("filename not set")

        try:
            print('filename: ' + self.filename)
            print('directory: ' + self.directory)
        except:
            pass

        print('self.properties.path', self.properties.path)
        OutDirectory = ''

        print('bpy.data.filename', bpy.data.filename)

        OutDirectory = os.path.dirname(self.properties.path)

        print('OutDirectory', OutDirectory)
			
        write(self.properties.path, context,
              OutDirectory,
              self.properties.exportScene,
              self.properties.exportSelected,
              self.properties.exportLights,
              self.properties.exportCameras,
              self.properties.exportPhysics,
              self.properties.exportBinary,
              self.properties.debug,
              1 # irrlicht version index
             )


        return {'FINISHED', }
	
    def invoke(self, context, event):
        wm = context.manager
        wm.add_fileselect(self)
        return {'RUNNING_MODAL', }


bpy.types.register(ExportIrr)

def menu_func(self, context):
    default_path = bpy.data.filename.replace(".blend", ".irr")
    self.layout.operator(ExportIrr.bl_idname, text="Irrlicht (.irr/.irrmesh)...").path = default_path
    
bpy.types.INFO_MT_file_export.append(menu_func)

if __name__ == "__main__":
    bpy.ops.export.irr(path="/tmp/test.irr")
