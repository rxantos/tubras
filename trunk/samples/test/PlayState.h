#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

class TPlayState : public Tubras::TState
{
private:
    Tubras::TEventDelegate  *ed;
    Tubras::TSound*         sound,*sound2,*sound3,*sound4,*sound5;
    ULONG           m_time;
    int             m_counter;
    Ogre::SceneNode* m_cubeParent;
    Tubras::TSceneNode* m_cardParent;
    ULONG           m_starttime;
    float           m_degrees;
    float           m_speed;
    int             m_flashstate;
    int             m_flashstate2;
    ULONG           m_flashtime;
    Tubras::TEntityNode*     m_cube;
    Ogre::Rectangle2D* m_rect;
    Ogre::Entity *  m_cubeEntity;
    Ogre::Entity *  m_cardEntity;
    Ogre::MaterialPtr m_material;
    Ogre::SceneNode * m_cubeNode;
    std::list<Tubras::TSceneNode*> m_cardNodes;
    Tubras::TSceneNode*     m_parent;
    Tubras::TInterval*      m_interval;
    Tubras::TFunctionInterval* m_finterval;
    Ogre::TextureUnitState* m_backTextureUnitState;
    Tubras::TWindow*  m_GUIRoot;
    Tubras::TStaticImage* m_frame;

    Tubras::TEventDelegate* m_flashDelegate;
    Tubras::TEventDelegate* m_toggleDelegate;
    Tubras::TEventDelegate* m_speedDelegate;
    Tubras::TEventDelegate* m_quitDelegate;
    Tubras::TEventDelegate* m_playGunShotDelegate;
    Tubras::TEventDelegate*  m_mouseDelegate;
    Tubras::TTask*			m_testTask;

private:
    int quitApp(Tubras::TSEvent event);
    int playGunShot(Tubras::TSEvent event);
    int flash(Tubras::TSEvent event);
    int adjustSpeed(Tubras::TSEvent event);
    int playDone(Tubras::TSEvent event);
    int procKey(Tubras::TSEvent event);
    int toggleParent(Tubras::TSEvent event);
    int intervalDone(Tubras::TSEvent event);
    int testTask(Tubras::TTask* task);
    void funcInterval(double T, void* userData);
    void createScene();
    Tubras::TSceneNode* createCard(int number,TVector3 pos,Ogre::SceneManager* sm);



public:
    TPlayState();
    virtual ~TPlayState();


    virtual int initialize();

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
