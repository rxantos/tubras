#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-----------------------------------------------------------------------------
import bpy


class Filename:
    def __init__(self,fullPath):
        self.fullPath = fullPath
        self.dirPath = Blender.sys.dirname(fullPath)
        self.fileName = Blender.sys.basename(fullPath)
        self.file, self.ext = Blender.sys.splitext(self.fileName)
        if self.file == 'Untitled':
            self.file += self.ext
            self.ext = ''

        self.dirParts = []
        part = ''
        for c in self.dirPath:
            if (c == '/') or (c == '\\'):
                self.dirParts.append(part)
                part = ''
            else:
                part += c

    def printDebug(self):
        print('fullPath',self.fullPath)
        print('dirPath',self.dirPath)
        print('fileName',self.fileName)
        print('file', self.file)
        print('ext',self.ext)
        print('dirParts',self.dirParts)

    def getBaseName(self):
        return self.file

    def setExtension(self,ext):
        self.ext = ext

