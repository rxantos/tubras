#!BPY

"""
Name: 'Irrlicht (.irrmesh, .irr)...'
Blender: 245
Group: 'Export'
Tooltip: 'Exports meshes to Irrlicht mesh & scene files'
"""

__author__ = ['Keith Murray (pc0de)']
__version__ = ''
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
           'Tubras, http://www.tubras.com']
__bpydoc__ = """\
Exports selected objects to Irrlicht

Read the script manual for further information.
"""
#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
#
# Ogre exporter written by Keith Murray based on the Ogre exporter written by 
# Michael Reimpell.
#
# Copyright (C) 2008 Keith Murray -- <pc0der@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# this export script is assumed to be used with the latest blender version.
#-----------------------------------------------------------------------------
import Blender
from Blender import sys as bsys
from Blender import Mathutils

#-----------------------------------------------------------------------------
#                            G l o b a l  V a r i a b l e s
#-----------------------------------------------------------------------------
GRegKey = 'irrexport'

# config options:
GExportDir = ''
GObjects = None
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True



#-----------------------------------------------------------------------------
#                          I r r l i c h t E x p o r t
#-----------------------------------------------------------------------------
class IrrlichtExport:
    def __init__(self,Objects,filename):
        self.Objects = Objects
        self.filename = filename
        print 'irr Filename:', filename
        
        
    #-------------------------------------------------------------------------
    #                            E x p o r t
    #-------------------------------------------------------------------------
    def Export(self):
        print 'IrrlichtExport.Export()'
        
#-----------------------------------------------------------------------------
#                         u p d a t e R e g i s t r y
#-----------------------------------------------------------------------------
def updateRegistry():
	d = {}
	d['GExportDir'] = GExportDir
	d['GConfirmOverWrite'] = GConfirmOverWrite
	d['GVerbose'] = GVerbose
	Blender.Registry.SetKey(GRegKey, d, True)

#-----------------------------------------------------------------------------
#                             f s C a l l b a c k 
#-----------------------------------------------------------------------------
def fsCallback(filename):
	global GErrorMsg, GExportDir, GObjects, GConfirmOverWrite, GVerbose

	if not filename.endswith('.irr'): filename = '%s.irr' % filename

	if bsys.exists(filename) and CONFIRM_OVERWRITE:
		if Blender.Draw.PupMenu('OVERWRITE?%t|File exists') != 1:
			return

	Blender.Window.WaitCursor(1)
	starttime = bsys.time()

	export_dir = bsys.dirname(filename)
	if export_dir != GExportDir:
		GExportDir = export_dir
		updateRegistry()

	iexport = IrrlichtExport(GObjects, filename)
	iexport.Export()
	
	if GErrorMsg:
		Blender.Draw.PupMenu(GErrorMsg)
		GErrorMsg = ''
	else:
		endtime = bsys.time() - starttime
		print "Data exported in %.3f seconds." % endtime

	# if VERBOSE: report_data()
	Blender.Window.WaitCursor(0)
	return

#-----------------------------------------------------------------------------
#                                  m a i n 
#-----------------------------------------------------------------------------


# Looking for a saved key in Blender's Registry
RegDict = Blender.Registry.GetKey(GRegKey, True)

if RegDict:
	try:
		GExportDir = RegDict['GExportDir']
		GConfirmOverWrite = RegDict['GConfirmOverWrite']
		GVerbose = RegDict['GVerbose']
	except KeyError: updateRegistry()


GObjects = Blender.Object.GetSelected()
if len(GObjects) == 0:
	GObjects = Blender.Scene.GetCurrent().getChildren()
print "GObjects = ", GObjects

if not GObjects:
	Blender.Draw.PupMenu('ERROR: No objects to export.')
else:
	fname = bsys.makename(ext=".irr")
	if GExportDir:
		fname = bsys.join(GExportDir, bsys.basename(fname))
	Blender.Window.FileSelector(fsCallback, "Export Irrlicht", fname)

