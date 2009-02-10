#ifndef _IDEBUG_H_
#define _IDEBUG_H_
#define _CRT_SECURE_NO_WARNINGS 1
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>


#include "irrlicht.h"

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

typedef rect<s32> rectd;
typedef std::ostringstream StrStream;



#include "COverlay.h"
#include "CTextOverlay.h"

IGUIEnvironment* getGUI();

#endif
