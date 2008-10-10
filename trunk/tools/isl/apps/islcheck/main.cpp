#include "CISL.h"
#include "getopt.h"
#include <errno.h>

static irr::core::stringc m_scriptName="";

//-----------------------------------------------------------------------------
//                              f i l e E x i s t s
//-----------------------------------------------------------------------------
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

    if(!fileExists(m_scriptName))
    {
        printf("\nError: Input Script Doesn't Exist\n");
        return 1;
    }

    CISL::CISL*   script = new CISL::CISL();

    script->processScript(m_scriptName);

    delete script;
}