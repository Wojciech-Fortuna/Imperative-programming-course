#include <stdio.h>                                                              
#include <math.h> 

int main (void) {
	int start;
	int stop;
	int pierwiastek;
	int suma;
	int licznik=0;
	printf ("Podaj poczatek przedzialu ");
	scanf ("%d",&start);
	if (start==1)
	{
		start=2;
	}
	printf ("Podaj koniec przedzialu ");
	scanf ("%d",&stop);
	for (int i=start; i<=stop; i++)
	{
		pierwiastek=sqrt(i);
		suma=1;
		for (int j=2; j<=pierwiastek; j++)
		{
			if (i%j==0)	
			{
				suma+=j;
				if (i/j!=j)
				{
					suma+=i/j;
				}
			}
		}
		if (suma==i)
		{
			printf ("%d ", i);
			licznik+=1;
		}
	}
	printf ("\nTych liczb jest %d", licznik);
	return 0;
}
