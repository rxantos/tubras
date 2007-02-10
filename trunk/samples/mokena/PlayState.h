//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------
#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

enum TCurrentState {csIdle,csRunning,csPaused};
#define cmEasy      0
#define cmNormal    1
#define cmHard      2


struct TPlayOptions
{
    int             m_difficulty;
    int             m_bgMusic;
    int             m_bgMusicVolume;
    Tubras::TString m_theme;
};

struct TPlayStatus
{
    TCurrentState   m_currentState;
};

struct TCardInfo
{
public:
    Tubras::TSceneNode*     m_node;
    TVector3                m_pos;
};

typedef std::list<struct TCardInfo*> TCardList;
typedef std::list<struct TCardInfo*>::iterator TCardListItr;

class TPlayState : public Tubras::TState
{
private:
    TCardMesh*                  m_cardMesh;
    Tubras::TDatabase*          m_db;
    struct TPlayStatus          m_playStatus;
    struct TPlayOptions         m_playOptions;
    Tubras::TEventDelegate  *ed;
    Tubras::TSound*         sound,*sound2,*sound3,*sound4,*sound5;
    ULONG           m_time;
    int             m_counter;
    Ogre::SceneNode* m_cubeParent;
    Tubras::TSceneNode* m_cardParent;
    Ogre::MaterialPtr m_material;
    ULONG           m_starttime;
    float           m_degrees;
    float           m_speed;
    int             m_flashstate;
    int             m_flashstate2;
    ULONG           m_flashtime;
    Tubras::TCardNode*  m_background;
    Ogre::Entity *  m_cubeEntity;
    Ogre::Entity *  m_cardEntity;
    Ogre::SceneNode * m_cubeNode;
    TCardList m_cardNodes;
    TCardList m_activeCards;
    Tubras::TSceneNode*     m_parent;
    Tubras::TInterval*      m_interval;
    Tubras::TFunctionInterval* m_finterval;
    TGUI::TGScreen*         m_GUIScreen;
    TGUI::TGImage*          m_frame;

    Tubras::TEventDelegate* m_flashDelegate;
    Tubras::TEventDelegate* m_toggleDelegate;
    Tubras::TEventDelegate* m_speedDelegate;
    Tubras::TEventDelegate* m_quitDelegate;
    Tubras::TEventDelegate* m_playGunShotDelegate;
    Tubras::TEventDelegate*  m_mouseDelegate;
    Tubras::TTask*			m_testTask;

private:
    int escape(Tubras::TSEvent event);
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
    void createCards();
    void layoutCards(int mode);
    Tubras::TModelNode* createCard(int number,TVector3 pos,Ogre::SceneManager* sm);

public:
    TPlayState();
    virtual ~TPlayState();


    virtual int initialize();

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
    struct TPlayOptions* getOptions() {return &m_playOptions;};
    void saveOptions();
};

#endif
