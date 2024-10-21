#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
//int add_relation (pair*, int, pair);

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(const pair *relation, int size)
{
	int powtorzone[size];
	int czy_relacje[size];
	int unikalne=0;
	int flaga;
	for (int i=0; i<size; i++)
	{
		flaga=0;
		for (int j=0; j<unikalne; j++)
		{
			if (relation[i].first==powtorzone[j])
			{
				flaga=1;
				if (czy_relacje[j]==0 && relation[i].first==relation[i].second)
				{
					czy_relacje[j]=1;
				}
				break;
			}
		}
		
		if (flaga==0)
		{
			unikalne+=1;
			powtorzone[unikalne-1]=relation[i].first;
			if (relation[i].first==relation[i].second)
			{
				czy_relacje[unikalne-1]=1;
			}
			else
			{
				czy_relacje[unikalne-1]=0;
			}
		}
		
		flaga=0;
		for (int j=0; j<unikalne; j++)
		{
			if (relation[i].second==powtorzone[j])
			{
				flaga=1;
				break;
			}
		}
		
		if (flaga==0)
		{
			unikalne+=1;
			powtorzone[unikalne-1]=relation[i].second;
			if (relation[i].first!=relation[i].second)
			{
				czy_relacje[unikalne-1]=0;
			}
		}
	}
	
	for (int i=0; i<unikalne; i++)
	{
		if (czy_relacje[i]==0)
		{
			return 0;
		}
	}
	return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(const pair *relation, int size)
{
	for (int i=0; i<size; i++)
	{
		if (relation[i].first==relation[i].second)
		{
			return 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(const pair *relation, int size)
{
	int flaga;
	for (int i=0; i<size; i++)
	{
		flaga=0;
		for (int j=0; j<size; j++)
		{
			if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
			{
				flaga=1;
				break;
			}
		}
		if (flaga==0)
		{
			return 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(const pair *relation, int size)
{
	for (int i=0; i<size; i++)
	{
		if (relation[i].first!=relation[i].second)
		{
			for (int j=0; j<size; j++)
			{
				if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(const pair *relation, int size)
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
			{
				return 0;
			}
		}
	}
	return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(const pair *relation, int size)
{
	int flaga;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size ;j++)
		{
			if (relation[i].second==relation[j].first)
			{
				flaga=0;
				for (int k=0; k<size; k++)
				{
					if (relation[i].first==relation[k].first && relation[j].second==relation[k].second)
					{
						flaga=1;
						break;
					}
				}
				if (flaga==0)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(const pair *relation, int size)
{
	if (is_reflexive(relation, size)==1 && is_antisymmetric(relation, size)==1 && is_transitive(relation, size)==1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
	
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(const pair *relation, int size)
{
	int macierz[size][size];
	int powtorzone[size];
	int unikalne=0;
	int flaga;
	int first_el;
	int second_el;
	for (int i=0; i<size;i++)
	{
		flaga=0;
		for (int j=0; j<unikalne; j++)
		{
			if (relation[i].first==powtorzone[j])
			{
				flaga=1;
				first_el=j;
				break;
			}
		}
		
		if (flaga==0)
		{
			unikalne+=1;
			powtorzone[unikalne-1]=relation[i].first;
			first_el=unikalne-1;
		}
		
		flaga=0;
		for (int j=0; j<unikalne; j++)
		{
			if (relation[i].second==powtorzone[j])
			{
				flaga=1;
				second_el=j;
				break;
			}
		}
		
		if (flaga==0)
		{
			unikalne+=1;
			powtorzone[unikalne-1]=relation[i].second;
			second_el=unikalne-1;
		}
		
		macierz[first_el][second_el]=1;
		macierz[second_el][first_el]=1;
	}
	
	for (int i=0; i<unikalne; i++)
	{
		for (int j=0; j<unikalne; j++)
		{
			if (i!=j && macierz[i][j]==0)
			{
				return 0;
			}
		}
	}
	return 1;
}

// A total order relation is a partial order relation that is connected
int is_total_order(const pair *relation, int size)
{
	if (is_partial_order(relation, size)==1 && is_connected(relation, size)==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int find_max_elements(const pair *relation, int size, int *max_elements)
{
	int no_max_elements=0;
	int flaga;
	int wstaw;
	for (int i=0; i<size; i++)
	{
		flaga=0;
		for (int j=0; j<size; j++)
		{
			if (relation[i].second==relation[j].first && relation[j].first!=relation[j].second)
			{
				flaga=1;
				break;
			}
		}
		
		if (flaga==0)
		{
			wstaw=0;
			while (wstaw<no_max_elements && max_elements[wstaw]<relation[i].second)
			{
				wstaw+=1;
			}
			if (wstaw<no_max_elements)
			{
				if (max_elements[wstaw]>relation[i].second)
				{
					for (int j=no_max_elements; j>wstaw; j--)
					{
						max_elements[j]=max_elements[j-1];
					}
					max_elements[wstaw]=relation[i].second;
					no_max_elements+=1;
				}
			}
			else
			{
				max_elements[no_max_elements]=relation[i].second;
				no_max_elements+=1;
			}
		}
	}
	return no_max_elements;
}
int find_min_elements(const pair *relation, int size, int *min_elements)
{
	int no_min_elements=0;
	int flaga;
	int wstaw;
	for (int i=0; i<size; i++)
	{
		flaga=0;
		for (int j=0; j<size; j++)
		{
			if (relation[i].first==relation[j].second && relation[j].first!=relation[j].second)
			{
				flaga=1;
				break;
			}
		}
		
		if (flaga==0)
		{
			wstaw=0;
			while (wstaw<no_min_elements && min_elements[wstaw]<relation[i].first)
			{
				wstaw+=1;
			}
			if (wstaw<no_min_elements)
			{
				if (min_elements[wstaw]>relation[i].first)
				{
					for (int j=no_min_elements; j>wstaw; j--)
					{
						min_elements[j]=min_elements[j-1];
					}
					min_elements[wstaw]=relation[i].first;
					no_min_elements+=1;
				}
			}
			else
			{
				min_elements[no_min_elements]=relation[i].first;
				no_min_elements+=1;
			}
		}
	}
	return no_min_elements;
}
int get_domain(const pair *relation, int size, int *domain)
{
	int n_domain=0;
	int flaga;
	int wstaw;
	for (int i=0; i<size;i++)
	{
		flaga=0;
		for (int j=0; j<n_domain; j++)
		{
			if (relation[i].first==domain[j])
			{
				flaga=1;
				break;
			}
		}
		
		if (flaga==0)
		{
			wstaw=0;
			while (wstaw<n_domain && domain[wstaw]<relation[i].first)
			{
				wstaw+=1;
			}
			if (wstaw<n_domain)
			{
				if (domain[wstaw]>relation[i].first)
				{
					for (int j=n_domain; j>wstaw; j--)
					{
						domain[j]=domain[j-1];
					}
					domain[wstaw]=relation[i].first;
					n_domain+=1;
				}
			}
			else
			{
				domain[n_domain]=relation[i].first;
				n_domain+=1;
			}
		}

		flaga=0;
		for (int j=0; j<n_domain; j++)
		{
			if (relation[i].second==domain[j])
			{
				flaga=1;
				break;
			}
		}
		
		if (flaga==0)
		{
			wstaw=0;
			while (wstaw<n_domain && domain[wstaw]<relation[i].second)
			{
				wstaw+=1;
			}
			if (wstaw<n_domain)
			{
				if (domain[wstaw]>relation[i].second)
				{
					for (int j=n_domain; j>wstaw; j--)
					{
						domain[j]=domain[j-1];
					}
					domain[wstaw]=relation[i].second;
					n_domain+=1;
				}
			}
			else
			{
				domain[n_domain]=relation[i].second;
				n_domain+=1;
			}
		}
	}
	return n_domain;
}

// Case 3:

int composition (const pair *relation, int size, const pair *relation2, int size2, pair *comp_relation)
{
	int n_comp_relation=0;
	int flaga;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size2; j++)
		{
			if (relation[i].second==relation2[j].first)
			{
				flaga=0;
				for (int k=0; k<n_comp_relation; k++)
				{
					if (relation[i].first==comp_relation[k].first && relation2[j].second==comp_relation[k].second)
					{
						flaga=1;
						break;
					}
				}
				if (flaga==0)
				{
					comp_relation[n_comp_relation].first=relation[i].first;
					comp_relation[n_comp_relation].second=relation2[j].second;
					n_comp_relation+=1;
				}
			}
		}
	}
	return n_comp_relation;
}

// Comparator for pair
int cmp_pair (const void *a, const void *b) {
}

int insert_int (int *tab, int n, int new_element) {
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
	for (int i=0; i<n; i++)
	{
		if (tab[i].first==new_pair.first && tab[i].second==new_pair.second)
		{
			return 0;
		}
	}
	tab[n].first=new_pair.first;
	tab[n].second=new_pair.second;
	return 1;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
	int liczba_relacji=0;
	int liczba_wprowadzen;
	pair new_pair;
	scanf ("%d",&liczba_wprowadzen);
	for (int i=0; i<liczba_wprowadzen; i++)
	{
		scanf ("%d", &new_pair.first);
		scanf ("%d", &new_pair.second);
		if (add_relation (relation,liczba_relacji,new_pair)==1)
		{
			liczba_relacji+=1;
		}
	}
	return liczba_relacji;
}

void print_int_array(const int *array, int n) 
{
	printf ("%d\n",n);
	for(int i = 0; i < n; ++i) 
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
		{
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		}
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

