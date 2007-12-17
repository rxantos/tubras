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
#ifndef _TSTATE_H_
#define _TSTATE_H_

namespace Tubras
{
    class TStateInfo
    {
    public:
        int     m_returnCode;

    };

    /**
    TState Class.
    @remarks
        A class inherited from TState is also an event handler.  This doesn't mean
        events are automatically sent to the inherited class.  Instead, the class
        contains the ability to receive events.
    */
    class TState : public TObject
    {
    protected:
        TString             m_name;
        
        TStateInfo          m_info;

    public:
        TState(TString name);
        virtual ~TState();

        TString getName() {return m_name;};

        virtual int initialize();

        virtual int Enter();
        virtual TStateInfo* Exit();
        virtual int Reset();
        virtual int Pause();
        virtual int Resume(TStateInfo* prevStateInfo);

        //
        // management convenience functions
        //
        int changeState(TString stateName);
        int pushState(TString stateName);
        int popState();

    };
}
#endif
