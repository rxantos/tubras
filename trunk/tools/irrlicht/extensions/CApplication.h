#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_
#include "irrlicht.h"
#include "CXMLConfig.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace irr
{
		//! Creates an archive from the filename
		/** \param file File handle to check.
		\return Pointer to newly created archive, or 0 upon error. */
    class CApplication : public IEventReceiver, public IReferenceCounted
    {
    protected:
        bool                    m_running;
        stringc                 m_title;
        int                     m_capNumber;
        f32                     m_orgMoveSpeed;
        f32                     m_orgJumpSpeed;
        int                     m_argc;
        const char**            m_argv;
        stringc                 m_currentDirectory;
        stringc                 m_appExecutable;
        stringc                 m_dataRoot;
        stringc                 m_configName;
        stringc                 m_logName;
        CXMLConfig*             m_config;


        IrrlichtDevice*         m_device;
        IrrlichtDevice*         m_nullDevice;
        IVideoDriver*           m_videoDriver;
        ISceneManager*          m_sceneManager;
        IFileSystem*            m_fileSystem;
        IGUIEnvironment*        m_gui;
        IGUIFont*               m_defaultFont;
        IGUIFont*               m_monoFont;
        ICameraSceneNode*       m_camera;
        IMetaTriangleSelector*  m_world;
        ISceneNodeAnimatorCollisionResponse* m_collisionResponse;
        IWriteFile*             m_logFile;

    protected:
        int _initFileSystems();

    public:
        //! CApplication Constructor
        /** \param title Window Title. */
        CApplication(const stringc& title="Irrlicht");

        virtual ~CApplication();

        ICameraSceneNode* getCamera() {return m_camera;}
        IMetaTriangleSelector* getWorld() {return m_world;}
        stringc getCurrentDirectory() {return m_currentDirectory;}
        IVideoDriver* getVideoDriver() {return m_videoDriver;}
        ISceneManager* getSceneManager() {return m_sceneManager;}
        IGUIEnvironment* getGUIEnvironment() {return m_gui;}
        ISceneNodeAnimatorCollisionResponse* getCollisionResponse() {return m_collisionResponse;}
        CXMLConfig* getConfig() {return m_config;}

        void setArgs(int argc,const char **argv) { m_argc = argc; m_argv = argv; }

        virtual bool OnEvent(const SEvent& event);

        void logMessage(stringc msg);

        //! Allows overriding classes to add scene content.  Invoked at the 
        //! end of "init()" if successful.
        virtual void createScene() {}

        //! Forces the run loop to exit.
        void stopRunning() {m_running=false;}

		//! Initializes the application object.  This method initializes 
        //! all the Irrlicht device and sub-systems. 
		/** \return 0 - success, otherwise error.*/
        virtual int init();

        //! Run loop.  Call "stopRunning()" method to exist the run loop.
        void run();
    };
}
#endif
