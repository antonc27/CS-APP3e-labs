/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
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
  int shift = n << 3;
  return (x >> shift) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int saved_bit = 1 & (x >> 31);
  int y = x & ~(1 << 31);
  int negative_n = ~n + 1;
  int restored = saved_bit << (31 + negative_n);
  return (y >> n) | restored;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int m1 = 0x55;
  int m2 = 0x33;
  int m4 = 0x0f;
  int c = 0;
  m1 = m1 + (m1 << 8);
  m1 = m1 + (m1 << 16);
  m2 = m2 + (m2 << 8);
  m2 = m2 + (m2 << 16);
  m4 = m4 + (m4 << 8);
  m4 = m4 + (m4 << 16);
  c = (x >> 1) & m1;
  x += ~c + 1;             //put count of each 2 bits into those 2 bits
  x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
  x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
  x += x >>  8;  //put count of each 16 bits into their lowest 8 bits
  x += x >> 16;  //put count of each 32 bits into their lowest 8 bits
  return x & 0x7f;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int saved_sign_bit = x >> 31;
  int tmax = ~(1 << 31);
  int neg_half_tmax = (0xc0 << 24) + 1;
  x += tmax;
  x >>= 1;
  x += neg_half_tmax;
  return ~((x >> 31) | saved_sign_bit) & 0x1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
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
  int mask = (((1 << (n + ~0)) + ~0) << 1) + 1; // (1 << n) - 1;
  int reduced = x & mask;
  int shift = (33 + ~n);
  int extended = (reduced << shift) >> shift;
  int diff = x ^ extended;
  return !diff;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int mask = x >> 31; // just stretching sign bit
  int bias = (1 << n) + ~0;
  x += mask & bias;
  return x >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int negative_bit;
  x = (x >> 1) + (x & 0x1);
  negative_bit = ((x + ~0) >> 31) & 0x1;
  return negative_bit ^ 0x1;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int a = (x >> 31) & 0x1;
  int b = (y >> 31) & 0x1;
  int c = (b ^ a) & 0x1;
  int diff = (b + ~a + 1) >> 1;
  int d = diff & 0x1;
  int y_pos_x_neg = c & d;
  int f = ~diff & 0x1;
  int not_y_neg_x_pos = ~(c & f) & 0x1;
  x += ~y;
  return (((x >> 31) & 0x1) | y_pos_x_neg) & not_y_neg_x_pos;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int r = 0;
  int m1 = ((0xff << 8) + 0xff) << 16; // 0xffff0000
  int m2 = 0xff << 8; // 0xff00
  int m3 = 0xf0;
  int m4 = 0xc;
  int m5 = 0x2;
  int mask = (!!(x & m1)) << 4;
  int shift = 16 & mask;
  x >>= shift;
  r |= shift;
  mask = (!!(x & m2)) << 3;
  shift = 8 & mask;
  x >>= shift;
  r |= shift;
  mask = (!!(x & m3)) << 2;
  shift = 4 & mask;
  x >>= shift;
  r |= shift;
  mask = (!!(x & m4)) << 1;
  shift = 2 & mask;
  x >>= shift;
  r |= shift;
  mask = !!(x & m5);
  shift = mask;
  x >>= shift;
  r |= shift;
  return r;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  int msb = (uf >> 31) & 0x1;
  if (uf == 0x7fc00000 || uf == 0xffc00000) {
    return uf;
  }
  msb = !msb;
  return (msb << 31) + ((uf << 1) >> 1);
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
  int mask;
  int mask2;
  int mantissa;
  int roundoff;
  int diff;
  int msb = x & (1 << 31);
  int count = 0;
  unsigned v;
  if (x == 0) {
    return 0;
  }
  if (msb) {
    x = -x;
  }
  v = x;
  while (v) {
    v >>= 1;
    if (v) {
      count += 1;
    }
  }
  mask = (1 << 23) - 1;
  if (count <= 23) {
    diff = 23 - count;
    mask >>= diff;
    mantissa = (x & mask) << diff;
  } else {
    diff = count - 23;
    mantissa = (x >> diff) & mask;
    
    mask2 = 1 << diff;
    roundoff = x & (mask2 - 1);
    mask2 >>= 1;
    if (roundoff > mask2) {
      mantissa += 1;
    } else if ((roundoff == mask2) && (mantissa & 0x1)) {
      mantissa += 1;
    }
  }
  return msb + ((count + 127) << 23) + mantissa;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int msb = uf & (1 << 31);
  int masked = uf & 0x7f800000;
  if (uf == 0 || uf == 0x80000000) {
    return uf;
  }
  if (masked == 0x7f800000) {
    return uf;
  } else if (!masked) {
    uf <<= 1;
    uf = msb + (uf & 0x7fffffff);
  } else {
    uf += (1 << 23);
  }
  return uf;
}
