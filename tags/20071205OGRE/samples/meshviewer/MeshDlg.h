//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
#ifndef _MESHDLG_H_
#define _MESHDLG_H_

using namespace Tubras;

class TMeshDlg : public TGUI::TGWindow
{
private:
    TGUI::TGListBox*        m_listBox;
    TGUI::TGSpinEdit*       m_scale;

public:
    TMeshDlg(TGUI::TGScreen* parent, std::vector<std::string> meshfiles);

    virtual ~TMeshDlg();
    virtual void show();
    virtual void hide();
    virtual void onKeyUp(int key, unsigned char ascii);
    bool cancelClicked(const TGUI::TGEventArgs& event);
    bool openClicked(const TGUI::TGEventArgs& event);


};


#endif