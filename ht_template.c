#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define MAX_RATE 4
#define MEMORY_ALLOCATION_ERROR  (-1)

typedef union {
	int int_data;
	char char_data;
	// ... other primitive types used
	void *ptr_data;
} data_union;

typedef struct ht_element {
	struct ht_element *next;
	data_union data;
} ht_element;

typedef void (*DataFp)(data_union);
typedef void (*DataPFp)(data_union*);
typedef int (*CompareDataFp)(data_union, data_union);
typedef size_t (*HashFp)(data_union, size_t);
typedef data_union (*CreateDataFp)(void*);

typedef struct {
	size_t size;
	size_t no_elements;
	ht_element *ht;
	DataFp dump_data;
	CreateDataFp create_data;
	DataFp free_data;
	CompareDataFp compare_data;
	HashFp hash_function;
	DataPFp modify_data;
} hash_table;

// ---------------------- functions to implement

// initialize table fields
void init_ht(hash_table *p_table, size_t size, DataFp dump_data, CreateDataFp create_data,
		 DataFp free_data, CompareDataFp compare_data, HashFp hash_function, DataPFp modify_data) 
{
	p_table->compare_data=compare_data;
	p_table->create_data=create_data;
	p_table->dump_data=dump_data;
	p_table->free_data=free_data;
	p_table->hash_function=hash_function;
	p_table->modify_data=modify_data;
	p_table->no_elements=0;
	p_table->size=size;
	p_table->ht=(ht_element*)malloc(size * sizeof(ht_element));
	for (size_t i = 0; i < size; i++) 
	{
        p_table->ht[i].next=NULL;
    }
}

// print elements of the list with hash n
void dump_list(const hash_table* p_table, size_t n) 
{
	ht_element *ptr=p_table->ht;
    for(size_t i=0; i<n; i++)
	{
        ptr++;
    }
    ptr=ptr->next;
    while (ptr!=NULL)
	{
        p_table->dump_data(ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

// Free element pointed by data_union using free_data() function
void free_element(DataFp free_data, ht_element *to_delete) {
	free_data(to_delete->data);
	free(to_delete);
}

// free all elements from the table (and the table itself)
void free_table(hash_table* p_table) 
{
    ht_element *ptr=p_table->ht;
    for (size_t i=0; i<p_table->size; i++) 
	{
        while (ptr!=NULL) 
		{
            ht_element *destroy=ptr;
            ptr=ptr->next;
            free_element(p_table->free_data, destroy);
        }
        ptr+=1;
    }
    free(p_table->ht);
}

// calculate hash function for integer k
size_t hash_base(int k, size_t size) {
	static const double c = 0.618033988; // (sqrt(5.) – 1) / 2.;
	double tmp = k * c;
	return (size_t)floor((double)size * (tmp - floor(tmp)));
}

void rehash(hash_table *p_table) 
{
	size_t new_size = p_table->size * 2;
    ht_element *new_ht = (ht_element*)malloc(p_table->size * 2 * sizeof(ht_element));
    for (size_t i=0; i<p_table->size*2; i++) 
	{
        new_ht[i].next=NULL;
    }
    for (size_t i = 0; i < p_table->size; i++) 
	{
        ht_element *ptr=p_table->ht[i].next;
        while (ptr!=NULL) 
		{
            ht_element *next=ptr->next;
            size_t new_index=p_table->hash_function(ptr->data, p_table->size*2);
            ptr->next=new_ht[new_index].next;
            new_ht[new_index].next=ptr;
            ptr=next;
        }
    }
    p_table->size=new_size;
    p_table->ht=new_ht;
}

// find element; return pointer to previous
ht_element *find_previous(hash_table *p_table, data_union data) 
{
	size_t index = p_table->hash_function(data, p_table->size);
    ht_element *previous = &(p_table->ht[index]);
    ht_element *current = previous->next;
    while (current!=NULL && p_table->compare_data(data, current->data)!=0) 
	{
        previous=current;
        current=current->next;
    }
    return previous;
}

// return pointer to element with given value
ht_element *get_element(hash_table *p_table, data_union *data) 
{
	ht_element *previous=find_previous(p_table, *data);
    return previous->next;


}

// insert element
void insert_element(hash_table *p_table, data_union *data) 
{
    if(get_element(p_table,data)==NULL) 
	{
        size_t index=p_table->hash_function(*data, p_table->size);
        ht_element *previous=&(p_table->ht[index]);
        ht_element *ad_as_next=previous->next;
        ht_element *element_to_add=(ht_element*)malloc(sizeof(ht_element));
        element_to_add->next=ad_as_next;
        element_to_add->data=*data;
        previous->next=element_to_add;
        p_table->no_elements++;
        if (p_table->no_elements >= p_table->size * MAX_RATE) 
		{
            rehash(p_table);
        }
    }
    
}

// remove element
void remove_element(hash_table *p_table, data_union data) 
{
    ht_element *previous=find_previous(p_table, data);
    ht_element *deleted=previous->next;
    if (deleted!=NULL && p_table->compare_data(data,deleted->data)==0) 
	{
        previous->next=deleted->next;
        p_table->no_elements--;
    }
}

// type-specific definitions

// int element

size_t hash_int(data_union data, size_t size) {
	return hash_base(data.int_data, size);
}

void dump_int(data_union data) 
{
	printf("%d ",data.int_data);
}

int cmp_int(data_union a, data_union b) 
{
	int first=a.int_data;
    int second=b.int_data;
    if(first<second)
	{
        return -1;
    }
	if(first>second)
	{
        return 1;
    }
    return 0;
}

data_union create_int(void* value) 
{
	int number;
    scanf("%d",&number);
    data_union union_number;
    union_number.int_data=number;
    return union_number;
}

// char element

size_t hash_char(data_union data, size_t size) {
	return hash_base((int)data.char_data, size);
}

void dump_char(data_union data) 
{
	printf("%c ",data.char_data);
}

int cmp_char(data_union a, data_union b) 
{
	char first=a.char_data;
	char second=b.char_data;
	int result;
	result=strcmp(&first,&second);
	if (result<0)
	{
		return -1;	
	}
	if (result>0)
	{
		return 1;
	}
	return 0;
}

data_union create_char(void* value) 
{
	char letter;
    scanf(" %c",&letter);
    data_union union_letter;
    union_letter.char_data=letter;
    return union_letter;
}

// Word element

typedef struct DataWord {
	char *word;
	int counter;
} DataWord;

void dump_word(data_union data) 
{
	DataWord *dw = (DataWord *)data.ptr_data;
    printf("%s %d", dw->word, dw->counter);
}

void free_word(data_union data) 
{
	DataWord *dw = (DataWord *)data.ptr_data;
    free(dw->word);
    free(dw);
}

int cmp_word(data_union a, data_union b) 
{
	DataWord *dw_a = (DataWord *)a.ptr_data;
    DataWord *dw_b = (DataWord *)b.ptr_data;
    if(dw_a->word==dw_b->word)
	{
        return 0;
    }
    return strcmp(dw_a->word, dw_b->word);
}

size_t hash_word(data_union data, size_t size) {
	int s = 0;
	DataWord *dw = (DataWord*)data.ptr_data;
	char *p = dw->word;
	while (*p) {
		s += *p++;
	}
	return hash_base(s, size);
}

void modify_word(data_union *data) 
{
	DataWord *ptr=(DataWord *)data->ptr_data;
    ptr->counter++;
}

data_union create_data_word(void *value) 
{
	char *word=(char *)value;
    DataWord *ptr=(DataWord*)malloc(sizeof(DataWord));
    ptr->word = strdup(word);
    ptr->counter=1;
    data_union data;
    data.ptr_data=ptr;
    return data;
}

// read text, parse it to words, and insert these words to the hashtable
void stream_to_ht(hash_table *p_table, FILE *stream) 
{
	char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stream)) {
        char *word = strtok(buffer, " .,?!:;-\t\n\r\f\v");
        while (word != NULL) {
            for (int i = 0; word[i]; i++) {
                word[i] = tolower(word[i]);
            }
            data_union data = p_table->create_data(word);
            ht_element *element = get_element(p_table, &data);
            if (element != NULL) {
                p_table->modify_data(&(element->data));
            } else {
                insert_element(p_table, &data);
            }
            word = strtok(NULL, " .,?!:;-\t\n\r\f\v");
        }
    }
}

// test primitive type list
void test_ht(hash_table *p_table, int n) {
	char op;
	data_union data;
	for (int i = 0; i < n; ++i) {
		scanf(" %c", &op);
//		p_table->create_data(&data);
		data = p_table->create_data(NULL); // should give the same result as the line above
		switch (op) {
			case 'r':
				remove_element(p_table, data);
				break;
			case 'i':
				insert_element(p_table, &data);
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
}

int main(void) {
	int to_do, n;
	size_t index;
	hash_table table;
	char buffer[BUFFER_SIZE];
	data_union data;

	scanf ("%d", &to_do);
	switch (to_do) {
		case 1: // test integer hash table
			scanf("%d %zu", &n, &index);
			init_ht(&table, 4, dump_int, create_int, NULL, cmp_int, hash_int, NULL);
			test_ht(&table, n);
			printf ("%zu\n", table.size);
			dump_list(&table, index);
			break;
		case 2: // test char hash table
			scanf("%d %zu", &n, &index);
			init_ht(&table, 4, dump_char, create_char, NULL, cmp_char, hash_char, NULL);
			test_ht(&table, n);
			printf ("%zu\n", table.size);
			dump_list(&table, index);
			break;
		case 3: // read words from text, insert into hash table, and print
			scanf("%s", buffer);
			init_ht(&table, 8, dump_word, create_data_word, free_word, cmp_word, hash_word, modify_word);
			stream_to_ht(&table, stdin);
			printf ("%zu\n", table.size);
			data = table.create_data(buffer);
			ht_element *e = get_element(&table, &data);
			if (e) table.dump_data(e->data);
			if (table.free_data) table.free_data(data);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	//free_table(&table);

	return 0;
}

