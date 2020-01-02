#!/usr/bin/env python

import sys
import os
import sh, shlex
from jira import JIRA
import getpass

line = 'Bug-Id: JIRA-58'

username = getpass.getuser()
passwd = getpass.getpass(prompt='Jira Password: ', stream=None)

jira = JIRA('http://jira', basic_auth=(username, passwd))

issue_id = line.split(':')[1].strip()
print(issue_id)

issue = jira.issue(issue_id)
print(issue)
print(issue.fields.resolution)
print(issue.fields.components)
components = ", ".join([c.name for c in issue.fields.components])
print(components)

subtasks = issue.fields.subtasks
for x in subtasks:
    branch = (x.fields.summary).split('-')[2].strip()
    x_issue = jira.issue(x.key)
    print('{}: {}'.format(branch, x_issue.fields.resolution))

#for field_name in issue.raw['fields']:
#    print "Field:", field_name, "Value:", issue.raw['fields'][field_name]
