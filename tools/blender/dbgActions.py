import Blender,sys

print '---------------------------------'

#
# print key info for selected object
#
selected = Blender.Object.GetSelected()
if len(selected) > 0:
	ob = selected[0]
	print ob
	if ob.type == 'Mesh':
		mesh = ob.getData(False,True)
		key = mesh.key
		if key:
			keyBlocks = key.blocks

			print 'keyBlocks: %s' % str(keyBlocks)

			for block in keyBlocks:
				print 'block:',str(block)
				print '   block.curval:', block.curval
				print '   block.pos:', block.pos
		
#
# print action, ipo, & curve info
#		
actionDict = Blender.Armature.NLA.GetActions()
print '\nactionDict:', str(actionDict)
for actionName in actionDict:
	print 'actionName:',str(actionName)
		
	action = actionDict[actionName]	
	print 'action frames:', str(action.getFrameNumbers())
		
	ipoDict = action.getAllChannelIpos()
	
	for ipoName in ipoDict:
		print '\nipo Name:', ipoName
		ipo = ipoDict[ipoName]
		
		print 'ipo.name:', ipo.name
		print 'ipo.blocktype:', ipo.blocktype
		print 'ipo.channel:', ipo.channel
		try:
			print 'ipo.curveConsts:',str(ipo.curveConsts)
		except RuntimeError, (value):
			print 'RuntimeError:',value
		print 'ipo.curves', str(ipo.curves)
		
		for curve in ipo.curves:
			print 'curve', curve
			print 'curve.name:', curve.name
			print 'curve.driver:', curve.driver
			try:
				print 'curve.driverChannel:', curve.driverChannel
			except RuntimeError, (value):
				print 'RuntimeError:',value
			# print 'curve.bezierPoints:', curve.bezierPoints

	