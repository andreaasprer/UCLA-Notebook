#!/usr/bin/env python3
import argparse
import random
import sys

# Setup argument parser
parser = argparse.ArgumentParser(description="A number guessing game")
parser.add_argument("-r", "--range", type=str, required=True, help="Range in the format n-m (inclusive)")
parser.add_argument("-t", "--tries", type=int, default=1, help="Number of tries (default is 1)")

# Parse the command-line arguments
args = parser.parse_args()

# Extract and validate the range argument
try:
    range_values = args.range.split("-")
    if len(range_values) != 2:
        raise ValueError("Invalid format for range. Use n-m.")
    start, end = int(range_values[0]), int(range_values[1])
    
    if start > end:
        sys.stderr.write("Exited with error 1: you cannot have a negative range :(\n")
        sys.exit(1)
except ValueError as e:
    sys.stderr.write(f"Exited with error 1: {e}\n")
    sys.exit(1)

# Generate the random number to guess
number_to_guess = random.randint(start, end)

# Set the number of tries
tries = args.tries

# Main game loop
while tries > 0:
    try:
        guess = int(input("> "))
    except ValueError:
        sys.stdout.write("Invalid input, please enter a number.\n")
        continue

    if guess == number_to_guess:
        sys.stdout.write("Yay you win :)\n")
        break
    else:
        tries -= 1
        if tries > 0:
            sys.stdout.write("Wrong! Try again.\n")
        else:
            sys.stdout.write("Wrong you fail :(\n")