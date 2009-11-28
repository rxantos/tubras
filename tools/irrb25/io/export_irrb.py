#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der over at the gmail thingy>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import bpy
__author__ = ['Keith Murray (pc0de)']
__version__ = '0.6'
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
    'irrb, http://code.google.com/p/tubras/wiki/irrb']
__bpydoc__ = """\
Exports selected objects to Irrlicht.

Read the script manual for further information.
"""

#-----------------------------------------------------------------------------
#                                   w r i t e
#-----------------------------------------------------------------------------
def write(filename, context, exportScene, exportSelected):

    scene = context.scene

    if not filename.lower().endswith('.irr'):
        filename += '.irr'
	
    file = open(filename, 'w')
    file.close()
	

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
    path = StringProperty(name="File Path", description="File path used for exporting the PLY file", maxlen= 1024, default= "")
    exportScene = BoolProperty(name="Export Scene", description="Export Scene", default=True)
    exportSelected = BoolProperty(name="Selected Object Only", description="Export Selected Object(s) Only", default=False)
    	
    def poll(self, context):
        return True
	
    def execute(self, context):
        if not self.path:
            raise Exception("filename not set")
			
        write(self.properties.path, context,
              self.properties.exportScene,
              self.properties.exportSelected,
             )

        return ('FINISHED', )
	
    def invoke(self, context, event):
        wm = context.manager
        wm.add_fileselect(self)
        return ('RUNNING_MODAL', )


bpy.ops.add(ExportIrr)

import dynamic_menu

def menu_func(self, context):
    default_path = bpy.data.filename.replace(".blend", ".irr")
    self.layout.operator(ExportIrr.bl_idname, text="Irrlicht (.irr/.irrmesh)...").path = default_path

menu_item = dynamic_menu.add(bpy.types.INFO_MT_file_export, menu_func)

if __name__ == "__main__":
    bpy.ops.export.irr(path="/tmp/test.irr")
