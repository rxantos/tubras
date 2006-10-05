#ifndef _OPTIONSSTATE_H_
#define _OPTIONSSTATE_H_

class TOptionsState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Tubras::TSound* sound1,* sound2, *ambientSound;
    Tubras::TSound* gui_rollover, *gui_click;
    Tubras::TWindow* m_GUIRoot;
    Tubras::TStaticImage* m_frame;
    Tubras::TFunctionInterval* m_finterval;
    int slideDirection;
    Tubras::TEventDelegate* m_mouseDelegate;
    Tubras::TEventDelegate* m_toggleDelegate;
    const CEGUI::Image* m_mouseCursor;

    Tubras::TImageButton* m_saveButton;
    Tubras::TImageButton* m_cancelButton;
    bool m_doSave;
    bool m_doCancel;

public:
    TOptionsState();
    virtual ~TOptionsState();

    virtual int initialize();
    int quitApp(Tubras::TSEvent event);
    void slideMenu(double T, void* userData);
    int slideDone(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);
    bool handleMouseButtonEnter(const CEGUI::EventArgs& event);
    bool handleMouseButtonDown(const CEGUI::EventArgs& event);
    int toggleMouse(Tubras::TSEvent event);
    int saveClicked(Tubras::TSEvent event);
    int cancelClicked(Tubras::TSEvent event);

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
