//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _GETOPT_H_
#define _GETOPT_H_

extern int optind, opterr;
extern char *optarg;

int getopt(int argc, char *argv[], const char *optstring);

#endif 
