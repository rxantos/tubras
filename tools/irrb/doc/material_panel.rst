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
to be defined per material.


