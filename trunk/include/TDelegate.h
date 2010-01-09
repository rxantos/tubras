//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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

    public:
        TDelegate(TDelegate* instance) : m_instance(instance), m_priority(0) {};
        TDelegate() : m_priority(0) {m_instance = this;};
        virtual ~TDelegate() {}

        int getPriority() {return m_priority;};
        void setPriority(int value) {m_priority = value;};

        TDelegate* getInstance() {return m_instance;};
    };

}
#endif

