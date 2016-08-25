#include<stdio.h>
#include "spinor.h"
//roll , boo, ceasor, rebound, upper
void main()
{	int i=0;	
	spinor_cr ani;

	SPINOR_CREATE(ani,150,stdout,upper);	
	printf("Downloading:   ");
	sleep(10);
	SPINOR_STOP(ani);
}
