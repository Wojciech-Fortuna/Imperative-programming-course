#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum TypyAut {
	Osobowy,
	Autobus,
	Ciezarowka
}TypyAut;

typedef enum TypyNapedu {
	electric,
	hybrid,
	combustion
}TypyNapedu;


typedef struct Vehicle{
	char *owner;
	int data_przegladu[3];
	TypyAut typ;
	TypyNapedu naped;
	union 
	{
		struct 
		{
			int liczba_osob;
			float moc;
		};
		struct
		{
			int siedzace;
			int stojace;
		};
		struct
		{
			float pojemnosc;
			float nacisk;
		};
	};
}Vehicle;

void new_owner(Vehicle *pvehicle)
{
	char *new_name=(char*)malloc(sizeof(char)*100);
	scanf ("%s",new_name);	
	pvehicle->owner=new_name;
	
}

int cmp_data(int *data1, int *data2)
{
	if (data1[2]<data1[2])
	{
		return 1;
	}
	if (data1[2]>data2[2])
	{
		return -1;
	}
	if (data1[1]<data2[1])
	{
		return 1;
	}
	if (data1[1]>data2[1])
	{
		return -1;
	}
	if (data1[0]<data2[0])
	{
		return 1;
	}
	if (data1[0]>data2[0])
	{
		return -1;
	}
	return 0;
}

int delayed(Vehicle *pvehicle, int size, int *base_date, char ***pdelayed_owners)
{
	char **delayed_owners=NULL;
	int licznik=0;
	for (int i=0; i<size; i++)
	{
		if (cmp_data(pvehicle[i].data_przegladu, base_date) == 1)
		{
			delayed_owners=(char**)realloc(delayed_owners, (licznik+1)*sizeof(char[100]));
			delayed_owners[licznik]=pvehicle[i].owner;
			licznik+=1;
		}
	}
	*pdelayed_owners=delayed_owners;
	return licznik;
}


void print_pojazd(Vehicle *pvehicle)
{

}


int main()
{
 	Vehicle *pojazd;
 	pojazd=(Vehicle*)malloc(sizeof(Vehicle));
	new_owner(pojazd);
	printf ("%s 3\n",(char*)pojazd->owner);	
	//new_owner(pojazd);
	//printf ("%s 3\n",(char*)pojazd->owner);	
	char ***pdelayed_owners;
	int dzis[3]={12,7,2023};
	delayed(pojazd, 1, dzis, pdelayed_owners);

}

