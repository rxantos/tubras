//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TNODEFACTORY_H_
#define _TNODEFACTORY_H_

namespace Tubras
{
    enum TSCENE_NODE_TYPE
    {
        TSNT_EMPTY  = MAKE_IRR_ID('t','e','m','p'),
        TSNT_PLANE  = MAKE_IRR_ID('t','p','l','n'),
        TSNT_AXIS   = MAKE_IRR_ID('t','a','x','s'),
        TSNT_DEBUG  = MAKE_IRR_ID('t','d','b','g'),
        TSNT_TCAM   = MAKE_IRR_ID('t','c','a','m'),
        TSNT_BACKGROUND = MAKE_IRR_ID('t','b','g','n'),
        TSNT_PARTICLE = MAKE_IRR_ID('t','p','r','t')
    };

    struct NodeInfo
    {
        TString name;
        u32     type;
    };

    class TNodeFactory : public ISceneNodeFactory, public TObject
    {

    public:

        TNodeFactory();
        ~TNodeFactory();
        int initialize();


        //! adds a scene node to the scene graph based on its type id
        /** \param type: Type of the scene node to add.
        \param parent: Parent scene node of the new node, can be null to add the scene node to the root.
        \return Returns pointer to the new scene node or null if not successful. */
        virtual ISceneNode* addSceneNode(ESCENE_NODE_TYPE type, ISceneNode* parent=0);

        //! adds a scene node to the scene graph based on its type name
        /** \param typeName: Type name of the scene node to add.
        \param parent: Parent scene node of the new node, can be null to add the scene node to the root.
        \return Returns pointer to the new scene node or null if not successful. */
        virtual ISceneNode* addSceneNode(const c8* typeName, ISceneNode* parent=0);

        //! returns amount of scene node types this factory is able to create
        virtual u32 getCreatableSceneNodeTypeCount() const;

        //! returns type name of a createable scene node type by index
        /** \param idx: Index of scene node type in this factory. Must be a value between 0 and
        uetCreatableSceneNodeTypeCount() */
        virtual const c8* getCreateableSceneNodeTypeName(u32 idx) const;

        //! returns type of a createable scene node type
        /** \param idx: Index of scene node type in this factory. Must be a value between 0 and
        getCreatableSceneNodeTypeCount() */
        virtual ESCENE_NODE_TYPE getCreateableSceneNodeType(u32 idx) const;

        //! returns type name of a createable scene node type 
        /** \param idx: Type of scene node. 
        \return: Returns name of scene node type if this factory can create the type, otherwise 0. */
        virtual const c8* getCreateableSceneNodeTypeName(ESCENE_NODE_TYPE type) const;

        static const NodeInfo types[];
        static const u32 typeCount;

    };
} 
#endif
