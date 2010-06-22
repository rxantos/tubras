import bpy

print('[action curves]')
for action in bpy.data.actions:
    print('action: {0}'.format(action.name))
    for curve in action.fcurves:
        print('   curve: {0}[{1}]'.format(curve.data_path, curve.array_index))