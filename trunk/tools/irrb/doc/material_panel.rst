==============
Material Panel
==============

.. toctree::
   :maxdepth: 2

The **irrB** material panel gives explicit control over every available Irrlicht material
property. Mapping from a Blender material to an Irrlicht is difficult at
best so **irrB** takes the approach of letting the user control the settings.
In cases where there is a direct match between a Blender material property
and an Irrlicht material property, **irrB** will use the Blender property and
include an additional panel element in the **irrB** material panel. 

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
at most two texture layers. The current Irrlicht internal vertex format support
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
=====================================

Irrlicht material properties may be found underneath Blender's Material panel group. 

**Type** - Type of material. Choices available are the 24 pre-defined Irrlicht material types.  
You may also choose "Custom" if you have created your own material type.  When "Custom" is selected,
a field named "Custom Name" will appear.  Use this field to enter your custom material name.

**Lighting** - Whether or not this material will be lit.

**Backface Culling** -  Whether or not backface culling is enabled. If enabled, backfaces won't 
be visible.  If disabled, backfaces will be visible (double-sided).  

**ZWriteEnable** - Whether or not the zbuffer is writable.  

**Normalize Normals** -  Whether or not the normals should be normalized.  Use this
if the mesh is lit and scaled.

**Link Diffuse** - Whether or not to link the diffuse color to Blender's material diffuse
property. 

**Gouraud** - Whether or not to use Gouraud or flat shading.

**Frontface Culling** - Whether or not frontface culling is enabled.  If enabled, frontfaces won't
be visible.  If disabled, frontfaces will be visible. 

**Fog** - Whether or not fog is enabled for this material.

**Use MipMaps** - Whether or not mipmaps are enabled.

**Use Blender Textures** - Whether or not to use textures/images from Blender's texture slots.

**ZBuffer** - ZBuffer comparison method for depth buffer test. "Never" (disabled), "Less or Equal",
"Equal", "Less", "Not Equal" "Greator or Equal", "Greator", "Always".  
	
**Antialiasing** - Whether or not anti-aliasing is enabled (EAAM_LINE_SMOOTH).

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

Texture Layer Properties

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
		