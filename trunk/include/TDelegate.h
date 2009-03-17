//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TDELEGATE_H_
#define _TDELEGATE_H_

namespace Tubras
{
    class TDelegate
    {
    protected:
        TDelegate*          m_instance;
        int                 m_priority;
        bool                m_enabled;

    public:
        TDelegate(TDelegate* instance) : m_instance(instance), m_priority(0), m_enabled(true) {};
        TDelegate() : m_priority(0), m_enabled(true) {m_instance = this;};
        virtual ~TDelegate() {}

        int getPriority() {return m_priority;};
        void setPriority(int value) {m_priority = value;};
        bool getEnabled() {return m_enabled;};
        void setEnabled(bool value) {m_enabled = value;};

        TDelegate* getInstance() {return m_instance;};
    };

}
#endif

