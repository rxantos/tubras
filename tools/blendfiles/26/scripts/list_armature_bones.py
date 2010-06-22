import bpy
print('[armature bones]')

for armature in bpy.data.armatures:
    print('armatures: {0}, bones: {1}'.format(armature.name, len(armature.bones)))
    for bone in armature.bones:
        print('    bone: {0}'.format(bone.name))