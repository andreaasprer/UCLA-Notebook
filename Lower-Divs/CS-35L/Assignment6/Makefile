# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

FILES = $(wildcard *.c) $(wildcard *.h)

randall: randall.c $(FILES)
	$(CC) $(CFLAGS) *.c -o $@

# Unit tests
check: randall
	@echo "Running test cases..."
	@echo "=========== TEST 1 ==========="
	@./randall 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)
	@echo "=========== TEST 2 ==========="
	@./randall -i rdrand 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)
	@echo "=========== TEST 3 ==========="
	@./randall -i mrand48_r 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)
	@echo "=========== TEST 4 ==========="
	@./randall -i /dev/random 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)
	@echo "=========== TEST 5 ==========="
	@./randall -i qwerty 20 2>&1 | (grep "Not valid file name" && echo "PASSED") || (echo "FAILED" && false)
	@echo "=========== TEST 6 ==========="
	@./randall -o stdio 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)	
	@echo "=========== TEST 7 ==========="
	@./randall -o asd 20 2>&1 | (grep "Invalid N" && echo "PASSED") || (echo "FAILED" && false)	
	
assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt $(FILES)
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

# Automatically formats all of your C code.
format:
	clang-format -i *.c *.h

# Helps find memory leaks.
valgrind: randall
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./randall 100

# Runs the Undefined Behavior (UBSAN) and Address (ASAN) sanitizers. GCC doesn’t support these on the SEASNet servers so we recommend using clang instead (a different C compiler).
sanitizers:
	clang -g3 -Wall -Wextra -mtune-native -mrdrnd -fsanitize=address \
		-fsanitize=undefined *.c -o randall

.PHONY: default clean assignment submission-tarball repository-tarball check format valgrind sanitizers

clean:
	rm -f *.o *.$(TAREXT) randall
