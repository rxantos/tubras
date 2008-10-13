#ifndef _CST_H_
#define _CST_H_

namespace CISL {
    enum SymbolType {stUndefined, stFloat, stInt, stString, stBool, stList,
    stColor, stMaterial, stConfig};

    class CSymbol;

    typedef irr::core::map<irr::core::stringc, CSymbol*> SYMMAP;
    typedef irr::core::array<irr::core::stringc> STACK;

    class CSymbol {
    private:
        irr::core::stringc  m_scope;
        irr::core::stringc  m_id;
        SymbolType          m_type;
        void*               m_value;
        int                 m_intValue;
        float               m_floatValue;
        irr::core::stringc  m_stringValue;

    public:
        CSymbol(irr::core::stringc id, SymbolType type)
        {
            m_id = id;
            m_type = type;
        }

        irr::core::stringc getID() {return m_id;}
        SymbolType getType() {return m_type;}
        void* getValue() {return m_value;}
    };

    class CST
    {
    private:
        SYMMAP              m_symbols;
        STACK               m_nameSpace;

    protected:
        irr::core::stringc _getSpaceID(irr::core::stringc id);

    public:
        CST();
        virtual ~CST();
        int reset() {};
        void print();
        int addSymbol(irr::core::stringc id, SymbolType type=stUndefined,
            char* value=0);
        irr::core::stringc pushSpace(irr::core::stringc id);
        irr::core::stringc popSpace();
    };
}

#endif
