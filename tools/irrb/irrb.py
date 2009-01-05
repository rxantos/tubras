#!BPY
"""
Name: 'Irrlicht (.irrmesh, .irr)...'
Blender: 248
Group: 'Export'
Tooltip: 'Exports meshes to Irrlicht mesh & scene files'
"""

__author__ = ['Keith Murray (pc0de)']
__version__ = ''
__url__ = ['Irrlicht, http://irrlicht.sourceforge.net/',
           'irrb, http://code.google.com/p/tubras/wiki/irrb']
__bpydoc__ = """\
Exports selected objects to Irrlicht

Read the script manual for further information.
"""
#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
#                                  m a i n 
#-----------------------------------------------------------------------------
import irrbmodules.iGUI
reload(irrbmodules.iGUI)
irrbmodules.iGUI.Main()


