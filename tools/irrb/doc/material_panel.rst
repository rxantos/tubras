==============
Material Panel
==============

.. toctree::
   :maxdepth: 2

The **irrB** material panel gives explicit control over every available Irrlicht material
property. Mapping from a Blender material to an Irrlicht is difficult at
best so **irrB** takes the approach of letting the user control the settings directly.
In cases where there is a direct match between a Blender material property
and an Irrlicht material property, **irrB** will use the Blender property and
include it as an additional panel element in the **irrB** material panel. 

.. container:: irrb-left

   .. image:: _static/img010.png 

For example, Blender and Irrlicht both have a "Diffuse" material attribute.
You can set the Diffuse color using Blender's GUI element, or in the **irrB**
material panel. 

The **irrB** material panel contains a property that corresponds to
every field that is available in Irrlicht's `SMaterial <http://irrlicht.sourceforge.net/docu/classirr_1_1video_1_1_s_material.html>`_ 
and `SMaterialLayer <http://irrlicht.sourceforge.net/docu/classirr_1_1video_1_1_s_material_layer.html>`_ 
data structures.  These structures are used to programatically define Irrlicht 
Material settings.

----

Irrlicht Materials
==================
Currently, Irrlicht contains 24 pre-defined material "types".  These materials range
from a simple "solid" material to  a "transparent with parallax mapping" material.

In addition to the 24 pre-defined material types, Irrlicht also allows you to create 
your own custom material type(s).

Irrlicht supports multiple materials per mesh and **irrB** supports exporting meshes
with multiple materials as well. 

.. container:: irrb-padleft140

	In Blender, you assign multiple materials to a mesh by:
	
		1. Selecting the mesh.
			
		2. Create a Material Slot and name the new material.
			
		3. Assign the newly created material to the appropriate faces in the mesh.
	
Each Blender Material that is created maintains its own set of related Irrlicht (**irrB**)
Material properties (type, diffuse, layers, etc.).    

---- 

Irrlicht Material Texture Layers
================================
Irrlicht allows up to four texture layers (`SMaterialLayer <http://irrlicht.sourceforge.net/docu/classirr_1_1video_1_1_s_material_layer.html>`_) 
to be defined per material.  All of the pre-defined Irrlicht material types use 
at most two texture layers. The current Irrlicht internal vertex format supports
at most two set of UV coordinates. 

Each texture layer is made up of information that includes an image/texture reference
and various other properties. **irrB** allows you to specify the image reference in 
Blender in two different ways.
	
**UV Mapped Image**.  Using Blender's UV Image Editor, you may assign one or more images
to the various UV mapped faces within the UV Image Editor itself. 

**Blender Texture Slot**. Blender allows one or more "texture slots" to be assigned 
to a material. 

Regardless of the method you use to specify the image reference for a texture layer, 
the layers associated properties are defined within the Irrlicht material property
panel.

----

irrB Irrlicht Material Properties
=================================

Irrlicht material properties may be found underneath Blender's Material panel group. 

**Type** - Type of material. Choices available are the 24 pre-defined Irrlicht material types.  
You may also choose "Custom" if you have created your own material type.  When "Custom" is selected,
a field named "Custom Name" will appear.  Use this field to enter your custom material name.

**Lighting** - Enable lighting.

**Backface Culling** -  Enable backface culling. If enabled, backfaces won't 
be visible.  If disabled, backfaces will be visible (double-sided).  

**ZWriteEnable** - Enable zbuffer writing.  

**Normalize Normals** -  Normalize normals after loading. Use this if the mesh is 
lit and scaled.

**Link Diffuse** - Link the diffuse color to Blender's material diffuse property. 

**Gouraud** - Use Gouraud or flat shading.

**Frontface Culling** - Enable frontface culling.  If enabled, frontfaces won't
be visible.  If disabled, frontfaces will be visible. 

**Fog** - Enable fog.

**Use MipMaps** - Enable using mipmaps.

**Use Blender Textures** - Use textures/images from Blender's texture slots. If a 
UV layer has an image assigned to it and also has images in the texture slots, the
images in the texture slots are used if the options is enabled.

**ZBuffer** - ZBuffer comparison method for depth buffer test. "Never" (disabled), "Less or Equal",
"Equal", "Less", "Not Equal" "Greator or Equal", "Greator", "Always".  
	
**Antialiasing** - Enable anti-aliasing (EAAM_LINE_SMOOTH).

**Color Material** - Defines the interpretation of vertex color in the lighting equation.
Values should be chosen from E_COLOR_MATERIAL. When lighting is enabled, vertex color can 
be used instead of the material values for light modulation. This allows to easily change e.g. 
the diffuse light behavior of each face. The default, ECM_DIFFUSE, will result in
a very similar rendering as with lighting turned off, just with light shading.

**Ambient** - How much ambient light (a global light) is reflected by this material. 

**Emissive** - Light emitted by this material.

**Diffuse** - How much diffuse light coming from a light source is reflected by this material.

**Specular** - How much specular light (highlights) is reflected. See "Shininess" on how to 
enable specular lights.

**Color Mask** - Defines the enabled color planes. Only enabled color planes will be rendered
to the current render target.

**Param1** - Free parameter, dependent on the material type. Used for example by the
EMT_PARALLAX_MAP_SOLID and EMT_TRANSPARENT_ALPHA_CHANNEL material types.

**Param2** - Free parameter, dependent on the material type.

**Shininess** - Value affecting the size of the specular highlights. A value of 20 is 
common.  If set to 0, no specular highlights are used.  To activate, set the shininess
of a material in the range 0.5-128.

**Thickness** - Thickness of non-3dimensional elements such as lines and points.

* **Texture Layer Properties**

.. container:: irrb-right

	.. image:: _static/img010b.png 

Located at the bottom of the Irrlicht material properties panel are the four 
Irrlicht texture layer property settings.

**UV Wrap Modes** - Texture clamp mode: "Repeat",  "Clamp",  "Clamp To Edge", 
"Clamp To Border", "Mirror", "Mirror Clamp", "Mirror Clamp To Edge", and 
"Mirror Clamp To Border" 

**Filter** - Filter method to use. "None", "Bilinear", "Trilinear".

**Anisotropic** - In Irrlicht you can use anisotropic filtering in conjunction with 
bilinear or trilinear texture filtering to improve render results. Value should be
in the range 2-16.  0 & 1 is disabled.

**LOD Bias** - Bias for mipmap selection. This value can make the textures more or 
less blurry than with the default value of 0. The value (divided by 8.f) is added 
to the mipmap level chosen initially, and thus takes a smaller mipmap for a region
if the value is positive.

----

Irrlicht Material Types
=======================

**solid** - Standard solid material. Only first texture is used as the diffuse texture.

**solid_2layer** - Solid material with 2 texture layers. The second is blended onto the first using the alpha value of
the vertex colors. This material is currently not implemented in OpenGL, but it works with DirectX.

**lightmap** - Material type with standard lightmap technique: There should be 2 textures: The first texture layer is
a diffuse map, the second is a light map. Vertex light is ignored.

**lightmap_add** - Material type with standard lightmap technique but lightmap and diffuse texture are not
modulated, but added instead.

**lightmap_m2** - Material type with standard lightmap technique: There should be 2 textures: The first texture
layer is a diffuse map, the second is a light map. Vertex light is ignored. The texture colors are effectively
multiplied by 2 for brightening.

**lightmap_m4** - Material type with standard lightmap technique: There should be 2 textures: The first texture
layer is a diffuse map, the second is a light map. Vertex light is ignored. The texture colors are effectively
multiplied by 4 for brightening.

**lightmap_light** - Like lightmap, but also supports dynamic lighting.

**lightmap_light_m2** - Like lightmap_m2, but also supports dynamic lighting.

**lightmap_light_m4** - Like lightmap_m4, but also supports dynamic lighting.

**detail_map** - Detail mapped material. The first texture is diffuse color map, the second is added to this and
usually displayed with a bigger scale value so that it adds more detail. The detail map is added to the diffuse
map using ADD_SIGNED, so that it is possible to add and substract color from the diffuse map. For example a
value of (127,127,127) will not change the appearance of the diffuse map at all. Often used for terrain
rendering.

**sphere_map** - Environment reflection Material. The "sphere relfection map" must be Texture 1.

**reflection_2layer** - A reflecting material with an optional additional non reflecting texture layer. The reflection
map should be set as Texture 1.

**trans_add** - A transparent material. Only the first texture is used. The new color is calculated by simply adding
the source color and the dest color. This means if for example a billboard using a texture with black background
and a red circle on it is drawn with this material, the result is that only the red circle will be drawn a little bit
transparent, and everything which was black is 100% transparent and not visible. This material type is useful for
particle effects.

**trans_alphach** - Makes the material transparent based on the texture alpha channel. The final color is blended
together from the destination color and the texture color, using the alpha channel value as blend factor. Only
first texture is used. If you are using this material with small textures, it is a good idea to load the texture in 32
bit mode (video::IVideoDriver::setTextureCreationFlag()). Also, an alpha ref is used, which can be manipulated
using SMaterial::MaterialTypeParam. If set to 0, the alpha ref gets its default value which is 0.5f and which
means that pixels with an alpha value >127 will be written, others not. In other, simple words: this value
controls how sharp the edges become when going from a transparent to a solid spot on the texture. Note that
irrb sets Param1 to 0.000001.

**trans_alphach_ref** - Makes the material transparent based on the texture alpha channel. If the alpha channel
value is greater than 127, a pixel is written to the target, otherwise not. This material does not use alpha
blending and is a lot faster than trans_alphach. It is ideal for drawing stuff like leaves of plants, because the
borders are not blurry but sharp. Only first texture is used. If you are using this material with small textures and
3d object, it is a good idea to load the texture in 32 bit mode (video::IVideoDriver::setTextureCreationFlag()).

**trans_vertex_alpha** - Makes the material transparent based on the vertex alpha value.

**trans_reflection_2layer** - A transparent reflecting material with an optional additional non reflecting texture
layer. The reflection map should be set as Texture 1. The transparency depends on the alpha value in the vertex
colors. A texture which will not reflect can be set als Texture 2. Please note that this material type is currently
not 100% implemented in OpenGL. It works in Direct3D.

**normalmap_solid** - A solid normal map renderer. First texture is the color map, the second should be the
normal map. Note that you should use this material only when drawing geometry consisting of vertices of type
S3DVertexTangents (EVT_TANGENTS). You can convert any mesh into this format using
IMeshManipulator::createMeshWithTangents() (See SpecialFX2 Tutorial). This shader runs on vertex shader
1.1 and pixel shader 1.1 capable hardware and falls back on a fixed function lighted material if this hardware is
not available. Only two lights are supported by this shader, if there are more, the nearest two are chosen.
Currently, this shader is only implemented for the D3D8 and D3D9 renderers.

**normalmap_trans_add** - A transparent normal map renderer. First texture is the color map, the second should
be the normal map. Note that you should use this material only when drawing geometry consisting of vertices of
type S3DVertexTangents (EVT_TANGENTS). You can convert any mesh into this format using
IMeshManipulator::createMeshWithTangents() (See SpecialFX2 Tutorial). This shader runs on vertex shader
1.1 and pixel shader 1.1 capable hardware and falls back on a fixed function lighted material if this hardware is
not available. Only two lights are supported by this shader, if there are more, the nearest two are chosen.
Currently, this shader is only implemented for the D3D8 and D3D9 renderers.

**normalmap_trans_vertexalpha** - A transparent (based on the vertex alpha value) normal map renderer. First
texture is the color map, the second should be the normal map. Note that you should use this material only when
drawing geometry consisting of vertices of type S3DVertexTangents (EVT_TANGENTS). You can convert any
mesh into this format using IMeshManipulator::createMeshWithTangents() (See SpecialFX2 Tutorial). This
shader runs on vertex shader 1.1 and pixel shader 1.1 capable hardware and falls back on a fixed function
lighted material if this hardware is not available. Only two lights are supported by this shader, if there are more,
the nearest two are chosen. Currently, this shader is only implemented for the D3D8 and D3D9 renderers.

**parallaxmap_solid** - Just like normalmap_solid, but uses parallax mapping too, which looks a lot more
realistic. This only works when the hardware supports at least vertex shader 1.1 and pixel shader 1.4. First
texture is the color map, the second should be the normal map. The normal map texture should contain the
height value in the alpha component. The IVideoDriver::makeNormalMapTexture() method writes this value
automatically when creating normal maps from a heightmap when using a 32 bit texture. The height scale of the
material (affecting the bumpiness) is being controlled by the SMaterial::MaterialTypeParam member. If set to
zero, the default value (0.02f) will be applied. Otherwise the value set in SMaterial::MaterialTypeParam is
taken. This value depends on with which scale the texture is mapped on the material. Too high or low values of
MaterialTypeParam can result in strange artifacts.

**parallaxmap_trans_add** - A material just like parallaxmap_solid, but it is transparent, using
EMT_TRANSPARENT_ADD_COLOR as base material.

**parallaxmap_trans_vertexalpha** - A material just like EMT_PARALLAX_MAP_SOLID, but it is transparent,
using EMT_TRANSPARENT_VERTEX_ALPHA as base material.

**onetexture_blend** - BlendFunc = source sourceFactor + dest destFactor ( E_BLEND_FUNC ) Using only
Textures(0). generic Blender
		