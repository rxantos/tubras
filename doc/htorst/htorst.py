import os.path
import sys
import os

#-----------------------------------------------------------------------------
#                                 P a r m
#-----------------------------------------------------------------------------
class Parm:
    def __init__(self, name):
        self.name = name
        self.desc = []

    def processLine(self, line):
        self.desc.append(line)

#-----------------------------------------------------------------------------
#                               M e t h o d
#-----------------------------------------------------------------------------
class Method:
    def __init__(self, name):
        self.name = name
        self.predesc = []
        self.postdesc = []
        self.desc = self.predesc
        self.parms = []
        self.ret = ''
        self.curParm = None

    def processLine(self, line):
        prefix = line[:2]
        desc = ''
        if line == '':
            if self.curParm:
                self.curParm.processLine(line)
            else:
                self.desc.append('')
        elif prefix == '\\p':
            if line.find(':'):
                name, desc = line[3:].split(':')

            self.curParm = Parm(name.strip())
            self.curParm.processLine(desc.strip())
            self.parms.append(self.curParm)

        elif prefix == '\\r':
            print('split:', line)
            if line.find(':') >= 0:
                name, desc = line[3:].split(':')
            else:
                name = line
            self.ret = Parm(name)
            if len(desc):
                self.ret.processLine(desc.strip())
            self.curParm = self.ret

#-----------------------------------------------------------------------------
#                                C l a s s
#-----------------------------------------------------------------------------
class Class:
    def __init__(self, name):
        self.name = name
        self.description = []
        self.methods = []
        self.properties = []
        self.curMethod = None

    def addMethod(self, name):
        pass

    def processLine(self, line):
        if line[:2] == '::':
            self.curMethod = Method(line[2:])
            self.methods.append(self.curMethod)
        elif self.curMethod:
            self.curMethod.processLine(line)
        else:
            self.description.append(line)
        pass

#-----------------------------------------------------------------------------
#                         _ d u m p C l a s s I n f o
#-----------------------------------------------------------------------------
def _dumpClassInfo(classes):
    print('-------------')
    for c in classes:
        print('class: {0}'.format(c.name))
        for m in c.methods:
            print('   method: {0}'.format(m.name))
            for p in m.parms:
                print('       parm: {0}'.format(p.name))
                if m.ret:
                    print('        ret: {0}'.format(m.ret.name))
                else:
                    print('        ret: None')

#-----------------------------------------------------------------------------
#                            p r o c e s s F i l e
#-----------------------------------------------------------------------------
def processFile(filename, outDirectory):

    classStack = []

    if outDirectory[len(outDirectory)-1] != os.sep:
        outDirectory += os.sep

    ofilename = os.path.basename(filename)
    ofilename = outDirectory + os.path.splitext(ofilename)[0] + '.rst'

    print('Processing "{0}" to "{1}"'.format(filename, ofilename))

    if os.path.exists(ofilename):
        os.unlink(ofilename)

    curClass = None

    fin = open(filename)
    fout = open(ofilename, 'w')
    for line in fin:

        pos = line.find('//!')
        if pos >= 0:
            sline = line[pos+3:].strip()
            print(sline)

            # new class definition?
            if len(sline) > 2 and sline[0] == ':' and sline[1] != ':':
                curClass = Class(sline[1:])
                classStack.append(curClass)
            elif curClass:
                curClass.processLine(sline)

    fout.close()
    fin.close()

    return classStack

#-----------------------------------------------------------------------------
#                                u s a g e
#-----------------------------------------------------------------------------
def usage(verbose=False):
    print('usage: htorst.py <out directory> <input header files...> ')
    
#-----------------------------------------------------------------------------
#                                 m a i n
#-----------------------------------------------------------------------------
if __name__ == '__main__':
    if len(sys.argv) < 3:
        usage()
        sys.exit(1)

    print(os.path.abspath(os.curdir))

    outDirectory = sys.argv[1]
    filenames = []
    args = sys.argv[2:]
    argc = len(args)
    for i in range(argc):
        parm = args[i]
        if not os.path.exists(parm):
            print('Input file missing: {0}'.format(parm))
            continue

        filenames.append(parm)

    for filename in filenames:
        classes = processFile(filename, outDirectory)
        _dumpClassInfo(classes)
