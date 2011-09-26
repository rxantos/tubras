===============
irrB Change Log
===============

0.6 (xx/xx/2010)
================

Added ability to export mesh node as Octree node.

Blender's "Horizon Color" now exported as the scenes "BackgroundColor".

Added support for controlling hardware mapping per exported object.

Added support for vertex color alpha channel.

iwalktest & imeshcvt now available as both 32 & 64 bit executables.

Added ability to set iwalktest configuration variables through the irrb
interface before launching.

Added option to make an executable out of an exported scene. This option
packs the exported files and embeds the packed file into the iwalktest
executable. The generated executable is saved as "{scenename}.exe" on Windows
or as "{scenename}" on Linux.

Added option to pack exported scene, models, and textures into a single .zip
file - {scenename}.zip

Added ability to export skydome, watersurface, and volumetric light scene
nodes. Node specific properties may be set through irrb interface.

Added interface to set Irrlicht specific scene node settings per Blender
object.

Updated to be installed as a Blender "AddOn". May also may be included in
the user defined scripts directory.

Added interface to set Irrlicht specific material settings per assigned
Blender material. 

Updated to work with Blender 2.5+

0.5 (xx/xx/2010)
================

bug fix - Fixed binary mesh creation when Output Directory contained spaces
- Added doubled quotes to imeshcvt file & directory parameters.

bug fix - Create default material for skybox generation.

Added an option to override the scene file output directory:
iConfig.ScriptOptions.sceneOutDir.  The default value '.' will cause the 
scene file to be written to "Output Directory".

Added an option (iConfig.ScriptOptions.copyExternalImages) to copy external images 
to the irrb destination texture directory.  Default is set to True.

0.4 (12/31/2009)
================

.irr Scene attribute "AmbientLight" is now written using Blender's World
ambient light value.

Added ability to export Fog (Blender Mist). Irrlicht default (video driver)
Fog settings are located in iConfig.py "SceneAttributes".
"Fog.Enabled" is controlled by enabling/disable Blenders World Mist.
"Start", "End", & "Density" are also overridden use Blenders World
Mist options. "Fog.Color" is set using Blender's World-Horizon color. 

Update to only export objects contained in active/visible layers.

Update to allow partial UserConfig definitions.

Added ability to write all game properties to scene node "userData".

Added hardware mapping hint ID properties ("HWMappingHint" & 
"HWMappingBufferType") for mesh objects.  The defaults are
"static" (EHM_STATIC) &  "vertexindex" (EBT_VERTEX_AND_INDEX).

Added exporting of physics attributes to mesh scene nodes. The attributes
are added to the "UserData" section of the node info. These attributes
may be read via the ISceneUserDataSerializer interface and feed into
the applications physics system (Bullet, Irrlicht (collision), PhysX, etc.).

Updated to allow custom materials (${materialtype}) to optionally specify
vertext type: ${materialtype}:{vertextype} where {vertextype} may be: 
'standard' (default), '2tcoords', or 'tangents'. Example: '$mymat:tangents',
would generate a material type named 'mymat' with EVT_TANGENTS vertices.

Updated to allow EVT_TANGENTS vertex type to be created for materials that
require it (normalmap_x, parallaxmap_x). Automatically detected & created.

Updated to allow a single mesh to contain more than 64k vertices (32 bit
indices). Applications will require the CIrrMeshWriter.cpp & 
CIrrMeshFileLoader.cpp patch.

bug fix - When manual entering directory paths, incorrect path was being 
returned by "CheckDirectory".

Added "Blender Version", "Platform uname", and iwalktest/imeshcvt env
variables to irrb.log file.

0.3 (02/10/2009)
================

Fixed "vertex colors" - Blender vertex colors are written if vertex color
exists and:

    * Face doesn't have a blender material assigned or
    * Material is assigned and has "VCol Paint" checked.

Added option to create directory if mesh, image, or scene path doesn't
exist.

Added logic to abort the export if error occurs when opening irrb.log file.

Updated to use substitution variables ($1, $2) in IWALKTEST environment
variable:

    $1 - Scene File (full path)
    $2 - Relative Base Directory
    
0.2 IWALKTEST environment variables that used "iwalktest.exe" should be 
updated to:

    iwalktest -i $1 -a $2

Added Blender "procedural" material as a face property - two faces in the 
same mesh with different procedural materials will cause two meshbuffers
to be generated.  Used to index Blender ID properties for Irrlicht 
specific material attributes.

Added "Irrlicht Version" target to handle future binary mesh format changes.

Changed irrb license from gpl to zlib/libpng.

Allow billboard & skybox images to be packed.

Added "billboard" exporting. Requirements:

    ID Property "irrb|inodetype=billboard".
    UV Mapped Plane (quad) with a single texture.
    Billboard size is based on the quads scale:
    
        Width = Blender X scale
        Height = Blender Z scale

Added "skybox" exporting. Requirements:
    ID Property "irrb|inodetype=skybox".
    UV Mapped Cube with 6 separate textures.
    Quad Faces with normals facing in.

Std attributes & user data now extracted from Blender ID Properties ['irrb']

Added -a (archive) cmd line parm to imeshcvt. "Create Binary Mesh" option
_always_ passes the relative base to imeshcvt.

Added light debug data to iwalktest - color and line direction for
directional lights. 'L' key - toggles visual.

bug fix - fixed Exception when mesh buffer exceeds 64k index limit.

bug fix - fixed directional light rotation calculation.

bug fix - meshes that are parented to a camera now have the correct
rotation and position written to the scene file.

bug fix - arbitrary rotations on meshes now working (including nested
parents).

fixed bug that prevented exporting non mesh objects when "Selected Meshes
Only" option was selected.

changed "Copy Textures" functionality to "Save Packed Textures". When selected,
only packed textures will be saved to the user specified directory.

removed $filename/$fullpath options for mesh/texture references.  _all_
file references now use relative paths - relative to the location 
specified in "Relative Base".

gui reorg - option buttons moved to the top.

bug fix - blender textures that have been loaded using relative paths are
now properly located by irrb.

added scene file name and path to iwalktest window caption.

iwalktest updated to use "lsl" config script.

shape debug info to log.

meshes that contain shape keys will have the "basis" mesh (1st) exported
as the base geometry regardless of the active key selected.

0.2 (03/30/2008)
================

Initial release
