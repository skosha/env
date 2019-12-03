#! /usr/bin/env python

import re
import time
import os, sys
import argparse, textwrap
import sh, shlex

class HelperFunctions:

    def set_verbose(self, verbose):
        self.__verbose = verbose
    # End of set_verbose

    def print_verbose(self, level, str):
        if level <= self.__verbose:
            print(str)
    # End of print_verbose

    def is_line_added(self, line):
        add = re.compile(r"\+[^\+].*")
        if add.match(line):
            comment = re.compile(r"\+\s{0,2}[\\*]")
            if comment.match(line):
                return False
            return True
    # End of is_line_added

    def is_line_deleted(self, line):
        rem = re.compile(r"\-[^\-].*")
        if rem.match(line):
            comment = re.compile(r"\-\s{0,2}[\\*]")
            if comment.match(line):
                return False
            return True
    # End of is_line_deleted

    def is_line_hunk_start(self, line):
        hunk = re.compile(r"@{2}")
        if hunk.match(line):
            return True
        return False
    # End of is_line_hunk_start

    def parse_hunk_line(self, line):
        org_start_i = 0
        new_start_i = 0
        hunk_list = line.split(' ')
        org_start_i = int((hunk_list[1].split(',')[0])[1:])
        new_start_i = int((hunk_list[2].split(',')[0])[1:])
        return org_start_i, new_start_i
    # End of parse_hunk_line

    def is_file_start(self, line):
        file_start = re.compile(r"[\-]{3}")
        if file_start.match(line):
            return True
        return False
    # End of is_file_start

    def is_file_test(self, fname):
        tests_re = re.compile(r"tests")
        if tests_re.search(fname):
            return True
        return False
    # End of is_file_tests

    def get_file_name(self, line, next_line):
        dev_null = re.compile("/dev/null")
        if dev_null.search(line):
            return (next_line.split())[1][2:]
        else:
            return (line.split())[1][2:]
    # End of get_file_name

# End of HelperFunctions

class DiffParser:
    __script            = os.path.basename(__file__)
    __version_str       = '1.0'
    __description       = 'Get code stats for a branch (non-comment code lines only)'
    __changelist_str    = '''
Changelist:
* Version 1.1 =>
    + Add check for branch to be 11ax_dev
* Version 1.0 =>
    + Add filters to filter the patch on
    + Refactor the patch dump
    + Filter out tests files and add an option to add them (--include-tests)
* Version 0.4 =>
    + Move from getopt to argparse in preparation for filters as arguments
* Version 0.3 =>
    + Print last commit at the end
* Version 0.2 =>
    + Modularize the code
    + Add functionality to dump all the changed lines to a text file
* Version 0.1 =>
    + Initial version
    + Only gives number of non-comment lines added to MLME

'''
    __epilog            = '''
Examples:
    - Stats of lines added to src
        >> {script}
    - Stats of lines added to src and dump the changed lines
      to a patch file
        >> {script} -d
        >> {script} --dump
    - Stats of lines added to src/module_1
        >> {script} -f "src/module_1"
    - Stats of lines added to src/module_1 src/module_2
        >> {script} -f "src/module_1 src/module_2"
    - Stats of lines added to src with tests files included
        >> {script} --include-tests
    - Verbose output
        >> {script} -v
    - More verbose output
        >> {script} -vv
'''.format(script=__script)

    __dump = False                  # Dump the patch data into a file
    __parsed_db = []                # Parsed stats
    __filter_string = 'src'         # By default we filter all of src files


    __repo_dir = "/home/kshah/repos/my_project"                             # Repo's root directory
    __rel_path = ''                                                         # cwd relative to repo_dir

    __authors = ['Kosha', 'neha']                                           # Author's

    def __init__(self):
        # Init sh bake for git on repo_dir
        self.__git = sh.git.bake(_tty_out=False, _cwd=self.__repo_dir)

        # Get relative path from repo_dir, used for filters later on
        cwd = os.getcwd()
        self.__rel_path = ''
        self.__rel_path = cwd[len(self.__repo_dir) + 1:]
        if not self.__rel_path:
            self.__rel_path = '.'
        self.__filter_string = os.path.join(self.__rel_path, self.__filter_string)

        # Create the argument parser
        self.__parser = argparse.ArgumentParser(
                description='%(prog)s v' + self.__version_str + '\n' + self.__description,
                formatter_class=argparse.RawTextHelpFormatter,
                epilog=textwrap.dedent(self.__epilog))
        self.__parser.add_argument('-d', '--dump', dest='dump', help="dump changed lines to a patch file", action="store_true")
        self.__parser.add_argument('-f', '--filter',  dest='filter', help='filter based on modules, provide a string with filters separated by ","', default='')
        self.__parser.add_argument('--include-tests', dest='use_tests', help='include tests files as well', action="store_true")
        self.__parser.add_argument('-v', '--verbose', help='increase output verbosity', action="count", default=0)
        self.__parser.add_argument('-V', '--version', action='version',
                version='%(prog)s v' + self.__version_str + textwrap.dedent(self.__changelist_str))
    # End of __init__

    def parse_args(self):
        # Parse the args
        args = self.__parser.parse_args()

        # Make sure we are on correct branch
        git_args = shlex.split(("rev-parse --abbrev-ref HEAD"))
        if (self.__git(git_args) != 'dev'):
            print('ERROR: Not on dev branch')
            sys.exit(2)

        fn.set_verbose(args.verbose)
        self.__dump = args.dump
        # Create the patch filename
        if self.__dump:
            self.__patch_fname = 'patch' + time.strftime("_%d%m%y_%H%M%S")
            open(self.__patch_fname, 'a').close()
        self.__filter_tests = not args.use_tests
        fn.print_verbose(1, '{}including tests'.format('not ' if self.__filter_tests else ''))
        if args.filter:
            self.__parse_filter(args.filter)    # Parse the filter and store the filter string
        fn.print_verbose(1, 'Using filter {}'.format(self.__filter_string))
    # End of parse_args

    def __validate_filters(self, filters):
        for filter in filters:
            if not os.path.isdir(os.path.join(self.__repo_dir, filter)):
                fn.print_verbose(0, 'invalid filter provided ({}). Filter should be relative to repo directory'.format(filter))
                sys.exit(2)
    # End of __validate_filter

    def __parse_filter(self, args_filter):
        filters = [x.strip() for x in args_filter.split(',')]
        filters = [os.path.join(self.__rel_path, f) for f in filters]
        self.__validate_filters(filters)
        self.__filter_string = " ".join(filters)
    # End of __parse_filter

    # Check if a file already exists in parsed stats db
    def __is_file_present(self, fname):
        return next((patch for patch in self.__parsed_db if patch["name"] == fname), None)
    # End of __is_file_present

    # Add a file's stats to the parsed stats db
    def __update_file_info(self, fname, adds, dels):
        new_patch = {} if not self.__is_file_present(fname) else self.__is_file_present(fname)
        if not new_patch:
            new_patch["name"] = fname
            new_patch["num_adds"] = adds
            new_patch["num_dels"] = dels
            self.__parsed_db.append(new_patch)
        else:
            new_patch["num_adds"] = new_patch.get("num_adds") + adds
            new_patch["num_dels"] = new_patch.get("num_dels") + dels
    # End of update_file_info

    def get_commits(self):
        commits = []
        for name in self.__authors:
            git_args = shlex.split(("--author={author} -w -G'(^[^\*# /])|(^#\w)|(^\s+[^\*#/])' --pretty='%h' {filter}".format(author=name, filter=self.__filter_string)))
            fn.print_verbose(1, 'Run "git log {}"'.format(git_args))
            logs = (self.__git.log(git_args)).splitlines()
            commits.extend(logs)
        return commits
    # End of get_commits

    def get_commit_time(self, commit):
        git_args = shlex.split('-s --format="%ct" {}'.format(commit))
        c_time = int(self.__git.show(git_args))
        fn.print_verbose(2, 'Run "git show {}"'.format(git_args))
        return c_time
    # End of get_commit_time

    def get_commit_diff(self, commit):
        git_args = shlex.split(("-w --ignore-blank-lines --pretty="" {hash} {filter}".format(hash=commit, filter=self.__filter_string)))
        diff_text = self.__git.show(git_args)
        fn.print_verbose(2, 'Run "git show {}"'.format(git_args))
        return diff_text
    # End of get_commit_diff

    def dump_patch(self, fname, fbuffer):
        if not self.__dump:
            return
        __found = False
        fname_str = '***** {}'.format(fname)
        with open(self.__patch_fname, 'r+') as out_file:
            contents = out_file.readlines()
            # Look for the file already being written about in the patch file
            for index, line in enumerate(contents):
                if fname_str in line:
                    # If the file already exists in the patch file, insert the
                    # new buffer at start of this files patch
                    contents.insert(index + 1, fbuffer)
                    __found = True
                    break
            if not __found:
                # A new file, so create an entry for it and add the patch
                contents.append(fname_str)
                contents.append('\n')
                contents.append(fbuffer)
                contents.append('\n')

            # Reset the file and write the contents back to it
            out_file.seek(0)
            out_file.writelines(contents)
    # End of dump_patch

    def parse_diff(self, diff_text):
        __file_name = ''
        __file_buffer = ''
        __add_line_no = __del_line_no = __total_adds = __total_dels = 0
        __first_time = True
        __skip_file = False
        __a_start = __b_start = 0
        for line in diff_text:
            if fn.is_file_start(line):
                line_2 = next(diff_text)
                if not (__first_time and __skip_file) and __file_name: # Update this file's info to parsed db
                    self.__update_file_info(__file_name, __add_line_no, __del_line_no)
                    self.dump_patch(__file_name, __file_buffer) # Dump the patch buffer into patch file
                    __total_adds += __add_line_no
                    __total_dels += __del_line_no
                else:
                    __first_time = False
                # Get the filename and check if its tests, skip if needed
                __file_name = fn.get_file_name(line, line_2)
                if self.__filter_tests and fn.is_file_tests(__file_name):
                    fn.print_verbose(2, 'Skipping tests file {}'.format(__file_name))
                    __skip_file = True
                    __file_name = ''
                else:
                    __skip_file = False
                # Reset file stats
                __add_line_no = 0
                __del_line_no = 0
                __file_buffer = ''
            elif fn.is_line_hunk_start(line):
                # Get the hunk's start line numbers for original (a) and new (b) files
                __a_start, __b_start = fn.parse_hunk_line(line)
            elif fn.is_line_added(line):    # Lines that are added (b)
                __b_start += 1
                if not __skip_file:         # tests files may be skipped
                    __add_line_no += 1
                    __file_buffer += '{} {}'.format(__b_start, line)
            elif fn.is_line_deleted(line):  # Line that are deleted (a)
                __a_start += 1
                if not __skip_file:         # tests files may be skipped
                    __del_line_no += 1
                    __file_buffer += '{} {}'.format(__a_start, line)
            else:   # Track the line numbers
                __a_start += 1
                __b_start += 1

        return __total_adds, __total_dels

    def print_message(self):
        if self.__dump:
            fn.print_verbose(0, "dump patch created {}".format(self.__patch_fname))
# End of class DiffParser

# Main Program
if __name__ == "__main__":
    fn = HelperFunctions()
    parser = DiffParser()

    parser.parse_args()

    # Get the commits to add
    commits = parser.get_commits()

    # Get the stats of the commits
    total_adds = 0
    total_dels = 0
    last_commit = ''
    last_commit_time = 0
    fn.print_verbose(1, '')
    for commit in commits:
        # Get commit time
        c_time = parser.get_commit_time(commit)
        if c_time > last_commit_time:
            last_commit_time = c_time
            last_commit = commit
        # Get this commit diff
        uni_diff_text = parser.get_commit_diff(commit)
        # Parse the diff and store the stats
        commit_total_adds, commit_total_dels = parser.parse_diff(uni_diff_text)
        total_adds += commit_total_adds
        total_dels += commit_total_dels
        fn.print_verbose(1, 'commit: {} adds: {} dels: {}'.format(commit, commit_total_adds, commit_total_dels))
    fn.print_verbose(1, '')

    parser.print_message()
    fn.print_verbose(0, 'last commit: {} committed  {}'.format(last_commit, time.ctime(last_commit_time)))
    fn.print_verbose(0, "effective lines added {}".format(total_adds - total_dels))
