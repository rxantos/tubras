#!BPY
"""
Name: 'Irrlicht (.irrmesh, .irr)...'
Blender: 246
Group: 'Export'
Tooltip: 'Exports meshes to Irrlicht mesh & scene files'
"""

__author__ = ['Keith Murray (pc0de)']
__version__ = '0.4'
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
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
#                                  m a i n 
#-----------------------------------------------------------------------------
import irrbmodules.iGUI
reload(irrbmodules.iGUI)
irrbmodules.iGUI.Main()


