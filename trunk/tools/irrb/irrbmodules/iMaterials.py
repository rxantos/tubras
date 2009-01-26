#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import Blender,iUtils,iFilename

# (material name, expected texture count)
irrMaterialTypes=( 
    ('solid', 1),
    ('solid_2layer', 2), 
    ('lightmap', 2),
    ('lightmap_add', 2),
    ('lightmap_m2', 2),
    ('lightmap_m4', 2),
    ('lightmap_light', 2),
    ('lightmap_light_m2', 2),
    ('lightmap_light_m4', 2),
    ('detail_map', 2),
    ('sphere_map', 1),
    ('reflection_2layer', 2),
    ('trans_add', 1),
    ('trans_alphach', 1),
    ('trans_alphach_ref', 1),
    ('trans_vertex_alpha', 1),
    ('trans_reflection_2layer', 2),
    ('normalmap_solid', 2),
    ('normalmap_trans_add', 2),
    ('normalmap_trans_vertexalpha', 2),
    ('parallaxmap_solid', 2),
    ('parallaxmap_trans_add', 2),
    ('parallaxmap_trans_vertexalpha', 2),
    ('onetexture_blend', 1)
    )

#-----------------------------------------------------------------------------
#                         g e t I r r M a t e r i a l
#-----------------------------------------------------------------------------
def getIrrMaterial(name):
    try:
        lname = name.lower()
        for info in irrMaterialTypes:
            if lname == info[0]:
                return info
    except:
        pass

    return None

#-----------------------------------------------------------------------------
#                         D e f a u l t M a t e r i a l
#-----------------------------------------------------------------------------
class DefaultMaterial:

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self,bobject,name,exporter,bmaterial):
        self.bobject = bobject
        self.bmesh = bobject.getData(False,True)
        self.bmaterial = bmaterial
        self.bimages = []
        self.name = name
        self.exporter = exporter

        #
        # Default attributes originally defined in "iConfig.py".  May be 
        # overridden in "UserConfig.py".
        #
        self.attributes = iUtils.defMaterialAttributes.copy()

        if bmaterial != None:
            shadeless = bmaterial.mode & Blender.Material.Modes['SHADELESS']

            if bmaterial.mode & Blender.Material.Modes['SHADELESS']:
                self.attributes['Lighting'] = 0
            else:
                self.attributes['Lighting'] = 1

        self.zWriteEnable = True
        self.zBuffer = 1

        if self.bmesh.mode & Blender.Mesh.Modes['TWOSIDED']:
            self.attributes['BackfaceCulling'] = 0
        else:
            self.attributes['BackfaceCulling'] = 1

        self.updateFromObject(self.bobject, self.bmaterial)

    #-------------------------------------------------------------------------
    #                         u p d a t e F r o m O b j e c t
    #-------------------------------------------------------------------------
    def updateFromObject(self, bobject, bmaterial):
        if (not 'irrb' in bobject.properties or
            not 'materials' in bobject.properties['irrb'] or
            not bmaterial.name in bobject.properties['irrb']['materials']):
            return

        self.attributes = bobject.properties['irrb']['materials'][bmaterial.name]

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
            svalue = iUtils.del2SColor(value)
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
    #                             g e t D i f f u s e
    #-------------------------------------------------------------------------
    def getDiffuse(self):
        return self.attributes['DiffuseColor']

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('      <material bmat="%s">\n' % self.name);
        self._iwrite(file,'enum','Type',self.attributes['Type'])
        self._iwrite(file,'color','Ambient',self.attributes['AmbientColor'])
        self._iwrite(file,'color','Diffuse',self.attributes['DiffuseColor'])
        self._iwrite(file,'color','Emissive',self.attributes['EmissiveColor'])
        self._iwrite(file,'color','Specular',self.attributes['SpecularColor'])
        self._iwrite(file,'float','Shininess',self.attributes['Shininess'])
        self._iwrite(file,'float','Param1',self.attributes['MaterialTypeParam'])
        self._iwrite(file,'float','Param2',self.attributes['MaterialTypeParam2'])
        self._iwrite(file,'bool','Wireframe',self.attributes['WireFrame'])
        self._iwrite(file,'bool','GouraudShading',self.attributes['GouraudShading'])
        self._iwrite(file,'bool','Lighting',self.attributes['Lighting'])
        self._iwrite(file,'bool','ZWriteEnable',self.attributes['ZWriteEnable'])
        self._iwrite(file,'int','ZBuffer',self.attributes['ZBuffer'])
        self._iwrite(file,'bool','BackfaceCulling',self.attributes['BackfaceCulling'])
        self._iwrite(file,'bool','FogEnable',self.attributes['FogEnable'])
        self._iwrite(file,'bool','NormalizeNormals',self.attributes['NormalizeNormals'])
        self._iwrite(file,'texture','Texture1',self.attributes['Layer1']['Texture'])
        self._iwrite(file,'texture','Texture2',self.attributes['Layer2']['Texture'])
        self._iwrite(file,'texture','Texture3',self.attributes['Layer3']['Texture'])
        self._iwrite(file,'texture','Texture4',self.attributes['Layer4']['Texture'])
        self._iwrite(file,'bool','BilinearFilter1',self.attributes['Layer1']['BilinearFilter'])
        self._iwrite(file,'bool','BilinearFilter2',self.attributes['Layer2']['BilinearFilter'])
        self._iwrite(file,'bool','BilinearFilter3',self.attributes['Layer3']['BilinearFilter'])
        self._iwrite(file,'bool','BilinearFilter4',self.attributes['Layer4']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter1',self.attributes['Layer1']['TrilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter2',self.attributes['Layer2']['TrilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter3',self.attributes['Layer3']['TrilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter4',self.attributes['Layer4']['TrilinearFilter'])

        stype = 'bool'
        if self.exporter.gIrrlichtVersion >= 16:
            stype = 'int'

        self._iwrite(file,stype,'AnisotropicFilter1',self.attributes['Layer1']['AnisotropicFilter'])
        self._iwrite(file,stype,'AnisotropicFilter2',self.attributes['Layer2']['AnisotropicFilter'])
        self._iwrite(file,stype,'AnisotropicFilter3',self.attributes['Layer3']['AnisotropicFilter'])
        self._iwrite(file,stype,'AnisotropicFilter4',self.attributes['Layer4']['AnisotropicFilter'])
            
        self._iwrite(file,'enum','TextureWrap1',self.attributes['Layer1']['TextureWrap'])
        self._iwrite(file,'enum','TextureWrap2',self.attributes['Layer2']['TextureWrap'])
        self._iwrite(file,'enum','TextureWrap3',self.attributes['Layer3']['TextureWrap'])
        self._iwrite(file,'enum','TextureWrap4',self.attributes['Layer4']['TextureWrap'])
        file.write('      </material>\n')

    #-------------------------------------------------------------------------
    #                          _ s e t T e x t u r e 
    #-------------------------------------------------------------------------
    def _setTexture(self, bImage, which):
        self.bimages.append(bImage)

        texFile = self.exporter.getImageFileName(self.bmesh.name,bImage,0)
        try:
            texFile = self.exporter.getImageFileName(self.bmesh.name,bImage,0)
        except:
            texFile = '** error accessing %s **' % bImage.name

        if which == 0:
            self.tex1 = texFile
        elif which == 1:
            self.tex2 = texFile
        elif which == 2:
            self.tex3 = texFile
        elif which == 3:
            self.tex4 = texFile

#-----------------------------------------------------------------------------
#                             U V M a t e r i a l
#-----------------------------------------------------------------------------
class UVMaterial(DefaultMaterial):

    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, imesh, bobject, name, exporter, face,bmaterial):
        DefaultMaterial.__init__(self,bobject,name,exporter,bmaterial)
        self.imesh = imesh


        matName = imesh.uvMatName
        activeUVLayer = self.bmesh.activeUVLayer

        if matName != None:
            #
            # custom name?
            #
            if matName[0] == '$':
                self.attributes['Type'] = matName[1:]
            else:
                self.attributes['Type'] = matName

        idx = 0
        uvLayerNames = self.bmesh.getUVLayerNames()
        for name in uvLayerNames:
            self.bmesh.activeUVLayer = name
            if face.image != None:
                self._setTexture(face.image,idx)
            idx += 1

        if matName != None:
            self.bmesh.activeUVLayer = matName
        else:
            self.bmesh.activeUVLayer = activeUVLayer

        if ((self.bmesh.mode & Blender.Mesh.Modes['TWOSIDED']) or  
                (face.mode & Blender.Mesh.FaceModes['TWOSIDE'])):
            self.attributes ['BackfaceCulling'] = 0
            
        if (face.mode & Blender.Mesh.FaceModes['LIGHT']):
            self.attributes['Lighting'] = 1

        if self.mType.lower() == 'trans_alphach':
            self.attributes['MaterialTypeParam'] = 0.000001
            
        self.bmesh.activeUVLayer = activeUVLayer

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'UVMaterial'

    #-------------------------------------------------------------------------
    #                             g e t I m a g e s
    #-------------------------------------------------------------------------
    def getImages(self):
        return self.bimages

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        DefaultMaterial.write(self,file)
        
#-----------------------------------------------------------------------------
#                         B l e n d e r M a t e r i a l
#-----------------------------------------------------------------------------
class BlenderMaterial(DefaultMaterial):
    
    #-------------------------------------------------------------------------
    #                               _ i n i t _
    #-------------------------------------------------------------------------
    def __init__(self, bmesh, name, exporter, bmaterial):
        DefaultMaterial.__init__(self,bmesh,name,exporter,bmaterial)
        self.attributes['DiffuseColor'] = '255, 255, 255, 255'
        if self.bmaterial != None:
            self.attributes['DiffuseColor'] = iUtils.rgb2DelStr(self.bmaterial.rgbCol)
        
    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'BlenderMaterial'

