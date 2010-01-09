//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _CXMLCONFIG_H_
#define _CXMLCONFIG_H_
#include "irrMap.h"
#include "irrString.h"
#include "IAttributes.h"

namespace irr {
    namespace io {

        typedef core::map<core::stringc, irr::io::IAttributes*> TSectionMap;
        typedef core::map<core::stringc, IAttributes*>::Iterator TSectionMapItr;

        class CXMLConfig : public IReferenceCounted
        {
            TSectionMap         m_sections;

        public:
            CXMLConfig();
            virtual ~CXMLConfig();
            bool load(const core::stringc& filename);
            IAttributes* getSection(const core::stringc& name);

            core::stringc getString(const core::stringc& key, const core::stringc& section="", const core::stringc& def="");
            bool getBool(const core::stringc& key, const core::stringc& section="", const bool& def=false);
            int getInt(const core::stringc& key, const core::stringc& section="", const int& def=0);
            f32 getFloat(const core::stringc& key, const core::stringc& section="", f32 def=0.0);
            core::vector3df getVector3(const core::stringc& key, const core::stringc& section="", const core::vector3df& def=core::vector3df());
            core::vector2df getVector2(const core::stringc& key, const core::stringc& section="", const core::vector2df& def=core::vector2df());
            video::SColor getColor(const core::stringc& key, const core::stringc& section="", const video::SColor& def=video::SColor());
            core::dimension2di getDimension(const core::stringc& key, const core::stringc& section="", const core::dimension2di& def=core::dimension2di());
        };
    }
}

#endif
