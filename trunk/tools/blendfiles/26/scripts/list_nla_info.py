#
# Blender actions may be assigned to 1 or more objects. An object only has 
# a single (if any) "active" action assigned to it. The active action is
# referenced through "obj.animation_data.action".
#
# NLA tracks are made up of 1 or more "strips". All NLA tracks associated with
# an object are stored in the "obj.animation_data.nla_tracks" collection.  
#
# Each NLA track is composed of 1 or more NLA Strips.  An NLA Strip contains a
# reference to a single Action along with NLA Strip related properties.
# 

import bpy
print('[actions]')
for action in bpy.data.actions:
	print('action: {0}'.format(action.name))
        

obj = bpy.context.active_object
if obj:
    print('\n[{0} - NLA Tracks]'.format(obj.name))
    if obj.animation_data:
        for track in obj.animation_data.nla_tracks:
            print('[track: {0}]'.format(track.name))
            for strip in track.strips:
                print('  Strip["{0}"]'.format(strip.name))
                print('     Action: {0}'.format(strip.action.name))
    else:
        print('No Animation Data For: {0}'.format(obj.name))
else:
    print('Active Object is None')