#include "iwalktest.h"


TAboutDlg::TAboutDlg(IGUIEnvironment* environment, IGUIElement* parent) : 
TGUIDialog(environment, parent, -1, TRecti(0,0,500,400), (TDialogButtons)0, true, true, false)
{
    setText(L"About");

    TGUIImage* image = getApplication()->addGUIImage("tex/iwalktest/iwalktest.png",
        -1.f, 40.f, -1.f, -1.f, false, this);
    if(image)
        addChild(image);


    addText(environment, 0, "Copyright (C) 2011, Tubras LTD", 0xFF770000);
    addText(environment, 1, "(http://code.google.com/p/tubras)", 0xFF770000);

    addText(environment, 3, "Rendering by Irrlicht 3d Engine");
    addText(environment, 4, "Copyright (C) 2002-2011 Nikolaus Gebhard", 0xFF007700);
    addText(environment, 5, "(http://irrlicht.sourceforge.net)", 0xFF007700);

    addText(environment, 7, "Physics by Bullet");
    addText(environment, 8, "Copyright (C) 2011 Erwin Coumans", 0xFF000077);
    addText(environment, 9, "(http://bulletphysics.org)", 0xFF000077);

    u32 xpos = (AbsoluteRect.getWidth() / 2) - 50;
    u32 ypos = AbsoluteRect.getHeight() - 75;
    environment->addButton(TRecti(xpos, ypos, xpos+100, ypos + 32), this, TID_DLG_CANCEL, L"Okey-dokey");
}

void TAboutDlg::addText(IGUIEnvironment* e, u32 idx, const c8* text, u32 color)
{
    int starty = 100; 
    int eheight = 2;
    int spacing = 2;
    f32 dmiddle = AbsoluteRect.getWidth() / 2.f;
    stringw wtext = text;

    IGUIFont* font=e->getSkin()->getFont();
    TDimension dim = font->getDimension(wtext.c_str());
    dim.Height += (font->getKerningHeight() + eheight);

    f32 fwidth = (f32) AbsoluteRect.getWidth();
    s32 xpos = (s32) (dmiddle - (dim.Width / 2.f));
    s32 ypos = starty + ((dim.Height + spacing) * idx);
    TRecti rect(xpos, ypos, xpos+dim.Width, ypos+dim.Height);

    IGUIStaticText* t = e->addStaticText(wtext.c_str(), rect, false, false, this);
    t->setOverrideColor(SColor(color));
}