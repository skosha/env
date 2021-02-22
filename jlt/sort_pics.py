#!/usr/bin/env python

import sys, getopt
import os
import fnmatch
import re

# Globals

class Helper:
    def __init__(self): pass

    def set_verbose(self, verbose):
        self.__verbose = verbose
    # End of set_verbose

    def print_verbose(self, level, str):
        if level <= self.__verbose:
            print(str)
    # End of print_verbose

# End of class Helper

class PicSort:
    __version = '0.4'
    __description = 'Sort Pictures'
    __changelist_str = '''
Changelist:
* version 0.4 =>
    + Cleanup and modularisation of helper functions
* version 0.3 =>
    + Move to argparse
    + Use incremental verbose
    + Use a destructor function
* version 0.2 =>
    + Add argument validation
    + Add changelist
    + Modularisation of the code
* version 0.1 =>
    + Initial version
    + Take a prefix and add it to all the image files
       and move them to jpg, raw and mobile folders.
    + Take a starting number to begin the image count as
    '''

    def __init__(self):
        self.__parser = argparse.ArgumentParser(
                description='%(prog)s v' + self.__version + '\n' + self.__description,
                formatter_class=argparse.RawTextHelpFormatter)
        self.__required_args = self.__parser.add_argument_group('Required arguments')
        self.__required_args.add_argument('prefix', help='prefix for filenames')
        self.__parser.add_argument('-n', '--num', dest='start_count', type=int, help='starting count of the filenames', default=0)
        self.__parser.add_argument('-v', '--verbose', help='increase output verbosity', action="count", default=0)
        self.__parser.add_argument('--version', action='version',
                version='%(prog)s v' + self.__version + textwrap.dedent(self.__changelist_str))

        self.cleanup = False
    # End of initiator

    def __del__(self):
        if self.__cleanup:
            # Delete unmatched CR2 files
            raw_pattern = re.compile(r'IMG_[0-9]{4}.CR2')
            files_to_del = [file for file in os.listdir(self.dir) if (raw_pattern.search(file) is not None)]
            for file in files_to_del:
                fn.print_verbose(1, 'Deleting ' + file)
                os.remove(file)
    # End of destructor

    def parse_args(self):
        self.__args = self.__parser.parse_args()

        # Create the jpg/ and raw/ path
        self.prefix         = self.__args.prefix
        self.start          = self.__args.start_count
        self.dir            = '.'
        self.jpg_path       = os.path.join(self.dir, 'jpg')
        self.raw_path       = os.path.join(self.dir, 'raw')
        self.mobile_path    = os.path.join(self.dir, 'mobile')

        if not os.path.exists(self.jpg_path):
            fn.print_verbose(1, 'Creating ' + self.jpg_path)
            os.makedirs(self.jpg_path)

        if not os.path.exists(self.raw_path):
            fn.print_verbose(1, 'Creating ' + self.raw_path)
            os.makedirs(self.raw_path)

        if not os.path.exists(self.mobile_path):
            fn.print_verbose(1, 'Creating ' + self.mobile_path)
            os.makedirs(self.mobile_path)
    # End of __init__

    def sort_files(self):
        # Find all the JPG files, sorted in time order
        pattern = re.compile(r'.*\.(jpg|JPG)')
        files = [file for file in os.listdir(self.dir) if (pattern.search(file) is not None)]
        files.sort(key=os.path.getctime)

        # Rename and move the jpg files to jpg/ and corresponding raw file to raw/
        count = self.start if self.start > 1 else 1
        for file in files:
            filename, extension = os.path.splitext(file)
            new_filename = os.path.join(self.jpg_path, self.prefix + '_' + str(count).zfill(3) + '.jpg')
            fn.print_verbose(1, 'Rename ' + file + ' to ' + new_filename)
            os.rename(file, new_filename)
            if (os.path.exists(filename + '.CR2')):
                new_filename = os.path.join(self.raw_path, self.prefix + '_' + str(count).zfill(3) + '.CR2')
                fn.print_verbose(1, 'Rename ' + filename + '.CR2 to ' + new_filename)
                os.rename(filename + '.CR2', new_filename)
            count += 1
        self.cleanup = True
    # End of sort_files
# End of PicSort

if __name__ == "__main__":

    fn = Helper()
    pics = PicSort()
    pics.sort_files(start_count)
