#ifndef _TESTTHEME_H_
#define _TESTTHEME_H_

class TTestTheme : public Tubras::TTheme
{
private:
    
public:
    TTestTheme(string basedir);
    int load();
    int unload();

};

#endif
