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
#ifndef _TNODEFACTORY_H_
#define _TNODEFACTORY_H_

namespace Tubras
{
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
