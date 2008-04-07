//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TXMLCONFIG_H_
#define _TXMLCONFIG_H_

namespace Tubras
{
    typedef TMap<TString, IAttributes*> TSections;
    typedef TMap<TString, IAttributes*>::Iterator TSectionsItr;

    class TXMLConfig : public IReferenceCounted
    {
    private:
        TSections       m_sections;
        IrrlichtDevice* m_device;

    public:
        TXMLConfig(IrrlichtDevice* device=0);
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
        TRectd getRectd(const TString& key, const TString& section="",const TRectd& def=TRectd());
    };

}
#endif
