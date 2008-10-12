#include "CISL.h"
#include <errno.h>
namespace CISL
{
    void islRecognitionError	    (pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 * tokenNames);

    //-------------------------------------------------------------------------
    //                                  C I S L
    //-------------------------------------------------------------------------
    CISL::CISL() : m_fileName(0),
        m_inputStream(0),
        m_lexer(0),
        m_tokenStream(0),
        m_parser(0),
        m_treeNodes(0),
        m_st(0),
        m_ot(0)
    {
    }

    //-------------------------------------------------------------------------
    //                                 ~ C I S L
    //-------------------------------------------------------------------------
    CISL::~CISL()
    {
        freeResources();
    }

    //-------------------------------------------------------------------------
    //                           f r e e R e s o u r c e s
    //-------------------------------------------------------------------------
    void CISL::freeResources()
    {
        if(m_st)
        {
            delete m_st;
            m_st = 0;
        }

        if(m_ot)
        {
            delete m_ot;
            m_ot = 0;
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
    }

    //-------------------------------------------------------------------------
    //                          g e t M a t e r i a l
    //-------------------------------------------------------------------------
    const irr::video::SMaterial* CISL::getMaterial(const irr::core::stringc materialName)
    {
        irr::video::SMaterial* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor* CISL::getColor(const irr::core::stringc colorName)
    {
        irr::video::SColor*  result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t F l o a t
    //-------------------------------------------------------------------------
    float CISL::getFloat(const irr::core::stringc varName)
    {
        float result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                              g e t I n t
    //-------------------------------------------------------------------------
    int CISL::getInt(const irr::core::stringc varName)
    {
        int result=0;
        return result;
    }

    //-------------------------------------------------------------------------
    //                            g e t S t r i n g
    //-------------------------------------------------------------------------
    const irr::core::stringc CISL::getString(const irr::core::stringc varName)
    {
        irr::core::stringc result="";

        return result;
    }

    //-------------------------------------------------------------------------
    //                             g e t L i s t
    //-------------------------------------------------------------------------
    const void* CISL::getList(const irr::core::stringc varName)
    {
        void* result=0;

        return result;
    }

    //-------------------------------------------------------------------------
    //                             d u m p T r e e 
    //-------------------------------------------------------------------------
    void CISL::dumpTree(pANTLR3_BASE_TREE tree)
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
            case LIST:
                printf("%sLIST (%s)\n", tabs.c_str(), string->chars);
                break;
            case COLDEF:
                printf("%sCOLDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case MATDEF:
                printf("%sMATDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case CNFDEF:
                printf("%sCNFDEF (%s)\n", tabs.c_str(), string->chars);
                break;
            case STARTDEF:
                ++level;
                break;
            case ENDDEF:
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
                dumpTree(t);
                --level;
            }
        }
        return;
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
    //                         v a l i d a t e S c r i p t
    //-------------------------------------------------------------------------
    CISLStatus CISL::validateScript(const irr::core::stringc fileName, 
        const CISLErrorHandler& errorHandler)
    {

        if(!fileExists(fileName))
        {
            ANTLR3_FPRINTF(stderr, "Script file doesn't exists.\n");
            return E_NO_FILE;
        }

        if(m_fileName)
        {
            freeResources();
        }

        // Create the m_inputStream stream based upon the argument supplied to us on the command line
        // for this example, the m_inputStream will always default to ./m_inputStream if there is no explicit
        // argument.
        //
        m_fileName = (pANTLR3_UINT8)fileName.c_str();

        // Create the m_inputStream stream using the supplied file name
        // (Use antlr3AsciiFileStreamNew for UCS2/16bit m_inputStream).
        //
        m_inputStream  = antlr3AsciiFileStreamNew(m_fileName);

        // The m_inputStream will be created successfully, providing that there is enough
        // memory and the file exists etc
        //
        if ( m_inputStream == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to open file %s \n", (char *)m_fileName);
            return E_BAD_INPUT;
        }

        // Our m_inputStream stream is now open and all set to go, so we can create a new instance of our
        // lexer and set the lexer m_inputStream to our m_inputStream stream:
        //  (file | memory | ?) --> inputstream -> lexer --> tokenstream --> parser ( --> treeparser )?
        //
        m_lexer        = islLexerNew(m_inputStream);      // CLexerNew is generated by ANTLR

        // Need to check for errors
        //
        if ( m_lexer == NULL )
        {
            ANTLR3_FPRINTF(stderr, "Unable to create the lexer due to malloc() failure1\n");
            return E_OUT_OF_MEMORY;
        }

        // Our lexer is in place, so we can create the token stream from it
        // NB: Nothing happens yet other than the file has been read. We are just 
        // connecting all these things together and they will be invoked when we
        // call the parser rule. ANTLR3_SIZE_HINT can be left at the default usually
        // unless you have a very large token stream/m_inputStream. Each generated lexer
        // provides a token source interface, which is the second argument to the
        // token stream creator.
        // Note tha even if you implement your own token structure, it will always
        // contain a standard common token within it and this is the pointer that
        // you pass around to everything else. A common token as a pointer within
        // it that should point to your own outer token structure.
        //
        m_tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(m_lexer));


        if (m_tokenStream == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate token stream\n");
            return E_OUT_OF_MEMORY;
        }

        // Finally, now that we have our lexer constructed, we can create the parser
        //
        m_parser        = islParserNew(m_tokenStream);  // CParserNew is generated by ANTLR3
        if (m_parser == NULL)
        {
            ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate parser\n");
            return E_OUT_OF_MEMORY;
        }

        // install our own error display & debug functions
        m_parser->pParser->rec->displayRecognitionError = islRecognitionError;
        

        // We are all ready to go. Though that looked complicated at first glance,
        // I am sure, you will see that in fact most of the code above is dealing
        // with errors and there isn;t really that much to do (isn;t this always the
        // case in C? ;-).
        //
        // So, we now invoke the parser. All elements of ANTLR3 generated C components
        // as well as the ANTLR C runtime library itself are pseudo objects. This means
        // that they are represented as pointers to structures, which contain any
        // instance data they need, and a set of pointers to other interfaces or
        // 'methods'. Note that in general, these few pointers we have created here are
        // the only things you will ever explicitly free() as everything else is created
        // via factories, that allocate memory efficiently and free() everything they use
        // automatically when you close the parser/lexer/etc.
        //
        // Note that this means only that the methods are always called via the object
        // pointer and the first argument to any method, is a pointer to the structure itself.
        // It also has the side advantage, if you are using an IDE such as VS2005 that can do it
        // that when you type ->, you will see a list of all the methods the object supports.
        //
        m_islAST = m_parser->script(m_parser);

        // If the parser ran correctly, we will have a tree to parse. In general I recommend
        // keeping your own flags as part of the error trapping, but here is how you can
        // work out if there were errors if you are using the generic error messages
        //
        if(m_parser->pParser->rec->state->errorCount > 0)
        {
            ANTLR3_FPRINTF(stderr, "The parser returned %d errors, tree walking aborted.\n", m_parser->pParser->rec->state->errorCount);
            return E_BAD_SYNTAX;
        }
        else
        {
            m_treeNodes   = antlr3CommonTreeNodeStreamNewTree(m_islAST.tree, ANTLR3_SIZE_HINT); // sIZE HINT WILL SOON BE DEPRECATED!!
            m_treeNodes->reset(m_treeNodes);
        }

        return E_OK;
    }

    //-------------------------------------------------------------------------
    //                         p r o c e s s S c r i p t
    //-------------------------------------------------------------------------
    CISLStatus CISL::processScript(const irr::core::stringc fileName, const CISLErrorHandler& errorHandler)
    {
        CISLStatus result=E_OK;
        pANTLR3_COMMON_TOKEN token;

        result = validateScript(fileName, errorHandler);

        if(result != E_OK)
            return result;

        //
        // dump lexer tokens
        //

        token = TOKENSOURCE(m_lexer)->nextToken(TOKENSOURCE(m_lexer));
        while(token && token->getType(token) != ANTLR3_TOKEN_EOF)
        {
            ANTLR3_STRING_struct* pstring = token->toString(token);

            token = TOKENSOURCE(m_lexer)->nextToken(TOKENSOURCE(m_lexer));
        }

        //
        // dump AST
        //
        printf("Raw AST Tree : \n%s\n", m_islAST.tree->toStringTree(m_islAST.tree)->chars);

        //
        // 
        //
        printf("\n-------\n\nAST Tree:\n");

        dumpTree(m_islAST.tree);


        //
        // interpret/walk the AST...
        //

        return result;
    }

}