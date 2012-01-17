==============
irrB Utilities
==============

.. toctree::
   :maxdepth: 2

.. container:: irrb-right

   .. image:: _static/img025.png 

The utilities **iwalktest** and **imeshcvt** may optionally be used to enhance 
the functionality of **irrB**. iwalktest is used to view exported Blender scenes. 
imeshcvt is used to convert meshes to an experimental binary mesh format (.irrbmesh).

Installation
============

The latest stable download of **irrbUtils** is accessible from both the "Project" 
and "Downloads" tabs of this `Tubras Google Code project <http://code.google.com/p/tubras>`_. 
On the "Project Home" tab, irrbUtils is listed in the "Featured Downloads" 
section. The current version is 0.6. It may be downloaded from here:

Windows:
	`irrbUtils-0.6-win.zip <http://tubras.googlecode.com/files/irrbUtils-0.6-win.zip>`_

Linux:
	`irrbUtils-0.6-linux.zip <http://tubras.googlecode.com/files/irrbUtils-0.6-linux.zip>`_

Each .zip file contains both 32 and 64 bit versions of the utilities. The 
zip file includes the following:

	| ``data/               // config and texture data``
	| ``imeshcvt.exe        // windows executable``
	| ``iwalktest.exe       // linux executable``
	| ``x64/imeshcvt.exe    // windows 64 bit executable``
	| ``x64/iwaltest.exe    // windows 64 bit executable``

The Linux zip file contains the same files except the executables have the .exe
extension removed.
 
Unzip the contents to a user **writable** directory because iwalktest creates a 
log file in the directory it is executed from.

----

Configuration
=============

In order to integrate iwalktest and imeshcvt with **irrB**, you need to set up 
environment variables which point to the locations of their respective executables.

**Windows** - If installed/unzipped to "c:\\irrbutils\\", then you would set the 
following environment variables:

	| ``IWALKTEST=c:\irrbutils\iwalktest.exe -i "$1" -a "$2"``
	| ``IMESHCVT=c:\irrbutils\imeshcvt.exe``

**Linux** - if installed to "/home/jethro/irrbutils", then you would set the following 
environment variables:

	| ``IWALKTEST=/home/jethro/iwalktest -i "$1" -a "$2"``
	| ``IMESHCVT=/home/jethro/imeshcvt``

The "$1" and "$2" substitution variables inform **irrB** where to insert the 
"Scene File" and "Base Directory" command line parameters.

Regardless of the OS you use, you may wish to run a different application 
instead of iwalktest (maybe your own or `irrEdit <http://www.ambiera.com/irredit/>`_). 
To do this, simply set the appropriate value in the IWALKTEST environment variable. 
For example to run irrEdit under Windows you would set the value to (assuming irrEdit is 
installed to "c:\\irredit\\"):

	| ``IWALKTEST=c:\irredit\irredit.exe "$1"``
	
This will cause the scene you export with **irrB** to be opened in irrEdit immediately 
after the export finishes (the scene file name is passed to irrEdit as a parameter).

If you want to run an application that requires information other than the scene 
file name you may set up the environment variable using the "$1" substitution 
variable. For example, your application (myapp.exe) requires a "-i" in front of 
the scene file name:

	| ``IWALKTEST=c:\myappdir\myapp.exe -i "$1" -u``

**irrB** will make the appropriate substitution before invoking your application.

----

iwalktest Usage
===============
.. container:: irrb-left

   .. image:: _static/img026.png
    
The default application used to view scenes exported by irrb is iwalktest.
iwalktest is a simple Irrlicht application that allows you to freely (God camera) move around and view your
scene. It also allows you to easily switch (F9 key) between the various cameras you choose to export.

The help panel identifies the keys and functionality that is available while iwalktest is running:

**wasd** - Camera movement keys. Holding the Shift key while moving will 
accelerate the movement by the amount defined in iwalktest.cfg ("avel" command). 
Note the "e" and "c" keys will move the camera up and down respectively.

**arrow** The up/down/left/right arrow keys control camera rotation.

**I** - Inverts the up-down mouse movement.

**L** -  Toggles visual light debug data.

**prt** - (Print Screen) will save a screen shot of the view to a file named 
"cap##.png" (## - screen shot number). The file will be save into the same 
directory iwalktest is located in.

**F1** - Toggles the visibility of the Help panel.

**F2** - Toggles the visibility of the Debug panel.

**F3** - Cycles the display mode (textured, wireframe, point cloud).

**F4** - Toggles Physics debug data if physics data is present.

**F5** - When the Debug Panel is visible, cycles through the various visual debug 
modes: vertex normals, bounding box, half transparency etc.

**F7** - Toggles camera God mode. 

**F8** - Toggles the console.

**F9** - If more than one camera exists in the scene, F9 cycles the active camera.

**F10** - Toggles GUI mode.

.. container:: irrb-left

	.. image:: _static/img027.png

**Debug Info**

**FPS** - Frames per second.

**Triangles** - Number of triangles being rendered.

**Physics Debug** - On/Off

**Camera Pos** - Camera position in world coordinates.

**Camera Rot** - Camera rotation

**Camera Tar** - Camera target vector.

**Active Sensor** - Active physics sensor.

----

imeshcvt Usage
==============

imeshcvt is a command line utility that allows you to:

* Display information about a mesh.
* Convert a mesh to another format.
* Manipulate a mesh using Irrlicht's IMeshManipulator.

imeshcvt options::

	usage: imeshcvt <options> -i[input file] -o<output file>
	<options> - Generic options:
		-a : folder archive
		-v : target mesh version (.irrbmesh only)
		
	<options> - Mesh Manipulator options:
		-f : flip surfaces
		-n : recalculate normals
		-s : recalculate normals smooth
		-t : create tangents
		
	[input file] Input mesh file to convert or report on. if no output mesh is specified, 
	             info is displayed for the input mesh. Required.
	
	<output file> Output mesh file to convert to.


If no output file is given, imeshcvt will simply display information about the input mesh::

	Input Mesh: \test\meshes\sphere.irrmesh
	Output Mesh:
	--------------- Mesh Info ----------------
	Load Time: 76ms
	Mesh Type: UNKNOWN
	AFrame Count: 1
	ABuffer Count: 1
	Material Count: 1
	Buffer Count: 1
	Vertex Count: 994
	Triangle Count: 1984
