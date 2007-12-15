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

#ifndef _TOBJECT_H_
#define _TOBJECT_H_

namespace Tubras
{
    class TEvent;

    class TObject
    {
    protected:
        TApplication*           m_app;

    public:
        TObject();
        virtual ~TObject();
        int initialize();

        TXMLConfig* getAppConfig();
        virtual ISceneNode* getRootSceneNode();
        virtual ISceneManager* getSceneManager();
        virtual IGUIEnvironment* getGUIManager();
        virtual IFileSystem* getFileSystem();
        virtual ITexture* getTexture(TString name);

        virtual void setCursorVisible(bool value);
        virtual bool sendEvent(TEvent* event);
        virtual bool queueEvent(TEvent* event);
        virtual void logMessage(TString msg);

        size_t acceptEvent(TString eventMsg,TEventDelegate* callback,void *extraData=0,
                    int priority=0,bool enabled=true);
        size_t registerEvent(TString eventName);
        int disableEvents(void *classInstance);
        int enableEvents(void *classInstance);

        virtual void setRenderMode(TRenderMode value);
        virtual TRenderMode getRenderMode();

        ISceneNode* addSceneNode(const char* sceneNodeTypeName, ISceneNode* parent=0);

        TSound* loadSound(TString fileName, bool positional=false);



    };

}
#endif
