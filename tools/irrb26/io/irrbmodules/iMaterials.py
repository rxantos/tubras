#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import bpy
import irrbmodules.iUtils as iUtils
import copy

EVT_STANDARD = 0
EVT_2TCOORDS = 1
EVT_TANGENTS = 2

# (material name, expected texture count)
irrMaterialTypes=( 
    ('solid', 1, EVT_STANDARD),
    ('solid_2layer', 2, EVT_2TCOORDS), 
    ('lightmap', 2, EVT_2TCOORDS),
    ('lightmap_add', 2, EVT_2TCOORDS),
    ('lightmap_m2', 2, EVT_2TCOORDS),
    ('lightmap_m4', 2, EVT_2TCOORDS),
    ('lightmap_light', 2, EVT_2TCOORDS),
    ('lightmap_light_m2', 2, EVT_2TCOORDS),
    ('lightmap_light_m4', 2, EVT_2TCOORDS),
    ('detail_map', 2, EVT_2TCOORDS),
    ('sphere_map', 1, EVT_STANDARD),
    ('reflection_2layer', 2, EVT_2TCOORDS),
    ('trans_add', 1, EVT_STANDARD),
    ('trans_alphach', 1, EVT_STANDARD),
    ('trans_alphach_ref', EVT_STANDARD),
    ('trans_vertex_alpha', 1, EVT_STANDARD),
    ('trans_reflection_2layer', 2, EVT_2TCOORDS),
    ('normalmap_solid', 2, EVT_TANGENTS),
    ('normalmap_trans_add', 2, EVT_TANGENTS),
    ('normalmap_trans_vertexalpha', 2, EVT_TANGENTS),
    ('parallaxmap_solid', 2, EVT_TANGENTS),
    ('parallaxmap_trans_add', 2, EVT_TANGENTS),
    ('parallaxmap_trans_vertexalpha', 2, EVT_TANGENTS),
    ('onetexture_blend', 1, EVT_STANDARD)
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
        self.bmesh = bobject.data
        self.bmaterial = bmaterial
        self.bimages = []
        self.name = name
        self.exporter = exporter
        self.useVertexColor = True
        self.vtCustom = None

        #
        # Default attributes originally defined in "iConfig.py".  May be 
        # overridden in "UserConfig.py".
        #
        self.attributes = copy.deepcopy(iUtils.defMaterialAttributes)

        self.attributes['FogEnable'] = 0
        if exporter.gContext.scene.world.mist.enabled:
            self.attributes['FogEnable'] = 1

        self._updateFromMaterial(self.bmaterial)

    #-------------------------------------------------------------------------
    #                 _ u p d a t e F r o m M a t e r i a l
    #-------------------------------------------------------------------------
    # Inheritence order -> "Object" -> "Mesh DataBlock" -> "Defaults" 
    # Upon entry it is expected that "self.attributes" has already been 
    # set to "Defaults".
    def _updateFromMaterial(self, bmaterial):
        if bmaterial == None:
            return

        # update from material ID properties if it exists.
        if 'irrb' in bmaterial.properties:
            props = bmaterial.properties['irrb']
            self._updateFromIDProperties(props)
        else: # examine assigned blender material
            if bmaterial.mode & Blender.Material.Modes['SHADELESS']:
                self.attributes['Lighting'] = 0
            else:
                self.attributes['Lighting'] = 1

            # this will have been turned on if enabled globally, so turn off
            # if explicitly set.
            if bmaterial.mode & Blender.Material.Modes['NOMIST']:
                self.attributes['FogEnable'] = 0

    #-------------------------------------------------------------------------
    #             _ u p d a t e F r o m I D P r o p e r t i e s
    #-------------------------------------------------------------------------
    def _updateFromIDProperties(self, props):
        for k,v in props.iteritems():
            self.attributes[k] = v        

    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'DefaultMaterial'

    #-------------------------------------------------------------------------
    #                         g e t V e r t e x T y p e
    #-------------------------------------------------------------------------
    def getVertexType(self):
        if self.vtCustom != None:
            return self.vtCustom

        info = getIrrMaterial(self.attributes['Type'])
        if info != None:
            return info[2]
        else:
            return EVT_STANDARD
                
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
        self._iwrite(file,'bool','FrontfaceCulling',self.attributes['FrontfaceCulling'])        
        self._iwrite(file,'bool','FogEnable',self.attributes['FogEnable'])
        self._iwrite(file,'bool','NormalizeNormals',self.attributes['NormalizeNormals'])
        self._iwrite(file,'int','AntiAliasing',self.attributes['AntiAliasing'])
        self._iwrite(file,'int','ColorMask',self.attributes['ColorMask'])

        stype = 'bool'
        if self.exporter.gIrrlichtVersion != '1.6':
            stype = 'int'

        tex = iUtils.flattenPath(self.attributes['Layer1']['Texture'])
        self._iwrite(file,'texture','Texture1',tex)
        self._iwrite(file,'enum','TextureWrap1',self.attributes['Layer1']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter1',self.attributes['Layer1']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter1',self.attributes['Layer1']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter1',self.attributes['Layer1']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias1',self.attributes['Layer1']['LODBias'])

        tex = iUtils.flattenPath(self.attributes['Layer2']['Texture'])
        self._iwrite(file,'texture','Texture2',tex)
        self._iwrite(file,'enum','TextureWrap2',self.attributes['Layer2']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter2',self.attributes['Layer2']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter2',self.attributes['Layer2']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter2',self.attributes['Layer2']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias2',self.attributes['Layer2']['LODBias'])

        tex = iUtils.flattenPath(self.attributes['Layer3']['Texture'])
        self._iwrite(file,'texture','Texture3',tex)
        self._iwrite(file,'enum','TextureWrap3',self.attributes['Layer3']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter3',self.attributes['Layer3']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter3',self.attributes['Layer3']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter3',self.attributes['Layer3']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias3',self.attributes['Layer3']['LODBias'])

        tex = iUtils.flattenPath(self.attributes['Layer4']['Texture'])
        self._iwrite(file,'texture','Texture4',tex)
        self._iwrite(file,'enum','TextureWrap4',self.attributes['Layer4']['TextureWrap'])
        self._iwrite(file,'bool','BilinearFilter4',self.attributes['Layer4']['BilinearFilter'])
        self._iwrite(file,'bool','TrilinearFilter4',self.attributes['Layer4']['TrilinearFilter'])
        self._iwrite(file,stype,'AnisotropicFilter4',self.attributes['Layer4']['AnisotropicFilter'])
        self._iwrite(file,'int','LODBias4',self.attributes['Layer4']['LODBias'])
            
        file.write('      </material>\n')

    #-------------------------------------------------------------------------
    #                          _ s e t T e x t u r e 
    #-------------------------------------------------------------------------
    def _setTexture(self, bImage, layerNumber):
        self.bimages.append(bImage)

        try:
            texFile = self.exporter.getImageFileName(self.bmesh.name,bImage,0)
        except:
            texFile = '** error accessing %s **' % bImage.name

        layerName = 'Layer' + str(layerNumber)
        self.attributes[layerName]['Texture'] = texFile

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
        if matName != None:
            #
            # custom name?
            #
            if matName[0] == '$':
                vtpos = matName.find(':')
                if vtpos < 0:
                    self.attributes['Type'] = matName[1:]
                else:
                    self.attributes['Type'] = matName[1:vtpos]
                    svt = matName[vtpos+1:].lower()
                    self.vtCustom = EVT_STANDARD
                    if svt == '2tcoords':
                        self.vtCustom = EVT_2TCOORDS
                    elif svt == 'tangents':
                        self.vtCustom = EVT_TANGENTS

            else:
                self.attributes['Type'] = matName

        activeUVIndex = self.bmesh.active_uv_texture_index
        layerNumber = 1
        for layerNumber in range(len(self.bmesh.uv_textures)):
            #self.bmesh.active_uv_texture_index = layerNumber
            uvFaceData = self.bmesh.uv_textures[layerNumber].data[face.index]
            if uvFaceData.image != None:
                self._setTexture(uvFaceData.image,layerNumber+1)

        if self.attributes['Type'].lower() == 'trans_alphach':
            self.attributes['MaterialTypeParam'] = 0.000001
            
        #self.bmesh.active_uv_texture_index = activeUVIndex

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
            if self.bmaterial.mode & Blender.Material.Modes.VCOL_PAINT:
                self.useVertexColor = True
            else:
                self.useVertexColor = False
        
    #-------------------------------------------------------------------------
    #                               g e t T y p e
    #-------------------------------------------------------------------------
    def getType(self):
        return 'BlenderMaterial'
