============
Object Panel
============

.. toctree::
   :maxdepth: 2

The **irrB** Object panel is designed to control Irrlicht scene node information 
that is exported to a scene (.irr) file. 

.. container:: irrb-left

   .. image:: _static/img005.png 

By default, Blender objects are mapped directly to their corresponding
Irrlicht scene node types.  For example, a Blender mesh object will be
exported as an Irrlicht mesh scene node, light to light, and camera to camera.

Irrlicht scene node types such as Billboard, Volumetric Light, and Water
Surface nodes will need to be explicitly set in the **Type** field of the
object panel because Blender doesn't have a corresponding object type.
What's more is if your application contains a custom scene node type, **irrB**
allows you set a custom scene node type as well.

The object panel also contains an easy to use field for explicitly
controlling whether or not an object is exported by **irrB**.  By default all
objects in Blender's visible layers are exported. There are occasions where
it isn't desirable to export all objects in a visible layer.  A good example
of this would be when a scene contains a mesh that has been added in order
to affect lighting/shadows for baking light maps. 

Depending on the currently selected object and it's selected **Type**,
varying options will appear in the object panel.

For example, if the currently selected Blender object is a mesh, you can choose 
from any of the following Irrlicht mesh types: standard, custom, water surface,
volumetric light, skydome, skybox, or billboard.  Based on the Irrlicht node type
selected, related Irrlicht options will also appear.  

Note that **All** objects exported to a scene have a corresponding **ID**.  An ID
is an integer value the defaults to -1 and may be used by your program to
locate one or more objects after a scene file has been loaded.

For more information, see `getSceneNodeFromId() <http://irrlicht.sourceforge.net/docu/classirr_1_1scene_1_1_i_scene_manager.html>`_ 
in the Irrlicht API documentation.

Custom Scene Node Properties
============================

Blender allows you to attach "custom" integer, string, bool, and/or float 
properties to any Blender object.  When **irrB** detects that an object contains 
custom Blender properties, those properties are then exported into the 
corresponding scene nodes "user attributes". 

This is useful for adding custom data that has meaning specific to your 
application. For example, "spawn points":

* Add a Blender "empty" object to a scene.
* Add a custom boolean object property to the empty object named "spawn" 
  and set it to "True".
* Your application code could then include code that looks for scene nodes
  with an attribute named "spawn" that was set to "True" and act
  accordingly.

Common Options
==============

**Export Object** - Indicator used to control whether or not a object is
exported.

**ID** - An arbitrary integer that may be used by your application to
locate a specific scene node or group of scene nodes.

----

Mesh Object Options
===================

Common Options:
	**Node Type** - This field is used to specify the Irrlicht mesh node type. 
	Valid options include standard, custom, water surface, volumetric light, 
	skydome, skybox, or billboard.  See below options specific to each node
	type.
	
	**Automatic Culling** - Enables or disables scene node automatic culling 
	based on the selected type.

	**Hardware Hint** - Hardware mapping hint used to indicate what, if any mesh 
	data should be stored on the hardware.
	
		* Never - Don't store on the hardware.
		* Static - Rarely changed, usually stored completely on the hardware.
		* Dynamic - Sometimes changed, driver optimized placement.
		* Stream - Always changed, cache optimizing on the GPU.
 	
	**Hint Buffer Type** - Hint on what data should be stored on the hardware.
		* None - No data.
		* Vertex - Vertex data.
		* Index - Index data.
		* Vertex & Index - Both Vertex and Index data.

	**Octree Node** - Enables or disables rendering the mesh as an Octree scene 
	scene node. This a good method for rendering scenes with lots of geometry.  
	The Octree is built on the fly from the mesh, much faster then a bsp tree. 
	When selected, the option "Octree Min Polycount" will appear.  
	Use this field to specify the minimum number of triangles per Octree node.
	
Mesh Node Type Options:

**Standard**
	Uses common options only.

**Billboard**
	**Shade Top** - The top color of the billboard.
	
	**Shade Bottom** - The bottom color of the billboard.
	
	**Top Width** - The width of the top edge of the billboard.
	
	**Bottom Width** - The width of the bottom edge of the billboard.
	
	**Height** - The height of the billboard.

**Skybox**
	Uses common options only.

**Skydome**
	**Horz Res** - Number of faces along the horizontal axis.
	
	**Vert Res** - Number of faces along the vertical axis.
	
	**Tex Pct** - The percentage of the image to use, e.g. 0.8 uses 
	the top 80% of the image, 1.0 uses the entire image.
	
	**Sphere Pct** - The percentage of the sphere to generate.  A value 
	of 1.0 generates exactly the upper hemisphere. 1.1 will generate slightly 
	more, and 2.0 will generate a full sphere. It is sometimes useful to use 
	a value slightly bigger than 1 to avoid a gap between some ground place and the sky. 
	
	**Radius** - The size of the sphere in "units".

**Volumetric Light**
	**Distance** - Distance to hypothetical light source point - affects FOV angle.
	
	**U Subdivide** - Number of subdivisions in the U space. Controls the number of
	"slices" in the volume: Total number of polygons = 2 + ((U Subdivide + 1) + (V Subdivide +1)) * 2.
	Each slice is a quad plus the rectangular plane at the bottom.
	
	**V Subdivide** - Number of subdvisions in the V space.
	
	**Foot Color** - Color at the source.
	
	**Tail Color** - Color at the end.
	
	**Dimension** - X & Z determine the size/dimension of the plane.  Y is the lenght of the beams.

**Water Surface**
	**Wave Length** - The length of the wave.
	
	**Wave Speed** - The speed of the wave.
	
	**Wave Height** - The height of the wave.

**Custom**
	**Custom node type** - The name of the custom node.

----

Light Object Options
====================

**Light Type**
	**Point** - A point light has a position in space and radiates light in all directions.
	
	**Spot** - A spot light has a position in space, direction, and a limited cone of influence.
	
	**Directional** - A directional light has a direction and an infinite distance.

**Ambient** - Ambient color emitted by the light

**Diffuse** - Diffuse color emitted by the light. This is the primary color you want to set. This property
references Blender's Light Diffuse property, so changing one changes the other.

**Specular** - Specular color emitted by the light.

**Radius** - Radius of light. Everything within this radius will be lit.

**Outer Cone** - The angle of the spot light's outer cone. Ignored for other lights.

**Inner Cone** - The angle of the spot light's inner cone. Ignored for other lights.

**Fall Off** - The light strength's decrease between Outer and Inner cone.

**Cast Shadows** - Indicates whether or not the light casts shadows.

**Attenuation** - Attenuation factors (constant, linear, quadratic). Changes the 
light strength fading over distance. Can also be altered by setting the radius, 
Attenuation will change to (0,1.f/radius,0). Can be overridden after radius was set. 

----

Camera Object Options
=====================

**Target** - The camera target (look at) position.

**Up Vector** - Up vector.

**FOV** - Field of view. 

**Aspect** - Aspect ratio.

**ZNear** - Near plane distance.

**ZFar** - Far plane distance. 

**Bind Target** - Bind the camera rotation to its target vector.

