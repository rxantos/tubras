//
// test angelscript script
// 

int count=0;
string rs="test string";

string initialize()
{
    TModelNode@ model;
    //TModelNode m("test");
    
    print(rs);
    print("initialize() invoked");
    tubras.testFunc();
    tubras.setGUICursorVisible(false);

    @model = tubras.loadModel("Cube.mesh");
    model.setPos(0.0,0.0,-15.0);

    return rs;
}

