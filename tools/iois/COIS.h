#ifndef _COIS_H_
#define _COIS_H_
#include "ois.h"
#ifdef _IRR_WINDOWS_
#include "windows.h"
#endif

using namespace irr;
using namespace irr::gui;
class COIS : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
{
private:
    IrrlichtDevice*         m_device;
    IGUIEnvironment*        m_gui;
    OIS::InputManager*      m_inputManager;
    void*			        m_windowHandle;
    u32                     m_display;
    bool                    m_showCursor;
    bool                    m_GUIEnabled;
    bool                    m_GUIExclusive;
    OIS::Keyboard*		    m_keyboard;
    OIS::Mouse*			    m_mouse;
    OIS::JoyStick*          m_joys[4];
    OIS::ForceFeedback*     m_ff[4];
    int                     m_numSticks;
public:
    COIS(IrrlichtDevice* idevice, bool showCursor=true);
    virtual ~COIS();
    int initialize();
    int capture();
    void setGUIEnabled(bool enabled);
    bool getGUIEnabled() {}
    void setGUIExclusive(bool exclusive);
    bool isKeyDown(OIS::KeyCode key);
    void setDisplaySize(int width, int height);
#ifdef _IRR_WINDOWS_
	static LRESULT _wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif


    // handlers
    virtual bool keyPressed( const OIS::KeyEvent& arg );
    virtual bool keyReleased( const OIS::KeyEvent& arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ); 
    virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
    virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
    virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
    virtual bool povMoved( const OIS::JoyStickEvent &arg, int pov );

};

#endif
