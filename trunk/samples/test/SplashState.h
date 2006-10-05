#ifndef _SPLASHSTATE_H_
#define _SPLASHSTATE_H_

class TSplashState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Ogre::Rectangle2D* m_logo;
    Ogre::TextureUnitState* m_textureState;
    Tubras::TFunctionInterval* m_finterval,*m_finterval2;
    Tubras::TSound* m_sound;
    ULONG m_starttime,m_shaketime;

public:
    TSplashState();
    virtual ~TSplashState();

    void shakeLogo();
    void adjustAlpha(double T, void* userData);
    int alphaDone(Tubras::TSEvent event);

    virtual int initialize();

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
