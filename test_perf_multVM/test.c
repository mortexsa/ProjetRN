#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define PTHREAD_THREADS_MAX 1024

int w = 10000;
int h = 10000;

typedef struct
{
	int deb;
	int fin;
	float* a;
	float** b;
	float* c;
}donnees;

void* MultVM(void* arg)
{
	int i,j;
	donnees* ar = (donnees*)arg;
	
	for(i = ar->deb;i < ar->fin;i++)
	{
		for(j=0;j<w;j++)
		{
			ar->c[i] += (ar->a[j])*(ar->b[i][j]);
		}
	}
	return NULL;
}

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
	
	if(h>=PTHREAD_THREADS_MAX)
		k = PTHREAD_THREADS_MAX-1;
	else
		k = h;
		
	pthread_t pthr[h];
	
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
	
	//----------------------------
    
    //----------------------------
	
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
    
    //----------------------------
    
    //----------------------------
    
    donnees* info = malloc(PTHREAD_THREADS_MAX*sizeof(donnees));
    donnees info_perso;
    info_perso.deb=(h/k)*(k-1);
    info_perso.fin=h;
    info_perso.a=a;
    info_perso.b=b;
    info_perso.c=c;
    
    for(k=1;k<PTHREAD_THREADS_MAX;k++)
    //for(k=1;k<2;k++)
    {
		for(i=0;i<h;i++)
			c[i] = 0;
		
		deb=clock();
		
		for(i=0;i<k;i++)
		{
			info[i].deb = (h/k)*i;
			info[i].fin = (h/k)*(i+1) - 1;
			info[i].a = a;
			info[i].b = b;
			info[i].c = c;
			
			pthread_create(&pthr[i], NULL, MultVM, &info[i]);
		}
		MultVM(&info_perso);
		
		for(i=0;i<k;i++)
		{
			pthread_join(pthr[i], NULL);
		}
		
		fin=clock();
		printf("%d thread : %fs\n", k, (double) (fin-deb)/CLOCKS_PER_SEC);
	}
    
    //----------------------------
    
    //----------------------------
    
    return 0;
}
