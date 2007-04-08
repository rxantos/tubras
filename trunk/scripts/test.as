//
// test angelscript script
// 

int count=0;
string rs="test string";
TModelNode@ model;

int handleEscape(string event)
{

    print("AS handleEscape invoked.");
    tubras.stopRunning();
    return 1;
}

string initialize()
{
    //TModelNode m("test");
    
    print(rs);
    print("initialize() invoked");
    tubras.testFunc();
    tubras.setGUICursorVisible(false);
    
    tubras.acceptEvent("key.down.esc","handleEscape");

    @model = tubras.loadModel("Cube.mesh");
    model.setPos(0.0,0.0,-15.0);

    return rs;
}

