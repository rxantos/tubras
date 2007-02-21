//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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
    enum TBodyType
    {
        btDynamic,
        btStatic,
        btKinematic
    };


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
        TSound* loadSound(TString soundFileName, TString resourceGroup="General");
        TModelNode* loadModel(TString meshFileName, TString resourceGroup="General",TString name="default", TSceneNode* parent=NULL, bool isStatic=false);
        TActorNode* loadActor(TString meshFileName, TString resourceGroup="General",TString name="default", TSceneNode* parent=NULL);

        TSceneNode* createSceneNode(TString name,TSceneNode* parent=NULL);

        TMaterial* createMaterial(TString name, TString resourceGroup);
        TMaterial* loadTexture(TString name, TString resourceGroup, TString imageName);

        void setGUICursorVisible(bool visible);
        bool getGUICursorVisible();

        //
        // task convenience functions
        //
        int removeTask(TString taskName);
        int removeTask(TTask* task);

        //
        // randomization convenience functions
        //
        int getRandomInt(int n);
        float getRandomFloat();

        virtual int initialize();


        virtual bool isKeyDown( OIS::KeyCode key );
        TState* getState(TString stateName);

        //
        // application convenience functions
        //
        virtual void logMessage(const char* msg);
        virtual bool getDebug();

        //
        // registry convenience functions
        //
        virtual int regOpenSection(TString section);
        virtual TString regReadKey(TString key, TString defaultValue);
        virtual int regReadKey(TString key, int defaultValue);
        virtual int regWriteKey(TString key,TString value);
        virtual int regWriteKey(TString key,int value);
        virtual bool regKeyExists(TString section, TString key);
        virtual bool regKeyExists(TString key);

        //
        // event convenience functions 
        //

        /** accept an event.
        */
        size_t acceptEvent(TString eventMsg,TEventDelegate* delegate,void *userData=NULL,
            int priority=0,bool enabled=true);

        size_t registerEvent(TString eventName);

        int disableEvents(void* classInstance);
        int enableEvents(void* classInstance);

        void setControllerEnabled(TString controllerName, bool value);
        void setNodeControllersEnabled(TString nodeName, bool value);
        virtual TController* getController(TString controllerName);

        /** remove a delegate. does delete the delegate.
        */
        int removeEventDelegate(TEventDelegate* callback);

        /** destroy a delegate.
        */
        int destroyEventDelegate(TEventDelegate* callback);

        /** destroy an interval
        */
        int destroyInterval(TInterval* interval);

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
        TString setEventPrefix(TString value);

        TRenderEngine* getRenderEngine();
        TSceneManager* getSceneManager();
        TDynamicWorld* getDynamicWorld();
        TCameraNode* getCamera(TString name);
        TThemeManager* getThemeManager();


    };

}
#endif