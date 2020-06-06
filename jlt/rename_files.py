#!/usr/bin/env python

from __future__ import print_function

import os
import sys
import argparse, textwrap

# Globals

class Helper:
    _verbose            = False

    def __init__(self): pass

    def files(self, path):
        for file in os.listdir(path):
            if os.path.isfile(os.path.join(path, file)):
                yield file

    def sorted_files(self, path):
        files = [file for file in os.listdir(path) if os.path.isfile(os.path.join(path, file))]
        files.sort(key=os.path.getctime)
        return files

    def set_verbose(self, verbose):
        self._verbose = verbose

    def verbose_print(self, str):
        if self._verbose: print(str)

    def print_over(self, str):
        print(str, end="\r")

    def verbose_print_over(self, str):
        if self._verbose: print(str, end="\r")


# End of class Helper

class RenameFiles:
    _version_str = '0.1'
    _changelist_str = '''
        v0.1 Initial version
            + Take source and destination directory
            + Start and end file number
            + Rename jpeg files

    '''

    def __init__(self):
        self._parser = argparse.ArgumentParser(
                description='%(prog)s v' + self._version_str + '\n',
                formatter_class=argparse.RawTextHelpFormatter)
        self._required_args = self._parser.add_argument_group('Required arguments')
        self._required_args.add_argument('src_dir', help='Source Directory')
        self._required_args.add_argument('prefix', help='Rename to prefix')
        self._parser.add_argument('-s', '--start', metavar='start_num', help='Starting file number (default: %(default)s)', type=int, default=1)
        self._parser.add_argument('-v', '--verbose', help='Verbose', action='store_true', default=False)
        self._parser.add_argument('--version', action='version',
                version='%(prog)s v' + self._version_str + textwrap.dedent(self._changelist_str))

    def parse_args(self, argv):
        self._args = self._parser.parse_args()
        fn.set_verbose(self._args.verbose)
        self._args.start -= 1

    def rename_files(self):
        for count, file_name in enumerate(fn.sorted_files(self._args.src_dir)):
            file_ext = os.path.splitext(file_name)[1]
            new_filename = self._args.prefix + '_' + str(count + self._args.start) + file_ext
            print('{old} -> {new}'.format(old=file_name, new=new_filename))
            #os.rename(file_name, new_filename)

    # End of rename_files

if __name__ == "__main__":

    fn = Helper()

    rename = RenameFiles()

    rename.parse_args(sys.argv[1:])
    rename.rename_files()
