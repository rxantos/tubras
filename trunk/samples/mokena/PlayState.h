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

struct TCardInfo
{
public:
    Tubras::TModelNode*     m_node;
    TVector3                m_pos;
    int                     m_pick;
    Ogre::SubEntity*        m_eFront;
    Tubras::TMaterial*      m_eFrontMat;
    Ogre::SubEntity*        m_eBack;
    Tubras::TColliderBox*   m_shape;
    Tubras::TDynamicNode*   m_dnode;
    Tubras::TLerpPosInterval* m_startLerp;
    Tubras::TLerpHprInterval* m_rotLerp1;
};

typedef std::vector<struct TCardInfo*> TCardList;
typedef std::vector<struct TCardInfo*>::iterator TCardListItr;
typedef std::vector<int> TIntList;
typedef std::vector<int>::iterator TIntListItr;

class TPlayState : public Tubras::TState
{
private:
    TCardMesh*              m_cardMesh;
    Tubras::TDatabase*      m_db;
    TPickState              m_pickState;
    Tubras::TSound          *sound4,*sound5;
    Tubras::TSound*         m_bgSound;
    Tubras::TSound*         m_timerSound;
    Ogre::SceneNode*        m_cubeParent;
    Tubras::TSceneNode*     m_cardParent;
    Tubras::TCardNode*      m_background;
    Ogre::Entity *          m_cardEntity;
    Ogre::SceneNode *       m_cubeNode;
    TCardList               m_cardNodes;
    TCardList               m_activeCards;
    Tubras::TSceneNode*     m_parent;
    TGUI::TGScreen*         m_GUIScreen;
    TGUI::TGImage*          m_hudImage;
    TGUI::TGImage*          m_readyImage;
    TGUI::TGImage*          m_waitImage;
    TGUI::TGImage*          m_pausedImage;
    TGUI::TGLabel*          m_timer;
    TGUI::TGLabel*          m_score;
    TTestTheme*             m_curTheme;
    ULONG                   m_playTime;
    ULONG                   m_curTime;
    Tubras::TFunctionInterval* m_timerLerp;
    int                     m_curThemeIdx;

private:
    int escape(Tubras::TSEvent event);
    int mousePick(Tubras::TSEvent event);
    int setupDone(Tubras::TSEvent event);
    int clickDone(Tubras::TSEvent event);
    int spinDone(Tubras::TSEvent event);
    int pickDone(Tubras::TSEvent event);
    int resetPick(Tubras::TSEvent event);
    int pickStateChanged(Tubras::TSEvent event);
    int bgSoundDone(Tubras::TSEvent event);
    int toggleParent(Tubras::TSEvent event);
    int testTask(Tubras::TTask* task);
    int goodMatch(Tubras::TTask* task);
    int badMatch(Tubras::TTask* task);
    void loadScene(struct TPlayOptions* options);
    void playTimer(double T, void* userData);
    Tubras::TString timeToStr(ULONG m_playTime);


    void createCards();
    void layoutCards(int mode);
    Tubras::TModelNode* createCard(int number,TVector3 pos,Ogre::SceneManager* sm);

    TCardListItr getRandomCardIterator(Tubras::TRandom& random,TCardList& temp);
    TIntListItr getRandomIntIterator(Tubras::TRandom& random,TIntList& temp);

    int loadTheme(struct TPlayOptions* options);

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
