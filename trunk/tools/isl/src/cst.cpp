//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "cislParser.h"

namespace isl
{

    //-------------------------------------------------------------------------
    //                               C S y m b o l
    //-------------------------------------------------------------------------
    CSymbol::CSymbol(irr::core::stringc scope, irr::core::stringc id, SymbolType type, 
        irr::core::stringc iParent, irr::core::stringc file, irr::u32 line, 
        irr::u32 pos)

    {
        m_scope = scope;
        m_id = id;
        if(m_scope.size() > 0)
            m_scopedID = m_scope + "." + id;
        else m_scopedID = id;
        m_iParent = iParent;
        m_value.rSymbol = this;
        m_value.rType = type;
        m_value.rUserData = 0;
        m_file = file;
        m_line = line;
        m_pos = pos;

    }


    //-------------------------------------------------------------------------
    //                                  C S T
    //-------------------------------------------------------------------------
    CST::CST()
    {
    }


    //-------------------------------------------------------------------------
    //                            f r e e T u p l e
    //-------------------------------------------------------------------------
    void freeTuple(EvalResult* er)
    {
        for(irr::u32 i=0; i< er->rTupleItems.size(); i++)
        {
            EvalResult* ter = er->rTupleItems[i];

            if(ter->rType == stTuple)
                freeTuple(ter);

            delete ter;
        }
    }

    //-------------------------------------------------------------------------
    //                                 ~ C S T
    //-------------------------------------------------------------------------
    CST::~CST()
    {
        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            EvalResult* er = symbol->getValue();
            if(er->rType == stTuple)
            {
                freeTuple(er);

            }
            delete symbol;
        }
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
            printf("ID=%s, SCOPE=%s, TYPE=", 
                symbol->getID().c_str(),
                symbol->getScope().c_str());
            switch(symbol->getType())
            {
            case stUndefined: 
                printf("undefined"); 
                break;
            case stFloat: 
                printf("float, VALUE=%f", symbol->getValue()->rFloat); 
                break;
            case stInt:
                printf("int, VALUE=%d", symbol->getValue()->rInteger); 
                break;
            case stString:
                printf("string, VALUE=\"%s\"", symbol->getValue()->rString.c_str()); 
                break;
            case stBool:
                printf("bool, VALUE=%s", symbol->getValue()->rBool ? "true" : "false"); 
                break;
            case stTuple:
                printf("tuple, ITEMS=%d", symbol->getValue()->rTupleItems.size()); 
                break;
            case stMaterial: 
                printf("material"); 
                break;
            case stConfig:
                printf("config"); 
                break;
            case stMatrix: 
                printf("matrix"); 
                break;
            case stLayer: 
                printf("layer"); 
                break;
            case stGUIElement:
                printf("guielement");
                break;
            case stParticle:
                printf("particle");
                break;
            default:
                printf("?? unknown ??");
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
    int CST::addSymbol(irr::core::stringc id, SymbolType type, irr::core::stringc iparent,
                    irr::core::stringc file, irr::u32 line, irr::u32 pos)
    {
        irr::core::stringc scope = _getScope();
        irr::core::stringc mid=id, sid;

        // id may contain scope as well
        if(id.find(".") >= 0)
        {
            sid = id;
            int pos;
            while((pos=sid.find(".")) >= 0)
            {
                if(scope.size())
                    scope += ".";
                scope += sid.subString(0,pos);
                sid = sid.subString(pos+1,sid.size());
            }   
            id = sid;
        }

        if(scope.size())
            mid  =  scope + "." + id;

        SYMMAP::Node* node = m_symbols.find(mid);
        if(node)
            return 1;

        CSymbol* symbol = new CSymbol(scope, id, type, iparent, file, line, pos+1);

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
    //                               s e t I P a r e n t
    //-------------------------------------------------------------------------
    int CST::setIParent(irr::core::stringc id, irr::core::stringc iparent)
    {
        SYMMAP::Node* node = m_symbols.find(id);
        if(!node)
            return 1;

        CSymbol* symbol = node->getValue();
        symbol->setIParent(iparent);

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
    //                         g e t C h i l d r e n 
    //-------------------------------------------------------------------------
    int CST::getChildren(CSymbol* parent, SYMMAP& children) 
    {
        irr::core::stringc pid = parent->getScopedID();
        pid += ".";
        irr::u32 len = pid.size();
        const irr::c8 *cpid = pid.c_str();

        if(parent->getChildCount() > 0)
            return 0;

        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            if(symbol == parent)
                continue;

            if(!strnicmp(cpid, symbol->getScope().c_str(), len))
            {
                children[symbol->getScopedID()] = symbol;
            }
        }       
        return 0;
    }
    //-------------------------------------------------------------------------
    //                       _ g a t h e r C h i l d r e n
    //-------------------------------------------------------------------------
    int CST::gatherChildren(CSymbol* parent) 
    {
      irr::core::stringc pid = parent->getScopedID();

        for ( SYMMAP::Iterator itr = m_symbols.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            if(symbol == parent)
                continue;
            if(pid == symbol->getScope())
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
                        gatherChildren(symbol);
                    }
                }
            }
        }

        return out.size();
    }
}
