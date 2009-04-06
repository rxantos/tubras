// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUISceneNode.h"
#include "ISceneManager.h"
#include "IGUIEnvironment.h"
#include "IVideoDriver.h"
#include "ICameraSceneNode.h"
#include "ISceneCollisionManager.h"
#include "os.h"

namespace irr
{
    namespace scene
    {
        //! constructor
        CGUISceneNode::CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::stringc& cursorImageFileName,
            IEventReceiver* eventReceiver,
            f32 activationDistance,
            const video::SColor& backgroundColor,
            const core::dimension2du& textureSize,
            const core::vector2df& size,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)
            : IGUISceneNode(parent, mgr, id),
            IGUIElement(gui::EGUIET_ELEMENT,0,0,id,core::rect<s32>()),
            ActivationDistance(activationDistance),
            BColor(backgroundColor),
            SceneManager(mgr),
            Cursor(0),
            Activated(false),
            Draw(true),
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

            // initialize the geometry
            Material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
            Material.Wireframe = false;
            Material.Lighting = false;
            Material.BackfaceCulling = false;
            //Material.ZBuffer = 0;
            Material.MaterialTypeParam = 0.0001f;
            Material.setTexture(0,RenderTarget);

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
                Cursor = mgr->getGUIEnvironment()->addImage(texture, core::vector2d<s32>(0,0));
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
                uevent.MouseInput.X = CursorPos.X;
                uevent.MouseInput.Y = CursorPos.Y;
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

            if (IGUISceneNode::IsVisible)
            {
                SceneManager->registerNodeForRendering(this, ESNRP_TRANSPARENT);

                ICameraSceneNode* camera = SceneManager->getActiveCamera();
                if(camera)
                {
                    // check if camera ray intersects our geometry
                    core::vector3df out;
                    core::vector3df pos = camera->getPosition();
                    core::vector3df end = (camera->getTarget() - pos);
                    end.normalize();
                    core::vector3df start=pos;
                    start += end*8.0f;
                    end = start + (end * camera->getFarValue());

                    bool intersect = Triangle.getIntersectionWithLine(start, end, out);
                    if(!intersect)
                        intersect = Triangle2.getIntersectionWithLine(start, end, out);

                    if(intersect)
                    {
                        // regardless of the tri we intersect, activate if the closest
                        // point is within our required distance.
                        core::vector3df p1 = Triangle.closestPointOnTriangle(pos);
                        core::vector3df p2 = Triangle2.closestPointOnTriangle(pos);                    

                        f32 distance = core::min_<f32>(p1.getDistanceFrom(pos),
                            p2.getDistanceFrom(pos));

                        if(distance <= ActivationDistance)
                        {
                            debug = out;
                            activated = true;

                            // calc cursor position
                            if(Cursor)
                            {
                                core::vector3df gdistance = out - UpperLeftCorner;
                                f32 xpct = gdistance.X / GeometrySize.X;
                                f32 ypct = -gdistance.Y / GeometrySize.Y;

                                CursorPos.X = (s32)(xpct * RenderTarget->getSize().Width);
                                CursorPos.Y = (s32)(ypct * RenderTarget->getSize().Height);
                                Cursor->setRelativePosition(CursorPos);
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
                event.UserEvent.UserData1 = IGUISceneNode::ID;
                event.UserEvent.UserData2 = (s32)&nevent;
                nevent.EventType = EGNET_ACTIVATED;
                nevent.UserData = activated;
                EventReceiver->OnEvent(event);                                  
            }

            ISceneNode::OnRegisterSceneNode();
        }

        //! renders the node.
        void CGUISceneNode::render()
        {
            static u16 indices[] = {0,1,2, 0,2,3};

            video::IVideoDriver* driver = SceneManager->getVideoDriver();
            gui::IGUIEnvironment* env = SceneManager->getGUIEnvironment();

            // update the RTT only when active or activation state changes 
            // for (cursor visibility).
            if(Activated || Draw)
            {

                Draw = false;
                driver->setRenderTarget(RenderTarget, true, true, BColor);

                drawAll();

                // draw the cursor 
                if(Activated && Cursor)
                    Cursor->draw();

                // set back old render target
                driver->setRenderTarget(0, false, false, 0);
            }

            driver->setMaterial(Material);
            driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
            driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 2);            
        }

        //! returns the axis aligned bounding box of this node
        const core::aabbox3d<f32>& CGUISceneNode::getBoundingBox() const
        {
            return Box;
        }


    } // end namespace scene
} // end namespace irr

