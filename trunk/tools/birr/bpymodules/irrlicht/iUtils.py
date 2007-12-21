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

iversion = '0.1'

def colour2str(value):
    rval = '%.8x' % value
    return rval

def rgb2SColor(value):
    r = int(round(value[0] * 255.0))
    g = int(round(value[1] * 255.0))
    b = int(round(value[2] * 255.0))

    SColor = 0xFF000000 | (r << 16) | (g << 8) | b
    return SColor

def rgb2str(value):
    ival = rgb2SColor(value)
    return colour2str(ival)

def float2str(value):
    rval = '%.6f' % value
    return rval

def int2str(value):
    rval = str(value)
    return rval

def bool2str(value):
    rval = 'false'
    if value:
        rval = 'true'
    return rval

def datetime2str(value):
    rval = 'mm/dd/yyyy hh:nn'
    yyyy = value[0]
    mm = value[1]
    dd = value[2]
    hh = value[3]
    nn = value[4]
    rval = '%.2d/%.2d/%d %.2d:%.2d' % (mm,dd,yyyy,hh,nn)
    return rval

def getversion():
    return 'v' + iversion
