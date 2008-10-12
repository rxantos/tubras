#ifndef _CST_H_
#define _CST_H_

namespace CISL {

    enum ValueType {vtNone, vtFloat, vtInt, vtString};

    class CSymbol {
    private:
        irr::core::stringc  m_scope;
        irr::core::stringc  m_id;
        ValueType           m_type;
        int                 m_intValue;
        float               m_floatValue;
        irr::core::stringc  m_stringValue;

    public:
        CSymbol(irr::core::stringc id);

        irr::core::stringc getID() {return m_id;};
        ValueType   getType() {return m_type;};
        int getIntValue() {return m_intValue;};
        float getFloatValue() {return m_floatValue;};
        irr::core::stringc getStringValue() {return m_stringValue;};
    };

    class CST
    {
    public:
        CST();
        virtual ~CST();
    };
}

#endif
