# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####

bl_addon_info = {
    'name': 'I/O: Irrlicht Scene/Mesh',
    'author': 'Keith Murray (pc0de)',
    'version': '0.6',
    'blender': '2.5.3',
    'location': 'File > Export > Irrlicht ',
    'url': 'http://code.google.com/p/tubras/wiki/irrb',
    'category': 'Export'}



import bpy

def menu_export(self, context):
    from io_irr import export_irrb
    default_path = bpy.data.filename.replace(".blend", ".irr")
    self.layout.operator(export_irrb.ExportIrr.bl_idname, text="Irrlicht (.irr)").path = default_path


def register():
    from io_irr import export_irrb
    bpy.types.register(export_irrb.ExportIrr)
    bpy.types.INFO_MT_file_export.append(menu_export)

def unregister():
    from io_irr import export_irrb
    bpy.types.unregister(export_irrb.ExportIrr)
    bpy.types.INFO_MT_file_export.remove(menu_export)

if __name__ == "__main__":
    register()

