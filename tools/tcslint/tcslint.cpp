//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <errno.h>

using namespace Tubras;

#ifdef WIN32
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
#endif

static irr::core::stringc m_scriptName="";

class ScriptErrorHandler : public TConfigErrorHandler
{
public:
    int handleError(irr::core::stringc fileName, int line, int code, irr::core::stringc errMessage)
    {
        printf("CLSL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
        return 0;
    }
};

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: tcslint <options> -i[input file] \n\n");
    printf("       <options> - Config Syntax Checker options:\n");
    printf("                     -s : dump symbol table\n");
    printf("                     -o : dump object info\n");
    printf("\n");
    printf("    [input file] - Configuration file.\n\n");
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{

    bool oDumpST=false;
    bool oDumpOI=false;

    printf("tcslint 0.1 Copyright(C) 2008-2011 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "soi:")) != EOF)
    {
        switch (c)
        {
        case 's':
            oDumpST = true;
            break;
        case 'o':
            oDumpOI = true;
            break;
        case 'i':
            m_scriptName = optarg;
            break;
        };
            
    }

    if(!m_scriptName.size())
    {
        if(optind >= argc)
        {
            showUsage();
            return 1;
        }
        m_scriptName = argv[optind++];
    }

    fprintf(stdout, "Input Script: %s\n",m_scriptName.c_str());
    ScriptErrorHandler errorHandler;

    TConfig*   tsl = new TConfig();

    TConfigStatus status = tsl->loadScript(m_scriptName,
        oDumpST, oDumpOI, &errorHandler);

    if(status != E_OK)
    {
        fprintf(stderr, "Script Load Error\n");
    }
    else fprintf(stdout, "\nNo Errors\n\n");


    delete tsl;
}
