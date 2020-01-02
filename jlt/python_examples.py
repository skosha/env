#!/usr/bin/env python

import re
import time
import os, sys
import csv
import inspect
import datetime
import commands
import tarfile
import zipfile
import distutils.spawn

import_list = [
    'import argparse',
    'import textwrap',
    'from jira import JIRA',
    'import getpass',
    'import shlex'
]

install_list = []
if import_list:
    try:
        exec('import sh')
    except ImportError:
        print('ImportError: Sh is pre-requisite. Please install using pip install sh')
        sys.exit(2)

    for imp in import_list:
        try:
            exec(imp)
        except ImportError:
            install_list.append(imp)

if install_list:
    for imp in install_list:
        pkg = imp.split()[1]
        print('Installing package {}'.format(pkg))
        sh.pip("install", pkg)
        exec(imp)

def is_expected_datetime_format(timestamp):
    for f in ['%Y-%m-%dT%H:%M:%S.%f%Z', '%Y-%m-%d']: # acceptable formats
        try:
            return datetime.datetime.strptime(timestamp, f)
        except ValueError:
            pass
    return False

class GitHelper:

    __jira = None

    def __init__(self):
        repo_dir = os.getcwd()
        repo_dir = sh.git(["rev-parse", "--show-toplevel"]).strip()
        self.__repo = sh.git.bake(_tty_out=False, _cwd=repo_dir)

    def setup_jira(self):
        username = getpass.getuser()
        passwd = getpass.getpass(prompt='Jira Password: ', stream=None)
        self.__jira = JIRA('http://scsc-jira', basic_auth=(username, passwd))

    def is_branch(self, branch):
        try:
            git_args = shlex.split(("show-ref refs/heads/{}".format(branch)))
            self.__repo(git_args)
        except:
            return False
        else:
            return True

    def cherries(self, src, dest):
        git_args = shlex.split(("{} {}".format(dest, src)))
        return (self.__repo.cherry(git_args))

    def short_hash(self, commit):
        git_args = shlex.split(("rev-parse --short {}".format(commit)))
        return self.__repo(git_args).stdout.strip()

    def bug_id(self, commit):
        BUG_ID = re.compile(' *Bug-Id: *')
        git_args = shlex.split(("-s --format='%b' {}".format(commit)))
        message = self.__repo.show(git_args).stdout
        bug_id = ((BUG_ID.split(message)[1]).split())[0].strip()
        validate_bug_id = re.compile(r"[0-9]{1,5}")
        if validate_bug_id.match(bug_id.split('-')[1]):
            return bug_id
        else:
            return None

    def commit_info(self, commit, dest):
        info = []
        # short hash
        git_args = shlex.split(("-s --format='%h' {}".format(commit)))
        info.append((self.__repo.show(git_args)).stdout)
        # bug id
        bug_id = self.bug_id(commit)
        bug_id = bug_id if bug_id else ' '
        info.append(bug_id)
        # commit date
        git_args = shlex.split(("-s --format='%cd' --date=local {}".format(commit)))
        info.append(self.__repo.show(git_args).stdout.strip())
        # author name
        git_args = shlex.split(("-s --format='%an' {}".format(commit)))
        info.append((self.__repo.show(git_args)).stdout.strip())
        # commit title
        git_args = shlex.split(("-s --format='%s' {}".format(commit)))
        info.append((self.__repo.show(git_args)).stdout.strip())

        # If Jira is to be used, fetch the dest branch status
        if self.__jira:
            if bug_id != ' ':
                issue = self.__jira.issue(bug_id)
                components = ', '.join([c.name for c in issue.fields.components])
                info.append(components)
                subtasks = issue.fields.subtasks
                resolution = ''
                for x in subtasks:
                    branch = (x.fields.summary).split('-')[2].strip()
                    if branch == dest:
                        x_issue = self.__jira.issue(x.key)
                        resolution = x_issue.fields.resolution.name if x_issue.fields.resolution else ''
                info.append(resolution)

        return info

    def commit_range(self, branch, start_sha, end_sha):
        git_args = shlex.split(("{} --format='%h' {}..{}".format(branch, start_sha, end_sha)))
        logs = (self.__repo.log(git_args)).splitlines()
        logs.append(start_sha)
        logs.reverse()
        return logs

    def commit_since(self, branch, since):
        git_args = shlex.split(("{} --since='{}'".format(branch, since)))
        logs = (self.__repo.log(git_args)).splitlines()
        logs.reverse()
        return logs

# End of GitHelper class

class NoTraceBackWithLineNumber(Exception):
    def __init__(self, msg):
        try:
            ln = sys.exc_info()[-1].tb_lineno
        except AttributeError:
            ln = inspect.currentframe().f_back.f_lineno
            self.args = "{0.__name__} (line {1}): {2}".format(type(self), ln, msg),
            sys.exit(self)

class ExampleError(NoTraceBackWithLineNumber):
    pass

if not sys.argv[1]:
    raise ExampleError('Needs an argument')

# Find an intersection of two lists
# common_list = sorted(set(larger_list) & set(smaller_list), key = larger_list.index)

def create_csv(fname):
    __title_row = 'col1, col2, col3'
    with open(fname, 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(__title_row)
        for i in range(10):
            row = 'val{i}_1, val{i}_2, val{i}_3'.format(i=i)
            writer.writerow(row)

def find_index(the_list, pattern):
    for i, s in enumerate(the_list):
        if pattern in s:
            return i
    return -1

# Search for a key value already existing in a list of dictonaries
def find_key_exists(the_dict_list, key_name, key_value):
    return next((item for item in the_dict_list if item[key_name] == key_value), None)

def file_insert_text_after(fname, text, pattern):
    search_pattern = re.compile(pattern)
    with open(fname, 'r+') as out_file:
        __found = False
        contents = out_file.readlines()
        for index, line in enumerate(contents):
            if search_pattern.search(line):
                contents.insert(index + 1, text)
                __found = True
        if not __found:
            contents.append(text)

        # Reset the file and write the contents back to it
        out_file.seek(0)
        out_file.writelines(contents)

def extract_archive(fname, dir):
    # If 'dir' does not exist, create it
    if not os.path.isdir(dir):
        os.makedirs(dir)
        dir_created = True
    # Extract the archive to 'dir'
    if tarfile.is_tarfile(fname):
        with tarfile.open(fname) as tarObj:
            tarObj.extractall(dir)
    elif zipfile.is_zipfile(fname):
        with zipfile.ZipFile(fname) as zipObj:
            zipObj.extractall(dir)
    else:
        print('{} is not an accepted archive file'.format(fname))
        # If we created the 'dir', delete it
        if dir_created:
            os.rmdir(dir)
        sys.exit(2)

def is_archive(self, fname):
    if tarfile.is_tarfile(fname):
        return True
    elif zipfile.is_zipfile(fname):
        return True
    return False

def is_binary(self, fname):
    ret = commands.getoutput('file -bi ' + fname)
    if ret.startswith('text'):
        return False
    return True

def make_dir(self, dir_path):
    if (os.path.isdir(dir_path)):
        os.system('rm -rf {dir}'.format(dir=dir_path))
    os.makedirs(dir_path)

def copy_dir(self, src_dir, dest_dir):
    self.make_dir(dest_dir)
    shutil.copytree(src_dir, dest_dir)

def list_intersection(list_1, list_2):
    return sorted(set(list_1) & set(list_2), key = list_1.index)

