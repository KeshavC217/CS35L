#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
import argparse
import string
class shuf:
    def __init__(self, filename):
        self.lines = filename.file.readlines()

    def chooseline(self, lim):
        myList = list(self.lines)
        random.shuffle(myList)
        myList = map(lambda s: s.strip(), myList)
        i=0
        lim1=int(lim)
        if lim1 < -1:
            sys.stderr.write("shuf: invalid line count '")
            sys.stderr.write(lim)
            sys.stderr.write("'\n")
        else:
            for elem in myList:
                if i == lim1:
                    break
                print (elem)
                i=i+1

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""
   
    parser = argparse.ArgumentParser(description='Shuffle based on param')
    parser.add_argument('-i', nargs='?', action='store', dest='s_val')
    parser.add_argument('file', nargs='?', type=argparse.FileType('r'))
    parser.add_argument('-n', nargs='?', action='store', dest='n_val', default=-1)
    args = parser.parse_args()
    options = parser.parse_args()
    lim =  args.n_val
    if args.file:
        generator = shuf(args)
        generator.chooseline(lim)
    if args.s_val:
        a = args.s_val
        ml2=a.split('-')
        int1=int(ml2[0])
        int2=int(ml2[1])
        if int1 > int2:
            sys.stderr.write("shuf: invalid input range '")
            sys.stderr.write(a)
            sys.stderr.write("'\n")
        elif int(lim) < -1:
            sys.stderr.write("shuf: invalid line count '")
            sys.stderr.write(args.nval)
            sys.stderr.write("'\n")
        else:
            ml2=list(range(int1, int2+1))
            random.shuffle(ml2)
            i=0
            lim2=int(lim)
            for elem in ml2:
                if i == (lim2):
                    break
                print (elem)
                i=i+1
    """try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) != 1:
        parser.error("wrong number of operands")
    input_file = args[0]

    try:
        generator = randline(input_file)
        for index in range(numlines):
            sys.stdout.write(generator.chooseline())
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))"""

if __name__ == "__main__":
    main()
