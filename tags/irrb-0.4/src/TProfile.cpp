//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
// based on Bullet's Quickprof class. See btQuikckProf.h 
#include "tubras.h"

namespace Tubras {
    static TTimer m_profileTimer;

    inline void Profile_Get_Ticks(unsigned long int * ticks)
    {
        *ticks = m_profileTimer.getMilliSeconds();
    }

    inline f32 Profile_Get_Tick_Rate(void)
    {
        //	return 1000000.f;
        return 1.f;
    }

    //-----------------------------------------------------------------------
    //                         T P r o f i l e N o d e
    //-----------------------------------------------------------------------
    // INPUT:                                                                                     
    // name - pointer to a static string which is the name of this profile node
    // parent - parent pointer                                                                    
    //                                                                                            
    // WARNINGS:                                                                                  
    // The name is assumed to be a static pointer, only the pointer is stored 
    // and compared for efficiency reasons.                                                                        
    //-----------------------------------------------------------------------
    TProfileNode::TProfileNode( const char * name, TProfileNode * parent ) : m_name( name ),
        m_totalCalls( 0 ),
        m_totalTime( 0 ),
        m_startTime( 0 ),
        m_recursionCounter( 0 ),
        m_parent( parent ),
        m_child( NULL ),
        m_sibling( NULL )
    {
        reset();
    }

    void TProfileNode::cleanUpMemory()
    {
        delete ( m_child);
        m_child = NULL;
        delete ( m_sibling);
        m_sibling = NULL;
    }

    TProfileNode::~TProfileNode( void )
    {
        delete ( m_child);
        delete ( m_sibling);
    }

    /***********************************************************************************************
    * INPUT:                                                                                      *
    * name - static string pointer to the name of the node we are searching for                   *
    *                                                                                             *
    * WARNINGS:                                                                                   *
    * All profile names are assumed to be static strings so this function uses pointer compares   *
    * to find the named node.                                                                     *
    *=============================================================================================*/
    TProfileNode * TProfileNode::getSubNode( const char * name )
    {
        // Try to find this sub node
        TProfileNode * child = m_child;
        while ( child ) {
            if ( child->m_name == name ) {
                return child;
            }
            child = child->m_sibling;
        }

        // We didn't find it, so add it

        TProfileNode * node = new TProfileNode( name, this );
        node->m_sibling = m_child;
        m_child = node;
        return node;
    }

    void TProfileNode::reset( void )
    {
        m_totalCalls = 0;
        m_totalTime = 0.0f;


        if ( m_child ) {
            m_child->reset();
        }
        if ( m_sibling ) {
            m_sibling->reset();
        }
    }

    void TProfileNode::call( void )
    {
        m_totalCalls++;
        if (m_recursionCounter++ == 0) {
            Profile_Get_Ticks(&m_startTime);
        }
    }

    bool TProfileNode::doReturn( void )
    {
        if ( --m_recursionCounter == 0 && m_totalCalls != 0 ) { 
            unsigned long int time;
            Profile_Get_Ticks(&time);
            time-=m_startTime;
            m_totalTime += (f32)time / Profile_Get_Tick_Rate();
        }
        return ( m_recursionCounter == 0 );
    }

    /***************************************************************************************************
    **
    ** TProfileIterator
    **
    ***************************************************************************************************/
    TProfileIterator::TProfileIterator( TProfileNode * start )
    {
        m_currentParent = start;
        m_currentChild = m_currentParent->getChild();
    }

    void TProfileIterator::first(void)
    {
        m_currentChild = m_currentParent->getChild();
    }

    void TProfileIterator::next(void)
    {
        m_currentChild = m_currentChild->getSibling();
    }

    bool TProfileIterator::isDone(void)
    {
        return m_currentChild == NULL;
    }

    void TProfileIterator::enterChild( int index )
    {
        m_currentChild = m_currentParent->getChild();
        while ( (m_currentChild != NULL) && (index != 0) ) {
            index--;
            m_currentChild = m_currentChild->getSibling();
        }

        if ( m_currentChild != NULL ) {
            m_currentParent = m_currentChild;
            m_currentChild = m_currentParent->getChild();
        }
    }

    void TProfileIterator::enterParent( void )
    {
        if ( m_currentParent->getParent() != NULL ) {
            m_currentParent = m_currentParent->getParent();
        }
        m_currentChild = m_currentParent->getChild();
    }

    /***************************************************************************************************
    **
    ** TProfileManager
    **
    ***************************************************************************************************/

    TProfileNode    TProfileManager::m_root( "Root", NULL );
    TProfileNode*   TProfileManager::m_currentNode = &TProfileManager::m_root;
    int             TProfileManager::m_frameCounter = 0;
    unsigned long int TProfileManager::m_resetTime = 0;

    /***********************************************************************************************
    * TProfileManager::startProfile -- Begin a named profile                                    *
    *                                                                                             *
    * Steps one level deeper into the tree, if a child already exists with the specified name     *
    * then it accumulates the profiling; otherwise a new child node is added to the profile tree. *
    *                                                                                             *
    * INPUT:                                                                                      *
    * name - name of this profiling record                                                        *
    *                                                                                             *
    * WARNINGS:                                                                                   *
    * The string used is assumed to be a static string; pointer compares are used throughout      *
    * the profiling code for efficiency.                                                          *
    *=============================================================================================*/
    void TProfileManager::startProfile( const char * name )
    {
        if (name != m_currentNode->getName()) {
            m_currentNode = m_currentNode->getSubNode( name );
        } 

        m_currentNode->call();
    }

    /***********************************************************************************************
    * TProfileManager::stopProfile -- Stop timing and record the results.                       *
    *=============================================================================================*/
    void TProfileManager::stopProfile( void )
    {
        // Return will indicate whether we should back up to our parent (we may
        // be profiling a recursive function)
        if (m_currentNode->doReturn()) {
            m_currentNode = m_currentNode->getParent();
        }
    }

    /***********************************************************************************************
    * TProfileManager::Reset -- Reset the contents of the profiling system                       *
    *                                                                                             *
    *    This resets everything except for the tree structure.  All of the timing data is reset.  *
    *=============================================================================================*/
    void TProfileManager::reset( void )
    { 
        m_profileTimer.reset();
        m_root.reset();
        m_root.call();
        m_frameCounter = 0;
        Profile_Get_Ticks(&m_resetTime);
    }

    /***********************************************************************************************
    * TProfileManager::getTimeSinceReset -- returns the elapsed time since last reset         *
    *=============================================================================================*/
    f32 TProfileManager::getTimeSinceReset( void )
    {
        unsigned long int time;
        Profile_Get_Ticks(&time);
        time -= m_resetTime;
        return (f32)time / Profile_Get_Tick_Rate();
    }

#include <stdio.h>

    void TProfileManager::dumpRecursive(TProfileIterator* profileIterator, int spacing)
    {
        TApplication* app = getApplication();
        TString spaces="";
        profileIterator->first();
        if (profileIterator->isDone())
            return;

        f32 accumulated_time=0,parent_time = profileIterator->isRoot() ? TProfileManager::getTimeSinceReset() : profileIterator->getCurrentParentTotalTime();
        int i;
        int frames_since_reset = TProfileManager::getFrameCountSinceReset();
        for (i=0;i<spacing;i++)
            spaces += ".";
        app->logMessage(LOG_INFO, " ");
        app->logMessage(LOG_INFO, "Profiling: %s (total running time: %.6f ms)",	profileIterator->getCurrentParentName(), parent_time );
        f32 totalTime = 0.f;

        int numChildren = 0;

        for (i = 0; !profileIterator->isDone(); i++,profileIterator->next())
        {
            numChildren++;
            f32 current_total_time = profileIterator->getCurrentTotalTime();
            accumulated_time += current_total_time;
            f32 fraction = parent_time > SIMD_EPSILON ? (current_total_time / parent_time) * 100.f : 0.f;
            app->logMessage(LOG_INFO, "%s %d -- %s (%.2f %%) :: %.6f ms / frame (%d calls)", spaces.c_str(), 
                i, profileIterator->getCurrentName(), 
                fraction,(current_total_time / (f32)frames_since_reset),
                profileIterator->getCurrentTotalCalls());
            totalTime += current_total_time;
            //recurse into children
        }

        if (parent_time < accumulated_time)
        {
            app->logMessage(LOG_INFO, "what's wrong");
        }

        app->logMessage(LOG_INFO, "%s %s (%.3f %%) :: %.6f ms", spaces.c_str(), "Unaccounted:",
            parent_time > SIMD_EPSILON ? ((parent_time - accumulated_time) / parent_time) * 100 : 0.f, 
            parent_time - accumulated_time);

        for (i=0;i<numChildren;i++)
        {
            profileIterator->enterChild(i);
            dumpRecursive(profileIterator,spacing+3);
            profileIterator->enterParent();
        }
    }

    void TProfileManager::dumpAll()
    {
        TProfileIterator* profileIterator = 0;
        profileIterator = TProfileManager::getIterator();
        getApplication()->logMessage(LOG_INFO, " ");
        getApplication()->logMessage(LOG_INFO, "-------------------------- P r o f i l e   D a t a --------------------------");
        dumpRecursive(profileIterator,0);
        getApplication()->logMessage(LOG_INFO, " ");
        getApplication()->logMessage(LOG_INFO, "----------------------E n d   P r o f i l e   D a t a -----------------------");
        TProfileManager::releaseIterator(profileIterator);
    }

}
