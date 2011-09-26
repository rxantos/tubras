==============
Material Panel
==============

.. toctree::
   :maxdepth: 2

The irrB material panel gives explicit control over every available Irrlicht material
property. Mapping from a Blender material to an Irrlicht is difficult at
best so irrB takes the approach of letting the user control the settings.
In cases where there is a direct match between a Blender material property
and an Irrlicht material property, irrB will use the Blender property and
include an additional panel element in the irrB material panel. 

.. container:: irrb-left

   .. image:: _static/img010.png 

For example, Blender and Irrlicht both have a "Diffuse" material attribute.
You can set the Diffuse color using Blender's GUI element, or in the irrB
material panel. 

The irrB material panel contains a property that corresponds to
every field that is available in Irrlicht's `SMaterial <http://irrlicht.sourceforge.net/docu/classirr_1_1video_1_1_s_material.html>`_ 
and `SMaterialLayer <http://irrlicht.sourceforge.net/docu/classirr_1_1video_1_1_s_material_layer.html>`_ 
data structures.  These structures are used to programatically define Irrlicht 
Material settings.


