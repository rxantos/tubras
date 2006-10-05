#ifndef _PAUSESTATE_H_
#define _PAUSESTATE_H_

class TPauseState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Tubras::TSound* sound1,* sound2, *ambientSound;
    Tubras::TSound* gui_rollover, *gui_click;
    CEGUI::Window* m_GUIRoot;
    CEGUI::Window* m_frame;
    Tubras::TFunctionInterval* m_finterval;
    int slideDirection;
    Tubras::TEventDelegate* m_mouseDelegate;
    Tubras::TEventDelegate* m_toggleDelegate;
    const CEGUI::Image* m_mouseCursor;

    Tubras::TImageButton* m_playButton;
    Tubras::TImageButton* m_quitButton;

    bool m_doQuit;
    bool m_doPlay;

public:
    TPauseState();
    virtual ~TPauseState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void slideMenu(double T, void* userData);
    int slideDone(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);
    bool handleMouseButtonEnter(const CEGUI::EventArgs& event);
    bool handleMouseButtonDown(const CEGUI::EventArgs& event);
    int toggleMouse(Tubras::TSEvent event);
    int playClicked(Tubras::TSEvent event);
    int quitClicked(Tubras::TSEvent event);

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
