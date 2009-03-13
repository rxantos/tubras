//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TMOTIONSTATE_H_
#define _TMOTIONSTATE_H_

namespace Tubras
{

    class TMotionState : public btDefaultMotionState
    {
    protected:
        bool            m_allowDeactivation;
    public:
        TMotionState(const btTransform& startTrans,bool allowDeactivation=true);
        virtual ~TMotionState();

        void setAllowDeactivation(bool value) {m_allowDeactivation = value;};
        bool getAllowDeactivation() {return m_allowDeactivation;};

	    virtual bool deactivationCallback(void*	userPointer);

    };

}

#endif

