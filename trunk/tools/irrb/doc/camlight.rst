Cameras and Lights
=========================
.. highlight:: cpp

.. toctree::
   :maxdepth: 2

irrB allows camera and light node data to be exported to scene files. Camera/Light node 
attributes are based on some of Blenders settings but may be overridden by assigning specific 
Blender ID Properties.

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
   
The camera specific attributes are: Target, UpVector, Fovy, Aspect, ZNear, and ZFar. 
All but the Target and UpVector may be set using the Camera properties (F9): 

Fovy. Set to (2 * atan(16.0 / (Blenders Lens -> Lens value)). May be overridden with a "float" logic property named "Fovy". 
Aspect. Set to the constant 1.25. May be overridden with a "float" logic property named "Aspect". 
ZNear. Set to Clipping -> Start value. 
ZFar. Set to Clipping -> End value. 
For now, the Target and UpVector attributes are set to (0,0,0) and (0,1,0) respectively. 

For now, the Target and UpVector attributes are set to (0,0,0) and (0,1,0) respectively. 

Light Details
-------------
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
The light specific attributes are: LightType, DiffuseColor, SpecularColor, Attenuation,
Radius, and CastShadows. 

LightType. Based on Blenders lamp type: 

* **lamp** -> Point 
* **area** -> Directional 
* **spot** -> Spot 
* **sun** -> Directional 
* **hemi** -> Directional 
  
* **AmbientColor** - Constant (0,0,0). 
* **DiffuseColor** - Set to the R,G,B components of the light color. 
* **SpecularColor** - Constant (1,1,1). 
* **Attenuation** - Set to (0.5 / (Blenders Energy Value)). 
* **Radius** - Set to (2.0 * (Blenders Distance Value)). 
* **CastShadows** - Constant "True". 

