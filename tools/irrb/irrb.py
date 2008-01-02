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
# Copyright (C) 2008 Keith Murray -- <pc0de@tubras.com>
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

#-----------------------------------------------------------------------------
#                                  m a i n 
#-----------------------------------------------------------------------------
import irrbmodules.iGUI
reload(irrbmodules.iGUI)
irrbmodules.iGUI.Main()


