#!/usr/bin/env python

import os, sys
import glob
import commands
import time
import tarfile
import distutils.spawn

class MyErrorErr(Exception):
    pass

class Common:
    def __init__(self):
        if sys.version_info[0] > 2:
            raise Exception('Must be using Python 2')

    def my_print(self, str):
        print str

    def extract_tar(self, file, dir):
        if os.path.exists(dir):
            fname, ext = os.path.splitext(file)
            if ext in ('.bz2', '.tbz2'):
                os.system('tar xjf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext in ('.gz', '.tgz'):
                os.system('tar xzf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.xz':
                os.system('tar xJf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.tar':
                os.system('tar xf {file} -C {dir}'.format(file=file, dir=dir))
            elif ext == '.rar':
                os.system('unrar e {file} > {dir}'.format(file=file, dir=dir))
            elif ext == '.zip':
                os.system('unzip {file} -d {dir}'.format(file=file, dir=dir))
            elif ext == '.7z':
                os.system('7z x {file} -o {dir}'.format(file=file, dir=dir))
        else:
            print 'Error in extracting ' + fname + ' to ' + dir
            sys.exit(2)

def MyError():
    raise MyErrorErr("Error from " + sys.argv[1])

fn = Common()
some_str = '/home/kshah/temp_bin'
device = 'mx140'

res = commands.getoutput('slsi_wlan_udi_log_decode').splitlines()
print res[len(res) - 1]

#fnames = glob.glob(some_str + '/device-fs/' + device + '*')
#print fnames
#dev_dir = [p for p in fnames if not os.path.isfile(p)]
#print dev_dir[0]

if distutils.spawn.find_executable("7z"):
    print '7z exists!'
if distutils.spawn.find_executable("tar"):
    print 'tar exists!'
if distutils.spawn.find_executable("unrar"):
    print 'unrar exists!'
if distutils.spawn.find_executable("unzip"):
    print 'unzip exists!'

#print glob.glob(sys.argv[1] + '/' + sys.argv[2] + '_*')

#print os.path.expanduser("~")

#file = os.popen('file -bi ' + sys.argv[1], 'r')
#print file.read()

ret = commands.getoutput('file -bi ' + sys.argv[1])
print ret.startswith('text')

file = sys.argv[1]
fname, ext = os.path.splitext(sys.argv[1])

os.makedirs('temp_bin')
fn.extract_tar(file, 'temp_bin')

while os.path.exists(file):
    file = fname + time.strftime("_%d%m%y_%H%M%S") + ext
print file

try:
    MyError()
except MyErrorErr as err:
    print str(err)

fn.my_print('Example string with a {filename} > symbol'.format(filename=file))
