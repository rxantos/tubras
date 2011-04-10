#include "iwalktest.h"


struct SCmdInfo
{
    char*       cmd;
    char*       desc;
    int (*handler) (TWalktest*, TGUIConsole* g, TEvent*);
    char*       alias;
};

int cmdHelp(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdFOV(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdFPS(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdAspect(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdClear(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdList(TWalktest* w, TGUIConsole* g, TEvent* e);
int cmdAnim(TWalktest* w, TGUIConsole* g, TEvent* e);

SCmdInfo commands[] = 
{
    {"help", "Display a list of commands.", cmdHelp, "?"},
    {"asr", "Get/Set current camera Aspect.", cmdAspect, 0},
    {"cls", "Clear the console display.", cmdClear, "clear"},
    {"fov", "Get/Set current camera FOV.", cmdFOV, 0},
    {"fps", "Display fps info.", cmdFPS, 0},
    {"ls", "List info for an object", cmdList, 0},
    {"anim", "List/Run animated nodes/animations", cmdAnim, 0},
    {"", "", 0, 0}
};

//-----------------------------------------------------------------------
//                          c m d C l e a r
//-----------------------------------------------------------------------
int cmdClear(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    g->clear();
    return 1;
}

//-----------------------------------------------------------------------
//                           n o d e C o u n t
//-----------------------------------------------------------------------
void nodeCount(ISceneNode* node, u32& nodes, u32& cameras, u32& lights)
{
    ++nodes;

    switch(node->getType())
    {
        case ESNT_LIGHT: ++lights; break;
        case ESNT_CAMERA: ++cameras; break;
        default:
            break;
    }

    list<ISceneNode*> children = node->getChildren();
    if(children.size())
    {
        list<ISceneNode*>::Iterator itr = children.begin();
        while(itr != children.end())
        {
            nodeCount(*itr, nodes, cameras, lights);
            itr++;
        }
    }
}

//-----------------------------------------------------------------------
//                        g e t N o d e L i s t
//-----------------------------------------------------------------------
void getNodeList(ISceneNode* node, array<ISceneNode*>& l)
{
    l.push_back(node);    

    list<ISceneNode*> children = node->getChildren();
    if(children.size())
    {
        list<ISceneNode*>::Iterator itr = children.begin();
        while(itr != children.end())
        {
            getNodeList(*itr, l);
            itr++;
        }
    }
}

//-----------------------------------------------------------------------
//                       w r i t e N o d e D a t a
//-----------------------------------------------------------------------
void writeNodeData(ISceneNode* node, TGUIConsole* g, bool summary=false)
{
    c8 buf[128];
    u32 ntype = node->getType();
    stringc sntype = "";
    stringc psnname = "null";

    ISceneNode* pnode = node->getParent();
    if(pnode)
        psnname = pnode->getName();

    sntype += char(ntype & 0xFF);
    sntype += char((ntype & 0xFF00) >> 8);
    sntype += char((ntype & 0xFF0000) >> 16);
    sntype += char((ntype & 0xFF000000) >> 24);

    if(summary)
    {
        sprintf(buf, "  name: %s, type: %s, id: %d, dbg: %s", node->getName(),
            sntype.c_str(), node->getID(), node->getDebugName());
        g->addText(buf);
        return;
    }

    vector3df apos = node->getAbsolutePosition();
    vector3df pos = node->getPosition();

    sprintf(buf, "  type: %s, id: %d, parent: %s, dbg: %s, apos: (%.2f, %.2f, %.2f), "
        "pos: (%.2f, %.2f, %.2f)", sntype.c_str(), node->getID(), psnname.c_str(),
        node->getDebugName(),
        apos.X, apos.Y, apos.Z,
        pos.X, pos.Y, pos.Z);
    g->addText(buf);

    if(ntype == ESNT_ANIMATED_MESH)
    {
        IAnimatedMeshSceneNode* anode = static_cast<scene::IAnimatedMeshSceneNode*>(node);

        u32 jcount = anode->getJointCount();
        sprintf(buf, "  joints: %d, frames: %d", jcount, anode->getEndFrame());
        g->addText(buf);

        for(u32 i=0; i<jcount; i++)
        {
            IBoneSceneNode* bnode = anode->getJointNode(i);
            apos = bnode->getAbsolutePosition();
            pos = bnode->getPosition();
            sprintf(buf, "  joint: %s, apos: (%.2f, %.2f, %.2f), pos: (%.2f, %.2f, %.2f)",
                bnode->getName(), 
                apos.X, apos.Y, apos.Z,
                pos.X, pos.Y, pos.Z);
            g->addText(buf);
        }
    }
}

//-----------------------------------------------------------------------
//                             c m d L i s t
//-----------------------------------------------------------------------
int cmdList(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    array<ISceneNode*> list;
    c8 buf[128];

    ISceneManager* sm = w->getRenderer()->getSceneManager();

    if(e->getNumParameters() == 1)
    {
        u32 nodes=0, cameras=0, lights=0;
        nodeCount(sm->getRootSceneNode(), nodes, cameras, lights);

        sprintf(buf, "  Scene Nodes: %d, Cameras: %d, Lights: %d", nodes, cameras, lights);
        g->addText(buf);

        // list nodes
        getNodeList(sm->getRootSceneNode(), list);
        for(u32 i=0; i < list.size(); i++)
        {
            ISceneNode* sn = list[i];
            if(sn)
            {
                writeNodeData(sn, g, true);
            }
        }            
    }
    else
    {
        TEventParameter* ep = e->getParameter(1);
        Tubras::TString p = ep->getStringValue();
        getNodeList(sm->getRootSceneNode(), list);
        bool found = false;
        for(u32 i=0; i < list.size(); i++)
        {
            if(p == list[i]->getName())
            {
                ISceneNode* sn = list[i];
                if(sn)
                {
                    found = true;
                    writeNodeData(sn, g);
                }
            }
        }
        if(!found)
        {
            sprintf(buf, "  not found");
            g->addText(buf);
        }
    }

    return 1;
}

//-----------------------------------------------------------------------
//                             c m d A n i m
//-----------------------------------------------------------------------
int cmdAnim(TWalktest* w, TGUIConsole* g, TEvent* e)
{

    const TArray<IAnimatedMeshSceneNode*>& anodes = w->getAnimatedNodes();

    c8 buf[128];

    if(e->getNumParameters() == 1)
    {
        for(u32 i=0; i < anodes.size(); i++)
        {
            IAnimatedMeshSceneNode* node = anodes[i];
            sprintf(buf, "Animated Node: %s", node->getName());
            g->addText(buf);
        }

    }
    else if (e->getNumParameters() == 2)
    {
        stringc nodeName = e->getParameter(1)->getStringValue();
        IAnimatedMeshSceneNode* node=0;
        for(u32 i=0; i < anodes.size(); i++)
        {
            stringc name = anodes[i]->getName();
            if(name == nodeName)
            {
                node = anodes[i];
                break;
            }
        }
        if(node)
        {
            node->setFrameLoop(0, node->getEndFrame());
            node->setAnimationSpeed(30);
        }
    }

    return 1;
}

//-----------------------------------------------------------------------
//                            c m d A s p e c t
//-----------------------------------------------------------------------
int cmdAspect(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    ICameraSceneNode* n = w->getRenderer()->getSceneManager()->getActiveCamera();
    const c8* name = n->getName();
    f32 oasp = n->getAspectRatio();

    c8 buf[128];

    if(e->getNumParameters() == 1)
    {
        sprintf(buf, "%s %.2f", name, oasp);
    }
    else
    {
        stringc asps = e->getParameter(1)->getStringValue();
        f32 asp = (f32)atof(asps.c_str());
        n->setAspectRatio(asp);
        sprintf(buf, "%s %.2f set to %.2f", name, oasp, asp);
    }

    g->addText(buf);

    return 1;
}

//-----------------------------------------------------------------------
//                            c m d F O V
//-----------------------------------------------------------------------
int cmdFOV(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    ICameraSceneNode* n = w->getRenderer()->getSceneManager()->getActiveCamera();
    const c8* name = n->getName();
    f32 ofov = n->getFOV();

    c8 buf[128];

    if(e->getNumParameters() == 1)
    {
        sprintf(buf, "%s %.2f", name, ofov);
    }
    else
    {
        stringc fovs = e->getParameter(1)->getStringValue();
        f32 fov = (f32)atof(fovs.c_str());
        n->setFOV(fov);
        sprintf(buf, "%s %.2f set to %.2f", name, ofov, fov);
    }

    g->addText(buf);

    return 1;
}

//-----------------------------------------------------------------------
//                            c m d F P S
//-----------------------------------------------------------------------
int cmdFPS(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    c8 buf[128];
    s32 fps = w->getRenderer()->getVideoDriver()->getFPS();

    sprintf(buf, "%d", fps);
    g->addText(buf);
    return 1;
}

//-----------------------------------------------------------------------
//                            c m d H e l p
//-----------------------------------------------------------------------
int cmdHelp(TWalktest* w, TGUIConsole* g, TEvent* e)
{
    u32 idx=0;

    while(commands[idx].handler)
    {
        stringc text= "  ";        
        text += commands[idx].cmd;
        text += " - ";
        text += commands[idx].desc;

        g->addText(text);

        ++idx;
    }

    return 1;
}

//-----------------------------------------------------------------------
//                        p r o c C o m m a n d
//-----------------------------------------------------------------------
int procCommand(TWalktest* w, TEvent* e)
{
    u32 idx=0;
    stringc cmd=e->getParameter(0)->getStringValue();

    while(commands[idx].handler)
    {
        if(cmd.equals_ignore_case(commands[idx].cmd) ||
            (commands[idx].alias &&
           cmd.equals_ignore_case(commands[idx].alias)))
        {
            return commands[idx].handler(w, w->getGUIConsole(), e);
        }
        ++idx;
    }

    w->getGUIConsole()->addText("* invalid command *");

    return 0;
}
