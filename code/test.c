#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"

#define WHT   "\x1B[8;47m"
#define BLK   "\x1B[8;40m"
#define RESET "\x1B[0m"

int main()
{
	test_chargerMNIST("/home/user/Bureau/train-images-idx3-ubyte");
	test_ChargerEtiquetteMNIST("/home/user/Bureau/train-labels-idx1-ubyte");
}

void test_chargerMNIST(char* path)
{	
	Image* im = ChargerMnist(path, 28, 28);
	
	if(!im) exit(-1);
	
	int i, j;
	for(i=0;i<28;i++)
	{
		for(j=0;j<28;j++)
		{
			if(im->dat[i*28+j].r > 0)
				printf(WHT "1" RESET);
			else
				printf(BLK "0" RESET);
		}
		printf("\n");
	}
	
	DelImage(im);
}

void test_ChargerEtiquetteMNIST(char* path)
{
	char* c = ChargerEtiquetteMNIST(path);
	printf("%c\n",*c);
	free(c);
}
