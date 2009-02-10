#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
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
    for y in range(height):
        if (callBack != None) and ((y % 10) == 0):
            callBack(y)
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
	
