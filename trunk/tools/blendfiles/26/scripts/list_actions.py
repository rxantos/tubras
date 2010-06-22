import bpy
print('[actions]')
for action in bpy.data.actions:
	print('action: {0}'.format(action.name))