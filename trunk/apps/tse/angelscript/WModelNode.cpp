#include "tubras.h"
#include "angelscript.h"
#include "wmodelnode.h"

void WModelNode_Construct(std::string& in, WModelNode *o)
{
	new(o) WModelNode(in);
}

WModelNode& WModel_Assign(WModelNode& model, WModelNode& modelOther)
{
	model = modelOther;
    model.name = modelOther.name;
    model.m_model = modelOther.m_model;
	return model;
}

void *WModelNode_Alloc(int size)
{
	return new char[size];
}


void WModelNode_Register(asIScriptEngine* engine)
{
    int r;
	//r = engine->RegisterObjectType("TModelNode", sizeof(WModelNode), asOBJ_CLASS_CDA); 
	r = engine->RegisterObjectType("TModelNode", 0, asOBJ_CLASS_DA); 
	r = engine->RegisterObjectBehaviour("TModelNode", asBEHAVE_ALLOC, "TModelNode &f(uint)", asFUNCTION(WModelNode_Alloc), asCALL_CDECL); 
	r = engine->RegisterObjectBehaviour("TModelNode", asBEHAVE_CONSTRUCT, "void f(string& in)", asFUNCTION(WModelNode_Construct), asCALL_CDECL_OBJLAST); 
	r = engine->RegisterObjectBehaviour("TModelNode", asBEHAVE_ADDREF, "void f()", asMETHOD(WModelNode, addRef), asCALL_THISCALL); 
	r = engine->RegisterObjectBehaviour("TModelNode", asBEHAVE_RELEASE, "void f()", asMETHOD(WModelNode, release), asCALL_THISCALL);
	r = engine->RegisterObjectBehaviour("TModelNode", asBEHAVE_ASSIGNMENT, "TModelNode &f(TModelNode &in)", asMETHOD(WModelNode, operator=), asCALL_THISCALL); 
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD, "TModelNode &f(TModelNode &in, TModelNode &in)", asFUNCTION(WModelNode::Add), asCALL_CDECL); 
    r = engine->RegisterObjectMethod("TModelNode","void setPos(float,float,float)",asMETHOD(WModelNode,setPos),asCALL_THISCALL);

}
