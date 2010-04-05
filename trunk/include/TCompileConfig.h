//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
//
// which sound system to use 
//
#if !defined(USE_NULL_SOUND) && !defined(USE_FMOD_SOUND) && !defined(USE_IRR_SOUND)
#define USE_NULL_SOUND 1
//#define USE_FMOD_SOUND 1
//#define USE_IRR_SOUND 1
#endif

#define HAVE_SNPRINTF 1
