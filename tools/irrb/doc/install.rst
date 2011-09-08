Installation
============

.. toctree::
   :maxdepth: 2

The latest stable download of **irrB** is accessible from both the "Project Home" 
and "Downloads" tabs of the Tubras Google Code project. On the "Project Home" 
tab, **irrB** is listed in the "Featured Downloads" section.

The current version may be downloaded from here: http://tubras.googlecode.com/files/irrb-0.6.zip
 
.. image:: _static/img001.png 
   :align: right

The contents of the zip package are: 

* io_export_irrlicht.py
* docs/changes.txt
* docs/license.html
* docs/UserGuide.pdf

To install **irrB**, unzip the contents of the zip file into a temporary directory 
and install it as a Blender **addon**.

1. Start Blender and call up the **User Preferences** dialog (File | User Preferences..).  
2. Click on the **Add-Ons** tab and then the **Install Add-On...** button located at 
   the bottom of the dialog.
3. Navigate to the directory that you previously unzipped the **irrB** zip file to, select 
   the file **io_export_irrlicht.py**, and then click the **Install Add-On...** button. 
4. Locate the **irrB** exporter in the **Import-Export** section and enable it by selecting 
   the corresponding check box. 

If you would like **irrB** to be automatically activated every time you start Blender, 
then click the **Save As Default** button located at the bottom of the dialog. 
If you don't click **Save As Default**, you will need activate the **irrB** add-on each 
time you start up Blender. 

Documentation on installing and configuring "iwalktest" for both Windows and Linux 
may be found here: **irrB** Utilities 

Requirements
------------
* Blender - Supported Blender Versions are 2.59+
* Python - **irrB** uses Blender's internal version of Python 3.x so you are not required to install Python.

