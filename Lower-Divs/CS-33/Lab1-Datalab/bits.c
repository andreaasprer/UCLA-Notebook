/*
 * CS:APP Data Lab
 *
 *
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
 /*
  * Instructions to Students:
  *
  * STEP 1: Read the following instructions carefully.
  */
 
 You will provide your solution to the Data Lab by
 editing the collection of functions in this source file.
 
 INTEGER CODING RULES:
  
   Replace the "return" statement in each function with one
   or more lines of C code that implements the function. Your code 
   must conform to the following style:
  
   int Funct(arg1, arg2, ...) {
       /* brief description of how your implementation works */
       int var1 = Expr1;
       ...
       int varM = ExprM;
 
       varJ = ExprJ;
       ...
       varN = ExprN;
       return ExprR;
   }
 
   Each "Expr" is an expression using ONLY the following:
   1. Integer constants 0 through 255 (0xFF), inclusive. You are
       not allowed to use big constants such as 0xffffffff.
   2. Function arguments and local variables (no global variables).
   3. Unary integer operations ! ~
   4. Binary integer operations & ^ | + << >>
     
   Some of the problems restrict the set of allowed operators even further.
   Each "Expr" may consist of multiple operators. You are not restricted to
   one operator per line.
 
   You are expressly forbidden to:
   1. Use any control constructs such as if, do, while, for, switch, etc.
   2. Define or use any macros.
   3. Define any additional functions in this file.
   4. Call any functions.
   5. Use any other operations, such as &&, ||, -, or ?:
   6. Use any form of casting.
   7. Use any data type other than int.  This implies that you
      cannot use arrays, structs, or unions.
 
  
   You may assume that your machine:
   1. Uses 2s complement, 32-bit representations of integers.
   2. Performs right shifts arithmetically.
   3. Has unpredictable behavior when shifting if the shift amount
      is less than 0 or greater than 31.
 
 
 EXAMPLES OF ACCEPTABLE CODING STYLE:
   /*
    * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
    */
   int pow2plus1(int x) {
      /* exploit ability of shifts to compute powers of 2 */
      return (1 << x) + 1;
   }
 
   /*
    * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
    */
   int pow2plus4(int x) {
      /* exploit ability of shifts to compute powers of 2 */
      int result = (1 << x);
      result += 4;
      return result;
   }
 
 FLOATING POINT CODING RULES
 
 For the problems that require you to implement floating-point operations,
 the coding rules are less strict.  You are allowed to use looping and
 conditional control.  You are allowed to use both ints and unsigneds.
 You can use arbitrary integer and unsigned constants. You can use any arithmetic,
 logical, or comparison operations on int or unsigned data.
 
 You are expressly forbidden to:
   1. Define or use any macros.
   2. Define any additional functions in this file.
   3. Call any functions.
   4. Use any form of casting.
   5. Use any data type other than int or unsigned.  This means that you
      cannot use arrays, structs, or unions.
   6. Use any floating point data types, operations, or constants.
 
 
 NOTES:
   1. Use the dlc (data lab checker) compiler (described in the handout) to 
      check the legality of your solutions.
   2. Each function has a maximum number of operations (integer, logical,
      or comparison) that you are allowed to use for your implementation
      of the function.  The max operator count is checked by dlc.
      Note that assignment ('=') is not counted; you may use as many of
      these as you want without penalty.
   3. Use the btest test harness to check your functions for correctness.
   4. Use the BDD checker to formally verify your functions
   5. The maximum number of ops for each function is given in the
      header comment for each function. If there are any inconsistencies 
      between the maximum ops in the writeup and in this file, consider
      this file the authoritative source.
 
 /*
  * STEP 2: Modify the following functions according the coding rules.
  * 
  *   IMPORTANT. TO AVOID GRADING SURPRISES:
  *   1. Use the dlc compiler to check that your solutions conform
  *      to the coding rules.
  *   2. Use the BDD checker to formally verify that your solutions produce 
  *      the correct answers.
  */

#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void)
{
    // Get Two's Complement of 1
    return (~1 + 1);
}
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
    // Apply DeMorgan's Law
    return ~(~x | ~y);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
    /* Use the property, UMax = 2TMax + 1, and if the result is correctly UMax then the input must be TMax.
       Add an additional check for when the input is -1 */
    int UMax = x + x + 1;
    int isNegOne = !(~x);
    return !(~UMax) & !isNegOne;
}
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x)
{
    /* Build up a 32 odd bit mask (same method used from oddBits function)
       and combine it to x to disregard the odd positions.
       If the result is equal to the binary representation of -1, then all even bits are 1 */
    int oddMask = 0xaa;
    int negativeOne = (~1 + 1);
    oddMask |= (oddMask << 8);
    oddMask |= (oddMask << 16);
    return !(negativeOne ^ (oddMask | x));
}
/*
 * fitsShort - return 1 if x can be represented as a
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int fitsShort(int x)
{
    /* Shift to the left by 16 bits and shift back, then check if same as input */
    int shifted = (x << 16) >> 16;
    return !(x ^ shifted);
}
/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void)
{
    /* Use 0xaa as a mask as its binary is 10101010. Then left shift and use | operator to build up to 32 bits. */
    int oddMask = 0xaa;
    oddMask |= (oddMask << 8);
    oddMask |= (oddMask << 16);
    return oddMask;
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y)
{
    /* Get the difference of x and y.
       CASE 1: if x and y have different signs, true if x is + and y is -.
       CASE 2: if x and y have same signs, check diffSign result
       CASE 3: x == y
    */
    int xSign = (x >> 31) & 1;
    int ySign = (y >> 31) & 1;
    int diff = x + (~y + 1);
    int diffSign = (diff >> 31) & 1;
    int isEqual = !(x ^ y);
    int isSignDiff = xSign ^ ySign;

    return (!isEqual) & (((!xSign) & ySign) | (!isSignDiff & !diffSign));
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n)
{
    /* Shift to the right arithmetically, then construct a mask that turns off any leading 1s.
       Add an extra check when no shift occurs (n = 0).
    */
    int aShift = x >> n;
    int mask = ~((1 << 31) >> (n + (~1 + 1)));
    int noShiftMask = ~((!n) + (~1 + 1));
    return (aShift & mask) | (noShiftMask & x);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
    /* Create a mask of either all 1s or 0s based on the logical value we get from x.
       Then create an if statement with the use of the | operator */
    int logicalVal = !!x;
    int mask = (logicalVal << 31) >> 31;
    return (mask & y) | (~mask & z);
}
/* Extra Credit (2 points each) */
/*
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int signMag2TwosComp(int x)
{
    /* Check sign of input. If positive, do nothing. If negative do 2s comp conversion with its magnitude.
       To determine sign, shift MSB all the way to the right */
    int sign = x >> 31;
    int magnitude = (~(1 << 31)) & x;
    return (~sign & x) | (sign & (~magnitude + 1));
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
    /*
       Shift MSB for x's original and twos complement value then combine.
       If x is 0, the original and twos complement will remain 0, otherwise will be UMAX.
       Adding one will negate the value.
    */
    int shift = x >> 31;
    int twosCompShift = (~x + 1) >> 31;
    int combined = shift | twosCompShift;
    return combined + 1;
}
