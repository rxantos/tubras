//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
        bool load(const TString& filename);
        IAttributes* getSection(const TString& name);

        TString getString(const TString& key, const TString& section="", const TString& def="");
        bool getBool(const TString& key, const TString& section="", const bool& def=false);
        int getInt(const TString& key, const TString& section="", const int& def=0);
        f32 getFloat(const TString& key, const TString& section="", f32 def=0.0);
        TVector3 getVector3(const TString& key, const TString& section="", const TVector3& def=TVector3());
        TVector2 getVector2(const TString& key, const TString& section="", const TVector2& def=TVector2());
        TColour getColour(const TString& key, const TString& section="", const TColour& def=TColour());
        TDimension getDimension(const TString& key, const TString& section="", const TDimension& def=TDimension());
    };

}
#endif
