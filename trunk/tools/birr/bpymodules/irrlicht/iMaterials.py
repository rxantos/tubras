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
import Blender,iUtils

#-----------------------------------------------------------------------------
#                         D e f a u l t M a t e r i a l
#-----------------------------------------------------------------------------
class DefaultMaterial:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self):
        self.mType = 'onetexture_blend'
        self.ambient = 0xFFFFFFFF
        self.diffuse = 0
        self.emissive = 0
        self.specular = 0
        self.shininess = 0
        self.param1 = 0.0
        self.param2 = 0.0
        self.tex1 = ''
        self.tex2 = ''
        self.tex3 = ''
        self.tex4 = ''
        self.wireframe = False
        self.gouraudShading = True
        self.lighting = False
        self.zWriteEnable = True
        self.zBuffer = 1
        self.backFaceCulling = True
        self.normalizeNormals = False
        self.fogEnable = False
        self.biFilter1 = True
        self.biFilter2 = True
        self.biFilter3 = True
        self.biFilter4 = True
        self.triFilter1 = False
        self.triFilter2 = False
        self.triFilter3 = False
        self.triFilter4 = False
        self.aniFilter1 = False
        self.aniFilter2 = False
        self.aniFilter3 = False
        self.aniFilter4 = False
        self.texWrap1 = "texture_clamp_repeat"
        self.texWrap2 = "texture_clamp_repeat"
        self.texWrap3 = "texture_clamp_repeat"
        self.texWrap4 = "texture_clamp_repeat"

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'DefaultMaterial'

    #-------------------------------------------------------------------------
    #                              _ i w r i t e
    #-------------------------------------------------------------------------
    def _iwrite(self,file,tag,name,value):
        svalue = '?enum?'
        if tag == 'enum':
            svalue = value
        elif tag == 'color':
            svalue = iUtils.colour2str(value)
        elif tag == 'float':
            svalue = iUtils.float2str(value)
        elif tag == 'texture':
            svalue = value
        elif tag == 'int':
            svalue = iUtils.int2str(value)
        elif tag == 'bool':
            svalue = iUtils.bool2str(value)

        out = '         <%s name="%s" value="%s"/>\n' % (tag,name,svalue)
        file.write(out)                

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('      <material>\n');
        self._iwrite(file,'enum','Type',self.mType)
        self._iwrite(file,'color','Ambient',self.ambient)
        self._iwrite(file,'color','Diffuse',self.diffuse)
        self._iwrite(file,'color','Emissive',self.emissive)
        self._iwrite(file,'float','Shininess',self.shininess)
        self._iwrite(file,'float','Param1',self.param1)
        self._iwrite(file,'float','Param2',self.param2)
        self._iwrite(file,'texture','Texture1',self.tex1)
        self._iwrite(file,'texture','Texture2',self.tex2)
        self._iwrite(file,'texture','Texture3',self.tex3)
        self._iwrite(file,'texture','Texture4',self.tex4)
        self._iwrite(file,'bool','Wireframe',self.wireframe)
        self._iwrite(file,'bool','GouraudShading',self.gouraudShading)
        self._iwrite(file,'bool','Lighting',self.lighting)
        self._iwrite(file,'bool','ZWriteEnable',self.zWriteEnable)
        self._iwrite(file,'int','ZBuffer',self.zBuffer)
        self._iwrite(file,'bool','BackfaceCulling',self.backFaceCulling)
        self._iwrite(file,'bool','FogEnable',self.fogEnable)
        self._iwrite(file,'bool','NormalizeNormals',self.normalizeNormals)
        self._iwrite(file,'bool','BilinearFilter1',self.biFilter1)
        self._iwrite(file,'bool','BilinearFilter2',self.biFilter2)
        self._iwrite(file,'bool','BilinearFilter3',self.biFilter3)
        self._iwrite(file,'bool','BilinearFilter4',self.biFilter4)
        self._iwrite(file,'bool','TrilinearFilter1',self.triFilter1)
        self._iwrite(file,'bool','TrilinearFilter2',self.triFilter2)
        self._iwrite(file,'bool','TrilinearFilter3',self.triFilter3)
        self._iwrite(file,'bool','TrilinearFilter4',self.triFilter4)
        self._iwrite(file,'bool','AnisotropicFilter1',self.aniFilter1)
        self._iwrite(file,'bool','AnisotropicFilter2',self.aniFilter2)
        self._iwrite(file,'bool','AnisotropicFilter3',self.aniFilter3)
        self._iwrite(file,'bool','AnisotropicFilter4',self.aniFilter4)
        self._iwrite(file,'enum','TextureWrap1',self.texWrap1)
        self._iwrite(file,'enum','TextureWrap2',self.texWrap2)
        self._iwrite(file,'enum','TextureWrap3',self.texWrap3)
        self._iwrite(file,'enum','TextureWrap4',self.texWrap4)            
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



