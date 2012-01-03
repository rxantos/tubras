============
Walk Testing
============

.. toctree::
   :maxdepth: 2

**irrB** contains an option to execute an application which may be used  
to view and walk test your freshly exported scene. You may use your own custom 
application for walk testing or you may use the "**iwalktest**" application that 
was written specifically to work with **irrB** and also uses Irrlicht for 
rendering.

Instructions on installing and using **iwalktest** may be found here: :doc:`irrB Utilities </utilities>` 

.. container:: irrb-right

	.. image:: _static/img016.png 

The "Walktest" GUI button will only appear in **irrB**'s export sub-panel if the 
following conditions are met: 

	1. The "**IWALKTEST**" OS environment variable is defined. 

	2. The **irrB** "Scene" option (Export Scene) is selected in the export sub-panel. 

With these conditions met, it's simply a matter of selecting the "Walktest" 
option to view your scene immediately after exporting. 

After you export a scene for the first time, a "Walktest" push button will appear 
underneath the "Export" button.. Clicking on this button will re-execute the 
defined walk test application with the last scene exported.

---- 

Walk Testing Setup
==================
To have **irrB** invoke your own custom application for walk testing, you must
create an OS environment variable named "**IWALKTEST**".  The value you assign
to the **IWALKTEST** environment variable should be the full path to your application
executable.

You may choose to pass your application two variables that **irrB** pre-defines:

	"$1" - The full path to the scene file that was exported.
	
	"$2" - The value of the "Out Directory" property in the **irrB** export sub-panel.
	
For example, say your application is stored as:

	"c:\\myapps\\mygame\\mygame.exe"
	
and it requires a command line parameter "-i" followed by the scene file name. In 
this case you would set the **IWALKTEST** environment variable to:

	IWALKTEST=c:\\myapps\\mygame\\mygame.exe -i "$1"
	
**irrB** will then invoke "mygame.exe" for walk testing and pass it the scene 
file name (full path) that was exported.
    
.. note:: 

	**irrB** sets the current directory to the directory in which the external 
	application resides before running the application. 
	
	**irrB** passes the full scene file path and file name to the external 
	application through the "**$1**" substitution variable. 
	
	If the "Pack Files" export option is selected, the full path to the generated 
	.zip file is passed as the scene file name.
	
----

Walktest Configuration Options
==============================

Walktest configuration options defined in the **irrB** export sub-panel are saved 
to a "configuration" file alongside the scene file.  This file is named 
"{Scene Name}.cfg".  For example, if you export a scene named "TestScene", the 
walktest options will be saved to a file named "TestScene.cfg".

The format of the walktest configuration file is that of an .ini file.

Example contents of a walk test configuration file::

	[options]
	debug = 4
	console = false
	velocity = 4.0
	angularvelocity = 100.0
	maxvertangle = 80
	velocitydamp = 0.0
	defcampos = {0, 5, -50}
	defcamtarget = {0, 0, 0}
	showHelpGUI = true
	showDebugGUI = true
	
	[video]
	driver = EDT_OPENGL
	resolution = 'medium'
	keepaspect = false
	colordepth = 32
	fullscreen = false
	vsync = true
	stencilbuffer = true
	antialias = 4
	
	[physics]
	library = Irrlicht
	broadphase = btDbvt
	maxSubSteps = 1
	fixedTimeStep = 60
	characterWidth = 1.0
	characterHeight = 2.5
	characterStepHeight = 0.3499999940395355
	characterJumpSpeed = 1.5  
