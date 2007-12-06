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

#ifndef _TXMLCONFIG_H_
#define _TXMLCONFIG_H_

namespace Tubras
{
    typedef TMap<TString, IAttributes*> TSections;
    typedef TMap<TString, IAttributes*>::Iterator TSectionsItr;

    class TXMLConfig : public IReferenceCounted
    {
        TSections       m_sections;

    public:
        TXMLConfig();
        virtual ~TXMLConfig();
        bool load(TString filename);
        IAttributes* getSection(TString name);

        TString getString(TString key, TString section="", TString def="");
        bool getBool(TString key, TString section="", bool def=false);
        int getInt(TString key, TString section="", int def=0);
        f32 getFloat(TString key, TString section="", f32 def=0.0);
        TVector3 getVector3(TString key, TString section="", TVector3 def=TVector3());
        TVector2 getVector2(TString key, TString section="", TVector2 def=TVector2());
        TColour getColour(TString key, TString section="", TColour def=TColour());
        TDimension getDimension(TString key, TString section="", TDimension def=TDimension());
    };

}
#endif
