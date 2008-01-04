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
//                          T H i g h S c o r e
//-----------------------------------------------------------------------
THighScore::THighScore()
{
}

//-----------------------------------------------------------------------
//                         ~ T H i g h S c o r e
//-----------------------------------------------------------------------
THighScore::~THighScore()
{
}

//-----------------------------------------------------------------------
//                      g e t S i n g l e t o n 
//-----------------------------------------------------------------------
template<> THighScore* Tubras::TSingleton<THighScore>::ms_Singleton = 0;
THighScore& THighScore::getSingleton(void)
{
    assert( ms_Singleton );  return ( *ms_Singleton );
}

//-----------------------------------------------------------------------
//                   g e t S i n g l e t o n P t r
//-----------------------------------------------------------------------
THighScore* THighScore::getSingletonPtr(void)
{
    return ms_Singleton;
}
