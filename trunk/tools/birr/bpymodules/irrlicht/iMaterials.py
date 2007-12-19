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
import Blender

#-----------------------------------------------------------------------------
#                         D e f a u l t M a t e r i a l
#-----------------------------------------------------------------------------
class DefaultMaterial:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self):        
        pass

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'DefaultMaterial'

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('      <material>\n');
        file.write('      </material>\n')


#-----------------------------------------------------------------------------
#                           I m a g e M a t e r i a l
#-----------------------------------------------------------------------------
class ImageMaterial(DefaultMaterial):

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bImage):
        DefaultMaterial.__init__(self)
        self.bImage = bImage

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'ImageMaterial'

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self, file):
        file.write('      <material>\n');
        file.write('      </material>\n')

#-----------------------------------------------------------------------------
#                         B l e n d e r M a t e r i a l
#-----------------------------------------------------------------------------
class BlenderMaterial(DefaultMaterial):
    
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bMaterial):
        DefaultMaterial.__init__(self)
        self.bMaterial = bMaterial
        
    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'BlenderMaterial'

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self, file):
        file.write('      <material>\n');
        file.write('      </material>\n')


