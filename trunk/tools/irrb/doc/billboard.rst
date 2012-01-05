==========
Billboards
==========

.. toctree::
   :maxdepth: 2

.. container:: irrb-right

	.. figure:: _static/img019.png

		Sample Billboard .blend file - `04-Billboard.blend <http://tubras.googlecode.com/svn/trunk/tools/blendfiles/26/04-Billboard.blend>`_
			
Creating a Billboard in Blender that will be exported as an Irrlicht Billboard scene node may be performed in 3 steps:

	**1.** Add a plane mesh to your scene at the position you would like the billboard to appear. The scale and rotation are ignored by **irrB**.
	
	**2.** Create an UV map for the plane and assign it an image using Blender's UV/Image Editor. 
	The actual UV coordinates are ignored by **irrB**, but you must assigned an image to the UV map. 
	
	**3.** Set the irrB Object Type to "Billboard" in the **irrB** object sub-panel.  Once the object
	type is set to "Billboard", you then define the width, height, vertex (shade) colors.

----
	
Transparency
============

.. container:: irrb-left

	.. image:: _static/img020.png

If the image you assigned to the billboard in the UV/Image Editor is transparent
and you would like the billboard to be transparent as well, simply create a
new Blender material and assign it to the billboard plane mesh. 

In the **irrB** material properties sub-panel, assign the material type to 
either "trans_alphach" or "trans_alphach_ref" depending on your requirements. 