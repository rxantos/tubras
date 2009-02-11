//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifdef TUBRAS_PLATFORM_WIN32
	#if !defined ( _WIN32_WCE )
		#include <io.h>
		#include <direct.h>
	#endif
#else
	#include <unistd.h>
	#include <limits.h>
	#include <stdlib.h>
#endif
#include <errno.h>
#include <stdio.h>

/*
static Tubras::TString scancodes[]=
{
    "0x00","esc","1","2","3","4","5","6","7","8","9","0",
    "minus","equal","back","tab",
    "q","w","e","r","t","y","u","i","o","p",
    "lbracket","rbracket","return","lcontrol",
    "a","s","d","f","g","h","j","k","l",
    "semicolon","apostrophe","grave","lshift","backslash",
    "z","x","c","v","b","n","m",
    "comma","period","slash","rshift","multiply","lmenu","space","capital",
    "f1","f2","f3","f4","f5","f6","f7","f8","f9","f10",
    "numlock","scroll","numpad7","numpad8","numpad9","subtract",
    "numpad4","numpad5","numpad6","add","numpad1","numpad2","numpad3",
    "numpad0","decimal","0x54","0x55","oem_102","f11","f12","0x59",										
    "0x5a","0x5b","0x5c","0x5d","0x5e","0x5f","0x60","0x61","0x62",
    "0x63","f13","f14","f15","0x67","0x68","0x69","0x6a","0x6b",
    "0x6c","0x6d","0x6e","0x6f","kana","0x71","0x72","abnt_c1",
    "0x74","0x75","0x76","0x77","0x78","convert", "0x7a","noconvert", 
    "0x7c","yen","abnt_c2","0x7f","0x80","0x81","0x82","0x83","0x84",
    "0x85","0x86","0x87","0x88","0x89","0x8a","0x8b","0x8c",
    "numpadequals","0x8e","0x8f","prevtrack","at","colon","underline",
    "kanji","stop","ax","unlabeled", "0x98","nexttrack", "0x9a",
    "0x9b","numpadenter","rcontrol", "0x9e", "0x9f","mute","calculater",
    "playpause", "0xa3","mediastop","0xa5","0xa6","0xa7","0xa8","0xa9",
    "0xaa","0xab","0xac","0xad","volumedown", "0xaf","volumeup", "0xb1",
    "webhome","numpadcomma", "0xb4","divide", "0xb6","prtscr","rmenu",
    "0xb9","0xba","0xbb","0xbc","0xbd","0xbe", "0xbf","0xc0","0xc1",
    "0xc2","0xc3","0xc4","pause","0xc6","home","up","pgup","0xca",
    "left", "0xcc","right", "0xce","end","down","pgdown","insert",
    "delete","0xd4","0xd5","0xd6","0xd7","0xd8","0xd9","0xda","lwin",
    "rwin","apps","power","sleep","0xe0","0xe1","0xe2","wake", "0xe4",
    "websearch","webfavorites","webstop","webforward","webback",
    "mycomputer","mail","mediaselect"
};
*/

static Tubras::TString scancodes[]=
{
    "0x00",     // 0x00
    "0x01",     // KEY_LBUTTON          = 0x01,  // Left mouse button
    "0x02",     // KEY_RBUTTON          = 0x02,  // Right mouse button
    "break",    // KEY_CANCEL           = 0x03,  // Control-break processing		
	"0x04",     // KEY_MBUTTON          = 0x04,  // Middle mouse button (three-button mouse)
	"0x05",     //	KEY_XBUTTON1         = 0x05,  // Windows 2000/XP: X1 mouse button
	"0x06",     //	KEY_XBUTTON2         = 0x06,  // Windows 2000/XP: X2 mouse button
    "0x07",
	"back",     //	KEY_BACK             = 0x08,  // BACKSPACE key
	"tab",      //	KEY_TAB              = 0x09,  // TAB key
    "0x0a", "0x0b",
	"clear",    //	KEY_CLEAR            = 0x0C,  // CLEAR key
	"return",   //	KEY_RETURN           = 0x0D,  // ENTER key
    "0x0e", "0x0f",
	"shift",    //	KEY_SHIFT            = 0x10,  // SHIFT key
	"control",  //	KEY_CONTROL          = 0x11,  // CTRL key
	"alt",      //	KEY_MENU             = 0x12,  // ALT key
	"pause",    //	KEY_PAUSE            = 0x13,  // PAUSE key
	"capital",  //	KEY_CAPITAL          = 0x14,  // CAPS LOCK key
	"kana",     //	KEY_KANA             = 0x15,  // IME Kana mode
    "0x16",    
    "junja",    //KEY_JUNJA            = 0x17,  // IME Junja mode
	"final",    //KEY_FINAL            = 0x18,  // IME final mode
	"hanja",    //	KEY_HANJA            = 0x19,  // IME Hanja mode
    "0x1a",
	"esc",      //	KEY_ESCAPE           = 0x1B,  // ESC key
	"convert",  //	KEY_CONVERT          = 0x1C,  // IME convert
	"nonconvert",   //	KEY_NONCONVERT       = 0x1D,  // IME nonconvert
	"accept",   //	KEY_ACCEPT           = 0x1E,  // IME accept
	"modechange",   //	KEY_MODECHANGE       = 0x1F,  // IME mode change request
	"space",    //	KEY_SPACE            = 0x20,  // SPACEBAR
	"prior",    //	KEY_PRIOR            = 0x21,  // PAGE UP key
    "next",     //	KEY_NEXT             = 0x22,  // PAGE DOWN key
	"end",      //	KEY_END              = 0x23,  // END key
	"home",     //	KEY_HOME             = 0x24,  // HOME key
	"left",     //	KEY_LEFT             = 0x25,  // LEFT ARROW key
	"up",       //	KEY_UP               = 0x26,  // UP ARROW key
    "right",    //	KEY_RIGHT            = 0x27,  // RIGHT ARROW key
	"down",     //	KEY_DOWN             = 0x28,  // DOWN ARROW key
	"select",   //	KEY_SELECT           = 0x29,  // SELECT key
	"print",    //	KEY_PRINT            = 0x2A,  // PRINT key
	"exec",     //	KEY_EXECUT           = 0x2B,  // EXECUTE key
	"prtscr",   //	KEY_SNAPSHOT         = 0x2C,  // PRINT SCREEN key
	"insert",   //	KEY_INSERT           = 0x2D,  // INS key
	"delete",   //	KEY_DELETE           = 0x2E,  // DEL key
	"help",     //	KEY_HELP             = 0x2F,  // HELP key
	"0",        //	KEY_KEY_0            = 0x30,  // 0 key
	"1",        //	KEY_KEY_1            = 0x31,  // 1 key
	"2",        //	KEY_KEY_2            = 0x32,  // 2 key
	"3",        //	KEY_KEY_3            = 0x33,  // 3 key
	"4",        //	KEY_KEY_4            = 0x34,  // 4 key
	"5",        //	KEY_KEY_5            = 0x35,  // 5 key
	"6",        //	KEY_KEY_6            = 0x36,  // 6 key
	"7",        //	KEY_KEY_7            = 0x37,  // 7 key
	"8",        //	KEY_KEY_8            = 0x38,  // 8 key
	"9",        //	KEY_KEY_9            = 0x39,  // 9 key
    "0x3a", "0x3b", "0x3c", "0x3d", "0x3e", "0x3f", "0x40",
	"a",        //	KEY_KEY_A            = 0x41,  // A key
	"b",        //	KEY_KEY_B            = 0x42,  // B key
	"c",        //	KEY_KEY_C            = 0x43,  // C key
	"d",        //	KEY_KEY_D            = 0x44,  // D key
	"e",        //	KEY_KEY_E            = 0x45,  // E key
	"f",        //	KEY_KEY_F            = 0x46,  // F key
	"g",        //	KEY_KEY_G            = 0x47,  // G key
	"h",        //	KEY_KEY_H            = 0x48,  // H key
	"i",        //	KEY_KEY_I            = 0x49,  // I key
	"j",        //	KEY_KEY_J            = 0x4A,  // J key
	"k",        //	KEY_KEY_K            = 0x4B,  // K key
	"l",        //	KEY_KEY_L            = 0x4C,  // L key
	"m",        //	KEY_KEY_M            = 0x4D,  // M key
	"n",        //	KEY_KEY_N            = 0x4E,  // N key
    "o",        //	KEY_KEY_O            = 0x4F,  // O key
    "p",        //	KEY_KEY_P            = 0x50,  // P key
	"q",        //	KEY_KEY_Q            = 0x51,  // Q key
	"r",        //	KEY_KEY_R            = 0x52,  // R key
	"s",        //	KEY_KEY_S            = 0x53,  // S key
	"t",        //	KEY_KEY_T            = 0x54,  // T key
	"u",        //	KEY_KEY_U            = 0x55,  // U key
	"v",        //	KEY_KEY_V            = 0x56,  // V key
	"w",        //	KEY_KEY_W            = 0x57,  // W key
	"x",        //	KEY_KEY_X            = 0x58,  // X key
	"y",        //	KEY_KEY_Y            = 0x59,  // Y key
	"z",        //	KEY_KEY_Z            = 0x5A,  // Z key
	"lwin",     //	KEY_LWIN             = 0x5B,  // Left Windows key (Microsoft� Natural� keyboard)
	"rwin",     //	KEY_RWIN             = 0x5C,  // Right Windows key (Natural keyboard)
	"apps",     //	KEY_APPS             = 0x5D,  //Applications key (Natural keyboard)
    "0x53",
	"sleep",    //	KEY_SLEEP            = 0x5F,  // Computer Sleep key
	"numpad0",  //	KEY_NUMPAD0          = 0x60,  // Numeric keypad 0 key
	"numpad1",  //	KEY_NUMPAD1          = 0x61,  // Numeric keypad 1 key
	"numpad2",  //	KEY_NUMPAD2          = 0x62,  // Numeric keypad 2 key
	"numpad3",  //	KEY_NUMPAD3          = 0x63,  // Numeric keypad 3 key
	"numpad4",  //	KEY_NUMPAD4          = 0x64,  // Numeric keypad 4 key
    "numpad5",  //	KEY_NUMPAD5          = 0x65,  // Numeric keypad 5 key
	"numpad6",  //	KEY_NUMPAD6          = 0x66,  // Numeric keypad 6 key
	"numpad7",  //	KEY_NUMPAD7          = 0x67,  // Numeric keypad 7 key
	"numpad8",  //	KEY_NUMPAD8          = 0x68,  // Numeric keypad 8 key
	"numpad9",  //	KEY_NUMPAD9          = 0x69,  // Numeric keypad 9 key
	"multiply",    //	KEY_MULTIPLY         = 0x6A,  // Multiply key
	"add",      //	KEY_ADD              = 0x6B,  // Add key
	"separator",    //	KEY_SEPARATOR        = 0x6C,  // Separator key
	"subtract", //	KEY_SUBTRACT         = 0x6D,  // Subtract key
	"decimal",  //	KEY_DECIMAL          = 0x6E,  // Decimal key
	"divide",   //	KEY_DIVIDE           = 0x6F,  // Divide key
	"f1",   //	KEY_F1               = 0x70,  // F1 key
	"f2",   //	KEY_F2               = 0x71,  // F2 key
	"f3",   //	KEY_F3               = 0x72,  // F3 key
	"f4",   //	KEY_F4               = 0x73,  // F4 key
	"f5",   //	KEY_F5               = 0x74,  // F5 key
	"f6",   //	KEY_F6               = 0x75,  // F6 key
	"f7",   //	KEY_F7               = 0x76,  // F7 key
	"f8",   //	KEY_F8               = 0x77,  // F8 key
	"f9",   //	KEY_F9               = 0x78,  // F9 key
	"f10",  //	KEY_F10              = 0x79,  // F10 key
	"f11",  //	KEY_F11              = 0x7A,  // F11 key
	"f12",  //	KEY_F12              = 0x7B,  // F12 key
	"f13",  //	KEY_F13              = 0x7C,  // F13 key
	"f14",  //	KEY_F14              = 0x7D,  // F14 key
	"f15",  //	KEY_F15              = 0x7E,  // F15 key
	"f16",  //	KEY_F16              = 0x7F,  // F16 key
	"f17",  //	KEY_F17              = 0x80,  // F17 key
	"f18",  //	KEY_F18              = 0x81,  // F18 key
	"f19",  //	KEY_F19              = 0x82,  // F19 key
	"f20",  //	KEY_F20              = 0x83,  // F20 key
	"f21",  //	KEY_F21              = 0x84,  // F21 key
	"f22",  //	KEY_F22              = 0x85,  // F22 key
	"f23",  //	KEY_F23              = 0x86,  // F23 key
	"f24",  //	KEY_F24              = 0x87,  // F24 key
    "0x88", "0x89", "0x8a", "0x8b", "0x8c", "0x8d", "0x8e", "0x8f",
	"numlock",  //	KEY_NUMLOCK          = 0x90,  // NUM LOCK key
	"scroll",   //	KEY_SCROLL           = 0x91,  // SCROLL LOCK key
    "0x92", "0x93", "0x94", "0x95", "0x96", "0x97", "0x98", "0x99",
    "0x9a", "0x9b", "0x9c", "0x9d", "0x9e", "0x9f",
	"lshift",   //	KEY_LSHIFT           = 0xA0,  // Left SHIFT key
	"rshift",   //	KEY_RSHIFT           = 0xA1,  // Right SHIFT key
	"lcontrol", //	KEY_LCONTROL         = 0xA2,  // Left CONTROL key
	"rcontrol", //	KEY_RCONTROL         = 0xA3,  // Right CONTROL key
	"lmenu",    //	KEY_LMENU            = 0xA4,  // Left MENU key
	"rmenu",    //	KEY_RMENU            = 0xA5,  // Right MENU key
    "0xa6", "0xa7", "0xa8", "0xa9", "0xaa", "0xab", "0xac", "0xad", "0xae", "0xaf",
    "0xb0", "0xb1", "0xb2", "0xb3", "0xb4", "0xb5", "0xb6", "0xb7", "0xb8", 
    "0xb9", "0xba", 
	"plus",     //	KEY_PLUS             = 0xBB,  // Plus Key   (+)
	"comma",    //	KEY_COMMA            = 0xBC,  // Comma Key  (,)
	"minus",    //	KEY_MINUS            = 0xBD,  // Minus Key  (-)
	"period",   //	KEY_PERIOD           = 0xBE,  // Period Key (.)
    "0xbf", "0xf0", "0xf1", "0xf2", "0xf3", "0xf4", "0xf5", 
	"attn", //	KEY_ATTN             = 0xF6,  // Attn key
	"crsel",    //	KEY_CRSEL            = 0xF7,  // CrSel key
	"exsel",    //	KEY_EXSEL            = 0xF8,  // ExSel key
	"ereof",    //	KEY_EREOF            = 0xF9,  // Erase EOF key
	"play", //	KEY_PLAY             = 0xFA,  // Play key
	"zoom", //	KEY_ZOOM             = 0xFB,  // Zoom key
    "0xfc",
	"pa1",  //	KEY_PA1              = 0xFD,  // PA1 key
	"clear"	// KEY_OEM_CLEAR        = 0xFE,   // Clear key
    
    };


namespace Tubras
{
    static TString  TButtonNames[] =
    {
        "left", "right", "middle", "left", "right", "middle"
    };


    //-----------------------------------------------------------------------
    //                       T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::TInputHandler() : m_eventManager(getEventManager()),
        m_binder(0),
        m_GUIEnabled(true),
        m_GUIExclusive(false),
        m_kpEvent(0),
        m_krEvent(0),
        m_mmEvent(0),
        m_mpEvent(0),
        m_mrEvent(0)
    {
        memset(m_keyStates,0,sizeof(m_keyStates));
    }

    //-----------------------------------------------------------------------
    //                     ~ T I n p u t H a n d l e r 
    //-----------------------------------------------------------------------
    TInputHandler::~TInputHandler()
    {
        if(m_binder)
            delete m_binder;

        if(m_kpEvent)
            m_kpEvent->drop();
        if(m_krEvent)
            m_krEvent->drop();
        if(m_mmEvent)
            m_mmEvent->drop();
        if(m_mpEvent)
            m_mpEvent->drop();
        if(m_mrEvent)
            m_mrEvent->drop();
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TInputHandler* TSingleton<TInputHandler>::ms_Singleton = 0;

    TInputHandler* TInputHandler::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TInputHandler& TInputHandler::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TInputHandler::Initialize()
    {
        int result=0;

        m_binder = new TInputBinder();
        if(m_binder->initialize())
            result = 1;

        m_kpEvent= new TEvent();
        m_kpEvent->addIntParameter(0);
        m_kpEvent->addIntParameter(0);

        m_krEvent= new TEvent();
        m_krEvent->addIntParameter(0);
        m_krEvent->addIntParameter(0);

        m_mmEvent = new TEvent("input.mouse.move");
        m_mmEvent->addPointerParameter(0);

        m_mpEvent= new TEvent();
        m_mpEvent->addPointerParameter(0);

        m_mrEvent= new TEvent();
        m_mrEvent->addPointerParameter(0);

        return result;
    }

    //-----------------------------------------------------------------------
    //                           k e y P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyPressed( const struct SEvent& arg ) 
    {
        if(m_GUIEnabled)
        {
            IGUIEnvironment* gui = getApplication()->getRenderer()->getGUIManager();

		    if (gui)
			    gui->postEventFromUser(arg);

            if(m_GUIExclusive)
                return true;
        }        

        TString sKeyString = "key.down.";
        sKeyString += scancodes[arg.KeyInput.Key];
        m_kpEvent->setName(sKeyString);
        m_kpEvent->getParameter(0)->setIntValue(arg.KeyInput.Key);
        m_kpEvent->getParameter(1)->setIntValue(1);

        m_eventManager->send(m_kpEvent);

        m_binder->processKey(sKeyString);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        k e y R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::keyReleased( const struct SEvent& arg ) 
    {
        if(m_GUIEnabled)
        {
            IGUIEnvironment* gui = getApplication()->getRenderer()->getGUIManager();

		    if (gui)
			    gui->postEventFromUser(arg);

            if(m_GUIExclusive)
                return true;
        }        

        TString sKeyString = "key.up.";
        sKeyString += scancodes[arg.KeyInput.Key];
        m_krEvent->setName(sKeyString);
        m_krEvent->getParameter(0)->setIntValue(arg.KeyInput.Key);
        m_krEvent->getParameter(1)->setIntValue(1);

        m_eventManager->send(m_krEvent);

        m_binder->processKey(sKeyString);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseMoved( const struct SEvent& arg ) {

        if(m_GUIEnabled)
        {
            IGUIEnvironment* gui = getApplication()->getRenderer()->getGUIManager();

		    if (gui)
			    gui->postEventFromUser(arg);

            if(m_GUIExclusive)
                return true;
        }        

#ifdef _DEBUG
        TStrStream msg;
        if(getApplication()->getDebug() >= 7)
        {
            msg << "input.mouse.move: (" << arg.MouseInput.X << "," 
                << arg.MouseInput.Y << ")";
            getApplication()->logMessage(msg.str().c_str());
        }
#endif

        m_mmEvent->getParameter(0)->setPointerValue((void*)&arg);

        m_eventManager->send(m_mmEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                        m o u s e P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mousePressed( const struct SEvent& arg ) {

        if(m_GUIEnabled)
        {
            IGUIEnvironment* gui = getApplication()->getRenderer()->getGUIManager();

		    if (gui)
			    gui->postEventFromUser(arg);

            if(m_GUIExclusive)
                return true;
        }        


#ifdef _DEBUG
        TStrStream msg;
        msg << "input.mouse.down." << TButtonNames[arg.MouseInput.Event].c_str() << ": (" << arg.MouseInput.X << "," 
            << arg.MouseInput.Y << ")";
        getApplication()->logMessage(msg.str().c_str());
#endif

        TString eventMsg = "input.mouse.down.";
        eventMsg += TButtonNames[arg.MouseInput.Event];
        m_mpEvent->setName(eventMsg);
        m_mpEvent->getParameter(0)->setPointerValue((void *)&arg);
        m_eventManager->send(m_mpEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                      m o u s e R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::mouseReleased( const struct SEvent& arg ) {

        if(m_GUIEnabled)
        {
            IGUIEnvironment* gui = getApplication()->getRenderer()->getGUIManager();

		    if (gui)
			    gui->postEventFromUser(arg);

            if(m_GUIExclusive)
                return true;
        }        


#ifdef _DEBUG
        TStrStream msg;
        msg << "input.mouse.up." << TButtonNames[arg.MouseInput.Event].c_str() << ": (" << arg.MouseInput.X << "," 
            << arg.MouseInput.Y << ")";
        getApplication()->logMessage(msg.str().c_str());
#endif

        TString eventMsg = "input.mouse.up.";
        eventMsg += TButtonNames[arg.MouseInput.Event];

        m_mrEvent->setName(eventMsg);
        m_mrEvent->getParameter(0)->setPointerValue((void *)&arg);
        m_eventManager->send(m_mrEvent);

        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n P r e s s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonPressed( const struct SEvent& arg ) {
        std::cout << "Joy ButtonPressed: " << arg.JoystickEvent.ButtonStates << "\n";
        //m_pInput->type = OISMouse;
        return true;
    }

    //-----------------------------------------------------------------------
    //                      b u t t o n R e l e a s e d
    //-----------------------------------------------------------------------
    bool TInputHandler::buttonReleased( const struct SEvent& arg) {
        std::cout << "Joy ButtonReleased: " << arg.JoystickEvent.ButtonStates << "\n";
        //m_pInput->type = OISMouse;
        return true; 
    }

    //-----------------------------------------------------------------------
    //                          a x i s M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::axisMoved( const struct SEvent& arg )
    {
        //std::cout << "\nJoy Axis: " << axis 
        //	  << " absolute X: " << arg.state.mAxes[axis].abX 
        //	  << " absolute Y: " << arg.state.mAxes[axis].abY
        //	  << " absolute Z: " << arg.state.mAxes[axis].abZ << std::endl;
        //m_pInput->type = OISJoyStick;
        return true;
    }

    //-----------------------------------------------------------------------
    //                           p o v M o v e d
    //-----------------------------------------------------------------------
    bool TInputHandler::povMoved( const struct SEvent& arg )
    {
        /*
        std::cout << "Joy POV (" << pov + 1 
        << ") Moved.Value = " << arg.state.mPOV[pov] << std::endl;
        m_pInput->type = OISJoyStick; 
        */
        return true;
    }

    //-----------------------------------------------------------------------
    //                           O n E v e n t
    //-----------------------------------------------------------------------
    bool TInputHandler::OnEvent(const SEvent& event)
    {
        bool result=false;
        switch(event.EventType)
        {
        case EET_KEY_INPUT_EVENT:
            if(m_keyStates[event.KeyInput.Key] = event.KeyInput.PressedDown)
                return keyPressed(event);
            else return keyReleased(event);
            break;
        case EET_MOUSE_INPUT_EVENT:
            if(event.MouseInput.Event == EMIE_MOUSE_MOVED)
                return mouseMoved(event);
            else if(event.MouseInput.Event <= EMIE_MMOUSE_PRESSED_DOWN)
                return mousePressed(event);
            else if(event.MouseInput.Event <= EMIE_MMOUSE_LEFT_UP)
                return mouseReleased(event);
            break;
        case EET_JOYSTICK_INPUT_EVENT:
            break;
        default:
            break;
        }

        return result;
    }

}

