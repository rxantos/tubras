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
#ifndef _TTEXTOVERLAY_H_
#define _TTEXTOVERLAY_H_

namespace Tubras
{

    typedef IGUIStaticText          TTextElement;
    enum TTextAlignment
    {
        taLeft,
        taCenter,
        taRight
    };


    class TTextOverlay : public TOverlay
    {
    private:
        TString                     m_fontName;
        TColour                     m_fontColor;
        float                       m_fontSize;
        TArray<TTextElement*>       m_textItems;
        TDimension  				m_margins;
   

    public:
        TTextOverlay(TString name,TRect dims, 
            TColour overlayColor=TColour(255,255,255,128));
        virtual ~TTextOverlay();
        void addItem(TString text, TTextAlignment a=taLeft);
        void removeItem(s32 index);
        void updateItem(s32 index,TString text);
        u32 getItemCount() {return m_textItems.size();}
        void setFont(IGUIFont* value);
    };

}

#endif
