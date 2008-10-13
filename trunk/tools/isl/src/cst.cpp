#include "cisl.h"

namespace CISL
{
    //-------------------------------------------------------------------------
    //                                  C S T
    //-------------------------------------------------------------------------
    CST::CST()
    {

    }

    //-------------------------------------------------------------------------
    //                                 ~ C S T
    //-------------------------------------------------------------------------
    CST::~CST()
    {

    }

    //-------------------------------------------------------------------------
    //                                 p r i n t
    //-------------------------------------------------------------------------
    void CST::print()
    {
        printf("\nCST Symbol Table:\n");
        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("Symbol ID=%s, type=", symbol->getID().c_str());
            switch(symbol->getType())
            {
            case stUndefined: 
                printf("undefined"); break;
            case stFloat: 
                printf("float, value=%f", symbol->getValue()->rFloat); break;
            case stInt:
                printf("int, int=%d", symbol->getValue()->rInteger); break;
            case stString:
                printf("string"); break;
            case stBool:
                printf("bool"); break;
            case stList:
                printf("list"); break;
            case stColor:
                printf("color"); break;
            case stMaterial: 
                printf("material"); break;
            case stConfig:
                printf("config"); break;
            }
            printf("\n");
        }
        printf("\n");
    }

    //-------------------------------------------------------------------------
    //                            _ g e t S p a c e I D
    //-------------------------------------------------------------------------
    irr::core::stringc CST::_getSpaceID(irr::core::stringc id)
    {
        irr::core::stringc result="";
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }
        result += id;
        return result;
    }

    //-------------------------------------------------------------------------
    //                             p u s h S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CST::pushSpace(irr::core::stringc name)
    {
        irr::core::stringc result="";

        m_nameSpace.push_back(name);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                              p o p S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CST::popSpace()
    {
        irr::core::stringc result="";
        irr::u32 idx = m_nameSpace.size();
        if(!idx)
            return result;

        m_nameSpace.erase(idx-1);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            result += (m_nameSpace[i] + ".");
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                               i d E x i s t s
    //-------------------------------------------------------------------------
    bool CST::idExists(irr::core::stringc id)
    {
        return m_symbols.find(id) != 0 ? true : false;
    }

    //-------------------------------------------------------------------------
    //                               a d d S y m b o l
    //-------------------------------------------------------------------------
    int CST::addSymbol(irr::core::stringc id, SymbolType type)
    {
        irr::core::stringc mid = _getSpaceID(id);

        SYMMAP::Node* node = m_symbols.find(mid);
        if(node)
            return 1;

        CSymbol* symbol = new CSymbol(mid);
        m_symbols[mid] = symbol;

        return 0;
    }

    //-------------------------------------------------------------------------
    //                               s e t V a l u e
    //-------------------------------------------------------------------------
    int CST::setValue(irr::core::stringc id, EvalResult* pr)
    {
        SYMMAP::Node* node = m_symbols.find(id);
        if(!node)
            return 1;

        CSymbol* symbol = node->getValue();
        symbol->setValue(pr);

        return 0;
    }

    //-------------------------------------------------------------------------
    //                               g e t V a l u e
    //-------------------------------------------------------------------------
    EvalResult* CST::getValue(irr::core::stringc id)
    {
        SYMMAP::Node* node = m_symbols.find(id);
        if(!node)
            return 0;

        CSymbol* symbol = node->getValue();
        return symbol->getValue();
    }

}