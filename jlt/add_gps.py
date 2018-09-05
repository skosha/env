#!/usr/bin/env python

import sys, getopt
import os
import re
import piexif
from PIL import Image

# Globals
version             = 0.2
verbose             = False
inFile              = ''
outFile             = ''
lastFile            = ''

def files(path):
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            yield file

def verbose_print(str):
    global verbose
    if verbose:
        print str

def print_usage():
    print 'Add GPS info Version: ' + str(version)
    print 'Extract GPS info from a photo and apply to others'
    print ''
    print 'Usage: add_gps.py -i <input_filename> -o <output_filename> [-r <last_filename>]'
    print '\t-h, --help     print this message'
    print '\t-V, --version  print version information'
    print '\t-v, --verbose  print verbose messages'
    print '\t-i, --input    filename to extract GPS info from'
    print '\t-o, --output   output filename to add GPS info to'
    print '\t-r, --range    if using a range of output file, add the last filename'
    print ''

def print_version():
    print 'Add GPS info Version: ' + str(version)
    print 'Extract GPS info from a photo and apply to others'
    print ''
    print 'Changelist:'
    print '\tv0.2'
    print '\t - Add argument validation'
    print '\t - Add changelist'
    print ''
    print '\tv0.1'
    print '\t - Initial version'
    print '\t - Take an input file, extract GPS info and add it to'
    print '\t   output file(s) range'
    print ''

def check_arg(arg):
    if arg.startswith('-'):
        print 'ERROR: Incorrect argument: ' + arg + '\n'
        print_usage()
        sys.exit(2)

def parse_args(argv):
    global verbose
    global inFile
    global outFile
    global lastFile
    try:
        opts, args = getopt.getopt(argv, "hVvi:o:r:", ["--help", "--version", "--verbose",
            "--input=", "--output=", "--range="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print_usage()
            sys.exit()
        elif opt in ("-V", "--version"):
            print_version()
            sys.exit()
        elif opt in ("-v", "--verbose"):
            verbose = True
        elif opt in ("-i", "--input"):
            check_arg(arg)
            inFile = arg
        elif opt in ("-o", "--output"):
            check_arg(arg)
            outFile = arg
        elif opt in ("-r", "--range"):
            check_arg(arg)
            lastFile = arg

    # Check the input file
    if not inFile:
        print_usage()
        sys.exit(2)
    elif not (os.path.exists(inFile)):
        print 'Error: Could not find the input file: ' + inFile
        sys.exit(2)

    # Prepare list of output files
    out_files = []
    if lastFile:
        filename, extension = os.path.splitext(outFile)
        num_pattern = re.compile(r'\d+')
        prefix_pattern = re.compile(r'\D+')
        prefix = prefix_pattern.search(filename).group(0)
        start_num = int(num_pattern.search(filename).group(0))
        end_num = int(num_pattern.search(lastFile).group(0))
        for i in range(start_num, end_num + 1):
            if (os.path.exists(prefix + str(i) + extension)):
                out_files.append(prefix + str(i) + extension)
    elif (os.path.exists(outFile)):
        out_files.append(outFile)
    else:
        print 'Error: Could not find output files'
        sys.exit(2)

    return out_files
# End of parse_args

def get_gps_data(file):
    img = Image.open(file)
    exif_dict = piexif.load(img.info['exif'])
    return exif_dict['GPS']

def add_gps_data(gps_ifd, file):
    img = Image.open(file)
    exif_dict = piexif.load(img.info['exif'])
    exif_dict['GPS'] = gps_ifd
    exif_bytes = piexif.dump(exif_dict)
    img.save(file, "jpeg", exif=exif_bytes, quality=95)

if __name__ == "__main__":
    out_files = parse_args(sys.argv[1:])

    # Extract the GPS information from input file
    verbose_print('Extract GPS info from ' + inFile + ' ...')
    gps_ifd = get_gps_data(inFile)

    for file in out_files:
        verbose_print('Adding GPS info to ' + file + ' ...')
        add_gps_data(gps_ifd, file)
