//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
//
// which sound system to use 
//
#if !defined(USE_SOUND_NULL) && !defined(USE_SOUND_FMOD) && !defined(USE_SOUND_IRR)
#define USE_SOUND_NULL 1
//#define USE_SOUND_FMOD 1
//#define USE_SOUND_IRR 1
#endif

#define HAVE_SNPRINTF 1
