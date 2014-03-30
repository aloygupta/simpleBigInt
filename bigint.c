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



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bigint.h"


/* Reads the sign and value of the biginteger in the form of
 * array of charcaters (decimal digits).In case of positive biginteger,giving
 * the '+' sign as input is optional. The function also adds '0's 
 * to the rest of the char array. (It returns bigint *   )
 */

bigint * readBigInt(void)
{
	int index;   /* array index variable */
	int j;		/* another index */
	char in;     /* to store input character */
	int zeroFlag=1;		/* flag to indicate whether string literal
						 represents zero or not*/
	/*allocate memory for a biginteger */
	
	/*allocate memory for a biginteger */
	
	bigint *n=(bigint *)malloc(sizeof(bigint));
	
	/* assign last variable of array of characters to nul */
	
	n->value[BISIZE]='\0';
	
	index=BISIZE-1;
	
	/* read sign of biginteger */
	do
	{
	in=getchar();
	if(in=='-')
	n->sign='-';
	else if(in=='+')
	n->sign='+';
	else if(in!=' ' && in!='\t' && in!='\n')
	{
		n->sign='+';
		n->value[index--]=in;			/* keep reading until */ 
										/* non-whitespace char is found*/
		
		if((in-'0')>0)
		zeroFlag=0;								
	}
		
	}while(in==' ' || in=='\t' || in=='\n');	
	
	
	while((in=fgetc(stdin))!='\n' && in!=' ' && in!='\t')
	{
		if(in!=EOF)
		{
			if(index>=0)
			{
			n->value[index--]=in; /* read values till newline charcter */									
									/* or EOF or i<0 */
			if((in-'0')>0)			
			zeroFlag=0;
			
			}
			else				
			break;
		}
		else
		{
			free(n);	/* if in==EOF then free variable and return NULL */
			return NULL;
		}
	}
	if(index==BISIZE-1)
	{
		free(n);		/*if no number is entered then */
		return NULL;	/* free variable and return NULL */
	}
	
	++index; /* get index back to position*/
	j=BISIZE-1;
	
	/* reverse the array of string digits */
	
	while(index<j)
	{
		in=n->value[index];		/* 'in' serving as temporary variable here */
		n->value[index]=n->value[j];
		n->value[j]=in;
		++index;
		--j;
	}
	index=index-(BISIZE-1-j);	/* adjust index to the required position */
	
	/* fill the rest of the character array with zeroes */
	
	for(j=0;j<index;j++)
	{
		n->value[j]='0';
	}
	
	if(zeroFlag)
	n->sign='+';
	
	return n;
}


/* Converts the string literal passed as argument into its 
 * biginteger representation. If length of argument is BISIZE+1 
 * it should include sign as first character, else size should be
 * <=BISIZE (and positive sign is implicitly assigned
 */

bigint *assignBigInt(char *n)
{
	int len=strlen(n);	/* length of string literal passed */
	int index; /* array index variable */
	int zeroFlag=1;		/* flag to indicate whether string literal
						 represents zero or not*/
	/*allocate memory for a biginteger */
	
	bigint *temp;
	
		
	if(len>(BISIZE+1))
	return NULL;
	
	if(len==(BISIZE+1))
	{
		if(n[0]!='+' && n[0]!='-')
		return NULL;
		
	}
	temp=(bigint *)malloc(sizeof(bigint));
	
	if(n[0]=='+' || n[0]=='-')
	temp->sign=n[0];
	else
	temp->sign='+';
	
		
	/* assign last variable of array of characters to nul */
	
	temp->value[BISIZE]='\0';
	
	index=BISIZE-1;
	
	len-=1;
	
	while(len>=1)
	{
		if((n[len]-'0')>0)
		zeroFlag=0;
		
		temp->value[index--]=n[len--];
		if(index<0)
		break;
	}
	
		
	if(n[len]!='+' && n[len]!='-')
	temp->value[index--]=n[len--];
	
	while(index>=0)
	temp->value[index--]='0';
	
	if(zeroFlag)
	temp->sign='+';	/* mathematically, zero is always given +ve sign */
	
	return temp;
}



/* Prints the biginteger passed as argument.Prints the sign only if its negative.
 * Returns EOF upon error
 */
 
int printBigInt(bigint *n)
{
	int ret;
	char * str=NULL;
	int index=0;		/* array index variable */
	
	if(n==NULL)			/* if n is NULL don't print anything and return EOF */
	return EOF;
	
	while(n->value[index++]=='0'); /* take index variable to first non-zero value*/
	
	--index;
	
	if(n->sign=='-')	/* print sign only if it is negative */ 	
	printf("-");
	
	str=&(n->value[index]);		/* obtain address of first non-zero value */
	
	if(*str=='\0')	/* if no non-zero char is present (biginteger is zero */
	{
	printf("0");
	ret=1;
	}
	else
	{	
	for(;*str;str++)
	{
		ret=putchar(*str);
		if(ret==EOF)	/* return EOF in case of error */
		return ret;
	}
	}
	return ret;
}


/*  Print the biginteger passed as argument followed by a newline character.
 *	It returns the value returned by printBigInt(bigint *n)	 
 */

int printlnBigInt(bigint *n)
{
	int ret=printBigInt(n);
	if(ret!=EOF)
	printf("\n");
	
	return ret;
}


/*  Converts an integer to its biginteger representation.
 *	Returns a pointer to the newly allocated bigint
 */
 
bigint * toBigInt(int x)
{
	
	int tmp;	
	int index;   /* array index variable */
	
	/*allocate memory for a biginteger */
	
	bigint *n=(bigint *)malloc(sizeof(bigint));
	
	/* assign last variable of array of characters to nul */
	
	n->value[BISIZE]='\0';
	
	index=BISIZE-1;
	
	tmp=x;
	
	/* assign the sign */
	if(tmp>=0)
	n->sign='+';
	else
	{
	n->sign='-';
	tmp*=-1;	/* make the tmp variable positive for modulo operations */
	}
	
	
	/* convert the integer to char array representation */
	while(tmp>0)
	{
		n->value[index--]=(tmp%10)+'0';
		tmp/=10;
	}
	
	/* add the extra zeroes */
	
	while(index>=0)
	{
		n->value[index--]='0';
	}
	
	return n;	/* return the assigned biginteger */
}


/* Returns a pointer to a biginteger which represents the absolute value
 *  of another biginteger passed as argument
 */

bigint * absBigInt(bigint *n)
{
	
	int i;
	
	/* variable to hold absolute value of n */
	
	bigint *temp=(bigint *)malloc(sizeof(bigint));
	
	/* assign nul character */
	temp->value[BISIZE]='\0';
	
	/* copy all digits from n to temp variable */
	for(i=BISIZE-1;i>=0;i--)
	{
		temp->value[i]=n->value[i];
	}
	
	/* assign positive sign, irrespective of original sign of n */
	temp->sign='+';
	
	return temp;
}



/* Performs addition of two bigintegers passed as argument.
 * Returns (bigint *)
 */

bigint * addBigInt(bigint * x, bigint *y)
{
	int carry=0;	/* initially no carry */
	int digit;		/* variable to hold digit */
	int i;			/* loop variable */
	
	/* variable to hold x+y */
	
	bigint *result=(bigint *)malloc(sizeof(bigint));
	
	/* assign nul character */
	result->value[BISIZE]='\0';
	
	if((x->sign=='+' && y->sign=='+') || (x->sign=='-' && y->sign=='-'))
	{
		/* 'if' block executes if both have same sign */
		
		result->sign=x->sign; /* assign sign */
		
		/* the loop to add two bigintegers */
		
		for(i=BISIZE-1;i>=0;i--)
		{
			/* calculate the result of addition of two digits and carry */
			digit=carry + (x->value[i]-'0') + (y->value[i]-'0');
			
			if(digit>9)
			{
			carry=1;		/* set carry if digit>9 else reset */
			digit %=10;	/* digit is calculated modulo 10 if digit>9 */
			}
			else			
			carry=0;
			
			/* assign digit as char in array */
			
			result->value[i]='0'+digit;
		}
		
		if(carry==1)		/* overflow occurs when a last carry is generated */
		return NULL;		/* return NULL in case of overflow */
	}
	
	else if(x->sign=='+' && y->sign=='-')
	{
		y->sign='+';
		result=subBigInt(x,y);
		y->sign='-';
	}
	else
	{
		x->sign='+';
		result=subBigInt(y,x);
		x->sign='-';
	}
	
	return result;	/* return pointer to the resultant bigint */
}

/* Perform subtraction of two bigintegers m and n passed as arguments
 * Returns a pointer to the resultant biginteger
 */	


bigint * subBigInt(bigint *m,bigint *n)
{
	int index;
	int carry=0;	/* 	initially no carry	*/
	int digit;
	int ch;		/* indicates case ++ +- -+ --	*/

	bigint *nineComplement;
	/* variable to hold addition of nine's Complement and m */
	bigint *temp;
	bigint *result;
	bigint *ONE;
	
	
	if(m->sign=='+' && n->sign=='+')
	ch=0;	/* case0, (+m)-(+n) */
	
	else if(m->sign=='+' && n->sign=='-')
	ch=1;	/* case1, (+m)-(-n)	*/
	
	else if(m->sign=='-' && n->sign=='+')
	ch=2;	/* case2, (-m)-(+n)	*/
	
	else
	ch=3;	/* case3, (-m)-(-n)	*/
	
	switch(ch)
	{
		case 0:
		
			
		nineComplement=(bigint *)malloc(sizeof(bigint));
		nineComplement->sign='+';
		nineComplement->value[BISIZE]='\0';
		
		for(index=BISIZE-1;index>=0;index--){			
		nineComplement->value[index]='0'+(9-(n->value[index]-'0'));
		}
			
		temp=(bigint *)malloc(sizeof(bigint));
	
		temp->sign='+';
		temp->value[BISIZE]='\0';
	
		
		/* the loop to add two bigintegers */
		
		for(index=BISIZE-1;index>=0;index--)
		{
			/* calculate the result of addition of two digits and carry */
			digit=carry + (m->value[index]-'0') + (nineComplement->value[index]-'0');
			
			if(digit>9)
			{
			carry=1;		/* set carry if digit>9 else reset */
			digit %=10;	/* digit is calculated modulo 10 if digit>9 */
			}
			else			
			carry=0;
			
			/* assign digit as char in array */
			
			temp->value[index]='0'+digit;
		}		
		
		result=(bigint *)malloc(sizeof(bigint));
		
		result->value[BISIZE]='\0';
					
		if(carry==1)
		{
		ONE=toBigInt(1);
		result->sign='+';
		result=addBigInt(temp,ONE);
		free(ONE);
		}
		else{
		result->sign='-';
			
		for(index=BISIZE-1;index>=0;index--){
			result->value[index]='0'+(9-(temp->value[index]-'0'));
				}
		}
		
	free(temp);
	free(nineComplement);		
		
	break;
	
	case 1:
	
	n->sign='+';
	result=addBigInt(m,n);
	/* restore sign of biginteger variable n */
	n->sign='-';
	break;
	
	case 2:
	
	m->sign='+';
	result=addBigInt(m,n);
	result->sign='-';
	/* restore sign of biginteger variable m */
	m->sign='-';
	break;

	
	case 3:
	
	m->sign='+';
	n->sign='+';
	
	result=subBigInt(n,m);
	
	/* restore sign of both biginteger variables m and n */
	m->sign='-';
	n->sign='-';
	
	break;
	
	}
	
	for(index=BISIZE-1;index>=0;index--)
	{
		if(result->value[index]!='0')
		return result;
	}
	result->sign='+';
	return result;
	
}


/* Multiplies two bigintegers passed as argument and returns a pointer
 * to the resultant bigint.The multiplication is carried out using 
 * long multiplication method.
 */
 

bigint * multiplyBigInt(bigint *m,bigint *n)
{
	int i,j,k;
	int carry;
	int places=0;
	int p;
	
	/* length of multiplicand */
	int len1=lengthBigInt(m);
	
	/* length of multiplier */
	int len2=lengthBigInt(n);
	
	bigint *result;
	bigint *temp,*temp2;
	
	if(len1<len2)
	{
		result=multiplyBigInt(n,m);
		return result;
	}
	
	result=toBigInt(0);
	
	for(j=BISIZE-1;j>=(BISIZE-len2);j--)
	{
		temp=(bigint *)malloc(sizeof(bigint));
		temp->value[BISIZE]='\0';
		temp->sign='+';
		
		/* append required number of zeroes */
		for(i=BISIZE-1;i>(BISIZE-1-places);i--)
		{
			temp->value[i]='0';
		}
		
		k=BISIZE-places-1;
		carry=0;
		
		/* carry out multiplication using long multiplication method */
		
		for(i=BISIZE-1;i>=(BISIZE-len1);i--)
		{
			p=(m->value[i]-'0')*(n->value[j]-'0');
			p+=carry;
			temp->value[k--]='0'+(p%10);
			carry=p/10;
		}
		
		
		temp->value[k]='0'+carry;
		
		/* fill the rest of the front digits with zero */		
		while(k)
		{
			temp->value[--k]='0';
		}
		
		/* get intermediate result */	
		temp2=addBigInt(result,temp);
		
		free(result);
		result=temp2;
		free(temp);
		++places;
	}
	
	/* assign appropriate sign */	
	if(m->sign==n->sign)
	result->sign='+';
	else
	result->sign='-';
	
	return result;
}



/* Performs division of x by y using long division method and
 * returns the quotient as argument
 */


bigint * divideBigInt(bigint *x,bigint *y)
{
	int len1,len2;
	int i;
	int in1,in2,in3=0;
	
	
	bigint *dividend,*quotient,*rem,*digit,*term1,*term2;
	
	bigint *ZERO=toBigInt(0);
	if(compareToBigInt(y,ZERO)==0)
	{
		free(ZERO);
		return NULL;
	}
	free(ZERO);
	len1=lengthBigInt(x);
	len2=lengthBigInt(y);
	
	
	
	
	if(len1<len2)
	return toBigInt(0);
	
	rem=toBigInt(0);
	quotient=toBigInt(0);
	
	if(y->sign=='-')	/* check whether divisor is negative or not */
	{
		y->sign='+';	/* if negative, make it positive and set flag */
		in3=1;
	}

	while(len1>0)
	{
		/* initially dividend is set to zero, as remainder is zero initially
		 * but for further iterations it gets the value of the remainder
		 */
		dividend=copyBigInt(rem);
		free(rem);
		
		/* bring down the new adjacent digit and append it to the dividend
		 * (copied from remainder in previous step) to get the new dividend,
		 * to perform division on
		 */
		appendDigitBigInt(dividend,x->value[BISIZE-(len1--)]);
	
		/* loop through 0 to 9 to check which is the right digit to get
		 * appended to the quotient
		 */
		for(i=0;i<=9;i++)
		{
			digit=toBigInt(i);
			term1=multiplyBigInt(y,digit);
			
			in1=compareToBigInt(dividend,term1);
			free(digit);
			
			/* check to see whether remainder is negative or positive 
			 * and stop when there's transition form positive to
			 * zero or negative
			 */
			
			digit=toBigInt(i+1);
			term2=multiplyBigInt(y,digit);
			
			in2=compareToBigInt(dividend,term2);
			free(digit);
		
			if(in1==0)
			{
				appendDigitBigInt(quotient,'0'+i);
				rem=subBigInt(dividend,term1);
				break;
			}
			
			if(in1==1)
			{
				if(in2==0)
				{
					appendDigitBigInt(quotient,'0'+(i+1));
					rem=subBigInt(dividend,term2);
					break;
				}
				
				else if(in2==-1)
				{
					appendDigitBigInt(quotient,'0'+i);
					rem=subBigInt(dividend,term1);
					break;
				}	
				else
				{
				}
				
			}
			
			free(term1);
			free(term2);
		}
		
	} 
	
	if(in3==1)
	y->sign='-';	/* restore sign if required */
	
	/* assign proper sign to quotient */
	if(x->sign==y->sign)
	quotient->sign='+';
	else
	quotient->sign='-';
	
	
	return quotient;
} 
				

/* Returns a pointer to the remainder when x is divided by y.
 * Returns NULL when y is zero.
 */
			
bigint * remBigInt(bigint *x, bigint *y)
{
	bigint *quotient, *remainder,*temp;;
	
	quotient=divideBigInt(x,y);
	
	if(quotient==NULL)
	{
	free(quotient);
	return NULL;
	}
	
	temp=multiplyBigInt(y,quotient);
	remainder=subBigInt(x,temp);
	
	free(temp);
	free(quotient);
	
	return remainder;
}

	

/* Comapres two biginteger variables m and n and returns an integer
 * indicating the comparison.
 * m>n then returns 1
 * m==n then returns 0
 * m<n then returns -1
 */

int compareToBigInt(bigint *m,bigint *n)
{
	int i;	/* loop variable */
	bigint *diff;	/* variable to store the difference m-n	*/
	
	diff=subBigInt(m,n);
	
	if(diff->sign=='-')
	{
		free(diff);
		return -1;		/* when m<n	*/
	}
	else
	{
		for(i=BISIZE-1;i>=0;i--)
		{
			if(diff->value[i]!='0')
			{
			free(diff);
			return 1;	/* when m>n	*/
			}
		}
		
		free(diff);
		return 0;	/* when m==n	*/
	}
}

/* Returns the number of digits in the biginteger variable passed
 * as argument.Maximum returned value can be BISIZE.
 * When value passed is zero, returns 1 , as 1 zero digit
 * is atleast required to represent the number zero
 */

int lengthBigInt(bigint *n)
{
int i;	/* loop variable	*/
int length=0;

for(i=0;i<=BISIZE-1;i++)
{
	if(n->value[i]!='0')
	{
		length=i;
		break;
	}
}
if(length==0)
return 1;
else
return (BISIZE-length);
}



/* Returns a pointer to the resultant bigint m ^n ,
 * where m is a biginteger and n is an integer
 */

bigint *powBigInt(bigint *m,int n)
{
	int i;
	bigint *result,*temp;
	result=toBigInt(1);
	
	if(n==0)
	return result;
	else if(n==1)
	{
		free(result);
		temp=toBigInt(0);
		result=addBigInt(m,temp);
		free(temp);
		return result;
	}
		
	for(i=1;i<=n;i++)
	{
		temp=multiplyBigInt(m,result);
		free(result);
		result=temp;
	}
	return result;
}

/* Returns a new bigint which is a copy of the one passed 
 * as argument
 */


bigint *copyBigInt(bigint *n)
{
	int i;
	bigint *copy=(bigint *)malloc(sizeof(bigint));
	
	/* assign nul character */
	copy->value[BISIZE]='\0';
	
	/* assign same sign as that of 'n' */
	copy->sign=n->sign;
	
	/* perform the copying of digits */
	for(i=BISIZE-1;i>=0;i--)
	{
		copy->value[i]=n->value[i];
	}
	
	return copy;
}

/* Reverses a bigint passed as argument in-place */


void reverseBigInt(bigint *n)
{
	char c;
	
	int j=BISIZE-1;
	int len=lengthBigInt(n);
	int i=BISIZE-len;
	

	while(i<j)	/* keep swapping in-palce till i<j */
	{
		c=n->value[i];
		n->value[i]=n->value[j];
		n->value[j]=c;
		i++;	
		j--;
	}
	
}

/* Appends a char(digit) to a bigint passed as argument.
 * Thus if n is value 12345 and '6' is passed then the bigint
 * is shifted one place left and '6' is appended.
 * The original bigint is changed in-place
 */
 

int appendDigitBigInt(bigint *n,char c)
{
	int i;
	int len=lengthBigInt(n);
	
	if(len==BISIZE)
	return 0;	/* overflow, can't add any more digits */
				
	/* shift digits to left by one place */
	
	for(i=BISIZE-(len+1);i<=BISIZE-2;i++)
	{
		n->value[i]=n->value[i+1];
	}
	
	/* append the new digit */
	n->value[BISIZE-1]=c;

	return 1;	/* return 1 on success */
}


/* Returns a pointer to the bigint representing Greatest Common Divisor (gcd)
 * of two bigintegers passed as argument.
 */		

bigint * gcdBigInt(bigint *m , bigint *n)
{
		
	/* Make copies of the two bigintegers to avoid permanent changes */
	bigint *x=copyBigInt(m);
	bigint *y=copyBigInt(n);
	
	bigint *ZERO=toBigInt(0);
	
	bigint *z;
	while(compareToBigInt(y,ZERO)!=0) /* loop till y!=0 */
	{
		
		/* perform usual calculations to compute gcd */
		z=copyBigInt(y);
		free(y);
		y=remBigInt(x,z);
		free(x);
		x=copyBigInt(z);
	}
	
	free(y);
	free(z);
	free(ZERO);
	
	return x; /* x ultimately represents the gcd */
}
		

/* Returns a pointer to the bigint representing Least Common Multiple (lcm)
 * of two bigintegers passed as argument.
 */		

bigint * lcmBigInt(bigint *m,bigint *n)
{
	/* lcm(m,n) = (m*n)/gcd(m,n) = (m/gcd(m,n))*n */
	bigint *gcd=gcdBigInt(m,n);
	bigint *tmp=divideBigInt(m,gcd);
	bigint *lcm=multiplyBigInt(tmp,n);
	
	free(gcd);
	free(tmp);
	
	return lcm;
}


			
		
	
