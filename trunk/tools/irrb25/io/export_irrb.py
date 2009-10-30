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
__version__ = '0.4'
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
    'irrb, http://code.google.com/p/tubras/wiki/irrb']
__bpydoc__ = """\
Exports selected objects to Irrlicht.

Read the script manual for further information.
"""

#-----------------------------------------------------------------------------
#                                   w r i t e
#-----------------------------------------------------------------------------
def write(filename, scene, opt_selected_only=False):
	
	if not filename.lower().endswith('.irr'):
		filename += '.irr'
	
	file = open(filename, 'w')
    close(file)
	

#-----------------------------------------------------------------------------
#                          E X P O R T _ O T _ i r r
#-----------------------------------------------------------------------------
class EXPORT_OT_irr(bpy.types.Operator):
	'''Export scene and object info to the native Irrlicht scene (.irr) and mesh (.irrmesh) formats'''
	__idname__ = "export.irr"
	__label__ = "Export IRR"
	
	# List of operator properties, the attributes will be assigned
	# to the class instance from the operator settings before calling.
	__props__ = [
		bpy.props.StringProperty(attr="path", name="File Path", description="Scene and mesh output directory", maxlen=1024, default=""),
		bpy.props.BoolProperty(attr="opt_selected_only", name="Selected Objects Only", description="Export selected objects only", default=False),
	]
	
	def poll(self, context):
		return True
	
	def execute(self, context):

		if not self.path:
			raise Exception("filename not set")
			
		write(self.path, context.scene, 
              self.opt_selected_only,
              )

		return ('FINISHED', )
	
	def invoke(self, context, event):	
		wm = context.manager
		wm.add_fileselect(self.__operator__)
		return ('RUNNING_MODAL', )


bpy.ops.add(EXPORT_OT_irr)

import dynamic_menu
menu_func = lambda self, context: self.layout.itemO("export.irr", text="Irrlicht (.irr/.irrmesh)...")
menu_item = dynamic_menu.add(bpy.types.INFO_MT_file_export, menu_func)

if __name__ == "__main__":
	bpy.ops.export.irr(path="/tmp/test.irr")

