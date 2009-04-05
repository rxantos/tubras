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
            ActivationDistance(activationDistance),
            BColor(backgroundColor),
            SceneManager(mgr),
            Cursor(0),
            Activated(false),
            EventReceiver(eventReceiver)
        {
#ifdef _DEBUG
            setDebugName("CGUISceneNode");
#endif

            video::IVideoDriver* driver = mgr->getVideoDriver();

            if (driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
            {
                RenderTarget = driver->addRenderTargetTexture(textureSize, "GUISceneNodeRTT");
            }

            // initialize the geometry
            Material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
            Material.Wireframe = false;
            Material.Lighting = false;
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

        }

        //! destructor
        CGUISceneNode::~CGUISceneNode()
        {
        }

        void CGUISceneNode::OnRegisterSceneNode()
        {
            bool activated = false;

            if (IsVisible)
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
                                core::position2di cpos((s32)(xpct * RenderTarget->getSize().Width),
                                    (s32)(ypct * RenderTarget->getSize().Height));
                                Cursor->setRelativePosition(cpos);
                            }
                        }
                    }
                }
            }

            if((Activated != activated) && EventReceiver)
            {
                Activated = activated;
                SEvent event;
                SGUISceneNodeEvent nevent;

                event.EventType = EET_USER_EVENT;
                event.UserEvent.UserData1 = ID;
                event.UserEvent.UserData2 = (s32)&nevent;
                nevent.EventType = EGNET_ACTIVATED;
                nevent.UserData = activated;
                EventReceiver->OnEvent(event);                                  
            }

            ISceneNode::OnRegisterSceneNode();
        }

        void CGUISceneNode::addGUIElement(gui::IGUIElement* element)
        {
            element->grab();
            element->remove();            
            Elements.push_back(element);
        }

        //! renders the node.
        void CGUISceneNode::render()
        {
            video::IVideoDriver* driver = SceneManager->getVideoDriver();
            gui::IGUIEnvironment* env = SceneManager->getGUIEnvironment();

            // set render target texture
            driver->setRenderTarget(RenderTarget, true, true, BColor);

            // draw the gui elements
            for(u32 i=0; i< Elements.size(); i++)
            {
                gui::IGUIElement* element = Elements[i];
                element->draw();
            }

            // draw the cursor if activated
            if(Activated && Cursor)
                Cursor->draw();

            // set back old render target
            driver->setRenderTarget(0, false, false, 0);

		    u16 indices[] = {	0,1,2, 0,2,3	};
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

