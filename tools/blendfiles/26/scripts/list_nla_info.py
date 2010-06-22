#
# Blender actions may be assigned to 1 or more objects. An object only has 
# a single (if any) "active" action assigned to it. The active action is
# referenced through "obj.animation_data.action".
#
# NLA tracks are made up of 1 or more actions. All NLA tracks associated with
# an object are stored in the "obj.animation_data.nla_tracks" collection.  
#
# Each NLA track is composed of 1 or more NLA Strips.  An NLA Strip contains a
# reference to a single Action along with NLA Strip related properties.
# 

import bpy
print('[actions]')
for action in bpy.data.actions:
	print('action: {0}'.format(action.name))
        

print('[nla tracks]')
cube = bpy.data.objects['Cube']
for track in cube.animation_data.nla_tracks:
    print('[track: {0}]'.format(track.name))