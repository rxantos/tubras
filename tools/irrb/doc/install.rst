============
Installation
============

.. toctree::
   :maxdepth: 2

The latest stable download of **irrB** is accessible from both the "Project Home" 
and "Downloads" tabs of the `Tubras Google Code project <http://code.google.com/p/tubras/>`_. On the "Project Home" 
tab, **irrB** is listed in the "Featured Downloads" section.

The current version may be downloaded from here: http://tubras.googlecode.com/files/irrb-0.6.zip

.. container:: irrb-right

	.. image:: _static/img001.png 

The contents of the zip package are: 

* io_export_irrlicht.py
* docs/{html documentation files}

To install **irrB**, unzip the contents of the zip file into a temporary directory 
and install it as a Blender **addon**.

1. Start Blender and call up the **User Preferences** dialog (File | User Preferences..).  
2. Click on the **Addons** tab and then the **Install Addon...** button located at 
   the bottom of the dialog.
3. Navigate to the directory where you previously unzipped the **irrB** zip file into, select 
   the file **io_export_irrlicht.py**, and then click the **Install Addon...** button. 
4. Locate the **irrB** exporter in the **Import-Export** section and enable it by selecting 
   the corresponding check box. 

If you would like **irrB** to be automatically activated every time you start Blender, 
then click the **Save As Default** button located at the bottom of the dialog. 
If you don't click **Save As Default**, you will to need activate the **irrB** add-on
each time you start up Blender. 

Documentation on installing and configuring "iwalktest" for both Windows and Linux 
may be found in the section named :doc:`irrB Utilities </utilities>`.

Requirements
============

* Blender - Supported Blender Versions are 2.61+
* Python - **irrB** uses Blender's internal version of Python 3.x so you are not required to install Python.
