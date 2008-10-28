//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "CISL.h"
#include "getopt.h"
#include <errno.h>

static irr::core::stringc m_scriptName="";

//-----------------------------------------------------------------------------
//                               s h o w U s a g e
//-----------------------------------------------------------------------------
void showUsage()
{
    printf("usage: islcheck <options> -i[input file] \n\n");
    printf("       <options> - ISL Syntax Checker options:\n");
    printf("                     -c : generate \"C\" structures\n");
    printf("                     -s : dump symbol table\n");
    printf("\n");
    printf("    [input file] - ISL file.\n\n");
}

//-----------------------------------------------------------------------------
//                                   m a i n
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    bool oGenC=false;
    bool oDumpST=false;

    printf("islcheck 0.1 Copyright(C) 2008 Tubras Software, Ltd\n\n");

    if(argc < 2)
    {
        showUsage();
        return 1;
    }

    int c;
    while ((c = getopt(argc, argv, "csi:")) != EOF)
    {
        switch (c)
        {
        case 'c':
            oGenC = true;
            break;
        case 's':
            oDumpST = true;
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

    printf(" Input Script: %s\n",m_scriptName.c_str());

    CISL::CISL*   script = new CISL::CISL();

    CISL::CISLStatus status = script->parseScript(m_scriptName);
    if(status != CISL::E_OK)
    {
        fprintf(stderr, "Check Errors\n");
    }

    delete script;
}