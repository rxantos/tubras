//-----------------------------------------------------------------------------
// Copyright (c) 2006-2009 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <errno.h>

using namespace Tubras;

#ifdef WIN32
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
#else
namespace irr
{
    namespace core
    {
    IRRLICHT_API const matrix4 IdentityMatrix(matrix4::EM4CONST_IDENTITY);
    }
}
#endif

static irr::core::stringc m_scriptName="";

class ScriptErrorHandler : public TSLErrorHandler
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
    printf("usage: tslcheck <options> -i[input file] \n\n");
    printf("       <options> - TSL Syntax Checker options:\n");
    printf("                     -s : dump symbol table\n");
    printf("                     -o : dump object info\n");
    printf("\n");
    printf("    [input file] - TSL file.\n\n");
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{

    bool oDumpST=false;
    bool oDumpOI=false;

    printf("tslcheck 0.1 Copyright(C) 2008-2009 Tubras Software, Ltd\n\n");

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

    TSL*   tsl = new TSL();

    TSLStatus status = tsl->loadScript(m_scriptName,
        oDumpST, oDumpOI, &errorHandler);

    if(status != E_OK)
    {
        fprintf(stderr, "Script Load Error\n");
    }
    else fprintf(stdout, "\nNo Errors\n\n");


    delete tsl;
}
