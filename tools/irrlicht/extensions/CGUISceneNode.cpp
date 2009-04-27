// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUISceneNode.h"
#include "ISceneManager.h"
#include "IGUIEnvironment.h"
#include "IVideoDriver.h"
#include "ICameraSceneNode.h"
#include "ISceneCollisionManager.h"
#include "line3d.h"
#include "os.h"
#include "SMaterial.h"

namespace irr
{
    namespace scene
    {
        //! constructor
        //  p1--------->p2
        //  ^ .          |
        //  |   .   T1   |
        //  |     .      |
        //  |  T2   .    |
        //  |         .  |
        //  p4<-------- p3
        //
        // Texture coordinates - p1(0,0), p2(0,1), p3(1,1), p4(0,1)
        //
        CGUISceneNode::CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::stringc& cursorImageFileName,
            GSN_ACTIVATION_MODE activationMode,
            IEventReceiver* eventReceiver,
            f32 activationDistance,
            const video::SColor& backgroundColor,
            const core::dimension2du& textureSize,
            const core::vector2df& size,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)
            : ISceneNode(parent, mgr, id, core::vector3df(0,0,0), core::vector3df(0,0,0), core::vector3df(1,1,1)),
            IGUIElement(gui::EGUIET_ELEMENT,0,0,id,core::rect<s32>()),
            ActivationDistance(activationDistance),
            ActivationMode(activationMode),
            BColor(backgroundColor),
            SceneManager(mgr),
            CollisionManager(mgr->getSceneCollisionManager()),
            Cursor(0),
            Activated(false),
            Draw(true),
            RenderGeometry(true),
            EventReceiver(eventReceiver),
            Hovered(0),
            Focus(0)
        {
#ifdef _DEBUG
            setDebugName("CGUISceneNode");
#endif

            Environment = mgr->getGUIEnvironment();

            video::IVideoDriver* driver = mgr->getVideoDriver();

            if (driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
            {
                RenderTarget = driver->addRenderTargetTexture(textureSize, "GUISceneNodeRTT");
            }
            Material.setTexture(0,RenderTarget);
            Material.Lighting = false;

            // initialize the geometry
            f32 halfSizeX = size.X/2.f;
            f32 halfSizeY = size.Y/2.f;

            core::vector3df p1(-halfSizeX, halfSizeY, 0);
            core::vector3df p2(halfSizeX, halfSizeY, 0);
            core::vector3df p3(halfSizeX, -halfSizeY, 0);
            core::vector3df p4(-halfSizeX, -halfSizeY, 0);

            core::matrix4 mat;
            mat.setTranslation(position);
            mat.setRotationDegrees(rotation);
            mat.transformVect(p1);
            mat.transformVect(p2);
            mat.transformVect(p3);
            mat.transformVect(p4);

            Plane.setPlane(p1, p2, p3);
            core::vector3df normal = Plane.Normal;

            Triangle.set(p1, p2, p3);
            Triangle2.set(p1, p3, p4);

            video::SColor color(0xFFFFFFFF);

            UpperLeftCorner = p1;
            UpperRightCorner = p2;
            GeometrySize.set(size.X, size.Y);

            Vertices[0] = video::S3DVertex(p1, normal, color, core::vector2df(0,0));
            Vertices[1] = video::S3DVertex(p2, normal, color, core::vector2df(1,0));
            Vertices[2] = video::S3DVertex(p3, normal, color, core::vector2df(1,1));
            Vertices[3] = video::S3DVertex(p4, normal, color, core::vector2df(0,1));

            Box.reset(Vertices[0].Pos);
            for (s32 i=1; i<4; ++i)
                Box.addInternalPoint(Vertices[i].Pos);

            // initialize the cursor image
            video::IImage* image = mgr->getVideoDriver()->createImageFromFile(cursorImageFileName);
            if(image)
            {
                video::ITexture* texture = mgr->getVideoDriver()->addTexture(cursorImageFileName, image);
                Cursor = addImage(texture, core::vector2d<s32>(0,0));
                image->drop();
                Cursor->grab();
                Cursor->remove();
            }

            AbsoluteRect = core::rect<s32>(0,0,textureSize.Width,textureSize.Height);
            AbsoluteClippingRect = AbsoluteRect;
            IGUIElement::Parent = 0;
        }

        CGUISceneNode::CGUISceneNode(IMeshSceneNode* parent, ISceneManager* mgr, s32 id,
                const core::stringc& cursorImageFileName,
                const core::vector3df vp1, const core::vector3df vp2, 
                const core::vector3df vp3, const core::vector3df vp4,
                IEventReceiver* eventReceiver,
                f32 activationDistance,
                const video::SColor& backgroundColor,
                const core::dimension2du& textureSize,
                const core::vector3df& position,
                const core::vector3df& rotation,
                const core::vector3df& scale)
            : ISceneNode(parent, mgr, id, position, rotation, scale),
            IGUIElement(gui::EGUIET_ELEMENT,0,0,id,core::rect<s32>()),
            ActivationDistance(activationDistance),
            ActivationMode(GSNAM_3D),
            BColor(backgroundColor),
            SceneManager(mgr),
            CollisionManager(mgr->getSceneCollisionManager()),
            Cursor(0),
            Activated(false),
            Draw(true),
            RenderGeometry(false),
            EventReceiver(eventReceiver),
            Hovered(0),
            Focus(0)
        {
            Environment = mgr->getGUIEnvironment();
            core::vector3df p1,p2,p3,p4;

            video::SColor color(0xFFFFFFFF);

            video::IVideoDriver* driver = mgr->getVideoDriver();

            if (driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
            {
                RenderTarget = driver->addRenderTargetTexture(textureSize, "GUISceneNodeRTT");
            }
            Material.setTexture(0,RenderTarget);
            Material.Lighting = false;

            IMesh* mesh = parent->getMesh();
            s32 mcount = mesh->getMeshBufferCount();
            IMeshBuffer* meshBuffer=0;

            // look for the meshbuffer to use
            for(s32 i=0; i<mcount; i++)
            {
                IMeshBuffer* mb = mesh->getMeshBuffer(i);
                video::SMaterial& mat = mb->getMaterial();
                for(u32 j=0;j<4;j++)
                {
                    video::ITexture* tex = mat.getTexture(j);
                    if(tex && (tex->getName().find("guinode") >= 0))
                    {
                        meshBuffer = mb;
                        break;
                    }                    
                }
            }

            if(meshBuffer)
            {
                u32 vcount = meshBuffer->getVertexCount();
                if(vcount == 4)
                {
                    switch(meshBuffer->getVertexType())
                    {
                    case video::EVT_STANDARD:
                        {
                            video::S3DVertex* v = (video::S3DVertex*)meshBuffer->getVertices();
                            p1 = v[0].Pos; p2 = v[1].Pos; p3 = v[2].Pos; p4 = v[3].Pos;
                            Vertices[0] = video::S3DVertex(p1, v[0].Normal, color, core::vector2df(0,0));
                            Vertices[1] = video::S3DVertex(p2, v[1].Normal, color, core::vector2df(1,0));
                            Vertices[2] = video::S3DVertex(p3, v[2].Normal, color, core::vector2df(1,1));
                            Vertices[3] = video::S3DVertex(p4, v[3].Normal, color, core::vector2df(0,1));
                        }
                        break;
                    case video::EVT_2TCOORDS:
                        {
                            video::S3DVertex2TCoords* v = (video::S3DVertex2TCoords*)meshBuffer->getVertices();
                            p1 = v[0].Pos; p2 = v[1].Pos; p3 = v[2].Pos; p4 = v[3].Pos;
                            Vertices[0] = video::S3DVertex(p1, v[0].Normal, color, core::vector2df(0,0));
                            Vertices[1] = video::S3DVertex(p2, v[1].Normal, color, core::vector2df(1,0));
                            Vertices[2] = video::S3DVertex(p3, v[2].Normal, color, core::vector2df(1,1));
                            Vertices[3] = video::S3DVertex(p4, v[3].Normal, color, core::vector2df(0,1));
                        }
                        break;
                    case video::EVT_TANGENTS:
                            video::S3DVertexTangents* v = (video::S3DVertexTangents*)meshBuffer->getVertices();
                            p1 = v[0].Pos; p2 = v[1].Pos; p3 = v[2].Pos; p4 = v[3].Pos;
                            Vertices[0] = video::S3DVertex(p1, v[0].Normal, color, core::vector2df(0,0));
                            Vertices[1] = video::S3DVertex(p2, v[1].Normal, color, core::vector2df(1,0));
                            Vertices[2] = video::S3DVertex(p3, v[2].Normal, color, core::vector2df(1,1));
                            Vertices[3] = video::S3DVertex(p4, v[3].Normal, color, core::vector2df(0,1));
                        break;
                    }
                }
            }

            // initialize the geometry

            core::matrix4 mat;
            mat.setTranslation(position);
            mat.setRotationDegrees(rotation);
            mat.transformVect(p1);
            mat.transformVect(p2);
            mat.transformVect(p3);
            mat.transformVect(p4);

            Plane.setPlane(p1, p2, p3);
            core::vector3df normal = Plane.Normal;

            Triangle.set(p1, p2, p3);
            Triangle2.set(p1, p3, p4);

            UpperLeftCorner = p1;
            UpperRightCorner = p2;
            GeometrySize.set(p2.X-p1.X, p3.Y-p2.Y);

            Box.reset(Vertices[0].Pos);
            for (s32 i=1; i<4; ++i)
                Box.addInternalPoint(Vertices[i].Pos);

            // initialize the cursor image
            video::IImage* image = mgr->getVideoDriver()->createImageFromFile(cursorImageFileName);
            if(image)
            {
                video::ITexture* texture = mgr->getVideoDriver()->addTexture(cursorImageFileName, image);
                Cursor = addImage(texture, core::vector2d<s32>(0,0));
                image->drop();
                Cursor->grab();
                Cursor->remove();
            }

            AbsoluteRect = core::rect<s32>(0,0,textureSize.Width,textureSize.Height);
            AbsoluteClippingRect = AbsoluteRect;
            IGUIElement::Parent = 0;
        }

        //! destructor
        CGUISceneNode::~CGUISceneNode()
        {
        }

        void CGUISceneNode::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
        {
            // todo - serialize node & gui element attributes
        }

        void CGUISceneNode::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
        {
            // todo
        }

        //! Returns the next element in the tab group starting at the focused element
        gui::IGUIElement* CGUISceneNode::getNextElement(bool reverse, bool group)
        {
            // start the search at the root of the current tab group
            IGUIElement *startPos = Focus ? Focus->getTabGroup() : 0;
            s32 startOrder = -1;

            // if we're searching for a group
            if (group && startPos)
            {
                startOrder = startPos->getTabOrder();
            }
            else
                if (!group && Focus && !Focus->isTabGroup())
                {
                    startOrder = Focus->getTabOrder();
                    if (startOrder == -1)
                    {
                        // this element is not part of the tab cycle,
                        // but its parent might be...
                        IGUIElement *el = Focus;
                        while (el && el->getParent() && startOrder == -1)
                        {
                            el = el->getParent();
                            startOrder = el->getTabOrder();
                        }

                    }
                }

                if (group || !startPos)
                    startPos = this; // start at the root

                // find the element
                IGUIElement *closest = 0;
                IGUIElement *first = 0;
                startPos->getNextElement(startOrder, reverse, group, first, closest);

                if (closest)
                    return closest; // we found an element
                else if (first)
                    return first; // go to the end or the start
                else if (group)
                    return this; // no group found? root group
                else
                    return 0;
        }

        //! sets the focus to an element
        bool CGUISceneNode::setFocus(IGUIElement* element)
        {
            if (Focus == element)
            {
                _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                return false;
            }

            // GUI Environment should not get the focus
            if (element == this)
                element = 0;

            // stop element from being deleted
            if (element)
                element->grab();

            // focus may change or be removed in this call
            IGUIElement *currentFocus = 0;
            if (Focus)
            {
                currentFocus = Focus;
                currentFocus->grab();
                SEvent e;
                e.EventType = EET_GUI_EVENT;
                e.GUIEvent.Caller = Focus;
                e.GUIEvent.Element = element;
                e.GUIEvent.EventType = gui::EGET_ELEMENT_FOCUS_LOST;
                if (Focus->OnEvent(e))
                {
                    if (element)
                        element->drop();
                    currentFocus->drop();
                    _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                    return false;
                }
                currentFocus->drop();
                currentFocus = 0;
            }

            if (element)
            {
                currentFocus = Focus;
                if (currentFocus)
                    currentFocus->grab();

                // send focused event
                SEvent e;
                e.EventType = EET_GUI_EVENT;
                e.GUIEvent.Caller = element;
                e.GUIEvent.Element = Focus;
                e.GUIEvent.EventType = gui::EGET_ELEMENT_FOCUSED;
                if (element->OnEvent(e))
                {
                    if (element)
                        element->drop();
                    if (currentFocus)
                        currentFocus->drop();
                    _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                    return false;
                }
            }

            if (currentFocus)
                currentFocus->drop();

            if (Focus)
                Focus->drop();

            // element is the new focus so it doesn't have to be dropped
            Focus = element;

            return true;
        }


        void CGUISceneNode::updateHoveredElement(core::position2d<s32> mousePos)
        {
            IGUIElement* lastHovered = Hovered;
            LastHoveredMousePos = mousePos;

            Hovered = getElementFromPoint(mousePos);

            if (Hovered)
            {
                u32 now = os::Timer::getTime ();

                if (Hovered != this)
                    Hovered->grab();

                if (Hovered != lastHovered)
                {
                    SEvent event;
                    event.EventType = EET_GUI_EVENT;

                    if (lastHovered)
                    {
                        event.GUIEvent.Caller = lastHovered;
                        event.GUIEvent.EventType = gui::EGET_ELEMENT_LEFT;
                        lastHovered->OnEvent(event);
                    }

                    /*
                    if ( ToolTip.Element )
                    {
                    ToolTip.Element->remove();
                    ToolTip.Element->drop();
                    ToolTip.Element = 0;
                    ToolTip.LastTime += 500;
                    }
                    else
                    {
                    // boost tooltip generation for relaunch
                    if ( now - ToolTip.LastTime < ToolTip.LastTime )
                    {
                    ToolTip.LastTime += 500;
                    }
                    else
                    {
                    ToolTip.LastTime = now;
                    }
                    }
                    */


                    event.GUIEvent.Caller = Hovered;
                    event.GUIEvent.EventType = gui::EGET_ELEMENT_HOVERED;
                    Hovered->OnEvent(event);
                }
            }

            if (lastHovered && lastHovered != this)
                lastHovered->drop();
        }


        //! Called if an event happened.
        bool CGUISceneNode::OnEvent(const SEvent& event)
        {
            if(event.EventType == EET_GUI_EVENT)
            {
                if(EventReceiver)
                    EventReceiver->OnEvent(event);
            }
            return false;
        }

        bool CGUISceneNode::postEventFromUser(const SEvent& event)
        {
            if(!Activated)
                return false;

            SEvent uevent = event;
            if(uevent.EventType == EET_MOUSE_INPUT_EVENT)
            {
                uevent.MouseInput.X = RTTCursorPos.X;
                uevent.MouseInput.Y = RTTCursorPos.Y;
            }

            switch(event.EventType)
            {
            case EET_GUI_EVENT:
                // hey, why is the user sending gui events..?
                break;
            case EET_MOUSE_INPUT_EVENT:

                updateHoveredElement(core::position2d<s32>(uevent.MouseInput.X, uevent.MouseInput.Y));

                if (uevent.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
                    if ( (Hovered && Hovered != Focus) || !Focus )
                    {
                        setFocus(Hovered);
                    }

                    // sending input to focus
                    if (Focus && Focus->OnEvent(uevent))
                        return true;

                    // focus could have died in last call
                    if (!Focus && Hovered)
                    {
                        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                        return Hovered->OnEvent(uevent);
                    }

                    break;
            case EET_KEY_INPUT_EVENT:
                {
                    // send focus changing event
                    if (uevent.EventType == EET_KEY_INPUT_EVENT &&
                        uevent.KeyInput.PressedDown &&
                        uevent.KeyInput.Key == KEY_TAB)
                    {
                        IGUIElement *next = getNextElement(uevent.KeyInput.Shift, uevent.KeyInput.Control);
                        if (next && next != Focus)
                        {
                            if (setFocus(next))
                                return true;
                        }
                    }
                    if (Focus)
                    {
                        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                        return Focus->OnEvent(uevent);
                    }
                }
                break;
            default:
                break;
            } // end switch

            _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
            return false;

        }

        void CGUISceneNode::OnRegisterSceneNode()
        {
            bool activated = false;

            if (ISceneNode::IsVisible)
            {
                SceneManager->registerNodeForRendering(this);
                ISceneNode::OnRegisterSceneNode();
            }

            if (ISceneNode::IsVisible && IGUIElement::IsEnabled)
            {
                ICameraSceneNode* camera = SceneManager->getActiveCamera();
                if(camera)
                {
                    // check if camera ray intersects our geometry
                    core::vector3df out,pos,end,target,start;

                    if(ActivationMode == GSNAM_3D)
                    {
                        start = pos = camera->getPosition();
                        end = (camera->getTarget() - pos);
                        start += end*8.0f;
                        end = start + (end * camera->getFarValue());
                    }
                    else 
                    {
                        core::line3df line = CollisionManager->getRayFromScreenCoordinates(CursorPos2D, camera);
                        start = pos = line.start;
                        //end = line.end - pos;
                        end = line.end;
                    }
                    target = end.normalize();

                    core::triangle3df T1 = Triangle;
                    core::triangle3df T2 = Triangle2;
                    core::matrix4 xfrm = getAbsoluteTransformation();
                    f32 sx=1.f,sy=1.f;
                    if(!xfrm.isIdentity())
                    {
                        xfrm.transformVect(T1.pointA);
                        xfrm.transformVect(T1.pointB);
                        xfrm.transformVect(T1.pointC);
                        xfrm.transformVect(T2.pointA);
                        xfrm.transformVect(T2.pointB);
                        xfrm.transformVect(T2.pointC);
                        sx = 1.f / xfrm.getScale().X;
                        sy = 1.f / xfrm.getScale().Y;
                    }

                    bool intersect = false;

                    // if backfaceculling is off, check for intersection on 
                    // both sides. otherwise make sure we're facing the 
                    // proper direction. (not working...)

                    core::vector3df ffTarget = T1.pointA - pos;
                    if(!Material.BackfaceCulling || T1.isFrontFacing(ffTarget))
                    {
                        // hit either tri?
                        intersect = T1.getIntersectionWithLine(start, end, out);
                        if(!intersect)
                            intersect = T2.getIntersectionWithLine(start, end, out);
                    }

                    if(intersect)
                    {
                        // regardless of the tri we intersect, activate if the closest
                        // point from either tri is within the requested distance.
                        debug = out;
                        
                        core::vector3df p1 = T1.closestPointOnTriangle(pos);
                        core::vector3df p2 = T2.closestPointOnTriangle(pos);                    

                        f32 distance = core::min_<f32>(p1.getDistanceFrom(pos),
                            p2.getDistanceFrom(pos));

                        if(distance <= ActivationDistance)
                        {
                            activated = true;
                            core::vector3df ULC = T1.pointA;
                            core::vector3df URC = T1.pointB;

                            // calc the gui cursor position
                            if(Cursor)
                            {
                                /*
                                UL---X-----------------UR
                                |\   |                  |
                                | \  |                  |
                                |  \ |                  |
                                |   \|                  |
                                Y    I                  |
                                |                       |
                                |                       |
                                LL---------------------LR

                                "2d" cursor pos depends on relative distances from UL->X & UL->Y.
                                "I" -> point of camera-ray intersection.
                                */
                                core::vector3df dir1(URC-ULC);
                                dir1.normalize();

                                // vector UL->I = hyp
                                core::vector3df dir2(out - ULC);
                                f32 hypLen = dir2.getLength();
                                dir2.normalize();

                                // angle between UL->UR & UL-I
                                f32 costheta = dir2.dotProduct(dir1);

                                // UL->X length
                                f32 gx = costheta * hypLen;

                                // I->X length
                                f32 gy = sqrt((hypLen*hypLen) + (gx*gx) - (2 * hypLen * gx * costheta));

                                f32 xpct = (gx / GeometrySize.X) * sx;
                                f32 ypct = (gy / GeometrySize.Y) * sy;

                                RTTCursorPos.X = (s32)(xpct * RenderTarget->getSize().Width);
                                RTTCursorPos.Y = (s32)(ypct * RenderTarget->getSize().Height);
                                Cursor->setRelativePosition(RTTCursorPos);
                            }
                        }
                    }
                }
            }

            if((Activated != activated) && EventReceiver)
            {
                Draw = true;
                Activated = activated;
                SEvent event;
                SGUISceneNodeEvent nevent;

                event.EventType = EET_USER_EVENT;
                event.UserEvent.UserData1 = ISceneNode::ID;
                event.UserEvent.UserData2 = (s32)&nevent;
                nevent.EventType = EGNET_ACTIVATED;
                nevent.UserData = activated;
                EventReceiver->OnEvent(event);                                  
            }
        }

        //! renders the node.
        void CGUISceneNode::render()
        {
            static u16 indices[] = {0,1,2, 0,2,3};
            video::IVideoDriver* driver = SceneManager->getVideoDriver();

            // update the RTT only when active or activation state changes 
            // for (cursor visibility).
            if(true || Activated || Draw)
            {
                Draw = false;

                // render the gui elements into the rtt.
                driver->setRenderTarget(RenderTarget, true, true, BColor);

                drawAll();

                // draw the cursor if activated and we're in 3d mode.                
                if(Activated && Cursor) // 2D debugging...
                //if(Activated && (ActivationMode==GSNAM_3D) && Cursor)
                    Cursor->draw();                

                // reset the render target
                driver->setRenderTarget(0, false, false, 0);
            }

            if(RenderGeometry)
            {
                driver->setMaterial(Material);
                driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
                driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 2);            
            }
        }

        //! returns the axis aligned bounding box of this node
        const core::aabbox3d<f32>& CGUISceneNode::getBoundingBox() const
        {
            return Box;
        }


    } // end namespace scene
} // end namespace irr

