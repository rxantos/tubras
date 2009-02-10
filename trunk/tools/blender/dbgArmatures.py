import Blender,sys

print '---------------------------------'
#
# extract/return all armatures associated with an object (mesh).
# armatures may be attached as a parent or as a one or more
# modifiers
#
def getArmatures(bObject):
	Armatures = []
	# check modifiers
	mods = bObject.modifiers
	if mods:
		for mod in mods:
			if mod.type == Blender.Modifier.Types.ARMATURE:
				armObj = mod[Blender.Modifier.Settings.OBJECT]
				if armObj and armObj.getType() == 'Armature':
					Armatures.append(armObj)
				
	# check parent
	parent = bObject.parent
	if parent and parent.getType() == 'Armature':
		Armatures.append(parent)
		
	return Armatures

def printBoneData(bone):
	print '   bone name: %s' % bone.name
	bmat = bone.matrix['ARMATURESPACE']
	print '        apos:', bmat.translationPart()
	print '      ascale:', bmat.scalePart()
	print '        brot:', bmat.rotationPart().toEuler()
	print '        blen:', bone.length
	print '        head:', bone.head['ARMATURESPACE']
	print '        tail:', bone.tail['ARMATURESPACE']
	print '      weight:', bone.weight
	
def printArmatureData(object):
	mat = object.matrixWorld
	
	armature = object.getData()	
	print 'Armature:', armature.name
	print '     pos:', mat.translationPart()
	print '     rot:', mat.rotationPart().toEuler()
	print '   scale:', mat.scalePart()
		
	print ' '
	print 'Bone Count:', len(armature.bones)	
	for bone in armature.bones.values():
		printBoneData(bone)
	
#
# process armature info for selected object
#
def processArmatureInfo():
	selected = Blender.Object.GetSelected()
	if len(selected) != 1:
		print 'More than one object selected'	
		return

	object = selected[0]
	if object.type == 'Mesh':

		print 'Mesh Name:', object.name		
		Armatures = getArmatures(object)

		print 'Armature Count:', len(Armatures)
		if len(Armatures) == 0:
			return
	
		for armObject in Armatures:
			printAramatureData(armObject)			
	elif object.type == 'Armature':
		printArmatureData(object)
	else:
		print 'Selected object not a mesh or armature'
	
editMode = Blender.Window.EditMode()
if editMode:
    Blender.Window.EditMode(0)
			
processArmatureInfo()

Blender.Window.EditMode(editMode)

	