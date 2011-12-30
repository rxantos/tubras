=================
Custom Properties
=================
.. highlight:: cpp
   :linenothreshold: 5

.. toctree::
   :maxdepth: 2

Blender allows custom properties to be added to any object (scene node) and/or 
object data. **irrB** detects these custom properties and exports them to the 
corresponding Irrlicht scene node as **userData**.

Custom property types that may be added include String, Integer, Float, Vector2d,
and Vector3d. If you include the word "color" in the property name and the property
type is a Blender array, **irrB** exports the property as a "colorf" type.

.. container:: irrb-right

	.. image:: _static/img015.png 
	
Given the custom properties added to a Blender "empty" object in the example image
located to the right, **irrB** will generate the following scene node **userData**::
 
   <node type="empty">
      <attributes>
         <string name="Name" value="SpawnPoint1"/>
         <int name="Id" value="-1"/>
         <bool name="Visible" value="true"/>
         <vector3d name="Position" value="7.508336, 3.424855, 7.244886"/>
         <vector3d name="Rotation" value="0, 0, 0"/>
         <vector3d name="Scale" value="1, 1, 1"/>
         <enum name="AutomaticCulling" value="frustum_box"/>
         <bool name="DebugDataVisible" value="false"/>
         <bool name="IsDebugObject" value="false"/>
         <bool name="ReadOnlyMaterials" value="false"/>
      </attributes>
      <userData>
         <attributes>
            <string name="Test String" value="test value"/>
            <vector2d name="Test Vector2" value="1, 2"/>
            <vector3d name="Test Vector3" value="1, 2, 3"/>
            <float name="TestFloat" value="1.25"/>
            <int name="spawnPoint" value="1"/>
         </attributes>
      </userData>
   </node>

Custom properties defined at Blender's Object level will only be exported to that
specific scene node.

Custom properties defined at Blender's Object Data level, will be exported to every
scene node that references that particular data.

----

Accessing User Attributes In Code
=================================

In order to access scene node userData properties in your application, 
you will need to create a class that implements the ISceneUserDataSerializer 
interface.  This newly created class will also need to override the 
**OnReadUserData** method::

	void SerializerClass::loadScene(const c8* fileName)
	{
		//
		// ISceneManager* sceneManager (previously initialized)
		//
		// The 2nd parameter to "loadScene" is a pointer a ISceneUserDataSerializer
		// interface.
		//
		sceneManager->loadScene(fileName,this);
	}
		
	//
	// this will be invoked for every scene node that contains UserData attributes.
	//
	void SerializerClass::OnReadUserData(ISceneNode* forSceneNode,
		io::IAttributes* userData)
	{
		ESCENE_NODE_TYPE type = forSceneNode->getType();
		if(type == ESNT_EMPTY)
		{
			int isSpawnPoint=0;
			if(userData->existsAttribute("spawnPoint"))
				isSpawnPoint = userData->getAttributeAsInt("spawnPoint");
			if(isSpawnPoint)
			{
				// store off the nodes (forSceneNode) position into an array 
				// of spawn locations.
			}
		}
	}

Custom scene node properties aren't limited to just meshes. They may also be defined for lights and cameras.