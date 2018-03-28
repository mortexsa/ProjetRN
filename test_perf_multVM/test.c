#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int w = 10000;
int h = 10000;

int main()
{
    clock_t deb,fin;
	int i,j,k;
	
	float* a = malloc(h*sizeof(float));
	float** b = malloc(h*sizeof(float*));
	for(i=0;i<h;i++)
	{
		b[i] = malloc(w*sizeof(float));
	}
	float* c = malloc(h*sizeof(float));
	
	pthread_t* pthr = malloc(h*sizeof(pthread_t));
	
	srand(time(NULL));
	
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			b[i][j] = rand()%1001;
		}
		a[i] = rand()%1001;
		c[i] = 0;
	}
	
	
	
	deb=clock();
	
    for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			c[i] += a[j]*b[i][j];
		}
	}
    
    fin=clock();
    printf("nothing : %fs\n", (double) (fin-deb)/CLOCKS_PER_SEC);
    
    
    for(k=0;k<h;k++)
    {
		deb=clock();
		
		
		
		fin=clock();
		printf("%d thread : %fs\n", k, (double) (fin-deb)/CLOCKS_PER_SEC);
	}
    
    
    return 0;
}
