//
// test angelscript script
// 

int count=0;
string rs="test string";

string initialize()
{
    print(rs);
    print("initialize() invoked");
    tubras.testFunc();
    tubras.setGUICursorVisible(false);
    return rs;
}

