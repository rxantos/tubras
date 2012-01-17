===================
Sky Boxes and Domes
===================

.. toctree::
   :maxdepth: 2

.. container:: irrb-right

   .. image:: _static/img021.png
   
Creating an Irrlicht Sky Box or Dome in Blender both require:

	**1.** Create an arbitrary mesh. A single plane will work fine both a sky box or dome.
	
	**2.** Create a new Blender Material for the newly created mesh.
	
After the material has been created, you simply need to assign the appropriate
number of images to the Blender material texture slots.

For a Sky Dome, only a single image meeds to be assigned to the first texture slot.

For a Sky Box, six texture slots will need to be created - each with an assigned image.
What's more is that **each texture slot must be named appropriately** (not the images
themselves).

The texture slot names for a Sky Box node must be "left", "right", "top", "bottom",
"front", and "back".  The names are case insensitive and the order they appear
in the texture slots isn't relevant.

----

Sky Dome Options
================

The Sky Dome options located in the **irrB** Object sub-panel:

.. image:: _static/img022.png

are used to control the size and density of the sphere mesh that is generated
for the sky dome. 

	**Horz Res** - Number of faces along the horizontal axis.
	
	**Vert Res** - Number of faces along the vertical axis.
	
	**Tex Pct** - The percentage of the image to use, e.g. 0.8 uses 
	the top 80% of the image, 1.0 uses the entire image.
	
	**Sphere Pct** - The percentage of the sphere to generate.  A value 
	of 1.0 generates exactly the upper hemisphere. 1.1 will generate slightly 
	more, and 2.0 will generate a full sphere. It is sometimes useful to use 
	a value slightly bigger than 1 to avoid a gap between the ground and sky. 
	
	**Radius** - The size of the sphere in "units".

.. note::

	The **Radius** field must be large enough to contain all of the objects in
	your scene.  Othewise, objects that fall outside of the sky dome radius will
	be hidden.
	
	The sky dome material should have "Fog" disabled in the **irrB** sub-panel 
	to prevent the image from being affected by fog.  If sky dome image appears
	as a solid color, the materials "Fog" setting is likely enabled.

.. container:: irrb-left

	.. figure:: _static/img028.png

		Sample Skybox/dome .blend file - `03-SkyBoxDome.blend <http://tubras.googlecode.com/svn/trunk/tools/blendfiles/26/03-SkyBoxDome.blend>`_

