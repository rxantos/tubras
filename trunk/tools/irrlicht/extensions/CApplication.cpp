#include "CApplication.h"

#ifdef _IRR_WINDOWS_
#if !defined ( _WIN32_WCE )
#include <io.h>
#include <direct.h>
#endif
#endif

namespace irr
{
    //-------------------------------------------------------------------------
    //                           C A p p l i c a t i o n
    //-------------------------------------------------------------------------
    CApplication::CApplication(const core::stringc& title) : IEventReceiver(),
        IReferenceCounted(),
        m_running(false), m_title(title), m_capNumber(1), m_argc(0), m_argv(0),
        m_device(0), m_nullDevice(0), m_videoDriver(0), m_sceneManager(0), 
        m_fileSystem(0), m_gui(0), m_defaultFont(0),
        m_monoFont(0), m_camera(0), m_world(0), m_collisionResponse(0),
        m_logFile(0)
    {
    }

    //-------------------------------------------------------------------------
    //                          ~ C A p p l i c a t i o n
    //-------------------------------------------------------------------------
    CApplication::~CApplication()
    {
        if(m_logFile)
            m_logFile->drop();

        if(m_nullDevice)
            m_nullDevice->drop();

        if(m_defaultFont)
            m_defaultFont->drop();

        if(m_monoFont)
            m_monoFont->drop();

        if(m_device)
            m_device->drop();
    }

    //-------------------------------------------------------------------------
    //                      _ i n i t F i l e S y s t e m s
    //-------------------------------------------------------------------------
    int CApplication::_initFileSystems()
    {
        IAttributes* pa = m_config->getSection("filesystems");
        u32 count = pa->getAttributeCount();

        stringc fs="",fn="";
        for(u32 i=0;i<count;i++)
        {
            fn = pa->getAttributeName(i);
            fs = pa->getAttributeAsString(i);
            if(fn.equals_ignore_case("folder"))
            {
                fs = m_fileSystem->getAbsolutePath(fs);
                fs = m_fileSystem->flattenFilename(fs);
                if(!m_fileSystem->addFolderFileArchive(fs.c_str(), false, false))
                {
                    stringc msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else if(fn.equals_ignore_case("zipfile"))
            {
                if(!m_fileSystem->addZipFileArchive(fs.c_str()))
                {
                    stringc msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else if(fn.equals_ignore_case("pakfile"))
            {
                if(!m_fileSystem->addPakFileArchive(fs.c_str()))
                {
                    stringc msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else 
            {
                stringc msg = "Unknown FileSystem Type: ";
                msg += fn;
                logMessage(msg.c_str());
            }

        }
        return 0;
    }

    //-------------------------------------------------------------------------
    //                                O n E v e n t
    //-------------------------------------------------------------------------
    bool CApplication::OnEvent(const SEvent& event)
    {
        switch(event.EventType)
        {
        case EET_LOG_TEXT_EVENT:
            logMessage(event.LogEvent.Text);
            break;
        case EET_KEY_INPUT_EVENT:
            {
                switch(event.KeyInput.Key)
                {
                case KEY_LSHIFT:
                case KEY_SHIFT:
                    {
                        core::list<ISceneNodeAnimator*>::ConstIterator anims=m_camera->getAnimators().begin();
                        ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims;
                        if(event.KeyInput.PressedDown)
                        {
                            anim->setMoveSpeed(m_orgMoveSpeed * 3.f);
                        }
                        else
                        {
                            anim->setMoveSpeed(m_orgMoveSpeed);
                        }
                    }
                    break;

                case KEY_ESCAPE:
                    if( !event.KeyInput.PressedDown ) // key up?
                        m_running = false;
                    return true;
                case KEY_SNAPSHOT:
                    {
                        if( !event.KeyInput.PressedDown ) // key up?
                        {
                            video::IImage* image = m_videoDriver->createScreenShot();
                            char buf[32];

                            sprintf(buf,"cap%.2d.png",m_capNumber++);

                            m_videoDriver->writeImageToFile(image,buf);

                            image->drop();
                        }
                        break;
                    }
                default:
                    break;
                }

            }
            break;
        default:
            break;
        };
        return false;
    }

    //-------------------------------------------------------------------------
    //                              l o g M e s s a g e 
    //-------------------------------------------------------------------------
    void CApplication::logMessage(stringc msg)
    {
        printf(msg.c_str());
        printf("\n");
        if(m_logFile)
        {
            m_logFile->write(msg.c_str(),msg.size());
            m_logFile->write("\n",1);
        }
    }

    //-------------------------------------------------------------------------
    //                                   i n i t
    //-------------------------------------------------------------------------
    int CApplication::init()
    {
        SIrrlichtCreationParameters cp;
        static SKeyMap keyMap[]={
            {EKA_MOVE_FORWARD, KEY_KEY_W},
            {EKA_STRAFE_LEFT, KEY_KEY_A},
            {EKA_MOVE_BACKWARD, KEY_KEY_S},
            {EKA_STRAFE_RIGHT, KEY_KEY_D},
            {EKA_JUMP_UP, KEY_SPACE}
        };
        int result=0;
        stringc msg;


        // use null device for early file system access
        IrrlichtDevice* m_nullDevice = createDevice(EDT_NULL);
        IFileSystem* fileSystem = m_nullDevice->getFileSystem();

        m_currentDirectory = fileSystem->getWorkingDirectory();
        m_currentDirectory = fileSystem->flattenFilename(m_currentDirectory);
        if(m_argv)
        {
            m_appExecutable = m_argv[0];
        }
        else
        {
            m_appExecutable = "irrlicht.exe";
        }


        stringc appBaseName;
        appBaseName = fileSystem->getFileBasename(m_appExecutable, false);

        //
        // create log writer
        //
        m_logName = appBaseName;
        m_logName += ".log";

        m_logFile = fileSystem->createAndWriteFile(m_logName);

        msg = "Created log file: ";
        msg += m_logName;
        logMessage(msg);

        //
        // configuration system
        //
        // locate the data directory - underneath our executable or outside of it.
        stringc temp("data/");
        if(!fileSystem->existFile(temp))
        {
            temp = "../data/";
            // todo - look for "data.zip"...
        }
        m_dataRoot = fileSystem->getAbsolutePath(temp);
        m_configName = m_dataRoot;
        m_configName += "/cfg/";
        m_configName += fileSystem->getFileBasename(m_appExecutable, false);
        m_configName += ".xml";


        if(!fileSystem->existFile(m_configName))
        {
            // not in data/cfg or ../data/cfg so look in the working directory.
            m_configName = fileSystem->getFileBasename(m_appExecutable, false);
            m_configName += ".xml";
            if(!fileSystem->existFile(m_configName))
            {
                return -1;
            }
        }

        // load the config file
        m_config = new CXMLConfig();
        if(!m_config->load(m_configName))
        {
            return -1;
        }

        // setup the device based on config settings
        stringc sdriver = m_config->getString("driver","video","EDT_OPENGL");
        cp.DriverType = EDT_OPENGL;
        if(sdriver == "EDT_DIRECT3D9")
            cp.DriverType = EDT_DIRECT3D9;        
        cp.WindowSize = m_config->getDimension("resolution","video",dimension2di(800, 600));
        cp.Bits = m_config->getInt("colordepth","video",32);
        cp.Fullscreen = m_config->getBool("fullscreen","video",false);
        cp.Vsync = m_config->getBool("vsync","video",true);
        cp.Stencilbuffer = m_config->getBool("stencilbuffer","video",false);
        cp.AntiAlias = m_config->getInt("antialias","video",0);
        cp.EventReceiver = this;
        cp.WindowId = 0;

        m_device =  createDeviceEx(cp);
        if(!m_device)
            return -1;

        m_fileSystem = m_device->getFileSystem();
        m_videoDriver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_gui = m_device->getGUIEnvironment();

        m_device->getCursorControl()->setVisible(m_config->getBool("HWCursorVisible","video",true));
        m_device->setWindowCaption(stringw(m_title).c_str());


        //
        // add configured file systems
        //
        if(_initFileSystems())
            return -1;

        //
        // set up the default font
        //        
        stringc fontFolder = "fnt/";
        stringc defFonts = fontFolder + "defaults.zip";
        if(m_fileSystem->existFile(defFonts.c_str()))
        {
            m_fileSystem->addZipFileArchive(defFonts.c_str());
            m_defaultFont = m_gui->getFont("tdeffont.xml");
            if(m_defaultFont)
            {
                m_defaultFont->grab();
                m_gui->getSkin()->setFont(m_defaultFont);
            }
            m_monoFont = m_gui->getFont("monospace.xml");
            if(m_monoFont)
            {
                m_monoFont->grab();
            }
        }

        m_world = m_sceneManager->createMetaTriangleSelector();

        // camera setup
        f32 rotateSpeed = m_config->getFloat("rotateSpeed","options",100.f);
        m_orgMoveSpeed = m_config->getFloat("moveSpeed","options",0.03f);
        f32 jumpSpeed = m_config->getFloat("jumpSpeed","options",0.05f);
        m_camera = m_sceneManager->addCameraSceneNodeFPS(0, rotateSpeed, m_orgMoveSpeed, -1,keyMap,5,true, jumpSpeed);

        vector3df v = m_config->getVector3("campos","options");
        m_camera->setPosition(v);

        v = m_config->getVector3("camtarget","options");
        m_camera->setTarget(v);

        bool collisionEnabled = m_config->getBool("collision","options");
        if(collisionEnabled)
        {
            vector3df gravity,ellipsoid;
            gravity = m_config->getVector3("gravity","options",vector3df(0,-0.1f,0));
            ellipsoid = m_config->getVector3("ellipsoid","options",vector3df(2,5,2));
            m_collisionResponse = m_sceneManager->createCollisionResponseAnimator(m_world,m_camera,
                ellipsoid, gravity);
            m_camera->addAnimator(m_collisionResponse);
        }

        createScene();

        return result;
    }

    //-------------------------------------------------------------------------
    //                                  r u n 
    //-------------------------------------------------------------------------
    void CApplication::run()
    {
        m_running = true;
        while(m_device->run() && m_running)
        {
            m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

            m_sceneManager->drawAll();
            m_gui->drawAll();

            m_videoDriver->endScene();
        }
    }

}
