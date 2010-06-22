import bpy

for object in bpy.data.objects:
    if object.type == 'MESH':
        parent = object.parent
        if parent.type == 'ARMATURE':
            print('object: {0}, armature: {1}'.format(object.name, parent.name))