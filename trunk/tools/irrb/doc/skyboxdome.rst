Sky Boxes and Domes
===================

.. toctree::
   :maxdepth: 2

Exporting Sky Boxes and Domes.

Creating a Skybox in Blender that will be exported as an Irrlicht Skybox scene node requires 4 steps:
1. Add a Cube mesh to your scene.  The position and scale are not relevant.  However, the rotation is important.  The Cube should NOT be arbitrarily rotated.  In order for irrb to determine the which images are the front/back, left/right, and top/bottom, each side of the cube must be perpendicular to the Blender axes.
2. Each one of the six Skybox images must be individually mapped to the appropriate face on the cube. The easiest method for doing this is to use “face select mode” CTRL-TAB, “faces”. Select the appropriate face to map, unwrap (U), and then assign the corresponding image. 
3. Flip the face normals so that all of normals are facing inward – Select all of the faces (CTRL-A), W, “flip normals”.
4. Add an “irrb” object ID property (“inodetype” = “skybox”) to the Cube indicating that the object should be exported as an Irrlicht Skybox scene node.

