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
        // sound convenience functions
        //
        TSound* loadSound(string resourceGroup,string filename);

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

        //
        // application convenience functions
        //
        virtual void logMessage(const char* msg);
        virtual bool getDebug();

        //
        // convenience functions that call back into the event manager.
        //

        /** Set up a new delegate to be called for a specific event.
        @remarks
        Delegate member functions must be of the type:
        int class::func(string eventMessage,void *extraData)

        A TEventDelegate may be created using:
        EVENT_DELEGATE(ClassName::member_function)
        */
        int acceptEvent(string eventMsg,TEventDelegate* delegate,void *userData=NULL,
            int priority=0,bool enabled=true);

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

    };

}
#endif