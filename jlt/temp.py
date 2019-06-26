#!/usr/bin/env python

from __future__ import print_function

import os, sys
import glob
import time
import tarfile
import distutils.spawn
import argparse, textwrap
import shutil



class Helper:
    _version_str = '0.1'
    _changelist_str = '''
        v0.1 Initial version
            + Take source and destination directory
            + Start and end file number
            + Copy/move the jpeg and CR2 files

    '''

    def __init__(self):
        self._parser = argparse.ArgumentParser(
                description='v' + self._version_str + '\nTest script',
                formatter_class=argparse.RawTextHelpFormatter)
        self._required_args = self._parser.add_argument_group('Required arguments')
        self._required_args.add_argument('src_dir', help='Source Directory')
        self._required_args.add_argument('dest_dir', help='Destination Directory')
        self._required_args.add_argument('-s', '--start', help='Starting file number (default: %(default)s)', type=int, default=0, required=True)
        self._required_args.add_argument('-e', '--end', help='Ending file number (default: %(default)s)', type=int, default=0, required=True)
        self._parser.add_argument('-m', '--move', help='Move the file (default: %(default)s)', action='store_true', default=False)
        self._parser.add_argument('-v', '--verbose', help='Verbose', action='store_true', default=False)
        self._parser.add_argument('--version', action='version',
                version='%(prog)s v' + self._version_str + textwrap.dedent(self._changelist_str))

    def parse_args(self, argv):
        return self._parser.parse_args()

#fn = Helper()

#args = fn.parse_args(sys.argv)

#print(args.src_dir)
#print(args.dest_dir)
#print(args.start)
#print(args.end)

shutil.copy2(sys.argv[1], sys.argv[2])
