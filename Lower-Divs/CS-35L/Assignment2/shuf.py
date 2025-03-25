#!/usr/bin/env python3
import argparse, random, sys

def main():
    parser = argparse.ArgumentParser()

    # mutually exclusive group for shuf modes
    mutexGroup = parser.add_mutually_exclusive_group()
    mutexGroup.add_argument('-e', '--echo', action='store_true',
                            help='treat each ARG as an input line')
    mutexGroup.add_argument('-i', '--input-range', metavar='LO-HI',
                            help='treat each number LO through HI as an input line')

    parser.add_argument('-n', '--head-count', metavar='COUNT', type=int,
                        help='output at most COUNT lines')
    parser.add_argument('-r', '--repeat', action='store_true',
                        help='output lines can be repeated')

    # prevent error when unknown args passed
    args, unknownArgs= parser.parse_known_args()
                
    if args.echo:
        lines = unknownArgs

    elif args.input_range:
        lo, hi = map(int, args.input_range.split('-'))
        lines = list(map(str, range(lo, hi + 1)))
    
    else: 
        # read from stdin
        if len(unknownArgs) == 0 or unknownArgs[0] == "-":
            file = "/dev/stdin"
        elif len(unknownArgs) > 1:
            parser.error(f"extra argument {unknownArgs[1]}")
        else:
            file = unknownArgs[0]
        try:
            open(file)
        except FileNotFoundError:
            parser.error(f"{file}: No such file or directory")
        lines = open(file).readlines()

    headCount = args.head_count if args.head_count else len(lines)    
    if args.repeat:
       while headCount >= 1 or not args.head_count:
            print(random.choice(lines).strip())
            headCount -= 1
       
    else:
        if not args.head_count:
            headCount = len(lines)
        random.shuffle(lines)
        for line in lines[:headCount]:
            print(line.strip())
        
if __name__ == "__main__":
    main()