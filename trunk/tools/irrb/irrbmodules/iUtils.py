#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
#
# Copyright (C) 2008 Keith Murray -- <pc0de@tubras.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# this export script is assumed to be used with the latest blender version.
#-----------------------------------------------------------------------------
import Blender, os, sys
from struct import pack

iversion = '0.3'

PATHTOKENS=('$fullpath','$filename','')
_logFile = None

#-----------------------------------------------------------------------------
#                               M A K E _ I D 2
#-----------------------------------------------------------------------------
lilEndian = pack('<h',1) == pack('=h',1)
def MAKE_ID2(c,d):
    if lilEndian:
        return (ord(d) << 8) | ord(c)
    else:
        return (ord(c) << 8) | ord(d)
    
# Blender block type ID's from database 
ID_SCE		= MAKE_ID2('S', 'C')
ID_LI		= MAKE_ID2('L', 'I')
ID_OB		= MAKE_ID2('O', 'B')
ID_ME		= MAKE_ID2('M', 'E')
ID_CU		= MAKE_ID2('C', 'U')
ID_MB		= MAKE_ID2('M', 'B')
ID_MA		= MAKE_ID2('M', 'A')
ID_TE		= MAKE_ID2('T', 'E')
ID_IM		= MAKE_ID2('I', 'M')
ID_IK		= MAKE_ID2('I', 'K')
ID_WV		= MAKE_ID2('W', 'V')
ID_LT		= MAKE_ID2('L', 'T')
ID_SE		= MAKE_ID2('S', 'E')
ID_LF		= MAKE_ID2('L', 'F')
ID_LA		= MAKE_ID2('L', 'A')
ID_CA		= MAKE_ID2('C', 'A')
ID_IP		= MAKE_ID2('I', 'P')
ID_KE		= MAKE_ID2('K', 'E')
ID_WO		= MAKE_ID2('W', 'O')
ID_SCR		= MAKE_ID2('S', 'R')
ID_VF		= MAKE_ID2('V', 'F')
ID_TXT		= MAKE_ID2('T', 'X')
ID_SO		= MAKE_ID2('S', 'O')
ID_GR		= MAKE_ID2('G', 'R')
ID_ID		= MAKE_ID2('I', 'D')
ID_AR		= MAKE_ID2('A', 'R')
ID_AC		= MAKE_ID2('A', 'C')
ID_SCRIPT	= MAKE_ID2('P', 'Y')
ID_NT		= MAKE_ID2('N', 'T')
ID_BR		= MAKE_ID2('B', 'R')
ID_PA		= MAKE_ID2('P', 'A')

#-----------------------------------------------------------------------------
#                               o p e n L o g
#-----------------------------------------------------------------------------
def openLog(fileName):
    global _logFile
    if Blender.sys.exists(fileName):
        os.unlink(fileName)
    _logFile = open(fileName,'w')
    #print 'irrb - unable to open logfile:',fileName
    #print 'exception:',sys.exc_info()[0]

    return False

#-----------------------------------------------------------------------------
#                              c l o s e L o g
#-----------------------------------------------------------------------------
def closeLog():
    global _logFile
    if _logFile != None:
        _logFile.close()

#-----------------------------------------------------------------------------
#                              w r i t e L o g
#-----------------------------------------------------------------------------
def writeLog(msg):
    data = msg + '\n'
    if _logFile != None:
        _logFile.write(data)

#-----------------------------------------------------------------------------
#                                d e b u g
#-----------------------------------------------------------------------------
def debug(msg):
    writeLog(msg)

#-----------------------------------------------------------------------------
#                            c o l o u r 2 s t r
#-----------------------------------------------------------------------------
def colour2str(value):
    rval = '%.8x' % value
    return rval

#-----------------------------------------------------------------------------
#                            r g b 2 S C o l o r
#-----------------------------------------------------------------------------
def rgb2SColor(value):
    r = int(round(value[0] * 255.0))
    g = int(round(value[1] * 255.0))
    b = int(round(value[2] * 255.0))

    SColor = 0xFF000000 | (r << 16) | (g << 8) | b
    return SColor

#-----------------------------------------------------------------------------
#                              r g b 2 s t r
#-----------------------------------------------------------------------------
def rgb2str(value):
    ival = rgb2SColor(value)
    return colour2str(ival)

#-----------------------------------------------------------------------------
#                             f l o a t 2 s t r 
#-----------------------------------------------------------------------------
def float2str(value):
    rval = '%.6f' % value
    return rval

#-----------------------------------------------------------------------------
#                               i n t 2 s t r
#-----------------------------------------------------------------------------
def int2str(value):
    rval = str(value)
    return rval

#-----------------------------------------------------------------------------
#                              b o o l 2 s t r
#-----------------------------------------------------------------------------
def bool2str(value):
    rval = 'false'
    if value:
        rval = 'true'
    return rval

#-----------------------------------------------------------------------------
#                           d a t e t i m e 2 s t r
#-----------------------------------------------------------------------------
def datetime2str(value):
    rval = 'mm/dd/yyyy hh:nn'
    yyyy = value[0]
    mm = value[1]
    dd = value[2]
    hh = value[3]
    nn = value[4]
    rval = '%.2d/%.2d/%d %.2d:%.2d' % (mm,dd,yyyy,hh,nn)
    return rval

#-----------------------------------------------------------------------------
#                             g e t v e r s i o n
#-----------------------------------------------------------------------------
def getversion():
    return 'v' + iversion

#-----------------------------------------------------------------------------
#                             g e t I n d e n t
#-----------------------------------------------------------------------------
def getIndent(level,extra=0):
    indent = ''
    for i in range(level+1):
        indent += '   '
    if extra > 0:
        for i in range(extra):
            indent += ' '
    return indent

#-----------------------------------------------------------------------------
#                            f i l t e r P a t h
#-----------------------------------------------------------------------------
def filterPath(path):
    out = ''
    path = path.strip()
    if path.lower() in PATHTOKENS:
        return path.lower()

    for c in path:
        if c == '/' or c == '\\':
            out = out + '/'
        else:
            out = out + c
    if out[len(out)-1] != '/':
        out = out + '/'
    return out

#-----------------------------------------------------------------------------
#                          f i l t e r D i r P a t h
#-----------------------------------------------------------------------------
def filterDirPath(path):

    out = ''
    path = path.strip()
    if path.lower() in PATHTOKENS:
        return path.lower()

    for c in path:
        if c == '/' or c == '\\':
            out = out + os.sep
        else:
            out = out + c
    if out[len(out)-1] != os.sep:
        out = out + os.sep
        
    return out

#-----------------------------------------------------------------------------
#                           g e t P r o p e r t y
#-----------------------------------------------------------------------------
def getProperty(pname,plist,caseSensitive=False):
    for p in plist:
        name = p.getName()
        if caseSensitive:
            if name == pname:
                return p
        else:
            if name.lower() == pname.lower():
                return p

    return None
