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
    def __init__(self,bnode,name,exporter,props,bmaterial):
        self.bnode = bnode
        self.bmesh = bnode.getData(False,True)
        self.bmaterial = bmaterial
        self.bimages = []
        self.name = name
        self.exporter = exporter
        self.properties = props
        self.mType = 'solid'
        self.ambient = 0xFFFFFFFF
        self.diffuse = 0xFFFFFFFF
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

        if bmaterial != None:
            shadeless = bmaterial.mode & Blender.Material.Modes['SHADELESS']
            print 'shadeless', shadeless

            if bmaterial.mode & Blender.Material.Modes['SHADELESS']:
                self.lighting = False
            else:
                self.lighting = True

        self.zWriteEnable = True
        self.zBuffer = 1

        if self.bmesh.mode & Blender.Mesh.Modes['TWOSIDED']:
            self.backFaceCulling = False
        else:
            self.backFaceCulling = True



        self.normalizeNormals = False
        self.fogEnable = False
        self.biFilter1 = False
        self.biFilter2 = False
        self.biFilter3 = False
        self.biFilter4 = False
        self.triFilter1 = False
        self.triFilter2 = False
        self.triFilter3 = False
        self.triFilter4 = False
        if self.exporter.gIrrlichtVersion >= 16:
            self.aniFilter1 = 0
            self.aniFilter2 = 0
            self.aniFilter3 = 0
            self.aniFilter4 = 0
        else:
            self.aniFilter1 = False
            self.aniFilter2 = False
            self.aniFilter3 = False
            self.aniFilter4 = False
        self.texWrap1 = "texture_clamp_repeat"
        self.texWrap2 = "texture_clamp_repeat"
        self.texWrap3 = "texture_clamp_repeat"
        self.texWrap4 = "texture_clamp_repeat"

        for p in self.properties:
            if p.getName() == 'lighting' and \
               p.getType() == 'BOOL':
                self.lighting = p.getData()

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
    #                             g e t D i f f u s e
    #-------------------------------------------------------------------------
    def getDiffuse(self):
        return (1.0,1.0,1.0)        

    #-------------------------------------------------------------------------
    #                                w r i t e
    #-------------------------------------------------------------------------
    def write(self,file):
        file.write('      <material bmat="%s">\n' % self.name);
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

        stype = 'bool'
        if self.exporter.gIrrlichtVersion >= 16:
            stype = 'int'

        self._iwrite(file,stype,'AnisotropicFilter1',self.aniFilter1)
        self._iwrite(file,stype,'AnisotropicFilter2',self.aniFilter2)
        self._iwrite(file,stype,'AnisotropicFilter3',self.aniFilter3)
        self._iwrite(file,stype,'AnisotropicFilter4',self.aniFilter4)
            
        self._iwrite(file,'enum','TextureWrap1',self.texWrap1)
        self._iwrite(file,'enum','TextureWrap2',self.texWrap2)
        self._iwrite(file,'enum','TextureWrap3',self.texWrap3)
        self._iwrite(file,'enum','TextureWrap4',self.texWrap4)            
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
    def __init__(self, imesh, bnode, name, exporter, props, face,bmaterial):
        DefaultMaterial.__init__(self,bnode,name,exporter,props,bmaterial)
        self.imesh = imesh


        matName = imesh.uvMatName
        activeUVLayer = self.bmesh.activeUVLayer

        if matName != None:
            #
            # custom name?
            #
            if matName[0] == '$':
                self.mType = matName[1:]
            else:
                self.mType = matName

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
            self.backFaceCulling = False
            
        if (face.mode & Blender.Mesh.FaceModes['LIGHT']):
            self.lighting = True

        if self.mType.lower() == 'trans_alphach':
            self.param1 = 0.000001
            
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
    def __init__(self, bmesh, name, exporter, props, bmaterial):
        DefaultMaterial.__init__(self,bmesh,name,exporter,props,bmaterial)
        if self.bmaterial != None:
            self.diffuse = iUtils.rgb2SColor(self.bmaterial.rgbCol)
        
    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'BlenderMaterial'

    #-------------------------------------------------------------------------
    #                             g e t D i f f u s e
    #-------------------------------------------------------------------------
    def getDiffuse(self):
        return self.bmaterial.rgbCol

