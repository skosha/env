#!/usr/bin/env python

from __future__ import print_function

import sys
import os
import shutil
import fnmatch
import re
import argparse, textwrap

# Globals

class Helper:
    _verbose            = False

    def __init__(self): pass

    def files(self, path):
        for file in os.listdir(path):
            if os.path.isfile(os.path.join(path, file)):
                yield file

    def set_verbose(self, verbose):
        self._verbose = verbose

    def verbose_print(self, str):
        if self._verbose: print(str)

    def print_over(self, str):
        print(str, end="\r")

    def verbose_print_over(self, str):
        if self._verbose: print(str, end="\r")


# End of class Helper

class PicsCopy:
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
        self._required_args.add_argument('-s', '--start', metavar='start_num', help='Starting file number (default: %(default)s)', type=int, default=0, required=True)
        self._required_args.add_argument('-e', '--end',  metavar='end_num', help='Ending file number (default: %(default)s)', type=int, default=0, required=True)
        self._parser.add_argument('-m', '--move', help='Move the file (default: %(default)s)', action='store_true', default=False)
        self._parser.add_argument('-v', '--verbose', help='Verbose', action='store_true', default=False)
        self._parser.add_argument('--version', action='version',
                version='%(prog)s v' + self._version_str + textwrap.dedent(self._changelist_str))

    def parse_args(self, argv):
        self._args = self._parser.parse_args()
        if (self._args.start >= self._args.end):
            print('Error: Invalid start/end filenumber')
            sys.exit(2)
        fn.set_verbose(self._args.verbose)

    def copy_files(self):
        total_files = 0
        file_list = []
        for count in range(self._args.start, self._args.end + 1):
            file_found = False
            filename = 'IMG_' + str(count).zfill(4)
            src_filename = os.path.join(self._args.src_dir, filename + '.JPG')
            if (os.path.exists(src_filename)):
                file_list.append(src_filename)
                file_found = True
                total_files += 1
            elif (os.path.exists(os.path.join(self._args.src_dir, filename + '.jpg'))):
                src_filename = os.path.join(self._args.src_dir, filename + '.jpg')
                file_list.append(src_filename)
                file_found = True
                total_files += 1
            if file_found:
                src_filename = os.path.join(self._args.src_dir, filename + '.CR2')
                if (os.path.exists(src_filename)):
                    file_list.append(src_filename)
                    total_files += 1

        files_copied = 0
        for file in file_list:
            if not fn._verbose: fn.print_over('{action} file {cur}/{total}'.format(action="Moving" if self._args.move else "Copying", cur=files_copied + 1, total=total_files))
            fn.verbose_print_over('{action} {file} to {dir} {cur}/{total}'.format(action="Moving" if self._args.move
                        else "Copying", file=file, dir=self._args.dest_dir,
                        cur=files_copied + 1, total=total_files))
            shutil.copy2(file, self._args.dest_dir)
            if self._args.move: os.remove(file)
            files_copied += 1
        print('\n{action} file {cur}/{total}'.format(action="Moved" if self._args.move else "Copied", cur=files_copied, total=total_files))
    # End of copy_files

if __name__ == "__main__":

    fn = Helper()

    pics = PicsCopy()

    pics.parse_args(sys.argv[1:])
    pics.copy_files()
