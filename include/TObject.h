//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
        virtual ITexture* getTexture(const TString& name);

        virtual void setCursorVisible(bool value);
        virtual bool sendEvent(TEvent* event);
        virtual bool queueEvent(TEvent* event);
        virtual void logMessage(const TString& msg);

        size_t acceptEvent(const TString& eventMsg,TEventDelegate* callback,void *extraData=0,
                    int priority=0,bool enabled=true);
        size_t registerEvent(const TString& eventName);
        int disableEvents(void *classInstance);
        int enableEvents(void *classInstance);

        virtual void setRenderMode(TRenderMode value);
        virtual TRenderMode getRenderMode();

        ISceneNode* addSceneNode(const char* sceneNodeTypeName, ISceneNode* parent=0);

        TSound* loadSound(const TString& fileName, bool positional=false);



    };

}
#endif
