//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
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

// timing framework includes
#include "ITimingEventListener.h"
#include "ITimingSource.h"
#include "IAnimator.h"
#include "IEvaluator.h"
#include "IInterpolator.h"
#include "ITimingTarget.h"
#include "CTimingSource.h"
#include "CKeyTimes.h"
#include "CKeyValues.h"
#include "CLinearInterpolator.h"
#include "CKeyInterpolators.h"
#include "CKeyFrames.h"
#include "CDiscreteInterpolator.h"  
#include "CSplineInterpolator.h"
#include "CAnimator.h"
#include "CTimingManager.h"


IGUIEnvironment* getGUI();

#endif
