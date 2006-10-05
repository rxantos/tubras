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

#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       T E v e n t H a n d l e r
    //-----------------------------------------------------------------------
    TEventHandler::TEventHandler() : TObject()
    {
    }

    //-----------------------------------------------------------------------
    //                       ~T E v e n t H a n d l e r
    //-----------------------------------------------------------------------
    TEventHandler::~TEventHandler()
    {

    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TEventHandler::initialize()
    {
        return TObject::initialize();
    }

    //-----------------------------------------------------------------------
    //                        a c c e p t E v e n t
    //-----------------------------------------------------------------------
    int TEventHandler::acceptEvent(string eventMsg,TEventDelegate* callback,void *extraData,
        int priority,bool enabled)
    {
        if(getEventManager())
            getEventManager()->accept(eventMsg,callback,extraData,priority,enabled);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                 r e m o v e E v e n t D e l e g a t e
    //-----------------------------------------------------------------------
    int TEventHandler::removeEventDelegate(TEventDelegate* callback)
    {
        if(getEventManager())
            getEventManager()->remove(callback);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                 d e s t r o y E v e n t D e l e g a t e
    //-----------------------------------------------------------------------
    int TEventHandler::destroyEventDelegate(TEventDelegate* callback)
    {
        if(getEventManager())
            getEventManager()->destroy(callback);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                         s e n d E v e n t
    //-----------------------------------------------------------------------
    int TEventHandler::sendEvent(TSEvent& event)
    {
        if(getEventManager())
            return getEventManager()->send(event);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                        q u e u e E v e n t
    //-----------------------------------------------------------------------
    int TEventHandler::queueEvent(TSEvent& event)
    {
        if(getEventManager())
            return getEventManager()->queue(event);
        return 0;
    }
    //-----------------------------------------------------------------------
    //                      s e t E v e n t P r e f i x 
    //-----------------------------------------------------------------------
    string TEventHandler::setEventPrefix(string value)
    {
        if(getEventManager())
            return getEventManager()->setEventPrefix(value);
        return "";
    }

    //-----------------------------------------------------------------------
    //             s e t E v e n t D e l e g a t e P r i o r i t y
    //-----------------------------------------------------------------------
    int TEventHandler::setEventDelegatePriority(TEventDelegate* callback, int priority)
    {
        callback->setPriority(priority);
        //
        // todo: notify event manager - priority update
        //
        return 0;
    }

    //-----------------------------------------------------------------------
    //             s e t E v e n t D e l e g a t e E n a b l e d
    //-----------------------------------------------------------------------
    int TEventHandler::setEventDelegateEnabled(TEventDelegate* callback, bool enabled)
    {
        callback->setEnabled(enabled);
        return 0;
    }




}