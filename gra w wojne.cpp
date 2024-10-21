#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define liczba_kart 52
#define N 10000

void swap (int array[], int i, int k) {
	int temp;
	temp=array[i];
	array[i]=array[k];
	array[k]=temp;
}



int main(void)
{

	int array[N];
	int ilosc;
	int k;
	int talia_A[N];
	int talia_B[N];
	int len_A=liczba_kart/2;
	int len_B=liczba_kart/2;
	int start_A=0;
	int start_B=0;
	int licznik=0;
	int stop=0;
	int start_A_wojna;
	int start_B_wojna;
	int wersja;
	int max_konflikt;
	int seed;
	
	scanf("%d", &seed);
	srand((unsigned) seed);
	scanf ("%d", &wersja);
	scanf ("%d", &max_konflikt);
	
	for (int i=0; i<liczba_kart; i++)
	{
		array[i]=i;
	}
	for (int i=0; i<liczba_kart-1; i++)
	{
		ilosc=liczba_kart-i;
		k=(rand()%ilosc)+i;
		swap (array, i, k);
	}
	for (int i=0;i<(liczba_kart/2);i++)
	{
		talia_A[i]=array[i];
	}
	for (int i=0;i<(liczba_kart/2);i++)
	{
		talia_B[i]=array[(liczba_kart/2)+i];
	}
	
	
		

	while (stop==0)
	{
		if (wersja==1)
		{
			if ((talia_A[start_A]/4)>(talia_B[start_B]/4))
			{
				talia_A[start_A+len_A]=talia_A[start_A];
				talia_A[start_A+len_A+1]=talia_B[start_B];
				len_A+=1;
				len_B-=1;
				start_A+=1;
				start_B+=1;
			}
			else if ((talia_A[start_A]/4)<(talia_B[start_B]/4))
			{
				talia_B[start_B+len_B]=talia_B[start_B];
				talia_B[start_B+len_B+1]=talia_A[start_A];
				len_B+=1;
				len_A-=1;
				start_A+=1;
				start_B+=1;
			}
			else if ((talia_A[start_A]/4)==(talia_B[start_B]/4))
			{
				talia_A[start_A+len_A]=talia_A[start_A];
				talia_B[start_B+len_B]=talia_B[start_B];
				start_A+=1;
				start_B+=1;
				if (len_A<2 || len_B<2)
				{
					stop=1;
					printf ("1 ");
					printf ("%d ", len_A);
					printf ("%d", len_B);
				}
			}
			licznik+=1;
		}
		else
		{
			start_A_wojna=start_A;
			start_B_wojna=start_B;
			while (stop==0 && (talia_A[start_A]/4)==(talia_B[start_B]/4))
			{
				start_A+=2;
				start_B+=2;
				licznik+=1;
				len_A-=2;
				len_B-=2;
					
				if (licznik==max_konflikt)
				{
					stop=1;
					printf ("0 ");
				}
				else if (len_A==0 || len_B==0)
				{
					stop=1;
					printf ("1 ");
				}
				else if ((len_A==1 || len_B==1) && (talia_A[start_A]/4)==(talia_B[start_B]/4))
				{
				stop=1;
				printf ("1 ");
				}
			}
			if (stop==0)
			{
				if ((talia_A[start_A]/4)>(talia_B[start_B]/4))
				{
					start_A+=1;
					start_B+=1;
					len_A-=1;
					len_B-=1;
					while (start_A>start_A_wojna)
					{
						talia_A[start_A+len_A]=talia_A[start_A_wojna];
						start_A_wojna+=1;
						len_A+=1;
					}
					while (start_B>start_B_wojna)
					{
						talia_A[start_A+len_A]=talia_B[start_B_wojna];
						start_B_wojna+=1;
						len_A+=1;
					}
				}
				else
				{
					start_A+=1;
					start_B+=1;
					len_A-=1;
					len_B-=1;
					while (start_B>start_B_wojna)
					{
						talia_B[start_B+len_B]=talia_B[start_B_wojna];
						start_B_wojna+=1;
						len_B+=1;
					}
					while (start_A>start_A_wojna)
					{
						talia_B[start_B+len_B]=talia_A[start_A_wojna];
						start_A_wojna+=1;
						len_B+=1;
					}					
				}
				licznik+=1;
			}
			else
			{
				while (start_A>start_A_wojna)
				{
					talia_A[start_A+len_A]=talia_A[start_A_wojna];
					start_A_wojna+=1;
					len_A+=1;
				}
				while (start_B>start_B_wojna)
				{
					talia_B[start_B+len_B]=talia_B[start_B_wojna];
					start_B_wojna+=1;
					len_B+=1;
				}
				printf ("%d ", len_A);
				printf ("%d", len_B);								
			}

		}
				
		if (stop==0)
		{				
			if (len_B==0)
			{
				stop=1;
				printf ("2 ");
				printf ("%d", licznik);
			}
			else if (len_A==0)
			{
				stop=1;
				printf ("3\n");
				for (int i=start_B; i<start_B+len_B;i++)
				{
					printf ("%d ", talia_B[i]);
				}
			}
			else if (licznik==max_konflikt)
			{
				stop=1;
				printf ("0 ");
				printf ("%d ", len_A);
				printf ("%d", len_B);
			}
		}
	
	}
}
