Cameras and Lights
=========================
.. highlight:: cpp

.. toctree::
   :maxdepth: 2

**irrB** allows camera and light node data to be exported to scene files. Camera
and light data is only exported when the corresponding is selected in **irrB**'s
export sub-panel.

.. container:: irrb-right

	.. image:: _static/img017.png 

Irrlicht camera and light specific properties may be set in **irrB**'s object
sub-panel.  

Camera Details 
--------------

A camera node in a .irr scene file will appear as follows::

   <node type="camera">
      <attributes>
         <string name="Name" value="Camera" />
         <int name="Id" value="-1" />
         <vector3d name="Position" value="7.481132, 5.343665, -6.507640" />
         <vector3d name="Rotation" value="26.440704, -46.691944, 0.000000" />
         <vector3d name="Scale" value="1.000000, 1.000000, 1.000000" />
         <bool name="Visible" value="true" />
         <enum name="AutomaticCulling" value="frustum_box" />
         <bool name="DebugDataVisible" value="false" />
         <bool name="IsDebugObject" value="false" />
         <bool name="ReadOnlyMaterials" value="false" />
         <vector3d name="Target" value="0.000000, 0.000000, 0.000000" />
         <vector3d name="UpVector" value="0.000000, 1.000000, 0.000000" />
         <float name="Fovy" value="0.857556" />
         <float name="Aspect" value="1.250000" />
         <float name="ZNear" value="0.10" />
         <float name="ZFar" value="100.00" />
      </attributes>
   </node>
   
Light Details
-------------

.. container:: irrb-right

	.. image:: _static/img018.png 

A light node in a .irr scene file will appear as follows::

   <node type="light">
      <attributes>
         <string name="Name" value="Lamp" />
         <int name="Id" value="-1" />
         <vector3d name="Position" value="4.076245, 5.903862, 1.005454" />
         <vector3d name="Rotation" value="52.738953, -16.936317, 0.000000" />
         <vector3d name="Scale" value="1.000000, 1.000000, 1.000000" />
         <bool name="Visible" value="true" />
         <enum name="AutomaticCulling" value="frustum_box" />
         <bool name="DebugDataVisible" value="false" />
         <bool name="IsDebugObject" value="false" />
         <bool name="ReadOnlyMaterials" value="false" />
         <enum name="LightType" value="Point" />
         <colorf name="AmbientColor" value="0.000000,0.000000, 0.000000, 1.000000" />
         <colorf name="DiffuseColor" value="1.000000, 1.000000, 1.000000 1.000000" />
         <colorf name="SpecularColor" value="1.000000,1.000000, 1.000000, 1.000000" />
         <vector3d name="Attenuation" value="0.000000 0.500000 0.000000" />
         <float name="Radius" value="60.00" />
         <bool name="CastShadows" value="true" />
      </attributes>
   </node>
   