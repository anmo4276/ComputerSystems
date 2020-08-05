/* 
 * CS:APP Data Lab 
 * 
 * <Andres Montealegre (anmo4276)>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
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
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/*
 * Total: 25 pts
 */
/* 
 * 1-pt puzzles 
 */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /*
  * 1. Find the complement (~) of x and the complement of y
  * 2. Use bitwise OR
  * 3. Find the complement of the OR to find the AND of x and y
  * In Logic terms: ¬(¬x V ¬y) = x & y
  * Example:
  * 6: 0110, ~6: 1001
  * 5: 0101, ~5: 1010
  * ~6|~5: 1011
  * ~1011: 0100 (4)
  */
  return ~(~x|~y); 
    
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
  *  Recitation Hint: Remove all 1’s from ( x | y ) where 1 exists in both x and y
  *  How to get the positions where 1 exists in both x and y?
  * 1. Find where x OR y is true (this still includes and)
  * 2. Find where x AND y is true ( this doesn't include or)
  * 3. Negate x and y, so AND places are now 0s, and everything else is a 1.
  * 4. Since we now no where the AND places are, we can call orEquivalent (step 1) & negateAND (step 2-3) and find XOR
  */
  int orEquivalent = ~(~x&~y); //Find where x OR y is true (this still includes and)
  int negateAND= ~(x&y); //Find where x AND y is true, and negate it so AND places are now 0s, and everything else is a 1.
  return orEquivalent & negateAND; //orEquivalent & negateAND returns where x OR y is true, excluding AND (XOR)
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  /*
  * 1. Bang x to return appropriate value. If X is 0, returns 1. If X is anything else, returns 0.
  */
  return !x; //Returns Bang X. If X is 0, returns 1 (true). If X is anything else, returns 0 (false).
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /*
  * Recitation Hint: From 16th to 32nd digit should be same.
  * Right shift in C is default arithmetic right shift.
  * 1. Left shift 16, then right shift sixteen so 16th to 32nd bit are now 1's.
  * 2. Call XOR to original number and new number from step 1. If number didn't change, checkSame = 0. Else, checkSame = nonzero Number
  * 3. Return Bang checkSame so if it can be represented (0), it returns 1. If number can't be represented, returns 0.
  */
  int arithmeticShift = (x << 16 ) >> 16; //Left shift sixteen, the right shift 16. So 16th to 32nd bit are now 1's. 
  int checkSame = x^ arithmeticShift; //If the numbers are the same (can be represented), checkSame = 0. Else, checkSame = nonzero Number
  return !checkSame; //Return Bang checkSame so if it can be represented (0), it returns 1. If number can't be represented, returns 0.  
}

/* 
 * 2-pt puzzles
 */
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*
  * 1. Find the shift amount desired by doing 32-n. 
  * 2. Left shift by shiftAmount, then right shift by shiftAmount. So nth to 32nd bit are now 1's.
  * 3. Call XOR to original number and new number from step 1. If number didn't change, checkSame = 0. Else, checkSame = nonzero Number
  * 4. Return Bang checkSame so if it can be represented (0), it returns 1. If number can't be represented, returns 0.
  */
  int shiftAmount = 32 + (~n+1); //32-n
  int arithmeticShift = (x << shiftAmount ) >> shiftAmount; //Left shift by shiftAmount, then right shift by shiftAmount. So nth to 32nd bit are now 1's. 
  int checkSame = x^ arithmeticShift; //If the numbers are the same (can be represented), checkSame = 0. Else, checkSame = nonzero Number
  return !checkSame; //Return Bang checkSame so if it can be represented (0), it returns 1. If number can't be represented, returns 0.  
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*
  * 1. Find desired shift amount in bits. Multiply n by 8 to convert bytes to bits
  * 2. Right shift x by number of bits (found in step 1) so desired bit is at LSB
  * 3. Using mask (0xFF), return the byte at the end (LSB)
  */
  int shiftAmount= (n<<3); //Multiply n by 8 (2^3) to convert bytes to bits.
  int shiftToByte = (x>>shiftAmount); //Right shift x, so the desired byte is at LSB
  return shiftToByte&0xFF; //Using mask (0xFF), return the byte at the end (LSB)
}

/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  /*
  * 1. Check x XOR y. If they are equal, it is 0. Else: nonZero Number 
  * 2. Bang result. Equal: 1, NotEqual: 0.
  * 3. Bang again to fit question requirements. Equal:0. NotEqual:1
  * 4. Return result
  */
  return !!(x^y); //x^y would return 0 if they are equal and some number if they are not. The first bang, would change the 0 (equals) to a 1 and a number (not equals) to 0.
                  //The second bang would then change the 1 (now equals) to 0 and the 0 (not equal) to 1, matching the questions return statement.
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  /*
  * 1. Check if x is zero. If zero: 0000, If Number:0001
  * 2. Right shift by 31 to find x's sign (at MSB). If Positive: 0000, If Negative: -1
  * 3. Return zeroOrNot (step 1) OR posOrNeg(step 2). If zero: 0 | 0 = 0, If Pos: 0001 | 0 = 1, If Neg: 0001|1111 = -1
  */
    int zeroOrNot = !!x; //If zero: 0000, If Number:0001
    int posOrNeg = (x >> 31); //Move to MSB to check sign. If Positive: 0000, If Negative: -1.
    return zeroOrNot | posOrNeg; //If zero: 0 | 0 = 0, If Pos: 0001 | 0 = 1, If Neg: 0001|1111 = -1
}
/* 
 * 3-pt puzzles 
 */
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) 
{
    /*
    * 1.Find the difference of y - x
    * 2.Find the sign of the difference (MSB). Positive = 0. Negative =1
    * 3.Create a mask of 0x80000000
    * 4. Find the MSB (sign of x and y using mask
    * 5.Check to see if x and y signs are different. If x and y have same sign = 0. Else = number
    * 6. Right shift sign, AND with 1. If x and y have same sign = 0. Else = 1
    * 7.If x and y have different Signs, and x is negative, returns 1. OR if y-x is positive and if the signs are the same (x and y same signs), returns 1. Else returns 0
    */
   int difference = y + (~x+1); //Find the difference of y - x
   int differenceSign = difference >> 31 & 1; // Find the sign of the difference (MSB). Positive = 0. Negative =1
   int mask = 1 << 31; //Create a mask of 0x80000000
   int xMask = mask & x; //Find the MSB of X using mask
   int yMask = mask & y; //Find the MSB of y using mask
   int sign = xMask ^ yMask; //Check to see if signs are different. If x and y have same sign = 0. Else = number.
   sign = (sign >> 31) & 1; //Right shift sign, AND with 1. If x and y have same sign = 0. Else = 1
   return (sign & (xMask>>31)) | (!differenceSign & !sign); 
    //If x and y have different Signs, and x is negative, returns 1. OR if y-x is positive and if the signs are the same (x and y same signs), returns 1. Else returns 0
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*
  * 1. Create a mask. Left shift 1 by 31 (0x80000000). Then right shift by n. Left shift once again, to correct shift amount. 
  * 2. Bitwise complemenet the mask (~). This way, MSB to number of shifted elements, are now zeros and everything behind are 1s.
  * 3. Right shift x by n, and use the mask. This way, x will be shifted to the right and the mask will make sure the shift is logical. 
  * 4. Return the result
  */
  int mask = ((1 << 31) >> n)<<1; //If 32, could overflow. So shift left 31. Extra one at end corrects shift amount
  mask = ~mask; //Negate mask so that 11110000 is now 00001111 
  return (x>>n)&mask; //Right shift x by n, and use the mask. This way, x will be shifted to the right and the mask will make sure the shift is logical. 
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  /*
  * 1. Create a mask. Left shift 1 by 31 (0x80000000). Then right shift by n. Left shift once again, to correct shift amount.
  * 2. Create second mask of -1
  * 3. Store the leftside of x using the first mask (step 1).
  * 4. Right shift the leftSide mask, so leftSide now starts at LSB
  * 5. Left shift the second mask (-1) by n and find its complement. This creates a mask that has leading 0s and ends with 1s (same size as leftSide)
  * 6. Find leftSide (step 4) AND mask (step5). This shifts x's left side to the LSB and makes sure it has leading 0s. (Logical Shift of LEFTSIDE)
  * 7. Left Shift x by n
  * 8. Find x (now formatted 0x76543210) OR leftSide (0x000000008)= 0x76543218
  * 9. Return result
  */
  int leftSide = ((1 << 31) >> n)<<1; //If 32, could overflow. So shift left 31. Extra one at end corrects shift amount
  int mask = ~(0x0); //Create mask of -1.
  leftSide = leftSide & x; //Store leftside of mask
  leftSide = leftSide >> (33+~n); //Right shift the leftSide mask, so leftSide now starts at LSB
  mask = ~(mask<<n); //-1 << n
  leftSide = leftSide & mask;//Logical Shift of LEFTSIDE. Makes sure LeftSide no has leading 0s and ends with x's original left side
  x= x <<n; //Left shift x by n
  return x|leftSide; //Return x (now formatted 0x76543210) OR leftSide (0x000000008)= 0x76543218
}
/*
 * 4-pt puzzles
 */
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value (Tmax), and when negative overflow occurs,
 *          it returns minimum negative value (Tmin)
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000 if over flow
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  /*
  * Recitation Hint: When you add two positive numbers and get a negative number as a result, this is positive overflow.
  * When you add two negative numbers and get a positive number as a result, this is negative overflow.
  * 1. Check the signs of y and x
  * 2. Find the sum of x+y
  * 3. Check the sign of the sum
  * 4. Using XOR, &, and the signs of sum, X, and Y, see if the sum overflows. Overflows if two same sign numbers' sum results in a different sign (Overflow = -1. No overflow = 0)
  * 5. Right Shift the sum if there is overflow. If overflow is positive, sum is right shifted 31 making it -1. If overflow is negative, sum is right shifted making it 0
  * 6. Left shift checkOverflow so checkOverflow = 0x80000000 if overflow, and 0 if no overflow
  * 7. Add the checkOverflow, calculated above, to the sum. Sum (neg) = 0 + 0x80000000 = 0x80000000, Sum (pos) = -1 + 0x80000000 = 0x7fffffff, Sum (no Overflow) = sum + 0 = sum
  * 8. Return sum
  */
  int signX = x>>31; //Find sign of X
  int signY= y>>31; //Find Sign of y
  int sum = x+y; //Find sum
  int sumSign = sum>>31; //Find the sign of sum
  int checkOverflow = (sumSign^signX) & (sumSign ^signY); //checkOverflow = -1 if overflows, 0 if no overflow
  sum = (sum>>(checkOverflow&31)); //Sum is 0 if negative overflow, -1 if positive, and sum if no overflow
  checkOverflow = checkOverflow <<31; // checkOverflow = 0x80000000 if overflow, and 0 if no overflow
  sum = sum + checkOverflow; //Sum (neg) = 0 + 0x80000000, Sum (pos) = -1 + 0x80000000, Sum (no Overflow) = sum + 0
  return sum;
}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  /*
  * 
  */
  return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
