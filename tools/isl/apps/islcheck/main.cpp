//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "cisl.h"
#include "getopt.h"
#include <errno.h>

static irr::core::stringc m_scriptName="";
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

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: islcheck <options> -i[input file] \n\n");
    printf("       <options> - ISL Syntax Checker options:\n");
    printf("                     -a : dump AST\n");
    printf("                     -s : dump symbol table\n");
    printf("                     -o : dump object info\n");
    printf("\n");
    printf("    [input file] - ISL file.\n\n");
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{

    bool oDumpAST=false;
    bool oDumpST=false;
    bool oDumpOI=false;

    printf("islcheck 0.1 Copyright(C) 2008 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "asoi:")) != EOF)
    {
        switch (c)
        {
        case 'a':
            oDumpAST = true;
            break;
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

    isl::CISL*   script = new isl::CISL();

    isl::CISLStatus status = script->loadScript(m_scriptName,
        oDumpAST, oDumpST, oDumpOI);
    if(status != isl::E_OK)
    {
        fprintf(stderr, "Check Errors\n");
    }
    else fprintf(stdout, "\nNo Errors\n\n");


    delete script;
}
