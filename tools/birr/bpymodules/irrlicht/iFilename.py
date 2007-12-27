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
import Blender


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
        print 'fullPath',self.fullPath
        print 'dirPath',self.dirPath
        print 'fileName',self.fileName
        print 'file', self.file
        print 'ext',self.ext
        print 'dirParts',self.dirParts

    def getBaseName(self):
        return self.file

    def setExtension(self,ext):
        self.ext = ext

