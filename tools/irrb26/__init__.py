import os.path
#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
bl_addon_info = {
    'name': 'I/O: Irrlicht Scene/Mesh Exporter',
    'author': 'Keith Murray (pc0de)',
    'version': '0.6',
    'blender': '2.5.3',
    'location': 'File > Export > Irrlicht ',
    'url': 'http://code.google.com/p/tubras/wiki/irrb',
    'category': 'Export'}

import bpy

# this is invoked everytime the "Export | Irrlicht" menu item is selected.
def menu_export(self, context):
    import export_irrb
    default_path = ""
    self.layout.operator(export_irrb.irrbExporter.bl_idname, text="Irrlicht (.irr/.irrmesh)").path = default_path

def register():
    import export_irrb
    bpy.types.register(export_irrb.irrbExporter)
    bpy.types.INFO_MT_file_export.append(menu_export)

def unregister():
    import export_irrb
    bpy.types.unregister(export_irrb.irrbExporter)
    bpy.types.INFO_MT_file_export.remove(menu_export)
