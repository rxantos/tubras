class WModelNode
{

public:
    WModelNode(std::string n) {name =n; refCount = 1; m_model=0;}
	WModelNode &operator=(const WModelNode &o) 
	{
		return *this;
	}
	int addRef() 
	{
		return ++refCount;
	}
	int release() 
	{
		int r = --refCount; 
		if( refCount == 0 ) delete this; 
		return r;
	}
	static WModelNode &Add(WModelNode &self, WModelNode &other)
	{
		return self;
	}

    void setPos(float x, float y , float z)
    {

        if(m_model)
            m_model->setPos(x,y,z);
    }

    std::string name;
    int refCount;
    Tubras::TModelNode*     m_model;


};


void WModelNode_Construct(std::string& in, WModelNode *o);
WModelNode& WModelNode_Assign(WModelNode& model, WModelNode& modelOther);
void WModelNode_Register(asIScriptEngine* engine);

