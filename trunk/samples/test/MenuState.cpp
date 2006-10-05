#include "tubras.h"
#include "test.h"
#include "cegui/elements/ceguiframewindow.h"

#define SLIDE_DURATION 0.9f

TMenuState::TMenuState() : TState("menuState")
{
    slideDirection = -1;
    m_doQuit = false;
    m_doPlay = false;
    m_doOptions = false;
    m_centerMouse = true;
}

TMenuState::~TMenuState()
{
    if(sound1)
        delete sound1;
    if(sound2)
        delete sound2;
    if(ambientSound)
        delete ambientSound;

    if(m_finterval)
        delete m_finterval;
}

int TMenuState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = sm->getRootSceneNode()->createChildSceneNode("MenuParent");

    sound1 = loadSound("General", "slideout.ogg");
    sound2 = loadSound("General", "slidein.ogg");
    ambientSound = loadSound("General", "ambient.ogg");
    ambientSound->setLoop(true);

    m_parent->flipVisibility();

    m_finterval = new Tubras::TFunctionInterval("slideMenu",SLIDE_DURATION,
        FUNCINT_DELEGATE(TMenuState::slideMenu));

    m_finterval->setDoneEvent("app.slideDone");
    acceptEvent("app.slideDone",EVENT_DELEGATE(TMenuState::slideDone));

    CEGUI::System* system = getGUISystem();
    system->setMouseMoveScaling(1.2);

    m_GUIRoot = new Tubras::TWindow(getGUISheet(), "root");
    m_GUIRoot->setVisible(true);
    
    m_frame = new Tubras::TStaticImage(m_GUIRoot,"background_wnd","menuSheet.png");
    m_frame->setPosition(0.99,0.0);
    m_frame->setSize(0.5,1.0);

    //
    // playButton setup 
    //

    m_playButton = new Tubras::TImageButton(m_frame, "playButton","playbutton.png");
    m_playButton->setPosition(0.35,0.25);
    m_playButton->setSize(0.40,0.20);
    acceptEvent("gui.playButton_clicked",EVENT_DELEGATE(TMenuState::playClicked));

    //
    // optionsButton setup 
    //

    m_optionsButton = new Tubras::TImageButton(m_frame,"optionsButton","optionsbutton.png");
    m_optionsButton->setPosition(0.20,0.45);
    m_optionsButton->setSize(0.70,0.20);
    acceptEvent("gui.optionsButton_clicked",EVENT_DELEGATE(TMenuState::optionsClicked));

    //
    // quitButton setup 
    //

    m_quitButton = new Tubras::TImageButton(m_frame, "quitButton","quitbutton.png");
    m_quitButton->setPosition(0.35,0.65);
    m_quitButton->setSize(0.40,0.20);
    acceptEvent("gui.quitButton_clicked",EVENT_DELEGATE(TMenuState::quitClicked));

    m_parent->flipVisibility();
    m_GUIRoot->setVisible(false);

    return 0;
}

int TMenuState::quitApp(Tubras::TSEvent event)
{
    m_app->stopRunning();
    return 0;
}

int TMenuState::slideDone(Tubras::TSEvent)
{
    if(slideDirection < 0)
        slideDirection = 1;
    else slideDirection = -1;
    if(m_doQuit)
        m_app->stopRunning();
    else if(m_doPlay)
        changeState("playState");
    else if(m_doOptions)
        pushState("optionsState");
    else
    {
        CEGUI::MouseCursor::getSingleton().show();
        ambientSound->play();
    }
    return 0;
}


void TMenuState::slideMenu(double T, void* userData)
{
    double value;
    if(slideDirection > 0)
        value = 0.5f + ((T / SLIDE_DURATION) * 0.5f);
    else value = 1.0f - ((T / SLIDE_DURATION) * 0.5f);
    m_frame->setPosition(value,0.0);
}

int TMenuState::toggleMouse(Tubras::TSEvent)
{

    logMessage("toggleMouse event");
    if(CEGUI::MouseCursor::getSingleton().isVisible())
        CEGUI::MouseCursor::getSingleton().hide();
    else CEGUI::MouseCursor::getSingleton().show();
    return 0;
}

int TMenuState::quitClicked(Tubras::TSEvent)
{
    m_doQuit = true;
    m_finterval->start();
    sound2->play();    
    return true;
}

int TMenuState::playClicked(Tubras::TSEvent)
{
    m_doPlay = true;
    m_finterval->start();
    sound2->play();
    m_centerMouse = true;
    return 0;
}

int TMenuState::optionsClicked(Tubras::TSEvent)
{
    m_doOptions = true;
    m_finterval->start();
    sound2->play();
    return 0;
}

int TMenuState::Enter()
{
    //
    // do this so mouse show works the first time around (sets d_wndWithMouse)
    //
    getGUISystem()->injectMouseMove(0,0);
    setGUIEnabled(true);

    //
    // disable bounding box display if previously enabled
    //
    getRenderEngine()->getSceneManager()->showBoundingBoxes(false);

    m_doPlay = false;
    m_doQuit = false;
    m_doOptions = false;
    m_parent->flipVisibility();

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;
    if(m_centerMouse)
    {
        CEGUI::MouseCursor::getSingleton().setPosition(CEGUI::Point(cx,cy));
        m_centerMouse = false;
    }
    m_GUIRoot->setVisible(true);


    m_finterval->start();
    sound1->play();
    return 0;
}

Tubras::TStateInfo* TMenuState::Exit()
{
    m_parent->flipVisibility();
    setGUIEnabled(false);
    if(m_doPlay)
        CEGUI::MouseCursor::getSingleton().hide();

    CEGUI::System::getSingleton().injectTimePulse(0.1);
    m_GUIRoot->setVisible(false);

    ambientSound->stop();
    return &m_info;
}

int TMenuState::Reset()
{
    return 0;
}

int TMenuState::Pause()
{
    Exit();

    return 0;
}

int TMenuState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    Enter();
    return 0;
}


