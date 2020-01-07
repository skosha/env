#!/usr/bin/env python

import sys
import re

input_hex = re.findall('..', sys.argv[1])
input = [int(x, 16) for x in input_hex]

string = "".join([chr(ascii) for ascii in input])

print string
