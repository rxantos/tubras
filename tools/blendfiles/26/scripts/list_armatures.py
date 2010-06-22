import bpy
print('[armatures]')

for armature in bpy.data.armatures:
    print('armatures: {0}'.format(armature.name))