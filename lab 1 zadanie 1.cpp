#include <stdio.h>
main (void) {
	int wynik=1;
	int n;
	printf ("Podaj liczbe ");
	scanf ("%d", &n);
	for (int i=2;i<=n;i++)
	{
		wynik*=i;
	}
	
	printf ("%d", wynik);
	
	return 0;
}
