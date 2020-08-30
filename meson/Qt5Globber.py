#!/usr/bin/env python3

import os, argparse, glob

parser = argparse.ArgumentParser(description='Team210 meson qt5 globber.')
parser.add_argument('-rcc', '--ressource-compiler', dest='rcc', action='store_true')
parser.add_argument('-uic', '--ui-compiler', dest='uic', action='store_true')
parser.add_argument('-moc', '--meta-object-compiler', dest='moc', action='store_true')
parser.add_argument('-src', '--source', dest='src', action='store_true')
args, rest = parser.parse_known_args()

if not rest:
    print("Warning: Qt5Globber was run without a directory argument. Will do nothing.")

for dirPath in rest:
    if args.rcc:
        headerFiles = glob.glob(os.path.join(dirPath, "**/*.h"), recursive=True) + glob.glob(os.path.join(dirPath, "*.hpp"), recursive=True)
        mocHeaders = []
        for headerFile in headerFiles:
            with open(headerFile, 'rt') as f:
                if 'Q_OBJECT' in f.read():
                    mocHeaders += headerFile
                f.close()
        for mocHeader in mocHeaders:
            if mocHeader != '':
                print(mocHeader)

    if args.rcc:
        resourceFiles = glob.glob(os.path.join(dirPath, "**/*.qrc"), recursive=True)
        for resourceFile in resourceFiles:
            if resourceFile != '':
                print(resourceFile)

    if args.uic:
        uiFiles = glob.glob(os.path.join(dirPath, "**/*.ui"), recursive=True)
        for uiFile in uiFiles:
            if uiFile != '':
                print(uiFile)

    if args.src:
        srcFiles = glob.glob(os.path.join(dirPath, "**/*.cpp"), recursive=True)
        for srcFile in srcFiles:
            if srcFile != '':
                print(srcFile)
