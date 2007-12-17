#ifndef _SANDBOX_H_
#define _SANDBOX_H_
#include "tubras.h"

using namespace Tubras;
class TSandbox : public TApplication
{
public:
    TSandbox(int argc,char **argv);
    ~TSandbox();
    int initialize();
    int toggleDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    void testInterval(double T, void* userData);
};

#endif