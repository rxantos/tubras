//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "CISLParser.h"
#include <errno.h>

namespace irr
{
namespace core
{
	const matrix4 IdentityMatrix(matrix4::EM4CONST_IDENTITY);
}
}

namespace CISL
{
    static char* MATVARS[] =
    { 
        "type", "ambient", "diffuse", "emissive", "specular", "shininess",
        "parm1", "parm2", "thickness", "gouraud", "lighting", "zwriteenable",
        "backfaceculling", "frontfaceculling", "fogenable","normalizenormals",
        "zbuffer", "layer1", "layer2", "layer3", "layer4", "layers", 0
    };

    static char* LAYVARS[] = 
    {
        "texture", "clampmode", "bilinear", "trilinear", "anisotropic",
        "transform", "scale", "offset", "rotation", "center", 0
    };

    static char* MTXVARS[] =
    {
        "r", "t", "s", 0
    };

    static const irr::core::matrix4 IdentityMatrix(irr::core::matrix4::EM4CONST_IDENTITY);

    void islRecognitionError	    (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);

    //-------------------------------------------------------------------------
    //                                  C I S L
    //-------------------------------------------------------------------------
    CISLParser::CISLParser() : m_fileName(0),
        m_inputStream(0),
        m_lexer(0),
        m_tokenStream(0),
        m_parser(0),
        m_treeNodes(0),
        m_unNamed(0),
        m_st(0)
    {
    }

    //-------------------------------------------------------------------------
    //                                 ~ C I S L
    //-------------------------------------------------------------------------
    CISLParser::~CISLParser()
    {
        _freeResources();
    }

    //-------------------------------------------------------------------------
    //                          _ f r e e R e s o u r c e s
    //-------------------------------------------------------------------------
    void CISLParser::_freeResources()
    {
        if(m_st)
        {
            delete m_st;
            m_st = 0;
        }

        if(m_treeNodes)
        {
            m_treeNodes->free(m_treeNodes);
            m_treeNodes = 0;
        }

        if(m_parser)
        {
            m_parser->free(m_parser);      
            m_parser = 0;
        }

        if(m_tokenStream)
        {
            m_tokenStream ->free  (m_tokenStream);  
            m_tokenStream = 0;
        }
        if(m_lexer)
        {
            m_lexer->free(m_lexer);      
            m_lexer = 0;
        }
        if(m_inputStream)
        {
            m_inputStream->close (m_inputStream);    
            m_inputStream = 0;
        }
        m_unNamed = 0;

    }

    //-------------------------------------------------------------------------
    //                         f i l e E x i s t s
    //-------------------------------------------------------------------------
    bool fileExists(const irr::core::stringc fileName)
    {
        struct stat buf;
        if(stat(fileName.c_str(),&buf) != 0)
        {
            if(errno == ENOENT)
            {
                return false;
            }
        }
        return true;
    }

    //-------------------------------------------------------------------------
    //                             d o I n c l u d e
    //-------------------------------------------------------------------------
    void* CISLParser::doInclude(char* filename)
    {
        irr::core::stringc fname = _extractString(filename);
        // need to track these to free them later...
        if(fileExists(fname))
        {

            return antlr3AsciiFileStreamNew((pANTLR3_UINT8)fname.c_str());
        }

        irr::core::stringc afilename="";
        for(irr::u32 i=0; i<m_incDirs.size(); i++)
        {
            afilename = m_incDirs[i] + fname;
            if(fileExists(afilename))
                return antlr3AsciiFileStreamNew((pANTLR3_UINT8)afilename.c_str());
        }



        return 0;
    }

    //-------------------------------------------------------------------------
    //                       a p p e n d I n c l u d e D i r s
    //-------------------------------------------------------------------------
    void CISLParser::appendIncludeDirs(irr::core::stringc dirs, char sep)
    {
        int idx,s=0,e,end=dirs.size();
        irr::core::stringc dir="";

        for(idx=0;idx<end;idx++)
        {
            if(dirs[idx] == sep)
            {
                dir = dirs.subString(s,idx);
                m_incDirs.push_back(dir);
                s = idx;
            }
        }
        dir = dirs.subString(s,end);
        m_incDirs.push_back(dir);
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-------------------------------------------------------------------------
    const irr::video::SMaterial* CISLParser::getMaterial(const irr::video::IVideoDriver* videoDriver,
        const irr::core::stringc varName)
    {
        irr::video::SMaterial* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor* CISLParser::getColor(const irr::core::stringc varName)
    {
        irr::video::SColor*  result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t F l o a t
    //-------------------------------------------------------------------------
    float CISLParser::getFloat(const irr::core::stringc varName)
    {
        float result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                              g e t I n t
    //-------------------------------------------------------------------------
    int CISLParser::getInt(const irr::core::stringc varName)
    {
        int result=0;
        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t S t r i n g
    //-------------------------------------------------------------------------
    const irr::core::stringc CISLParser::getString(const irr::core::stringc varName)
    {
        irr::core::stringc result="";

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t L i s t
    //-------------------------------------------------------------------------
    const void* CISLParser::getList(const irr::core::stringc varName)
    {
        void* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_extractDir(irr::core::stringc filename)
    {
        irr::core::stringc result="";
        // find last forward or backslash
        irr::s32 lastSlash = filename.findLast('/');
        const irr::s32 lastBackSlash = filename.findLast('\\');
        lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

        if ((irr::u32)lastSlash < filename.size())
            return filename.subString(0, lastSlash+1);
        else
            return ".";
    }

    //-------------------------------------------------------------------------
    //                            _ d u m p T r e e 
    //-------------------------------------------------------------------------
    void CISLParser::_dumpTree(pANTLR3_BASE_TREE tree)
    {
        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";


        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);
            tabs = "";
            for(int i=0;i < level; i++)
                tabs += "\t";

            switch(token->type)
            {
            case ASSIGN:
                printf("%sASSIGN (%s)\n", tabs.c_str(), string->chars );
                break;
            case NAME:
                printf("%sNAME (%s)\n", tabs.c_str(), string->chars);
                break;
            case ADD:
                printf("%sADD (%s)\n", tabs.c_str(), string->chars);
                break;
            case SUB:
                printf("%sSUB (%s)\n", tabs.c_str(), string->chars);
                break;
            case MUL:
                printf("%sMUL (%s)\n", tabs.c_str(), string->chars);
                break;
            case DIV:
                printf("%sDIV (%s)\n", tabs.c_str(), string->chars);
                break;
            case INTEGER:
                printf("%sINTEGER (%s)\n", tabs.c_str(), string->chars);
                break;
            case FLOAT:
                printf("%sFLOAT (%s)\n", tabs.c_str(), string->chars);
                break;

            case HEX:
                printf("%sHEX (%s)\n", tabs.c_str(), string->chars);
                break;

            case BOOLLITERAL:
                printf("%sBOOL (%s)\n", tabs.c_str(), string->chars);
                break;

            case STRING:
                printf("%sSTRING (%s)\n", tabs.c_str(), string->chars);
                break;
            case TUPLE:
                printf("%sTUPLE (%s)\n", tabs.c_str(), string->chars);
                break;
            case MATDEF:
                printf("%sMATDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case CNFDEF:
                printf("%sCNFDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case MTXDEF:
                printf("%sMTXDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case LAYDEF:
                printf("%sLAYDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case INHERIT:
                printf("%sINHERIT (%s)\n", tabs.c_str(), string->chars);
                break;
            case DOT:
                printf("%sDOT (%s)\n", tabs.c_str(), string->chars);
                break;
            case SDEF:
                ++level;
                break;
            case EDEF:
                --level;
                break;
            default:
                printf("%sUNKNOWN TOKEN: %d (%s)\n", tabs.c_str(), token->type, string->chars);
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return;
        }

        /* Need a new string with nothing at all in it.
        */
        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);

                ++level;
                _dumpTree(t);
                --level;
            }
        }
        return;
    }

    //-------------------------------------------------------------------------
    //                         _ d u m p O b j e c t s
    //-------------------------------------------------------------------------
    void CISLParser::_dumpObjects()
    {
        printf("Object Counts:\n");
        printf("\nMaterials: %d\n", m_matDefs.size());
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }

        printf("\nLayers: %d\n", m_layDefs.size());
        for ( SYMMAP::Iterator itr = m_layDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }

        printf("\nMatrices: %d\n", m_mtxDefs.size());
        for ( SYMMAP::Iterator itr = m_mtxDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }

        printf("\nConfigs: %d\n", m_cnfDefs.size());
        for ( SYMMAP::Iterator itr = m_cnfDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            printf("    ID: %s, child count: %d\n", symbol->getScopedID().c_str(), symbol->getChildren().size());
        }
    }

    //-------------------------------------------------------------------------
    //                         _ s t a r t D E F S y m 
    //-------------------------------------------------------------------------
    int CISLParser::_startDEFSym(pANTLR3_BASE_TREE tree, SymbolType type)
    {
        pANTLR3_STRING  string, sparent;
        pANTLR3_BASE_TREE   t, t2;
        pANTLR3_COMMON_TOKEN token;
        pANTLR3_BASE_TREE parent;
        irr::core::stringc uname="";

        //
        // unnamed definition - use assignment lvalue as namespace.
        //
        if(!tree->children)
        {
            parent = (pANTLR3_BASE_TREE)tree->u;
            token = parent->getToken(parent);
            if(token && token->type == ASSIGN)
            {
                t   = (pANTLR3_BASE_TREE) parent->children->get(parent->children, 0);
                token = t->getToken(t);
                m_st->pushSpace((token->getText(token))->chars);
            }

            else 
            {
                uname += m_unNamed++;
                uname += "__";
                m_st->pushSpace(uname);
            }
            return 0;
        }

        t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, 0);
        token = t->getToken(t);
        if(token->type == NAME)
        {
            string = token->getText(token);
            m_st->addSymbol(string->chars, type, "", 
                token->input->istream->getSourceName(token->input->istream)->chars,
                token->line, token->charPosition);
            m_st->pushSpace(string->chars);
        }
        else if(token->type == INTEGER)
        {
            irr::core::stringc sname;
            switch(type)
            {
            case stMaterial:
                sname = "material"; break;
            case stConfig:
                sname = "config"; break;
            case stMatrix:
                sname = "matrix"; break;
            case stLayer:
                sname = "layer"; break;
            };
            sname += token->getText(token)->chars;
            m_st->addSymbol(sname, type, "",
                token->input->istream->getSourceName(token->input->istream)->chars,
                token->line, token->charPosition);
            m_st->pushSpace(sname);
        }
        else if(token->type == INHERIT)
        {
            if(t->children->count != 2)
            {
                return E_BAD_SYNTAX;
            }
            t2 = (pANTLR3_BASE_TREE) t->children->get(t->children, 0);
            token = t->getToken(t2);
            if(token->type != NAME)
                return E_BAD_SYNTAX;
            string = token->getText(token);

            t2 = (pANTLR3_BASE_TREE) t->children->get(t->children, 1);
            token = t->getToken(t2);
            if(token->type != NAME)
                return E_BAD_SYNTAX;
            sparent = token->getText(token);

            m_st->addSymbol(string->chars, type, sparent->chars,                
                token->input->istream->getSourceName(token->input->istream)->chars,
                token->line, token->charPosition);

            m_st->pushSpace(string->chars);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t D o t t e d N a m e    
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_getDottedName(pANTLR3_BASE_TREE tree, irr::u32 startidx,
        irr::u32 endidx)
    {
        pANTLR3_BASE_TREE   t,parent;
        pANTLR3_COMMON_TOKEN token;
        irr::core::stringc result="";

        if(!tree->children)
        {
            parent = (pANTLR3_BASE_TREE)tree->u;
            token = parent->getToken(parent);
            if(token && token->type == ASSIGN)
            {
                t   = (pANTLR3_BASE_TREE) parent->children->get(parent->children, 0);
                token = t->getToken(t);
                result = (token->getText(token))->chars;
            }
            else result = "?_getDottedName?";
            return result;
        }

        if(endidx == 0)
            endidx = tree->children->count;
        for(irr::u32 i=startidx;i<endidx;i++)
        {
            t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
            token = t->getToken(t);
            if(token->type == ASSIGN)
                break;
            if(token->type == INHERIT)
            {
                return _getDottedName(t, 0, t->children->count-1);
            }
            else if(token->type == INTEGER)
            {
                pANTLR3_COMMON_TOKEN ptoken = tree->getToken(tree);
                switch(ptoken->type)
                {
                case LAYDEF:
                    result = "layer"; break;
                case CNFDEF:
                    result = "config"; break;
                case MATDEF:
                    result = "material"; break;
                case MTXDEF:
                    result = "matrix"; break;
                };
            }
            if(i>startidx)
                result += ".";
            result += token->getText(token)->chars;
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                           _ g e t S c o p e  
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_getScope(pANTLR3_BASE_TREE tree, irr::u32 startidx,
        irr::u32 endidx)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        irr::core::stringc result="";

        if(!tree->children)
            return "";

        if(endidx == 0)
            endidx = tree->children->count;
        for(irr::u32 i=startidx;i<endidx;i++)
        {
            t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
            token = t->getToken(t);
            if(token->type == ASSIGN)
                break;
            if(token->type == INHERIT)
            {
                return _getDottedName(t, 0, t->children->count-1);
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                              b u i l d S T
    //-------------------------------------------------------------------------
    int CISLParser::_buildST(pANTLR3_BASE_TREE tree)
    {
        int result = 0;

        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t, p;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";

        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);

            switch(token->type)
            {
            case ASSIGN:
                if(!tree->children)
                    return 0;
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, 0);
                token = t->getToken(t);
                if(token->type == NAME)
                {
                    irr::core::stringc dname = _getDottedName(tree);

                    m_st->addSymbol(dname, stUndefined, "",                 
                        token->input->istream->getSourceName(token->input->istream)->chars,
                        token->line, token->charPosition);
                }
                else printf("Add Symbol ASSIGN - unknown token type\n");
                break;
            case INHERIT:
                i = 0;
                break;
            case MATDEF:
                _startDEFSym(tree, stMaterial);
                break;
            case MTXDEF:
                _startDEFSym(tree, stMatrix);
                break;
            case LAYDEF:
                _startDEFSym(tree, stLayer);
                break;
            case CNFDEF:
                _startDEFSym(tree, stConfig);
                break;
            case EDEF:
                m_st->popSpace();
                break;
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return 0;
        }

        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
                t->u = tree;
                ++level;
                _buildST(t);
                --level;
            }
        }
        return result;
    }

    //-------------------------------------------------------------------------
    //                       _ e x t r a c t S t r i n g
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_extractString(char *str)
    {
        irr::core::stringc temp = str;
        if(temp.size() == 2)
            return "";

        return temp.subString(1, temp.size()-2);
    }

    //-------------------------------------------------------------------------
    //                            _ g e t S p a c e I D
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_getSpaceID(irr::core::stringc id)
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
    //                            _ p u s h S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_pushSpace(irr::core::stringc name)
    {
        irr::core::stringc result="";

        m_nameSpace.push_back(name);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            if(i>0)
                result += ".";
            result += m_nameSpace[i];
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                             _ p o p S p a c e
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_popSpace()
    {
        irr::core::stringc result="";
        irr::u32 idx = m_nameSpace.size();
        if(!idx)
            return result;

        m_nameSpace.erase(idx-1);
        for(irr::u32 i=0; i<m_nameSpace.size(); i++)
        {
            if(i>0)
                result += ".";
            result += m_nameSpace[i];
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                             _ g e t O p 
    //-------------------------------------------------------------------------
    int CISLParser::_getOp(pANTLR3_BASE_TREE tree, irr::u32 idx, struct EvalResult* pr)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        EvalResult op1,op2;
        EvalResult* cvalue;

        t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, idx);
        token = t->getToken(t);
        switch(token->type)
        {
        case NAME:
            cvalue = m_st->getValue((char *) token->getText(token)->chars);
            if(cvalue)
            {
                if((pr->rType == stUndefined) || (cvalue->rType == pr->rType))
                {
                    pr->rType = cvalue->rType;
                    switch(pr->rType)
                    {
                    case stInt:
                        pr->rInteger = cvalue->rInteger; 
                        break;
                    case stFloat:
                        pr->rFloat = cvalue->rFloat; 
                        break;
                    };
                }
                else
                {
                    // type mis-match...
                }
            }
            else
            {
                // undefined symbol...
            }
            break;
        case INTEGER:
            pr->rType = stInt;
            pr->rInteger = atoi((char *)token->getText(token)->chars);
            break;
        case FLOAT:
            pr->rType = stFloat;
            pr->rFloat = (float)atof((char *)token->getText(token)->chars);
            break;
        case MUL:
        case DIV:
        case SUB:
        case ADD:
            _getOp(t, 0, &op1);
            _getOp(t, 1, &op2);
            _doMath(pr, token->type, &op1, &op2);
            break;
        };

        return 0;
    }

    //-------------------------------------------------------------------------
    //                              _ d o M a t h
    //-------------------------------------------------------------------------
    int CISLParser::_doMath(struct EvalResult* result, ANTLR3_UINT32 op, struct EvalResult* op1, struct EvalResult* op2)
    {
        if(op1->rType == stInt || op1->rType == stFloat)
        {
            irr::f32 o1=op1->rFloat;
            irr::f32 o2=op2->rFloat;
            irr::f32 res;

            // convert both operands to float
            if(op1->rType == stInt)
                o1 = (irr::f32) op1->rInteger;
            if(op2->rType == stInt)
                o2 = (irr::f32) op2->rInteger;

            // math
            switch(op)
            {
            case ADD:
                res = o1 + o2;
                break;
            case SUB:
                res = o1 - o2;
                break;
            case MUL:
                res = o1 * o2;
                break;
            case DIV:
                res = o1 / o2;
                break;
            };

            // set return type & value
            if(op1->rType == stInt && op2->rType == stInt)
            {
                result->rType = stInt;
                result->rInteger = (int) res;
            }
            else
            {
                result->rType = stFloat;
                result->rFloat = res;
            }
        }
        else if(op1->rType == stString)
        {
            if(op == ADD)
            {
            }
            else
            {
                // invalid string operation.
            }
        }
        else
        {
            // type mis-match - can't perform math on object definitions.
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                                _ e v a l
    //-------------------------------------------------------------------------
    int CISLParser::_eval(pANTLR3_BASE_TREE tree, pANTLR3_BASE_TREE parent, int cidx, struct EvalResult* pr)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        EvalResult op1,op2;
        EvalResult* cvalue;
        irr::core::stringc cname="";

        pr->rType = stUndefined;
        pr->rInteger = 0;
        pr->rFloat = 0;
        pr->rBool = "";

        token = tree->getToken(tree);

        switch(token->type)
        {
        case NAME:
            if(cidx == parent->getChildCount(parent)-1)
                cname = (char *) token->getText(token)->chars;
            else cname = _getDottedName(parent, cidx);
            cvalue = m_st->getValue(cname.c_str());
            if(cvalue)
            {
                if((pr->rType == stUndefined) || (cvalue->rType == pr->rType))
                {
                    pr->rType = cvalue->rType;
                    switch(pr->rType)
                    {
                    case stInt:
                        pr->rInteger = cvalue->rInteger; 
                        break;
                    case stFloat:
                        pr->rFloat = cvalue->rFloat; 
                        break;
                    case stString:
                        pr->rString = cvalue->rString;
                        break;
                    case stTuple:
                        pr->rTupleItems = cvalue->rTupleItems;
                        break;
                    };
                }
                else
                {
                    // type mis-match...
                }
            }
            else
            {
                // undefined symbol...
            }
            break;
        case STRING:
            pr->rType = stString;
            pr->rString = _extractString((char *)token->getText(token)->chars);
            break;
        case INTEGER:
            pr->rType = stInt;
            pr->rInteger = atol((char *)token->getText(token)->chars);
            break;
        case FLOAT:
            pr->rType = stFloat;
            pr->rFloat = (irr::f32) atof((char *)token->getText(token)->chars);
            break;            
        case HEX:
            pr->rType = stInt;
            pr->rInteger = strtol((char *)token->getText(token)->chars + 2, NULL, 16);
            break;            
        case BOOLLITERAL:
            pr->rType = stBool;
            pr->rBool = strcmp((char *)token->getText(token)->chars,"true") ? false : true;
            break;
        case TUPLE:
            pr->rType = stTuple;
            for(irr::u32 i=0;i<tree->getChildCount(tree);i++)
            {
                EvalResult* cer = new EvalResult();
                pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild(tree,i);
                _eval(child, tree, 0, cer);
                pr->rTupleItems.push_back(cer);
            }
            break;
        case LAYDEF:
            pr->rType = stLayer;
            break;
        case MATDEF:
            pr->rType = stMaterial;
            break;
        case MTXDEF:
            pr->rType = stMatrix;
            break;
        case CNFDEF:
            pr->rType = stConfig;
            break;
        case MUL:
        case DIV:
        case SUB:
        case ADD:
            _getOp(tree, 0, &op1);
            _getOp(tree, 1, &op2);
            _doMath(pr, token->type, &op1, &op2);
            break;
        };

        return 0;
    }

    //-------------------------------------------------------------------------
    //                                _ g e t I P a r e n t
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_getIParent(pANTLR3_BASE_TREE tree, pANTLR3_BASE_TREE parent, int cidx)
    {
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        irr::core::stringc cname="";

        token = tree->getToken(tree);

        switch(token->type)
        {
        case NAME:
            if(cidx == parent->getChildCount(parent)-1)
                cname = (char *) token->getText(token)->chars;
            else cname = _getDottedName(parent, cidx);
            break;
        case MATDEF:
        case MTXDEF:
        case CNFDEF:
        case LAYDEF:
            cname = _getDottedName(tree);
            break;
        };

        return cname;
    }

    //-------------------------------------------------------------------------
    //                            _ i n t e r p r e t
    //-------------------------------------------------------------------------
    int CISLParser::_interpret(pANTLR3_BASE_TREE tree)
    {
        int result = 0;

        pANTLR3_STRING  string;
        ANTLR3_UINT32   i;
        ANTLR3_UINT32   n;
        pANTLR3_BASE_TREE   t;
        pANTLR3_COMMON_TOKEN token;
        static int level=-1;
        static irr::core::stringc tabs = "";
        irr::core::stringc id;
        struct EvalResult er;


        token = tree->getToken(tree);
        if(token)
        {
            string = token->getText(token);

            switch(token->type)
            {
            case ASSIGN:
                if(!tree->children)
                    return 0;

                id = _getSpaceID(_getDottedName(tree));

                // skip past "=" token
                irr::u32 i;
                for(i=0;i<tree->children->count-1;i++)
                {
                    t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);
                    token = t->getToken(t);
                    if(token->type == ASSIGN)
                        break;
                }
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, ++i);
                _eval(t, tree, i, &er);
                m_st->setValue(id, &er);
                if(er.rType > stObjectStart)
                {
                    irr::core::stringc iparent = _getSpaceID(_getIParent(t, tree, i));
                    if(!iparent.equals_ignore_case(id))
                        m_st->setIParent(id, iparent);
                }
                break;
            case SDEF:
                result = 0;
                break;
            case EDEF:
                result = 0;
                _popSpace();
                break;
            case MATDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stMaterial;
                m_st->setValue(id, &er);                
                _pushSpace(_getDottedName(tree));
                break;
            case CNFDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stConfig;
                m_st->setValue(id, &er);                
                _pushSpace(_getDottedName(tree));
                break;
            case MTXDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stMatrix;
                m_st->setValue(id, &er);                
                _pushSpace(_getDottedName(tree));
                break;
            case LAYDEF:
                id = _getSpaceID(_getDottedName(tree));
                er.rType = stLayer;
                m_st->setValue(id, &er);                
                _pushSpace(_getDottedName(tree));
                break;
            };
        }

        if	(tree->children == NULL || tree->children->size(tree->children) == 0)
        {
            return 0;
        }

        if	(tree->children != NULL)
        {
            n = tree->children->size(tree->children);

            for	(i = 0; i < n; i++)
            {   
                t   = (pANTLR3_BASE_TREE) tree->children->get(tree->children, i);

                ++level;
                _interpret(t);
                --level;
            }
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t V a l u e R e s u l t
    //-------------------------------------------------------------------------
    EvalResult* CISLParser::_getValueResult(CSymbol* sym, irr::core::stringc val)
    {

        SYMMAP&  vars = sym->getChildren();

        for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
        {
            CSymbol* child = citr->getValue();
            if(val.equals_ignore_case(child->getID()))
                return child->getValue();
        }
        //
        // inheritence?
        //
        irr::core::stringc iparent = sym->getIParent();
        if(iparent.size())
        {
            return _getValueResult(m_st->getSymbol(iparent), val);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t I n t V a l u e
    //-------------------------------------------------------------------------
    int CISLParser::_getIntValue(EvalResult* er, int defval)
    {
        int result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = er->rInteger;
            break;
        case stFloat:
            result = (int) er->rFloat;
            break;
        case stString:
            result = atoi(er->rString.c_str());
            break;
        case stTuple:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t F l o a t V a l u e
    //-------------------------------------------------------------------------
    irr::f32 CISLParser::_getFloatValue(EvalResult* er, irr::f32 defval)
    {
        irr::f32 result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = (irr::f32) er->rInteger;
            break;
        case stFloat:
            result = er->rFloat;
            break;
        case stString:
            result = (irr::f32) atof(er->rString.c_str());
            break;
        case stTuple:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t B o o l V a l u e
    //-------------------------------------------------------------------------
    bool CISLParser::_getBoolValue(EvalResult* er, bool defval)
    {
        bool result=defval;

        switch(er->rType)
        {
        case stBool: 
            result = er->rBool;
            break;
        case stInt:
            result = er->rInteger ? true : false;
            break;
        case stFloat:
            result = er->rFloat ? true : false;
            break;
        case stString:
            result = atoi(er->rString.c_str()) ? true : false;
            break;
        case stTuple:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                      _ g e t S t r i n g  V a l u e
    //-------------------------------------------------------------------------
    irr::core::stringc CISLParser::_getStringValue(EvalResult*er, irr::core::stringc defval)
    {
        irr::core::stringc result=defval;

        switch(er->rType)
        {
        case stBool: 
            break;
        case stInt:
            break;
        case stFloat:
            break;
        case stString:
            result = er->rString;
            break;
        case stTuple:
            // pull first item...
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //             _ g e t C o l o r V a l u e F r o m T u p l e
    //-------------------------------------------------------------------------
    irr::u32 CISLParser::_getColorValueFromTuple(const TUPLEITEMS& items, irr::u32 idx)
    {
        irr::u32 result=0;
        EvalResult* per;

        //
        // default undefined alpha to 255, color components default to 0.
        //
        if(idx == 3)
            result = 255;

        if(!items.size() || (idx > items.size()-1))
            return result;

        per = items[idx];

        if(per->rType == stInt)
        {
            result = per->rInteger;
        }
        else if(per->rType == stFloat)
        {
            if(per->rFloat <= 1.0)
                result = (irr::u32)(255.0 * per->rFloat);
            else
                result = (irr::u32) per->rFloat;
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                      _ g e t V e c t o r 2 d V a l u e 
    //-------------------------------------------------------------------------
    irr::core::vector2df& CISLParser::_getVector2dValue(EvalResult* er)
    {
        static irr::core::vector2df result;
        irr::f32 fv;
        result.X = result.Y = 0;
        EvalResult* per;

        switch(er->rType)
        {
        case stTuple:
            {
                TUPLEITEMS& items = er->rTupleItems;
                for(irr::u32 i=0; i<2; i++)
                {
                    if(i >= items.size())
                        break;

                    per = items[i];

                    fv = .0;
                    if(per->rType == stInt)
                    {
                        fv = (irr::f32)per->rInteger;
                    }
                    else if(per->rType == stFloat)
                    {
                        fv = per->rFloat;
                    }
                    switch(i)
                    {
                    case 0:
                        result.X = fv; break;
                    case 1:
                        result.Y = fv; break;
                    }
                }
            }
            break;
        case stInt:
            result.X = (irr::f32)er->rInteger;
            break;
        case stFloat:
            result.X = er->rFloat;
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                      _ g e t V e c t o r V a l u e 
    //-------------------------------------------------------------------------
    irr::core::vector3df& CISLParser::_getVectorValue(EvalResult* er)
    {
        static irr::core::vector3df result;
        irr::f32 fv;
        result.X = result.Y = result.Z = 0;
        EvalResult* per;

        switch(er->rType)
        {
        case stTuple:
            {
                TUPLEITEMS& items = er->rTupleItems;
                for(irr::u32 i=0; i<3; i++)
                {
                    if(i >= items.size())
                        break;

                    per = items[i];

                    fv = .0;
                    if(per->rType == stInt)
                    {
                        fv = (irr::f32)per->rInteger;
                    }
                    else if(per->rType == stFloat)
                    {
                        fv = per->rFloat;
                    }
                    switch(i)
                    {
                    case 0:
                        result.X = fv; break;
                    case 1:
                        result.Y = fv; break;
                    case 2:
                        result.Z = fv; break;
                    }
                }
            }
            break;
        case stInt:
            result.X = (irr::f32)er->rInteger;
            break;
        case stFloat:
            result.X = er->rFloat;
            break;
        };

        return result;
    }

    //-------------------------------------------------------------------------
    //                        _ g e t M a t r i x V a l u e
    //-------------------------------------------------------------------------
    irr::core::matrix4& CISLParser::_getMatrixValue(EvalResult* er)
    {
        static irr::core::matrix4 result;
        irr::u32 i;
        irr::core::vector3df vec;

        result = IdentityMatrix;

        if(er->rType == stMatrix)
        {
            irr::core::matrix4* iresult = (irr::core::matrix4*)er->rUserData;
            result = *iresult;
        }
        else if(er->rType == stTuple)
        {
            //
            // tuple of tuples (rotation, translation, scale)
            //
            EvalResult* per;
            for( i=0; i < 3; i++)
            {
                if(i >= er->rTupleItems.size())
                    break;

                vec.set(0,0,0);
                per = er->rTupleItems[i];
                if(per->rType == stTuple)
                {
                    vec = _getVectorValue(per);
                }
                switch(i)
                {
                case 0:
                    result.setRotationDegrees(vec); break;
                case 1:
                    result.setTranslation(vec); break;
                case 2:
                    result.setScale(vec); break;
                }

            }            
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                         _ g e t C o l o r V a l u e
    //-------------------------------------------------------------------------
    const irr::video::SColor& CISLParser::_getColorValue(EvalResult* er)
    {
        static irr::video::SColor result;
        EvalResult* ter;

        // default black full alpha
        result.set(255,0,0,0);

        switch(er->rType)
        {
        case stInt:
            result.setRed((er->rInteger & 0xFF000000) >> 24);
            result.setGreen((er->rInteger & 0x00FF0000) >> 16);
            result.setBlue((er->rInteger & 0x0000FF00) >> 8);
            result.setAlpha(er->rInteger & 0x000000FF);
            break;
        case stTuple:
            result.setRed(_getColorValueFromTuple(er->rTupleItems,0));
            result.setGreen(_getColorValueFromTuple(er->rTupleItems,1));
            result.setBlue(_getColorValueFromTuple(er->rTupleItems,2));
            result.setAlpha(_getColorValueFromTuple(er->rTupleItems,3));
            break;
        }

        return result;
    }

    //-------------------------------------------------------------------------
    //                  _ g e t M a t e r i a l L a y e r V a l u e
    //-------------------------------------------------------------------------
    bool CISLParser::_getMaterialLayerValue(irr::video::IVideoDriver* videoDriver,
        CSymbol* parent, irr::core::stringc layerid, 
        irr::video::SMaterialLayer& output)
    {
        CSymbol* child=0;
        bool found=false;
        irr::core::vector3df vec;
    
        SYMMAP&  vars = parent->getChildren();        
        for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
        {
            child = citr->getValue();
            if(layerid.equals_ignore_case(child->getID()))
            {
                found = true;
                break;
            }
        }

        if(!found)
            return false;

        EvalResult* er = _getValueResult(child, "clampmode");
        if(er)
            output.TextureWrap = (irr::video::E_TEXTURE_CLAMP) _getIntValue(er, 0);

        er = _getValueResult(child, "texture");
        if(er && videoDriver)
            output.Texture = videoDriver->getTexture(_getStringValue(er));

        er = _getValueResult(child, "bilinear");
        if(er)
            output.BilinearFilter = _getBoolValue(er);

        er = _getValueResult(child, "trilinear");
        if(er)
            output.TrilinearFilter = _getBoolValue(er);

        er = _getValueResult(child, "anisotropic");
        if(er)
            output.AnisotropicFilter = _getBoolValue(er);

        er = _getValueResult(child, "transform");
        if(er)
            output.setTextureMatrix(_getMatrixValue(er));

        // transform matrix overrides
        irr::core::vector2df scale, offset, center, rotation;


        er = _getValueResult(child, "scale");
        if(er)
        {
            scale = _getVector2dValue(er);
        }
        else
        {
            vec = output.getTextureMatrix().getScale();
            scale.X = vec.X;
            scale.Y = vec.Y;
        }

        er = _getValueResult(child, "offset");
        if(er)
        {
            offset = _getVector2dValue(er);
        }
        else
        {
            vec = output.getTextureMatrix().getTranslation();
            offset.X = vec.X;
            offset.Y = vec.Y;
        }

        er = _getValueResult(child, "center");
        if(er)
        {
            center = _getVector2dValue(er);
        }
        else
        {
            center.X = 0.5;
            center.Y = 0.5;
        }

        er = _getValueResult(child, "rotation");
        if(er)
        {
            rotation = _getVector2dValue(er);
        }
        else
        {
            vec = output.getTextureMatrix().getRotationDegrees();
            rotation.X = vec.X;
        }

        irr::core::matrix4 tmat;
        tmat.buildTextureTransform(rotation.X * irr::core::DEGTORAD, center, offset, scale);
        output.setTextureMatrix(tmat);

        return true;
    }

    //-------------------------------------------------------------------------
    //                      _ c r e a t e M a t r i c e s
    //-------------------------------------------------------------------------
    int CISLParser::_createMatrices()
    {
        irr::core::stringc cid;
        irr::core::matrix4* pmtx;
        int idx;
        bool found;

        // print invalid var warnings
        for ( SYMMAP::Iterator itr = m_mtxDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            SYMMAP&  vars = symbol->getChildren();
            irr::core::stringc scope = symbol->getID();

            for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
            {
                CSymbol* csymbol = citr->getValue();
                if(!scope.equals_ignore_case(csymbol->getScope()))
                    continue;

                cid = csymbol->getID();
                found = false;
                idx = 0;
                while(MTXVARS[idx])
                {
                    if(cid.equals_ignore_case(MTXVARS[idx]))
                    {
                        found = true;
                        break;
                    }
                    ++idx;
                }
                if(!found)
                {
                    printf("Warning - Ignoring Invalid Material Variable: %s.%s\n", csymbol->getScope().c_str(),
                        cid.c_str());
                }
            }
        }

        // create matrices
        for ( SYMMAP::Iterator itr = m_mtxDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            pmtx = new irr::core::matrix4();

            EvalResult* er = _getValueResult(symbol, "r");
            if(er)
                pmtx->setRotationDegrees(_getVectorValue(er));

            er = _getValueResult(symbol, "t");
            if(er)
                pmtx->setTranslation(_getVectorValue(er));

            er = _getValueResult(symbol, "s");
            if(er)
                pmtx->setScale(_getVectorValue(er));

            symbol->setUserData(pmtx);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                      _ p r i n t M a t r i c e s
    //-------------------------------------------------------------------------
    void CISLParser::_printMatrices()
    {
        irr::core::matrix4* pmtx;
        irr::core::vector3df v;

        printf("\n");
        for ( SYMMAP::Iterator itr = m_mtxDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            pmtx = (irr::core::matrix4*) symbol->getUserData();

            printf("matrix (%s):\n", symbol->getScopedID());

            printf("[%7.2f %7.2f %7.2f %7.2f]\n",(*pmtx)[0], (*pmtx)[1], (*pmtx)[2], (*pmtx)[3]);
            printf("[%7.2f %7.2f %7.2f %7.2f]\n",(*pmtx)[4], (*pmtx)[5], (*pmtx)[6], (*pmtx)[7]);
            printf("[%7.2f %7.2f %7.2f %7.2f]\n",(*pmtx)[8], (*pmtx)[9], (*pmtx)[10], (*pmtx)[11]);
            printf("[%7.2f %7.2f %7.2f %7.2f]\n",(*pmtx)[12], (*pmtx)[13], (*pmtx)[14], (*pmtx)[15]);

            v = pmtx->getRotationDegrees();
            printf("   rotation: %7.2f %7.2f %7.2f\n", v.X, v.Y, v.Z);
            v = pmtx->getScale();
            printf("      scale: %7.2f %7.2f %7.2f\n", v.X, v.Y, v.Z);
            v = pmtx->getTranslation();
            printf("translation: %7.2f %7.2f %7.2f\n\n", v.X, v.Y, v.Z);
        }

        return;
    }


    //-------------------------------------------------------------------------
    //                 _ c r e a t e M a t e r i a l L a y e r s
    //-------------------------------------------------------------------------
    int CISLParser::_createMaterialLayers(irr::video::IVideoDriver* videoDriver)
    {
        irr::video::SMaterialLayer* play;
        irr::core::stringc cid;
        int idx;
        bool found;
        irr::SIrrlichtCreationParameters cp;
        irr::core::vector3df vec;

        if(!m_matDefs.size())
            return 0;

        // print invalid var warnings
        for ( SYMMAP::Iterator itr = m_layDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            SYMMAP&  vars = symbol->getChildren();
            irr::core::stringc scope = symbol->getID();

            for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
            {
                CSymbol* csymbol = citr->getValue();
                if(!scope.equals_ignore_case(csymbol->getScope()))
                    continue;

                cid = csymbol->getID();
                found = false;
                idx = 0;
                while(LAYVARS[idx])
                {
                    if(cid.equals_ignore_case(LAYVARS[idx]))
                    {
                        found = true;
                        break;
                    }
                    ++idx;
                }
                if(!found)
                {
                    printf("Warning - Ignoring Invalid Material Layer Variable: %s.%s\n", csymbol->getScope().c_str(),
                        cid.c_str());
                }
            }
        }

        // create material layers
        for ( SYMMAP::Iterator itr = m_layDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            play = new irr::video::SMaterialLayer();

            EvalResult* er = _getValueResult(symbol, "clampmode");
            if(er)
                play->TextureWrap = (irr::video::E_TEXTURE_CLAMP) _getIntValue(er, 0);

            er = _getValueResult(symbol, "texture");
            if(er && videoDriver)
                play->Texture = videoDriver->getTexture(_getStringValue(er));

            er = _getValueResult(symbol, "bilinear");
            if(er)
                play->BilinearFilter = _getBoolValue(er);

            er = _getValueResult(symbol, "trilinear");
            if(er)
                play->TrilinearFilter = _getBoolValue(er);

            er = _getValueResult(symbol, "anisotropic");
            if(er)
                play->AnisotropicFilter = _getBoolValue(er);

            er = _getValueResult(symbol, "transform");
            if(er)
                play->setTextureMatrix(_getMatrixValue(er));

            // transform matrix overrides
            irr::core::vector2df scale, offset, center, rotation;


            er = _getValueResult(symbol, "scale");
            if(er)
            {
                scale = _getVector2dValue(er);
            }
            else
            {
                vec = play->getTextureMatrix().getScale();
                scale.X = vec.X;
                scale.Y = vec.Y;
            }

            er = _getValueResult(symbol, "offset");
            if(er)
            {
                offset = _getVector2dValue(er);
            }
            else
            {
                vec = play->getTextureMatrix().getTranslation();
                offset.X = vec.X;
                offset.Y = vec.Y;
            }

            er = _getValueResult(symbol, "center");
            if(er)
            {
                center = _getVector2dValue(er);
            }
            else
            {
                center.X = 0.5;
                center.Y = 0.5;
            }

            er = _getValueResult(symbol, "rotation");
            if(er)
            {
                rotation = _getVector2dValue(er);
            }
            else
            {
                vec = play->getTextureMatrix().getRotationDegrees();
                rotation.X = vec.X;
            }

            irr::core::matrix4 tmat;
            tmat.buildTextureTransform(rotation.X * irr::core::DEGTORAD, center, offset, scale);
            play->setTextureMatrix(tmat);

            symbol->setUserData(play);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                      _ c r e a t e M a t e r i a l s
    //-------------------------------------------------------------------------
    int CISLParser::_createMaterials(irr::video::IVideoDriver* videoDriver)
    {
        irr::video::SMaterial* pmat;
        irr::core::stringc cid;
        int idx;
        bool found;
        irr::SIrrlichtCreationParameters cp;

        if(!m_matDefs.size())
            return 0;

        // print invalid var warnings
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            SYMMAP&  vars = symbol->getChildren();
            irr::core::stringc scope = symbol->getID();

            for(SYMMAP::Iterator citr = vars.getIterator(); !citr.atEnd(); citr++)
            {
                CSymbol* csymbol = citr->getValue();
                if(!scope.equals_ignore_case(csymbol->getScope()))
                    continue;

                cid = csymbol->getID();
                found = false;
                idx = 0;
                while(MATVARS[idx])
                {
                    if(cid.equals_ignore_case(MATVARS[idx]))
                    {
                        found = true;
                        break;
                    }
                    ++idx;
                }
                if(!found)
                {
                    printf("Warning - Ignoring Invalid Material Variable: %s.%s\n", csymbol->getScope().c_str(),
                        cid.c_str());
                }
            }
        }

        // create materials
        for ( SYMMAP::Iterator itr = m_matDefs.getIterator(); !itr.atEnd(); itr++)
        {
            CSymbol*  symbol = itr->getValue();
            pmat = new irr::video::SMaterial();

            EvalResult* er = _getValueResult(symbol, "type");
            if(er)
                pmat->MaterialType = (irr::video::E_MATERIAL_TYPE) _getIntValue(er, 0);

            er = _getValueResult(symbol, "ambient");
            if(er)
                pmat->AmbientColor = _getColorValue(er);

            er = _getValueResult(symbol, "diffuse");
            if(er)
                pmat->DiffuseColor = _getColorValue(er);

            er = _getValueResult(symbol, "emissive");
            if(er)
                pmat->EmissiveColor = _getColorValue(er);

            er = _getValueResult(symbol, "specular");
            if(er)
                pmat->SpecularColor = _getColorValue(er);

            er = _getValueResult(symbol, "shininess");
            if(er)
                pmat->Shininess = _getFloatValue(er, 20.0);

            er = _getValueResult(symbol, "parm1");
            if(er)
                pmat->MaterialTypeParam = _getFloatValue(er, 0.0);

            er = _getValueResult(symbol, "parm2");
            if(er)
                pmat->MaterialTypeParam2 = _getFloatValue(er, 0.0);

            er = _getValueResult(symbol, "thickness");
            if(er)
                pmat->Thickness = _getFloatValue(er, 1.0);

            er = _getValueResult(symbol, "gouraud");
            if(er)
                pmat->Thickness = _getBoolValue(er, true);

            er = _getValueResult(symbol, "lighting");
            if(er)
                pmat->Lighting = _getBoolValue(er, true);

            er = _getValueResult(symbol, "zwriteenable");
            if(er)
                pmat->ZWriteEnable = _getBoolValue(er, true);

            er = _getValueResult(symbol, "backfaceculling");
            if(er)
                pmat->BackfaceCulling = _getBoolValue(er, true);

            er = _getValueResult(symbol, "frontfaceculling");
            if(er)
                pmat->FrontfaceCulling = _getBoolValue(er, false);

            er = _getValueResult(symbol, "fogenabled");
            if(er)
                pmat->FogEnable = _getBoolValue(er, false);

            er = _getValueResult(symbol, "normalizenormals");
            if(er)
                pmat->NormalizeNormals = _getBoolValue(er, false);

            er = _getValueResult(symbol, "zbuffer");
            if(er)
                pmat->ZBuffer = _getIntValue(er, 1);

            //
            // assign layers if defined
            //
            irr::video::SMaterialLayer layer;
            if(_getMaterialLayerValue(videoDriver, symbol, "layer1", layer))
                pmat->TextureLayer[0] = layer;

            if(_getMaterialLayerValue(videoDriver, symbol, "layer2", layer))
                pmat->TextureLayer[1] = layer;

            if(_getMaterialLayerValue(videoDriver, symbol, "layer3", layer))
                pmat->TextureLayer[2] = layer;

            if(_getMaterialLayerValue(videoDriver, symbol, "layer4", layer))
                pmat->TextureLayer[3] = layer;

            symbol->setUserData(pmat);
        }

        return 0;
    }

    //-------------------------------------------------------------------------
    //                         v a l i d a t e S c r i p t
    //-------------------------------------------------------------------------
    CISLParserStatus CISLParser::validateScript(const irr::core::stringc fileName, 
        const CISLParserErrorHandler& errorHandler)
    {

        if(!fileExists(fileName))
        {
            ANTLR3_FPRINTF(stderr, "Script file doesn't exists.\n");
            return E_NO_FILE;
        }

        if(m_fileName)
        {
            _freeResources();
        }

        m_fileName = (pANTLR3_UINT8)fileName.c_str();
        m_inputStream  = antlr3AsciiFileStreamNew(m_fileName);
        if ( m_inputStream == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to open file %s \n", (char *)m_fileName);
            return E_BAD_INPUT;
        }

        //
        // create an instance of the ANTLR generated lexer
        //
        m_lexer        = islLexerNew(m_inputStream);      // CLexerNew is generated by ANTLR

        // realloc to include our context data 
        m_lexer = (pislLexer) ANTLR3_REALLOC(m_lexer,sizeof(struct LexerContext));
        m_lexer->pLexer->ctx = m_lexer;
        if ( m_lexer == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to create the lexer due to malloc() failure1\n");
            return E_OUT_OF_MEMORY;
        }

        ((struct LexerContext*)m_lexer)->pisl = this;

        // 
        // Create the lexer token stream.
        // 
        m_tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(m_lexer));


        if (m_tokenStream == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate token stream\n");
            return E_OUT_OF_MEMORY;
        }

        //
        // Create an instance of the ANTLR generated parser
        //
        m_parser        = islParserNew(m_tokenStream);  // CParserNew is generated by ANTLR3
        if (m_parser == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate parser\n");
            return E_OUT_OF_MEMORY;
        }

        // install our own error display & debug functions
        m_parser->pParser->rec->displayRecognitionError = islRecognitionError;


        // 
        // lex & parse
        // 
        m_islAST = m_parser->script(m_parser);

        if(m_parser->pParser->rec->state->errorCount == 0)
        {
            m_treeNodes   = antlr3CommonTreeNodeStreamNewTree(m_islAST.tree, ANTLR3_SIZE_HINT);
            m_treeNodes->reset(m_treeNodes);
        }
        else
        {
            ANTLR3_FPRINTF(stderr, "The parser returned %d errors, tree walking aborted.\n", m_parser->pParser->rec->state->errorCount);
            return E_BAD_SYNTAX;
        }

        return E_OK;
    }

    //-------------------------------------------------------------------------
    //                           p a r s e S c r i p t
    //-------------------------------------------------------------------------
    CISLParserStatus CISLParser::parseScript(const irr::core::stringc fileName, const CISLParserErrorHandler& errorHandler)
    {
        CISLParserStatus result=E_OK;
        pANTLR3_COMMON_TOKEN token;

        appendIncludeDirs(_extractDir(fileName));

        result = validateScript(fileName, errorHandler);

        if(result != E_OK)
            return result;

        //
        // dump formatted AST
        //
        printf("\n-------\n\nAST Tree:\n");
        _dumpTree(m_islAST.tree);

        //
        // first pass - build symbol table for forward references
        //
        m_st = new CST();
        if(_buildST(m_islAST.tree) > 0)
        {
            ANTLR3_FPRINTF(stderr, "Symbol Table build error.\n");
            return E_BAD_SYNTAX;
        }

        //
        // second pass - interpretation
        //
        if(_interpret(m_islAST.tree) > 0)
        {
            ANTLR3_FPRINTF(stderr, "Interpreter error.\n");
            return E_BAD_SYNTAX;
        }
        m_st->print();

        //
        // now we're ready to generate our object (matrix, layer, material & config) definitions.
        //
        m_st->getDefinitions(stMatrix, m_mtxDefs);
        m_st->getDefinitions(stLayer, m_layDefs);
        m_st->getDefinitions(stMaterial, m_matDefs);
        m_st->getDefinitions(stConfig, m_cnfDefs);
        _dumpObjects();

        //
        // creating materials/layers requires an IVideoDriver* for texture loading.
        // isl scripts containing materials used by applications will require the 
        // applicationn to link to the irrlicht runtime. applications using isl
        // for config only, won't require the irrlicht runtime.
        //
        _createMatrices();

        // for debugging only
        _createMaterialLayers(0);

        // testing... materials won't be created/loaded unless requested by the host application.
        _createMaterials(0);

        _printMatrices();
        return E_OK;
    }
}
