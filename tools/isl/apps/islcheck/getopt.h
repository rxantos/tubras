//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _GETOPT_H_
#define _GETOPT_H_

extern int optind, opterr;
extern char *optarg;

int getopt(int argc, char *argv[], char *optstring);

#endif 
