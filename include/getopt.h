//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _GETOPT_H_
#define _GETOPT_H_

extern int optind, opterr;
extern const char *optarg;

int getopt(int argc, const char *argv[], const char *optstring);

#endif 
