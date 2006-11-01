//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TOBJECT_H_
#define _TOBJECT_H_

namespace Tubras
{

    class TApplication;
    class TSound;
    class TTimer;
    class TSceneNode;
    class TModelNode;
    class TSound;
    class TMaterial;
    class TRenderEngine;
    class TController;
    class TDynamicWorld;

    typedef fd::delegate<int (class TTask*)> TTaskDelegate;

    class TObject
    {
    protected:
        TApplication*           m_app;
        TTimer*                 m_globalClock;
    public:
        TObject();
        virtual ~TObject();
        //
        // loader convenience functions
        //
        TSound* loadSound(string resourceGroup,string filename);
        TModelNode* loadModel(string name, string resourceGroup, string filename, TSceneNode* parent, bool isStatic=false);

        TSceneNode* createSceneNode(string name,TSceneNode* parent=NULL);

        TMaterial* createMaterial(string name, string resourceGroup);
        TMaterial* loadTexture(string name, string resourceGroup, string imageName);

        //
        // task convenience functions
        //
        int removeTask(string taskName);
        int removeTask(TTask* task);

        //
        // randomization convenience functions
        //
        int getRandomInt(int n);
        float getRandomFloat();

        virtual int initialize();


		virtual bool isKeyDown( OIS::KeyCode key );

        //
        // application convenience functions
        //
        virtual void logMessage(const char* msg);
        virtual bool getDebug();

        //
        // event convenience functions 
        //

        /** accept an event.
        */
        size_t acceptEvent(string eventMsg,TEventDelegate* delegate,void *userData=NULL,
            int priority=0,bool enabled=true);

        size_t registerEvent(string eventName);

        int disableEvents(void* classInstance);
        int enableEvents(void* classInstance);

        void setControllerEnabled(string controllerName, bool value);
        void setNodeControllersEnabled(string nodeName, bool value);
        virtual TController* getController(string controllerName);

        /** remove a delegate. does delete the delegate.
        */
        int removeEventDelegate(TEventDelegate* callback);

        /** destroy a delegate.
        */
        int destroyEventDelegate(TEventDelegate* callback);

        /** Sends an event to be processed by listening delegates.
        */
        int sendEvent(TSEvent& event);

        /** Queues an event to be processed by listening delegates.
        */
        int queueEvent(TSEvent& event);

        /** Sets an event delegates priority
        */
        int setEventDelegatePriority(TEventDelegate* callback, int priority);

        /** Enable/Disable an event delegate
        */
        int setEventDelegateEnabled(TEventDelegate* callback, bool enabled);

        /** Set a temporary prefix that is prepended to all events.
        @remarks
        In order to reset, call again with a value of ("").
        */
        string setEventPrefix(string value);

        TRenderEngine* getRenderEngine();
        TSceneManager* getSceneManager();
        TDynamicWorld* getDynamicWorld();
		TCameraNode* getCamera(string name);


    };

}
#endif