//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

//
// which sound system to use 
//
#if !defined(USE_NULL_SOUND) && !defined(USE_FMOD_SOUND) && !defined(USE_IRR_SOUND)
//#define USE_NULL_SOUND 1
//#define USE_FMOD_SOUND 1
#define USE_IRR_SOUND 1
#endif

//
// config script
//
#if !defined(USE_LSL_SCRIPT) && !defined(USE_ISL_SCRIPT)
// #define USE_ISL_SCRIPT
#define USE_LSL_SCRIPT 1
#endif

#if !defined(TUBRAS_EXCLUDE_PHYSICS)
#define TUBRAS_INCLUDE_PHYSICS
#endif

#define USE_PYTHON_SCRIPTING 1

#define HAVE_SNPRINTF 1
