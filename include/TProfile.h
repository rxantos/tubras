//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
// based on Bullet's Quickprof class. See btQuickProf.h 
#ifndef _TPROFILE_H_
#define _TPROFILE_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                         T P r o f i l e N o d e
    //-----------------------------------------------------------------------
    class TProfileNode
    {
    protected:
        const char*     m_name;
        int             m_totalCalls;
        float           m_totalTime;
        unsigned long int  m_startTime;
        int             m_recursionCounter;

        TProfileNode*   m_parent;
        TProfileNode*   m_child;
        TProfileNode*   m_sibling;

    public:
        TProfileNode(const char* name, TProfileNode* parent);
        ~TProfileNode();

        TProfileNode*   getSubNode(const char* name);

        TProfileNode*   getParent()		{ return m_parent; }
        TProfileNode*   getSibling()		{ return m_sibling; }
        TProfileNode*   getChild()			{ return m_child; }

        void            cleanUpMemory();
        void            reset();
        void            call();
        bool            doReturn();

        const char*     getName()       { return m_name; }
        int             getTotalCalls() { return m_totalCalls; }
        float           getTotalTime()  { return m_totalTime; }
    };

    //-----------------------------------------------------------------------
    //                      T P r o f i l e I t e r a t o r
    //-----------------------------------------------------------------------
    class TProfileIterator 
    {
    protected:

        TProfileNode *	m_currentParent;
        TProfileNode *	m_currentChild;

        TProfileIterator( TProfileNode * start );
        friend	class	TProfileManager;


    public:
        // Access all the children of the current parent
        void        first();
        void        next();
        bool        isDone();
        bool        isRoot() { return (m_currentParent->getParent() == 0); }

        void        enterChild( int index );    // Make the given child the new parent
        void        enterLargestChild();        // Make the largest child the new parent
        void        enterParent();              // Make the current parent's parent the new parent

        // Access the current child
        const char* getCurrentName()            { return m_currentChild->getName(); }
        int         getCurrentTotalCalls()      { return m_currentChild->getTotalCalls(); }
        float       getCurrentTotalTime()       { return m_currentChild->getTotalTime(); }

        // Access the current parent
        const char* getCurrentParentName()      { return m_currentParent->getName(); }
        int         getCurrentParentTotalCalls(){ return m_currentParent->getTotalCalls(); }
        float       getCurrentParentTotalTime() { return m_currentParent->getTotalTime(); }
    };

    //-----------------------------------------------------------------------
    //                      T P r o f i l e M a n a g e r
    //-----------------------------------------------------------------------
    class TProfileManager
    {
    private:
        static  TProfileNode    m_root;
        static  TProfileNode*   m_currentNode;
        static  int             m_frameCounter;
        static  unsigned long int  m_resetTime;

    public:
        static  void    startProfile( const char * name );
        static  void    stopProfile( void );

        static	void    cleanUpMemory(void)
        {
            m_root.cleanUpMemory();
        }

        static  void    reset( void );
        static  void    incrementFrameCounter( void );
        static  int     getFrameCountSinceReset( void )		{ return m_frameCounter; }
        static  float   getTimeSinceReset( void );

        static	TProfileIterator *	getIterator( void )	
        { 
            return new TProfileIterator( &m_root ); 
        }
        static  void    releaseIterator( TProfileIterator * iterator ) { delete ( iterator); }

        static  void    dumpRecursive(TProfileIterator* profileIterator, int spacing);

        static  void    dumpAll();
    };

    //-----------------------------------------------------------------------
    //                      T P r o f i l e S a m p l e
    //-----------------------------------------------------------------------
    // ProfileSampleClass is a simple way to profile a function's scope
    // Use the TPROFILE macro at the start of scope to time
    class	TProfileSample {
    public:
        TProfileSample( const char * name )
        { 
            TProfileManager::startProfile( name ); 
        }

        ~TProfileSample( void )					
        { 
            TProfileManager::stopProfile(); 
        }
    };


#define	TPROFILE( name )    TProfileSample __profile( name )

}
#endif
