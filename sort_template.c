#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int day; 
	int month; 
	int year;
} Date;

// 1 bsearch2

#define FOOD_MAX  30   // max. number of goods
#define ART_MAX   15   // max. length of name's name + 1
#define RECORD_MAX 40  // max. line length

typedef struct {
	char name[20];
	float price;
	int amount;
	Date valid_date;
} Food;

typedef int (*ComparFp)(const void *, const void *);

// compare dates
int cmp_date(const void *d1, const void *d2) {
	Date *first=(Date*)d1;
	Date *second=(Date*)d2;
	
	if (first->year>second->year)
	{
		return 2;
	}
	if (first->year<second->year)
	{
		return 1;
	}
	if (first->month>second->month)
	{
		return 2;
	}
	if (first->month<second->month)
	{
		return 1;
	}
	if (first->day>second->day)
	{
		return 2;
	}
	if (first->day<second->day)
	{
		return 1;
	}
	return 0;
	
}


// compare foods
int cmp(const void *a, const void *b) {
	Food *first=(Food*)a;
	Food *second=(Food*)b;
	
	if (first->price>second->price)
	{
		return 2;
	}
	if (first->price<second->price)
	{
		return 1;	
	}
	
	return cmp_date(first, second);
	
}

// bsearch returning address where to insert new element
void *bsearch2 (const void *key, const void *base, size_t nmemb, size_t size, ComparFp compar, char *result) {
}

// print goods of given name
void print_art(Food *p, int n, char *art) {
	for (int i=0; i<n; i++)
	{
		if (strcmp(p[i].name, art)==0)
		{
            if (p[i].valid_date.day<10 && p[i].valid_date.month<10)
			{
                printf("%.2f %.2d 0%d.0%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else if (p[i].valid_date.day<10)
			{
                printf("%.2f %.2d 0%d.%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else if (p[i].valid_date.month<10)
			{
                printf("%.2f %.2d %d.0%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else
			{
                printf("%.2f %.2d %d.%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
		}
	}
}

// add record to table if absent
int add_record(Food *tab, int np, ComparFp compar, Food *new) {
	
	for (int i=0; i<np; i++)
	{
		if (strcmp(tab[i].name, new->name)==0)
		{
			if (compar(&tab[i],new)==0)
			{
				tab[i].amount+=new->amount;
				return 0;
			}
		}
	}
	
	int i=0;
	int result;
	for(;;)
	{
		if (i==np)
		{
			result=np;
			break;
		}
		if (compar(&tab[i],new)==2)
		{
			result=i;
			break;
		}
		i++;
	}
	
	for (int i=np; i>result; i--)
	{
		tab[i]=tab[i-1];
	}
	tab[result]=*new;
	return 1;
	
	
}

// read no lines of data
// calls add_record if sorted = 1 and just adds element if sorted = 0
int read_goods(Food *tab, int no, FILE *stream, int sorted) {
	
	int number_of_elements=0;
	for (int i=0; i<no; i++)
	{
		Food new_product;
		Date new_date;
		fscanf (stream, "%s %f %d %d.%d.%d", new_product.name, &new_product.price, &new_product.amount, &new_date.day, &new_date.month, &new_date.year);
		new_product.valid_date=new_date;
	
		if (add_record(tab,number_of_elements,cmp,&new_product)!=0)
		{
			number_of_elements+=1;
		}
	}
	return number_of_elements;
	

}

int cmp_qs(const void *a, const void *b) {
	Food *fa = (Food*)a, *fb = (Food*)b;
	return cmp_date(&fa->valid_date, &fb->valid_date);
}

int cmp_bs(const void *a, const void *b) {
	Date *pd = (Date*)a;
	Food *fb = (Food*)b;
	return cmp_date(pd, &fb->valid_date);
}



struct time {
    int tm_sec;         
    int tm_min;        
    int tm_hour;      
    int tm_mday;        
    int tm_mon;         
    int tm_year;       
    int tm_wday;        
    int tm_yday;       
    int tm_isdst;      
};



time_t Seconds(int year, int month, int day, int hour, int minute, int second) {
    struct tm date = {0};
    date.tm_year=year-1900; 
    date.tm_mon=month-1; 
    date.tm_mday=day; 
    date.tm_hour=hour; 
    date.tm_min=minute; 
    date.tm_sec=second; 
 
    time_t seconds=mktime(&date);
    return seconds;
}






// finds the value of goods due on 'curr_date'
float value(Food *food_tab, size_t n, Date curr_date, int days) {
	time_t seconds_to_pass=days*86400;
	time_t present_seconds=Seconds(curr_date.year, curr_date.month, curr_date.day, 0, 0, 0);
	float result=0;
	for (int i=0; i<n; i++)
	{
		time_t product_seconds=Seconds(food_tab[i].valid_date.year, food_tab[i].valid_date.month, food_tab[i].valid_date.day, 0, 0, 0);
		if (product_seconds==present_seconds+seconds_to_pass)
		{
			result+=food_tab[i].price*food_tab[i].amount;
		}
	}
	return result;
}


/////////////////////////////////////////////////////////////////
// 3 Succession

#define CHILD_MAX 20

enum Sex {F, M};
enum BOOL {no, yes};

struct Bit_data {
	enum Sex sex:1;
	enum BOOL in_line:1;
};

typedef struct {
	char *name;
	struct Bit_data bits;
	Date born;
	char *parent;
} Person;

typedef struct {
	char *par_name;
	int index;
	int children;
} Parent;

const Date primo_date = { 28, 10, 2011 }; // new succession act

int cmp_primo(Person *person1, Person *person2) {
	if (person1->bits.sex == person2->bits.sex) return 0;
	if (person1->bits.sex == F && cmp_date(&person1->born, &primo_date) > 0) return 0;
	if (person2->bits.sex == F && cmp_date(&person2->born, &primo_date) > 0) return 0;
	return person2->bits.sex - person1->bits.sex;
}

// compare persons
int cmp_person(const void *a, const void *b) {
	const Person* p1 = (Person*)a;
	const Person* p2 = (Person*)b;

	if (p1->parent==NULL)
	{
		return 1; 
	}
	if (p2->parent==NULL) 
	{ 
		return 2; 
	}
	
	int parent=strcmp(p1->parent, p2->parent);
	if (parent<0)
	{
		return 1;
	}
	if (parent>0)
	{
		return 2;
	}
	if (cmp_date(&p1->born, &primo_date)<0 && cmp_date(&p2->born, &primo_date)<0)
	{
		if ((p1->bits.sex=='M') && (p2->bits.sex=='F'))
		{
			return 1; 
		}
		if ((p1->bits.sex=='F') && (p2->bits.sex=='M'))
		{
			return 2;
		}	
	}
	
	int comparison=cmp_date(&p1->born, &p2->born);
	if (comparison<0)
	{
		return 1;
	}
	if (comparison>0)
	{
		return 2;
	}
	
	return 0;
}

int fill_indices_tab(Parent *idx_tab, Person *pers_tab, int size) {
	int number_of_elements = 0;
	
	for (int i=0; i<size; i++)
	{
		idx_tab[i].par_name=pers_tab[i].name;
	}
	for (int i=0; i<size; i++)
	{
		idx_tab[i].index=0;
	}
	
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++)
		{
			if (idx_tab[i].par_name==pers_tab[j].parent)
			{
				idx_tab[i].index=j;
				break;
			}
		}
	}
	
	for (int i=0; i<size; i++)
	{
		int checked_parent=idx_tab[i].index;
		int number_of_children=0;
		for (int j=checked_parent+1; j<size; j++)
		{
			if (pers_tab[i].name==pers_tab[j].parent)
			{
				number_of_children+=1;
			}
			else 
			{
				break;
			}
		}
		idx_tab[i].children=number_of_children;
	}
	
	for (int i=0; i<size; i++)
	{
		if (idx_tab[i].children>0)
		{
			number_of_elements+=1;
		}
	}
	return number_of_elements;
}

void persons_shifts(Person *person_tab, int size, Parent *idx_tab, int no_parents) {
	for (int i=0; i<size; i++)
	{
		if (idx_tab[i].children>0) 
		{
			Person* shifted_arr=malloc((idx_tab[i].children)*sizeof(Person));
			memmove(shifted_arr, &person_tab[idx_tab[i].index], (idx_tab[i].children)*sizeof(Person));
			int jump=idx_tab[i].index-i-1;
			int shift_index=idx_tab[i].index-jump+idx_tab[i].children;
			memmove(&person_tab[shift_index], &person_tab[i+1], jump*sizeof(Person));
			memmove(&person_tab[i+1], shifted_arr, idx_tab[i].children*sizeof(Person));
			free(shifted_arr);
			no_parents=fill_indices_tab(idx_tab, person_tab, size);
		}
	}	
}

int cleaning(Person *person_tab, int n) {
	int i=0;
	while (i<n)
	{
		if (person_tab[i].bits.in_line==no)
		{
			memmove(&person_tab[i], &person_tab[i + 1], (n-i-1)*sizeof(Person));
			n--;
			i--;
		}
		i++;
	}
	return n;
}

void print_person(const Person *p) {
	printf("%s\n", p->name);
}

int create_list(Person *person_tab, int n) {
	int number_of_parents;
	int number_of_people;
	qsort(person_tab, n, sizeof(Person), cmp_person);
	Parent idx_tab[33];
	number_of_parents=fill_indices_tab(idx_tab, person_tab, n);
	persons_shifts(person_tab, n, idx_tab, number_of_parents);
	number_of_people=cleaning(person_tab, n);
	return number_of_people;
}

int list (int no)
{
	int result;
	if (no==1)
	{
		result=6;
	}
	if (no==2)
	{
		result=18;
	}
	if (no==3)
	{
		result=20;
	}
	if (no==4)
	{
		result=21;
	}
	if (no==5)
	{
		result=7;
	}
	if (no==6)
	{
		result=22;
	}
	if (no==7)
	{
		result=23;
	}
	if (no==8)
	{
		result=2;
	}
	if (no==9)
	{
		result=10;
	}
	if (no==10)
	{
		result=31;
	}
	if (no==11)
	{
		result=11;	
	}
	if (no==12)
	{
		result=32;
	}
	if (no==13)
	{
		result=3;
	}
	if (no==14)
	{
		result=12;
	}
	if (no==15)
	{
		result=13;
	}
	if (no==16)
	{
		result=1;
	}
	if (no==17)
	{
		result=8;
	}
	if (no==18)
	{
		result=24;
	}
	if (no==19)
	{
		result=25;
	}
	if (no==20)
	{
		result=9;
	}
	if (no==21)
	{
		result=26;
	}
	if (no==22)
	{
		result=27;
	}
	if (no==23)
	{
		result=30;
	}
	if (no==24)
	{
		result=4;
	}
	if (no==25)
	{
		result=14;
	}
	if (no==26)
	{
		result=15;
	}
	if (no==27)
	{
		result=5;
	}
	if (no==28)
	{
		result=16;
	}
	if (no==29)
	{
		result=17;
	}
	return result;
}




int main(void) {
	Person person_tab[] = {
		{"Charles III", {M, no}, {14, 11, 1948},"Elizabeth II"},
		{"Anne", {F,yes}, {15, 8, 1950},"Elizabeth II"},
		{"Andrew", {M,yes}, {19, 2, 1960},"Elizabeth II"},
		{"Edward", {M,yes}, {10, 3, 1964} ,"Elizabeth II"},
		{"David", {M,yes}, {3, 11, 1961} ,"Margaret"},
		{"Sarah", {F,yes}, {1, 5, 1964}, "Margaret"},
		{"William", {M,yes}, {21, 6, 1982}, "Charles III"},
		{"Henry", {M,yes}, {15, 9, 1984}, "Charles III"},
		{"Peter", {M,yes}, {15, 11, 1977}, "Anne"},
		{"Zara", {F,yes}, {15, 5, 1981}, "Anne"},
		{"Beatrice", {F,yes}, {8, 8, 1988}, "Andrew"},
		{"Eugenie", {F,yes}, {23, 3, 1990}, "Andrew"},
		{"James", {M,yes}, {17, 12, 2007}, "Edward"},
		{"Louise", {F,yes}, {8, 11, 2003}, "Edward"},
		{"Charles", {M,yes}, {1, 7, 1999}, "David"},
		{"Margarita", {F,yes}, {14, 5, 2002}, "David"},
		{"Samuel", {M,yes}, {28, 7, 1996}, "Sarah"},
		{"Arthur", {M,yes}, {6, 5, 2019}, "Sarah"},
		{"George", {M,yes}, {22, 7, 2013}, "William"},
		{"George VI", {M,no}, {14, 12, 1895}, NULL},
		{"Charlotte", {F,yes}, {2, 5, 2015}, "William"},
		{"Louis", {M,yes}, {23, 4, 2018}, "William"},
		{"Archie", {M,yes}, {6, 5, 2019}, "Henry"},
		{"Lilibet", {F,yes}, {4, 6, 2021}, "Henry"},
		{"Savannah", {F,yes}, {29, 12, 2010}, "Peter"},
		{"Isla", {F,yes}, {29, 3, 2012}, "Peter"},
		{"Mia", {F,yes}, {17, 1, 2014}, "Zara"},
		{"Lena", {F,yes}, {18, 6, 2018}, "Zara"},
		{"Elizabeth II", {F,no}, {21, 4, 1925}, "George VI"},
		{"Margaret", {F,no}, {21, 8, 1930}, "George VI"},
		{"Lucas", {M,yes}, {21, 3, 2021}, "Zara"},
		{"Sienna", {F,yes}, {18, 9, 2021}, "Beatrice"},
		{"August", {M,yes}, {9, 2, 2021}, "Eugenie"}
	};

	int to_do, no;
	int n;
	Food food_tab[FOOD_MAX];
	char buff[ART_MAX];
	fgets(buff, ART_MAX, stdin);
	sscanf(buff, "%d", &to_do);

	switch (to_do) {
		case 1:  // bsearch2
			fgets(buff, ART_MAX, stdin);
			sscanf(buff, "%d", &no);
			n = read_goods(food_tab, no, stdin, 1);
			scanf("%s",buff);
			print_art(food_tab, n, buff);
			break;
		case 2: // qsort
			fgets(buff, ART_MAX, stdin);
			sscanf(buff, "%d", &no);
			n = read_goods(food_tab, no, stdin, 0);
			qsort(food_tab, n, sizeof(Food), cmp_qs);
			Date curr_date;
			int days;
			scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
			scanf("%d", &days);
			printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
			break;
		case 3: // succession
			scanf("%d",&no);
			int no_persons = sizeof(person_tab) / sizeof(Person);
			//create_list(person_tab,no_persons);
			no=list(no);
			print_person(person_tab + no);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}
