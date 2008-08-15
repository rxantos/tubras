#ifndef _COIS_H_
#define _COIS_H_
#include "OIS.h"
#ifdef _IRR_WINDOWS_
#include "windows.h"
#endif

#define MAX_JOYS    4

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
    bool                    m_buffered;
    bool                    m_debugEnabled;
    bool                    m_GUIEnabled;
    bool                    m_GUIExclusive;
    OIS::Keyboard*		    m_keyboard;
    OIS::Mouse*			    m_mouse;
    OIS::JoyStick*          m_joys[MAX_JOYS];
    OIS::ForceFeedback*     m_ff[MAX_JOYS];
    u32                     m_numSticks;



public:
    COIS(IrrlichtDevice* idevice, bool showCursor=true, bool buffered=true, bool debugEnabled=false);
    virtual ~COIS();
    int initialize();
    int capture();
    void setDebugEnabled(bool value) {m_debugEnabled = value;}
    void setGUIEnabled(bool value) {m_GUIEnabled = value;}
    bool getGUIEnabled() {return m_GUIEnabled;}
    void setGUIExclusive(bool value) {m_GUIExclusive = value;}
    bool getGUIExclusive() {return m_GUIExclusive;}
    EKEY_CODE getIrrKeyCode(OIS::KeyCode key);
    bool isKeyDown(OIS::KeyCode key);
    void setDisplaySize(int width, int height);
    u32  getNumSticks() {return m_numSticks;}
    bool hasForceFeedback(u32 stickNumber);
#ifdef _IRR_WINDOWS_
    LONG_PTR m_oldWndProc;
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
