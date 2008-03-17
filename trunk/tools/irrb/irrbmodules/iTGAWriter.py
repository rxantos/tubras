#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
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
# A modified version of "write_tgafile" in "uv_export.py" by Martin Poirier.
#-----------------------------------------------------------------------------
import Blender

#-----------------------------------------------------------------------------
#                               w r i t e T G A
#-----------------------------------------------------------------------------
def writeTGA(bImage,outFilename,RLE=True,callBack=None):
    file=open(outFilename,'wb')

    width,height = bImage.size
    bpp = bImage.depth

    if bpp < 24:
        file.close()
        print 'writeTGA only handles 24 or 32 bit images'
        return 1
    
    header = []
    for i in range(18):
        header.append(chr(0))
    if RLE:
        header[2] = chr(10)     # rle bgra image
    else:
        header[2] = chr(2)      # bgra image
    header[13] = chr(width / 256)
    header[12] = chr(width % 256)
    header[15] = chr(height / 256)
    header[14] = chr(height % 256)
    header[16] = chr(bpp)       # 24 or 32 bpp
    if bpp == 32:
        header[17] = chr(03)    # 00vhaaaa - useful alpha data

    #
    # write header
    #
    for byte in header:
	  file.write(byte)

    #
    # write data
    #
    for y in range(width):
        if (callBack != None) and ((y % 10) == 0):
            callBack(y)
        run = ''
        runLength = 1
        first = True
        lastPixel = ''
        for x in range(width):
            p = bImage.getPixelI(x,y)   # rgba
            pixel = chr(p[2]) + chr(p[1]) + chr(p[0])
            if bpp == 32:
                pixel += chr(p[3])
                
            if not RLE:
                file.write(pixel)
            else:
                if first:
                    lastPixel = pixel
                    first = False
                else:
                    if (pixel != lastPixel) or (runLength == 128):
                        packet = chr(128+runLength-1)
                        rleData = packet + lastPixel
                        file.write(rleData)
                        lastPixel = pixel
                        runLength = 1
                    else:
                        runLength += 1
        #
        # write last run
        #
        if RLE:
            packet = chr(128+runLength-1)
            rleData = packet + lastPixel
            file.write(rleData)
            		
    file.close()
    return 0
	
