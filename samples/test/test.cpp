#include "Tubras.h"
#include "test.h"
#include <stdlib.h>

using namespace Tubras;

class TTestApp : public TApplication
{
private:
    int         screenNumber;

public:
    TTestApp(int argc,char **argv) : TApplication(argc,argv) 
    {
        getApplication()->setGUIScheme("TaharezLookSkin.scheme","TaharezLook");
        getApplication()->setThemeDirectory("themes");
    }

    virtual ~TTestApp()
    {
    }

    //
    // show/hide the console
    //
    int TTestApp::showConsole(Tubras::TSEvent event)
    {
        toggleConsole();
        return 1;
    }

    //
    // take a screen shot of our window.
    //
    int TTestApp::saveScreen(Tubras::TSEvent event)
    {
        
        TStrStream fileName;
        string ext;

        ext = getConfigFile()->getSetting("ScreenCapExt","Options");

        fileName << "cap" << screenNumber++ << "." << ext;

        captureScreen(fileName.str().c_str());
        return 0;
    }

    //
    // normally we would only override this if we aren't using
    // the state management functionality. 
    //
    int initialize()
    {
        //
        // invoke TApplication initialize which initializes all of the
        // sub-systems (render, sound, input etc.)
        //
        if(TApplication::initialize())
            return 1;

        //
        // take a screen shot when the Print-Scrn is pressed
        //
        acceptEvent("key.down.Key_183",EVENT_DELEGATE(TTestApp::saveScreen));

        //
        // allow the engine console to be toggled
        //
        acceptEvent("key.down.F12",EVENT_DELEGATE(TTestApp::showConsole));

        screenNumber = 1;

        return 0;

    }

	//
	// override the applications createStates() to create our 
	// own individual states. If we chose not to override this, our 
	// application class derivative would be the only active state.
	//
    int createStates()
    {
        new TSplashState();
        new TMenuState();
        new TPlayState();
        new TOptionsState();
        new TPauseState();

		string istate = m_configFile->getSetting("InitialState","Options");
		if(istate.empty())
			istate = "splashState";
		setInitialState(istate);
        return 0;
    }

    //
    // override the applications createThemeClass() to return 
    // an instance of our theme subclass.
    //
    Tubras::TTheme* createThemeClass(string baseDir)
    {
        return new TTestTheme(baseDir);
    }



};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif

        TTestApp app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;

    }

