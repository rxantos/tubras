===
Fog
===

.. toctree::
   :maxdepth: 2

**irrB** allows you to add fog to you Irrlicht scene using Blender's Mist settings.

.. container:: irrb-left

	.. image:: _static/img023.png
	
Blender's Mist settings are located in the World panel and are translated to 
Irrlicht Fog settings as follows:

+------------------------------+---------------------------+   
| Blender                      | Irrlicht                  |
+==============================+===========================+
| Horizon Color                | Fog Color                 |
+------------------------------+---------------------------+   
| Minimum                      | Density                   |
+------------------------------+---------------------------+   
| Start                        | Start                     |
+------------------------------+---------------------------+   
| Depth                        | End                       |
+------------------------------+---------------------------+   
| Height                       | Exported but not used     |
+------------------------------+---------------------------+   
| Falloff - Quadratic, Linear, | EFT_FOG_EXP, EFT_FOG_LIN, |
| Inverse Quadratic.           | EFT_FLOG_EXP2             |
+------------------------------+---------------------------+   

In addition to the "global" fog settings, fog may also be enabled/disabled at 
the material level. If global fog (mist) is enabled and a material's fog setting
is disabled, then that particular material will not be rendered with fog.

.. container:: irrb-left

	.. figure:: _static/img029.png

		Sample Fog .blend file - `08-Fog.blend <http://tubras.googlecode.com/svn/trunk/tools/blendfiles/26/08-Fog.blend>`_

