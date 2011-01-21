import os.path
import sys
import os

class Class:
    def __init__(self, name):
        self.name = name
        self.methods = []
        self.properties = []

    def addMethod(self, name):
        pass
#-----------------------------------------------------------------------------
#                            p r o c e s s F i l e
#-----------------------------------------------------------------------------
def processFile(filename, outDirectory):

    if outDirectory[len(outDirectory)-1] != os.sep:
        outDirectory += os.sep

    ofilename = os.path.basename(filename)
    ofilename = outDirectory + os.path.splitext(ofilename)[0] + '.rst'

    print('Processing "{0}" to "{1}"'.format(filename, ofilename))

    if os.path.exists(ofilename):
        os.unlink(ofilename)


    fin = open(filename)
    fout = open(ofilename, 'w')
    for line in fin:

        pos = line.find('//!')
        if pos >= 0:
            sline = line[pos+3:].strip()
            print(sline)
            fout.write(sline)

    fin.close()



#-----------------------------------------------------------------------------
#                                u s a g e
#-----------------------------------------------------------------------------
def usage(verbose=False):
    print('usage: htorst.py <input header files> <out directory>')
    
#-----------------------------------------------------------------------------
#                                 m a i n
#-----------------------------------------------------------------------------
if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()
        sys.exit(1)

    outDirectory = './'
    filenames = []
    args = sys.argv[1:]
    argc = len(args)
    for i in range(argc):
        parm = args[i]
        if not os.path.exists(parm):
            print('Input file missing: {0}'.format(parm))
            continue

        if i < argc-1:
            filenames.append(parm)
        else:
            if not os.path.isdir(parm):
                filenames.append(parm)
            else:
                outDirectory = parm

    for filename in filenames:
        processFile(filename, outDirectory)

