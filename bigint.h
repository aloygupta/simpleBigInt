/****************************************************************************
 * simpleBigInt Library
 * 
 * Copyright (c) 2014,
 * Aloy Gupta <aloygupta1993@gmail.com>
 * All rights reserved.
 *
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of 'simpleBigInt' nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/

#ifndef _BIGINT_H_
#define _BIGINT_H_

#include<stdlib.h>

#define BISIZE 3000

struct bigint{
	char sign;					/* sign of the biginteger */
	char value[BISIZE+1];		/* to store the value of the bigintger of */ 
								/* BISIZE number of decimal digits */    
};

/* a derived datatype for biginteger */

typedef struct bigint bigint;

/* Reads the sign and value of the biginteger in the form of
 * array of charcaters (decimal digits).In case of positive biginteger,giving
 * the '+' sign as input is optional. The function also adds '0's 
 * to the rest of the char array. (It returns bigint *   )
 */

bigint * readBigInt(void);


/* Converts the string literal passed as argument into its 
 * biginteger representation. If length of argument is BISIZE+1 
 * it should include sign as first character, else size should be
 * <=BISIZE (and positive sign is implicitly assigned
 */

bigint *assignBigInt(char *n);



/* Prints the biginteger passed as argument.Prints the sign only if its negative.
 * Returns EOF upon error
 */
 
int printBigInt(bigint *n);



/*  Print the biginteger passed as argument followed by a newline character.
 *	It returns the value returned by printBigInt(bigint *n)	 
 */

int printlnBigInt(bigint *n);



/*  Converts an integer to its biginteger representation.
 *	Returns a pointer to the newly allocated bigint
 */
 
bigint * toBigInt(int x);


/* Returns a pointer to a biginteger which represents the absolute value
 *  of another biginteger passed as argument
 */

bigint * absBigInt(bigint *n);



/* Performs addition of two bigintegers passed as argument.
 * Returns (bigint *)
 */

bigint * addBigInt(bigint * x, bigint *y);



/* Perform subtraction of two bigintegers m and n passed as arguments
 * Returns a pointer to the resultant biginteger
 */	

bigint * subBigInt(bigint *m,bigint *n);


/* Multiplies two bigintegers passed as argument and returns a pointer
 * to the resultant bigint.The multiplication is carried out using 
 * long multiplication method.
 */
 

bigint * multiplyBigInt(bigint *m,bigint *n);


/* Performs division of x by y using long division method and
 * returns the quotient as argument
 */

bigint * divideBigInt(bigint *x,bigint *y);


/* Returns a pointer to the remainder when x is divided by y.
 * Returns NULL when y is zero.
 */
			
bigint * remBigInt(bigint *x, bigint *y);



/* Comapres two biginteger variables m and n and returns an integer
 * indicating the comparison.
 * m>n then returns 1
 * m==n then returns 0
 * m<n then returns -1
 */

int compareToBigInt(bigint *m,bigint *n);




/* Returns the number of digits in the biginteger variable passed
 * as argument.Maximum returned value can be BISIZE.
 * When value passed is zero, returns 1 , as 1 zero digit
 * is atleast required to represent the number zero
 */

int lengthBigInt(bigint *n);


/* Returns a pointer to the resultant bigint m ^n ,
 * where m is a biginteger and n is an integer
 */

bigint *powBigInt(bigint *m,int n);



/* Returns a new bigint which is a copy of the one passed 
 * as argument
 */

bigint *copyBigInt(bigint *n);



/* Reverses a bigint passed as argument in-place */

void reverseBigInt(bigint *n);



/* Appends a char(digit) to a bigint passed as argument.
 * Thus if n is value 12345 and '6' is passed then the bigint
 * is shifted one place left and '6' is appended.
 * The original bigint is changed in-place
 */
 
int appendDigitBigInt(bigint *n,char c);


/* Returns a pointer to the bigint representing Greatest Common Divisor (gcd)
 * of two bigintegrs passed as argument.
 */		

bigint * gcdBigInt(bigint *m , bigint *n);



/* Returns a pointer to the bigint representing Least Common Multiple (lcm)
 * of two bigintegers passed as argument.
 */		

bigint * lcmBigInt(bigint *m,bigint *n);




#endif
