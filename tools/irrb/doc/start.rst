Getting Started
===============
.. highlight:: cpp
   :linenothreshold: 5

.. toctree::
   :maxdepth: 2

**Key Points**

* Blender Objects are written as Irrlicht scene nodes to an Irrlicht scene file (.irr). 
* Blender Mesh Objects have their Mesh *Data*  written to mesh files (.irrmesh). 
* Multiple Blender Mesh Objects may link to the same Mesh Data. In this case 
  only a single .irrmesh file will be generated and multiple Mesh nodes will be 
  written to the scene file. 

Before you start using **irrB** you should at the very least have a
fundamental understanding of how to use Blender.

In order to better understand how **irrB** works with Blender, it will help
you to know the relationship between Blenders "Objects" and "Object Data". 

In a general sense, "Objects" are things (meshes, cameras, lights, etc.) you add 
to a Blender/Irrlicht scene that have three things in common:

* **Type** - Identifies the object type (mesh, camera, light).
* **Transform** - The object position, rotation, and scale.
* **Data** - The object type specific data.

"**Data**" is additional information that is specific to an object
"**Type**".  For example, light data will contain a light type (spot, area,
sun, etc.), a diffuse color, and other light parameters. Whereas mesh data will 
contain vertex, face, and material/texture information. 

.. note::
   
   A Blender "Object" is exported to Irrlicht's scene file (.irr) as a **scene
   node**. The xml scene node data in the .irr file contains the object
   position, rotation, scale, and object specific data.

It's important to understand that multiple objects (of the same type) may 
reference the same object data. For example, you may have a single mesh 
displayed in a scene multiple times at different positions and/or scales. 

The Irrlicht Scene File (.irr)
------------------------------

The native Irrlicht scene file format is simply an XML file which includes 
information for all objects contained in a scene. For example, when a
mesh object is exported to an Irrlicht scene file (.irr), the following XML 
data is written::

   <node type="mesh">
     <attributes>
        <string name="Name" value="Cube" />
        <int name="Id" value="-1" />
        <vector3d name="Position" value="0.000000, 0.000000, 0.000000" />
        <vector3d name="Rotation" value="0.000000, 0.000000, 0.000000" />
        <vector3d name="Scale" value="1.000000, 1.000000, 1.000000" />
        <bool name="Visible" value="true" />
        <bool name="AutomaticCulling" value="true" />
        <bool name="DebugDataVisible" value="false" />
        <bool name="IsDebugObject" value="false" />
        <bool name="ReadOnlyMaterials" value="false" />
        <string name="Mesh" value="mdl/Cube.irrmesh" />
     </attributes>
   </node>
   
This sample shows what is written to the .irr scene file for the default
Cube scene node that appears when Blender is first started. You can see 
the Object level elements:

* **Type** (1): ``<node type="mesh">``
* **Transform** (5,6,7): ``Position, Rotation, & Scale``
* **Data** (13): ``<string name="Mesh" value="mdl/Cube.irrmesh"/>``

Note that the mesh object data is actually a reference to another file
("mdl/Cube.irrmesh") which contains the mesh vertex, index, and material
information. 

