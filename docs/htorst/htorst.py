import sys
import os

#-----------------------------------------------------------------------------
#                            c o n v e r t F i l e
#-----------------------------------------------------------------------------
def convertFile(filename, outDirectory):
    pass

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
    for i in range(1, argc):
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
        convertFile(filename, outDirectory)

