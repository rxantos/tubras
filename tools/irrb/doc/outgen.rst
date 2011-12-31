======================
Output File Generation
======================
.. highlight:: cpp
   :linenothreshold: 5

.. toctree::
   :maxdepth: 2

References to mesh and image locations are ALL relative to the location specified
in the "Out Directory" option located in the **irrB** export panel. This allows scenes to 
be loaded from arbitrary locations as long as the base and relative sub-directories 
remain intact.

**irrB** allows you to choose a single Output Directory.  Depending on whether 
or not you choose to export a scene file, **irrB** behaves as follows:

	**Create Scene File** - Not Selected.  All mesh files (.irrmesh) and packed 
	images are saved to the Output Directory location.
	
	**Create Scene File** - Selected.  All mesh files (.irrmesh) are saved to 
	a sub-directory named **mdl** (model) underneath the Output Directory location.  
	All packed textures are saved to a sub-directory named **tex** underneath the 
	Output Directory location.

Given:
	1. You are exporting a singe scene named "test".
	
	2. The scene contains a single cube named "Cube", and a packed texture named "checkers.png".
	
	3. The "Out Directory" is set to "c:\\scenes\\".

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
	<material bmat="uvmat:grid.png:00100">
		<texture name="Texture1" value="tex/grid.png"/>
        
----

Image Copying
=============
All non-packed texture/image files are copied to the texture directory in order
to maintain the integrity of the relative image references in scene nodes 
and mesh files.
 
For example, if you open and assign an existing image ("c:\\myimages\\patterns\\bricks.png") 
to the Cube UV map, the Cube.irrmesh texture reference would then look like::

	<buffer>
	<material bmat="uvmat:grid.png:00100">
		<texture name="Texture1" value="tex/bricks.png"/>
		
The original image ("c:\\myimages\\patterns\\bricks.png") is copied to the 
texture directory underneath the output directory: "{out directory}/tex/bricks.png".

Images that have the same name but are stored in different directories, are 
written to the texture directory using Blender's internally assigned file name.

----

Packed Output
=============
**irrB** contains an option named "Pack Files" located in the export panel. When 
selected, **irrB** exports/writes all of the scene, model, and texture files
following the rules outlined above.  After all of the files have been written
and image files copied, **irrB** then packs (zip) all of the files into a 
single file and names the file "{scene name}.zip". 
