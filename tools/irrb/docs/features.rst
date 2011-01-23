Features
========
The Irrlicht/Blender Exporter exports Blender scene and static node data to the native Irrlicht scene (.irr) and mesh (.irrmesh) file formats. 

Implemented Features:

* Blender Scene data is exported to Irrlicht native scene format (.irr). 
* Blender Mesh data is exported to the Irrlicht native mesh format (.irrmesh). 
* Export Blender ID Properties and Logic Properties as Irrlicht scene UserData. 
* Export Blender Lamp, Mesh, Camera, and Empty objects. 
* Export Game Engine Materials and corresponding UV data. 
* Export Blender Generated Lightmap/Baked Materials. 
* Export Object Parent/Child relationships and transforms. 
* Export Irrlicht Skybox, SkyDome, and Billboards.
* Export Fog and Blender Mist settings.
* Export Collision, Sensor, Constraint, and Rigid body physics data.
* Export materials that require Irrlicht's EVT_TANGENTS vertex type.
* Export Irrlicht's hardware mapping hints.
* Export Meshes with 64k+ vertices.
* Export Meshes as Octree nodes.
* Export Volumetric Light and Water Surface nodes.
* Specify Textures as two-sided, transparent, and/or using lighting per face. 
* Blender Packed UV Images are automatically saved to disk.
* Automatic translation between Blender and Irrlicht coordinate systems. 
* Export all assets (scene, mesh, & textures) to a single file (.zip).
* Optionally generate a 32 and/or 64 bit executable with embedded assets.
* Optionally "walk test" your scene immediately after it has been exported using the Irrlicht render engine.

Working on for 0.7

* Particles
* iwalktest Bullet Integration

Todo 

* Sound nodes  
* Animation

