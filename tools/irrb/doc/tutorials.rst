=========
Tutorials
=========

.. toctree::
   :hidden:
   
   tut01
   tut02
   tut03
   tut04

Below are a list of tutorials on how to use **irrB** with Blender.

The tutorials on this wiki are NOT intended to teach you how to use Blender. 
Even though the tutorials may mention Blender key combinations and mouse buttons 
for certain functionality, you will be doing yourself a big favor by spending a 
little time learning the basics of Blender. The Blender Wiki Manual is a very 
good place to start for beginners.

Before proceeding with a particular tutorial, please review the Tutorial Setup 
located in the next section.

----

Tutorial List
=============

.. raw:: html

	<br>
	<table border="1" width="90%">
		<tr>
			<td><b>Tutorial</b></td>
			<td><b>Description</b></td>
		</tr>
		<tr>
			<td>
				<a href="tut01.html">
				Solid Material
				</a>
			</td>
			<td>
				Export an object with a single UV mapped texture. Also learn how 
				to bake a Blender defined material onto a UV assigned image.         
			</td>
		</tr>
		<tr>
			<td>
				<a href="tut02.html">
				Multiple Materials
				</a>
			</td>
			<td>
				Export an object with multiple UV mapped textures.           
			</td>
		</tr>
		<tr>
			<td>
				<a href="tut03.html">
				Transparent Material
				</a>
			</td>
			<td>
				Export an object with a transparent UV mapped texture.           
			</td>
		</tr>
		<tr>
			<td>
				<a href="tut04.html">
				Basic Light Mapping
				</a>
			</td>
			<td>
				Generate and export a lightmap to a secondary UV layer.           
			</td>
		</tr>
	</table>
	
----

Tutorial Setup
==============

The tutorials will use the irrb Utilities for viewing the exporter results. 
Installation instructions for the utilities may found in the irrb User Guide.

Each of irrb tutorials assume the following directory structure for exported content:

The scene file (Scene.irr) will be created inside of the specific tutorial subdirectory. 
For irrbTut1, this will be "c:\irrbScenes\irrbTut1\Scene.irr". Each scenes mesh 
data will be saved inside of the "mdl" sub-directory underneath the appropriate tutorial. 
The same holds true for related images ("tex" sub-directory).

For irrbTut1, the Output Directory would be setup as follows: