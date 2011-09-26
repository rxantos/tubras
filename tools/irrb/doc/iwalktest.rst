=====================
iwalktest Integration
=====================

.. toctree::
   :maxdepth: 2

irrB integrates an optional utility named "iwalktest" which allows you 
to view and walk through your freshly exported scene using the Irrlicht 
engine. iwalktest is currently available to execute on both the 
Windows and Linux platforms. 

Instructions on iwalktest installation and usage may be found here: irrB Utilities 

The "Walk Test" GUI button will only appear in irrB's GUI if the following conditions are met: 

1. The "IWALKTEST" OS environment variable is defined. 

2. The irrB "Create Scene File" toggle button is selected. 

With these conditions met, it's simply a matter of selecting the "Walk Test" 
toggle button to view your scene immediately after exporting. 

After you export a scene for the first time, a "Run Walk Test" push button will appear 
at the bottom of the irrB interface. Clicking on this button will re-execute iwalktest 
with the last scene exported. 

If you prefer to run a different application other than "iwalktest.exe", you may 
do so by setting the "IWALKTEST" environment variable to point to your own application. 

A couple of notes on how irrB executes the external application: 

* **irrB** sets the current directory to the directory in which the external application 
  resides before running the application. 

* irrB passes the full scene file path and file name to the external application. If 
  the environment variable contains a "$1", the scene file is substituted in its 
  place. A "$2" substitution variable is replaced with value of the "Output Directory" path.

