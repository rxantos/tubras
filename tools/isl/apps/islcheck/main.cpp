#include "CISL.h"


int main(int argc, char* argv[])
{
    CISL::CISL*   script = new CISL::CISL();

    script->validateScript(argv[1]);

    delete script;
}