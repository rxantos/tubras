#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

class TMenuState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Tubras::TSound* sound1,* sound2, *ambientSound;
    Tubras::TSound* gui_rollover, *gui_click;
    Tubras::TWindow* m_GUIRoot;
    Tubras::TStaticImage* m_frame;
    Tubras::TFunctionInterval* m_finterval;
    int slideDirection;
    Tubras::TEventDelegate* m_toggleDelegate;
    const CEGUI::Image* m_mouseCursor;

    Tubras::TImageButton* m_playButton;
    Tubras::TImageButton* m_quitButton;
    Tubras::TImageButton* m_optionsButton;
    bool m_doQuit;
    bool m_doPlay;
    bool m_doOptions;
    bool m_centerMouse;

public:
    TMenuState();
    virtual ~TMenuState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void slideMenu(double T, void* userData);
    int slideDone(Tubras::TSEvent event);
    int toggleMouse(Tubras::TSEvent event);
    int playClicked(Tubras::TSEvent event);
    int quitClicked(Tubras::TSEvent event);
    int optionsClicked(Tubras::TSEvent event);

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
