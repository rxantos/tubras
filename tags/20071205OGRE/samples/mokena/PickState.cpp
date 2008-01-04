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
#include "mokena.h"


//-----------------------------------------------------------------------
//                          T P i c k S t a t e
//-----------------------------------------------------------------------
TPickState::TPickState()
{
    reset();
}

//-----------------------------------------------------------------------
//                              r e s e t
//-----------------------------------------------------------------------
void TPickState::reset()
{
    setCanPick(true);
    m_card1 = 0;
    m_card2 = 0;
    m_activeCard = 0;
    m_activeCards = 0;
}

//-----------------------------------------------------------------------
//                          s e t C a n P i c k
//-----------------------------------------------------------------------
void TPickState::setCanPick(bool value) 
{
    m_canPick = value;
    Tubras::TSEvent event;
    event.bind(new Tubras::TEvent("pickStateChanged"));
    event->addIntParameter(m_canPick);
    Tubras::getApplication()->sendEvent(event);
}


//-----------------------------------------------------------------------
//                       s e t A c t i v e C a r d
//-----------------------------------------------------------------------
int TPickState::setActiveCard(struct TCardInfo* card)
{
    ++m_activeCards;

    m_activeCard = card;
    if(!m_card1)
        m_card1 = card;
    else if(!m_card2)
        m_card2 = card;

    return m_activeCards;
}
