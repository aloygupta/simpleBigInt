#include <stdio.h>
#include "bigint.c"

int main()
{
	
	bigint * x,*y,*z;
	printf("Enter two numbers\n");
	x=readBigInt();
	y=readBigInt();
	
	z=addBigInt(x,y);
	printf("\nAddition: ");
	printlnBigInt(z);

	free(z);
		
	z=subBigInt(x,y);
	printf("\nSubtraction: ");
	printlnBigInt(z);
	free(z);
	
	z=multiplyBigInt(x,y);
	printf("\nMultiplication: ");
	printlnBigInt(z);
	free(z);
		
	z=divideBigInt(x,y);
	printf("\nDivision: ");
	printlnBigInt(z);
	free(z);
	
	z=remBigInt(x,y);
	printf("\nRemainder : ");
	printlnBigInt(z);

	free(z);
	z=gcdBigInt(x,y);
	printf("\ngcd : ");
	printlnBigInt(z);
	
	z=gcdBigInt(x,y);
	printf("\nlcm : ");
	printlnBigInt(z);
	
	free(z);
	free(x);
	free(y);
	
	return 0;
}
