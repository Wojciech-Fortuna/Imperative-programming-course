#include <stdio.h>                                                              
#include <math.h> 

int main (void) {
	int n;
	int pierwiastek;
	int a=0;
	int b=1;
	int temp;
	int koniec=0;
	printf ("Podaj liczbe ");
	scanf ("%d", &n);
	pierwiastek=int(sqrt(n));
	while (koniec==0)
	{
		if (a*b==n)
		{
			printf ("Tak");
			koniec=1;
		}
		else
		{
			temp=b;
			b=a+b;
			a=temp;
			if (a>pierwiastek)
			{
			printf ("Nie");
			koniec=1;
			}
		}

	
	}
	return 0;
}
