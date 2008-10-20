#include "cisl.h"

namespace CISL
{

    //-------------------------------------------------------------------------
    //                               C S y m b o l
    //-------------------------------------------------------------------------
    CSymbol::CSymbol(irr::core::stringc scope, irr::core::stringc id, SymbolType type, irr::core::stringc iParent)
    {
        m_scope = scope;
        m_id = id;
        if(m_scope.size() > 0)
            m_scopedID = m_scope + "." + id;
        else m_scopedID = id;
        m_iParent = iParent;
        m_value.rType = type;
        m_userData = 0;
    }


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
        printf("CST Symbol Table:\n");
        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("Symbol Scope='%s', ID=%s, type=", symbol->getScope().c_str(),
                symbol->getID().c_str());
            switch(symbol->getType())
            {
            case stUndefined: 
                printf("undefined"); 
                break;
            case stFloat: 
                printf("float, value=%f", symbol->getValue()->rFloat); 
                break;
            case stInt:
                printf("int, int=%d", symbol->getValue()->rInteger); 
                break;
            case stString:
                printf("string, string=\"%s\"", symbol->getValue()->rString.c_str()); 
                break;
            case stBool:
                printf("bool, bool=%s", symbol->getValue()->rBool ? "true" : "false"); 
                break;
            case stList:
                printf("list"); 
                break;
            case stMaterial: 
                printf("material"); 
                break;
            case stConfig:
                printf("config"); 
                break;
            }

            if(symbol->getIParent().size())
            {
                printf(", iParent=%s", symbol->getIParent().c_str());
            }
            printf("\n");
        }
        printf("\n");
    }

    //-------------------------------------------------------------------------
    //                            _ g e t S p a c e I D
    //-------------------------------------------------------------------------
    irr::core::stringc CST::_getScope()
    {
        irr::core::stringc result="";
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            if(i>0)
                result += ".";
            result += m_nameSpace[i];
        }
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
    int CST::addSymbol(irr::core::stringc id, SymbolType type, irr::core::stringc iparent)
    {
        irr::core::stringc scope = _getScope();
        irr::core::stringc mid;
        
        if(scope.size() > 0)
            mid = scope + "." + id;
        else mid = id;

        SYMMAP::Node* node = m_symbols.find(mid);
        if(node)
            return 1;

        CSymbol* symbol = new CSymbol(scope, id, type, iparent);

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
    //                            g e t S y m b o l
    //-------------------------------------------------------------------------
    CSymbol* CST::getSymbol(irr::core::stringc scopedID)
    {
        SYMMAP::Node* node = m_symbols.find(scopedID);
        if(!node)
            return 0;        

        return node->getValue();
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

    //-------------------------------------------------------------------------
    //                       _ g a t h e r C h i l d r e n
    //-------------------------------------------------------------------------
    int CST::_gatherChildren(CSymbol* parent) 
    {
        irr::core::stringc pid = parent->getScopedID();
        irr::s32 firstDot;
        irr::u32 plen;

        if(firstDot = pid.findFirstChar(".", pid.size())) 
        {
            pid = pid.subString(0, firstDot);
        }
        pid += ".";
        plen = pid.size();

        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            if(symbol == parent)
                continue;
            if(pid.equalsn(symbol->getScopedID(),plen))
            {
                parent->addChild(symbol);

            }
        }       
        return 0;
    }

    //-------------------------------------------------------------------------
    //                         g e t D e f i n i t i o n s
    //-------------------------------------------------------------------------
    int CST::getDefinitions(SymbolType type, SYMMAP& out)
    {
        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            if(symbol->getType() == type)
            {
                out[symbol->getScopedID()] = symbol;
                if(type > stObjectStart)
                {
                    if(!symbol->getChildCount())
                    {
                        _gatherChildren(symbol);
                    }
                }
            }
        }
       
        return out.size();
    }


}