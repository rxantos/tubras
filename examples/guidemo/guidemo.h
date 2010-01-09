//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _GUIDEMO_H_
#define _GUIDEMO_H_
#include "tubras.h"

using namespace Tubras;
class TGUIDemo : public TApplication
{
protected:
    TGUIScreen*         m_screen;
public:
    TGUIDemo();
    ~TGUIDemo();
    int initialize();
    int toggleDebug(const TEvent* event);
    int cycleDebug(const TEvent* event);
    int togglePhysicsDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    int onClick(const TEvent* event);
    void testInterval(double T, void* userData);

	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};

#endif

