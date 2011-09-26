======================
Output File Generation
======================

.. toctree::
   :maxdepth: 2


Key Points
==========

References to mesh and image locations are ALL relative.
The relative location is based on the location of the "Output Directory" field.

Details
=======

irrb allows you to choose a single Output Directory.  Depending on whether 
or not you choose to export a scene file, irrb behaves as follows:

* **Create Scene File** - Not Selected.  All mesh files (.irrmesh) and 
  packed images are saved to the Output Directory location.

* **Create Scene File** - Selected.  All mesh files (.irrmesh) are saved 
  to a sub-directory named **mdl** (model) underneath the Output Directory 
  location.  All packed textures are saved to a sub-directory named **tex**
  underneath the Output Directory location.

Given:
1. You are exporting a singe scene named "test".
2. The scene contains a single cube named "Cube", and a packed texture named "checkers.png".
3. The "Out Directory" is set to "c:\scenes\".

The following will be generated:
* c:/scenes/test.irr		// scene file
* c:/scenes/mdl/Cube.irrmesh	// Cube mesh 
* c:/scenes/tex/checkers.png	// checkers texture

All mesh and texture references will be relative to the "Out Directory".  
In the example above, the test.irr scene file will reference the Cube mesh as "mdl/Cube.irrmesh"::

   <node type="mesh">
	<attributes>
		<string name="Mesh" value="mdl/Cube.irrmesh"/>

 The Cube.irrmesh file will reference the checkers texture as "tex/checkers.png"::

   <buffer>
	<material bmat="uvmat:checkers.png:00100">
		<texture name="Texture1" value="tex/checkers.png"/>
        
Note that non-packed texture references are also written relative to the "Out Directory".  
For example, if you open and assign an existing image ("c:\myimages\patterns\brick.png") 
to the Cube UV map, the Cube.irrmesh texture reference would then look
like::

   <buffer>
	<material bmat="uvmat:checkers.png:00100">
		<texture name="Texture1" value="../myimages/patterns/brick.png"/>

iwalktest can be very useful for determining why a mesh isn't appearing in a scene and/or 
why a texture isn't appearing properly. The first question to ask yourself: 
"Is the mesh/texture being loaded?". iwalktest will log mesh/texture loading errors to 
its log file "iwalktest.log" which is located in the same directory as the iwalktest 
executable. Windows users can also check for load errors in the iwalktest console 
window if it is configured to be displayed (default). 
