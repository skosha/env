#!/usr/bin/env python

import sys, getopt
import os
import glob
import commands
import tarfile
import distutils.spawn
import time

class Common:
    _version = 1.3
    _verbose = False

    _description = 'Advance py_script script v{version}'.format(version=_version)
    _usage = """
Usage: py_script.py [options] -i <log_file> [-r <release_num>|-b <build>|-l] [-o <out_file>]

Options:
    Files:
    -i, --input         input log file
    -o, --output        output file name, optional.
    Build, one of the three needs to be provided:
    -r, --release       <release_num>, release number in decimal
    -b, --build         <build>, can be a directory or a tar file
    -l, --local         local. With a local decode, the dev decoder file is
                        used and it expects a symbol file
    Options (optional):
    -h, --help          Print this message
    -V, --version       Print version history
    -v, --verbose       Verbose
    -d, --device        Device name. Default is arm9.
    -s, --sym           symbol file name. Default is derived from the build.
    --dev               Use cmdDecode from dev folder. Expects the dev folder
                        to be $HOME/repos/fw/
    --decoder           Supply custom decoder file to use
    --debug             Debug. Prints debug information and does not perform
                        any function
    --cmd-opts          Custom cmd decode options. Default - '--nocolor'

Dependencies:
    - dev folder is $HOME/repos/fw
    - release folder is /home/releases
    - log bin decode file is $HOME/bin/log_decode

Examples:
    decode based on release number:
            py_script.py -r 2508 -i log.txt
    use release symbol files, but dev decoder:
            py_script.py -r 2508 -dev -i log.txt
    use local build:
            py_script.py -b ~/repos/fw/builds/ -i log.txt
    use local archive:
            py_script.py -b buil.tar.xz -i log.txt
    no release:
            py_script.py -l -sym symbols.dbg -i log.txt

   """
    _changelist = """
Changelist:
* version 1.3 =>
    + Convert to python
    + Converted arguments to be consistent Unix style
    + Modularize the code
    + Added an option to provide custom decoder file
    + Added an option to provide custom decoder options
* Version 1.2 =>
    + Fix for date appended output file name
    + More modularization
* Version 1.1 =>
    + Fixed issues if local and no symbol file
    + Added support for local build directory/archive file too
    + Refactored the code a bit and made it modular
* Version 1.0 =>
    + Initial version
    """

    _7z_exists      = False
    _tar_exists     = False
    _unrar_exists   = False
    _unzip_exists   = False

    def __init__(self):
        if sys.version_info[0] > 2:
            raise Exception("Must be using Python 2")
        self._7z_exists      = True if distutils.spawn.find_executable("7z")     else False
        self._tar_exists     = True if distutils.spawn.find_executable("tar")    else False
        self._unrar_exists   = True if distutils.spawn.find_executable("unrar")  else False
        self._unzip_exists   = True if distutils.spawn.find_executable("unzip")  else False

    def print_usage(self):
        print self._description
        print self._usage

    def print_version(self):
        print self._description
        print self._changelist
        print '-------------------------------'
        print 'Using python version {version}\n'.format(version=sys.version)
        print '-------------------------------'
        if not self._tar_exists:
            print 'Could not find tar command'
        else:
            print commands.getoutput('tar --version').splitlines()[0] + '\n'
        print '-------------------------------'
        if not self._unrar_exists:
            print 'Could not find unrar command'
        else:
            print commands.getoutput('unrar --version').splitlines()[0] + '\n'
        print '-------------------------------'
        if not self._unzip_exists:
            print 'Could not find unzip command'
        else:
            print commands.getoutput('unzip -v').splitlines()[0]
            print commands.getoutput('unzip -v').splitlines()[5] + '\n'
        print '-------------------------------'
        if not self._7z_exists:
            print 'Could not find 7z command'
        else:
            print commands.getoutput('7z').splitlines()[1]
            print commands.getoutput('7z').splitlines()[2] + '\n'
        print '-------------------------------'

    def check_arg(self, arg):
        if arg.startswith('-'):
            print 'ERROR: Incorrect argument: ' + arg + '\n'
            self.print_usage()
            sys.exit(2)

    def verbose_print(self, str):
        if self._verbose:
            print '\n' + str

    def set_verbose(self, verbose):
        self._verbose = verbose

    def extract_tar(self, file, dir):
        if os.path.exists(dir):
            fname, ext = os.path.splitext(file)
            if ext in ('.bz2', '.tbz2') and self._tar_exists:
                self.verbose_print('tar xjf {file} -C {dir}'.format(file=file, dir=dir))
                os.system('tar xjf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext in ('.gz', '.tgz') and self._tar_exists:
                self.verbose_print('tar xzf {file} -C {dir}'.format(file=file, dir=dir))
                os.system('tar xzf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.xz' and self._tar_exists:
                self.verbose_print('tar xJf {file} -C {dir}'.format(file=file, dir=dir))
                os.system('tar xJf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.tar' and self._tar_exists:
                self.verbose_print('tar xf {file} -C {dir}'.format(file=file, dir=dir))
                os.system('tar xf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.rar' and self._unrar_exists:
                self.verbose_print('unrar e {file} > {dir}'.format(file=file, dir=dir))
                os.system('unrar e {file} > {dir}'.format(file=file, dir=dir))
            elif ext == '.zip' and self._unzip_exists:
                self.verbose_print('unzip {file} -d {dir}'.format(file=file, dir=dir))
                os.system('unzip {file} -d {dir}'.format(file=file, dir=dir))
            elif ext == '.7z' and self._7z_exists:
                self.verbose_print('7z x {file} -o {dir}'.format(file=file, dir=dir))
                os.system('7z x {file} -o {dir}'.format(file=file, dir=dir))
            else:
                print self._tar_exists
                print ext
                print 'Error in extracting ' + file + ' to ' + dir
                sys.exit(2)
        else:
            print 'Error in extracting ' + file + ' to ' + dir
            sys.exit(2)

    def is_binary(self, fname):
        ret = commands.getoutput('file -bi ' + fname)
        if ret.startswith('text'):
            return False
        return True

# End of class Helper

class DecoderError(Exception):
    pass

class Decoder:
    _cleanup = False
    _dev_decoder_file       = ''
    _releases_root          = ''
    _log_decode             = ''
    _log_file               = ''
    _out_file               = ''
    _sym_file               = ''
    _decoder_file           = ''
    _release_num            = 0
    _build                  = ''
    _local                  = False
    _debug                  = False
    _device                 = ''
    _home_dir               = ''
    _release_decode_loc     = ''
    _sym_file_loc           = ''
    _sym_name               = 'symbols.dbg'
    _cmd_opts               = ''

    def __init__(self):
        self._home_dir = os.path.expanduser("~")
        self._releases_root = '/home/releases'
        self._dev_decode_file = self._home_dir + '/repos/fw/decode.pl'
        self._log_decode = self._home_dir + '/bin/log_decode'
        self._device = 'arm9'
        self._release_decode_loc  = '/decode.pl'
        self._sym_file_loc = '/debug/symbols.dbg'
        self._cmd_opts = '--nocolor'

    def parse_args(self, argv):
        try:
            opts, args = getopt.getopt(argv, "hVvr:b:li:o:d:s:", ["help", "version",
            "verbose", "release=", "build=", "local", "input=",
            "output=", "device=", "sym=", "dev", "debug", "decoder=",
            "cmd-opts="])
        except getopt.GetoptError as err:
            print str(err)
            fn.print_usage()
            sys.exit(2)
        for opt, arg in opts:
            if opt in ("-h", "--help"):
                fn.print_usage()
                sys.exit()
            elif opt in ("-V", "--version"):
                fn.print_version()
                if not os.path.exists(self._log_decode):
                    print 'decoder not found'
                else:
                    res = commands.getoutput('log_decode').splitlines()
                    print res[len(res) - 1]
                print '\n'
                sys.exit()
            elif opt in ("-v", "--verbose"):
                fn.set_verbose(True)
            elif opt == "--debug":
                self._debug = True
            elif opt in ("-i", "--input"):
                fn.check_arg(arg)
                self._log_file = arg
            elif opt in ("-o", "--output"):
                fn.check_arg(arg)
                self._out_file = arg
            elif opt in ("-s", "--sym"):
                fn.check_arg(arg)
                self._sym_file = arg
            elif opt in ("-b", "--build"):
                fn.check_arg(arg)
                self._build = arg
            elif opt == "--local":
               self._local = True
               self._decoder_file = self._dev_decode_file
            elif opt in ("-r", "--release"):
                fn.check_arg(arg)
                self._release_num = int(arg)
            elif opt in ("-d", "--device"):
                fn.check_arg(arg)
                self._device = arg
            elif opt == "--dev":
               self._decoder_file = self._dev_decode_file
            elif opt == "--decoder":
                fn.check_arg(arg)
                self._decoder_file = arg
            elif opt == "--cmd-opts":
                print arg
                self._cmd_opts = arg
            else:
                print 'Abort: Unknown option {option} {arg}'.format(option=opt, arg=arg)
                fn.print_usage()
                sys.exit(2)
    # End of parse_args

    def decode_args(self):
        # Verify the input log file
        if not os.path.exists(self._log_file):
            raise DecoderError('Error: Could not find ' + self._log_file)
        elif fn.is_binary(self._log_file):
            # Log file is binary, convert it to text
            if os.path.exists(self._log_decode):
                fname, ext = os.path.splitext(self._log_file)
                fn.verbose_print('{decoder} {logfile} > {outfile}'.format(decoder=self._log_decode, logfile=self._log_file,
                            outfile=fname + '_decoded.txt'))
                os.system('{decoder} {logfile} > {outfile}'.format(decoder=self._log_decode, logfile=self._log_file, outfile=fname + '_decoded.txt'))
                self._log_file = fname + '_decoded.txt'
                if not os.path.exists(self._log_file):
                    raise DecoderError('Error: Could not decode ' + fname + ext)
            else:
                raise DecoderError('Panic: no {decoder} to decode binary log {log_file}'.format(decoder=self._log_decode, log_file=self._log_file))

        # Derive the output filename
        if not self._out_file:
            fname, ext = os.path.splitext(self._log_file)
            self._out_file = fname + '_decoded' + ext
        fname, ext = os.path.splitext(self._out_file)
        while os.path.exists(self._out_file):
            self._out_file = fname + time.strftime("_%d%m%y_%H%M%S") + ext

        # Derive the release directory
        if (self._release_num > 0): # Numbered Release
            res = glob.glob(self._releases_root + '/' +
                    str(self._release_num) + '_*')
            if len(res):
                self._release_dir = [p for p in res if os.path.isdir(p)][0]
            else:
                raise DecoderError('Could not find the release directory for {release_num}'.format(release_num=self._release_num))
        elif os.path.isdir(self._build): # Local build directory
            self._release_dir = self._build
        elif self._build: # Local build archive
            temp_dir = self._home_dir + '/temp_bin'
            if (os.path.isdir(temp_dir)):
                os.system('rm -rf {dir}'.format(dir=temp_dir))
            os.makedirs(temp_dir)
            fn.verbose_print('Extracting...')
            fn.extract_tar(self._build, temp_dir)
            self._release_dir = temp_dir
            self._cleanup = True
        elif not self._local: # No release/build
            raise DecoderError('Error: Could not derive the build')

        # Derive the decoder file, if not already provided
        if not self._decoder_file:
            self._decoder_file = self._release_dir + self._release_decode_loc

        # Derive the symbol file
        if self._local and not self._sym_file: # Use provided symbol file
            self._sym_file = self._sym_name
        elif os.path.isdir(self._release_dir): # Use the symbol file from build/release folder
            print self._release_dir
            res = glob.glob(self._release_dir + self._device + '*')
            if len(res):
                dev_dir = [p for p in res if os.path.isdir(p)][0]
                self._sym_file = dev_dir + self._sym_file_loc
            else:
                raise DecoderError('Error: Could not find the device {device} folder'.format(device=self._device))
        else:
            raise DecoderError('Error: Could not resolve the symbol file')
    # End of decode_args

    def cmd_decode(self):
        assert os.path.exists(self._decoder_file), 'PANIC: no decoder file'
        assert os.path.exists(self._sym_file), 'PANIC: no symbol file'
        assert os.path.exists(self._log_file), 'PANIC: no input log file'

        if not self._debug:
            fn.verbose_print('cat {logfile} | {decoder} {cmd_opts} --fw_dbg_file={symfile} > {outfile}'.format(logfile=self._log_file, decoder=self._decoder_file, cmd_opts=self._cmd_opts, symfile=self._sym_file, outfile=self._out_file))
            os.system('cat {logfile} | {decoder} {cmd_opts} --fw_dbg_file={symfile} > {outfile}'.format(logfile=self._log_file, decoder=self._decoder_file, cmd_opts=self._cmd_opts, symfile=self._sym_file, outfile=self._out_file))
        else:
            print 'log file     - ' + self._log_file
            print 'out file     - ' + self._out_file
            print 'decoder file - ' + self._decoder_file
            print 'symbol file  - ' + self._sym_file
    # End of cmd_decode

    def cleanup(self):
        if self._cleanup:
            fn.verbose_print('Deleting {dir}'.format(dir=self._release_dir))
            os.system('rm -rf {dir}'.format(dir=self._release_dir))
    # End of cleanup

# End of class Decoder

# Main Program
if __name__ == "__main__":
    fn = Common()
    decodeApp = Decoder()

    if len(sys.argv) < 2:
        fn.print_usage()
        sys.exit()

    decodeApp.parse_args(sys.argv[1:])

    try:
        decodeApp.decode_args()
    except DecoderError as err:
        print str(err)
        decodeApp.cleanup()
        sys.exit(2)

    try:
        decodeApp.cmd_decode()
    except DecoderError as err:
        print str(err)
        decodeApp.cleanup()
        sys.exit(2)

    decodeApp.cleanup()
