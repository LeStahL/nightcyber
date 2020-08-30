#!/usr/bin/env python3

import os, argparse, glob

parser = argparse.ArgumentParser(description='Team210 meson globber.')
args, rest = parser.parse_known_args()

if len(rest) < 2:
    print("Warning: Qt5Globber was run with too few arguments. Will exit.")
    quit()

resourceFiles = glob.glob(os.path.join(rest[1], "**/*." + rest[0]), recursive=True)
for resourceFile in resourceFiles:
    if resourceFile != '':
        print(resourceFile)