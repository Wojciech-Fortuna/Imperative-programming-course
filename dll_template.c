#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// list node
typedef struct Node {
	int *data;
	size_t array_size;
	struct Node* next;
	struct Node* prev;
} Node;

// doubly linked list
typedef struct List {
	Node *head;
	Node *tail;
} List;

// iterator
typedef struct iterator {
	struct Node* node_ptr;
	size_t position;
} iterator;

// forward initialization
iterator begin(Node* head) {
	iterator it = { head, 0 };
	return it;
}

// backward initialization;
// points to the element following the last one
iterator end(Node* tail) {
	iterator it = { tail, tail->array_size };
	return it;
}

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);
	if (ptr) return ptr;
	exit(EXIT_FAILURE);
}

void *safe_realloc(void *old_ptr, size_t size) {
	void *ptr = realloc(old_ptr, size);
	if (ptr) return ptr;
	free(old_ptr);
	exit(EXIT_FAILURE);
}

Node *create_node(int *data, size_t array_size, Node *next, Node *prev) {
	Node *node = safe_malloc(sizeof(Node));
	node->data = data;
	node->array_size = array_size;
	node->next = next;
	node->prev = prev;
	return node;
}

// initialize list
// creates the front and back sentinels
void init(List *list) {
	list->head = create_node(NULL, 0, NULL, NULL);
	list->tail = create_node(NULL, 0, NULL, list->head);
	list->head->next = list->tail;
}

// to implement ...

// append node to the list
void push_back(List *list, int *data, size_t array_size) 
{
	Node *new=create_node(data,array_size,NULL,NULL);
	list->tail->prev->next=new;
	new->prev=list->tail->prev;
	list->tail->prev=new;
	new->next=list->tail;
}

// set iterator to move n elements forward from its current position
void skip_forward(iterator* itr, size_t n) 
{
	while (n>0)
	{
		Node* new_ptr=itr->node_ptr->next;
		itr->node_ptr=new_ptr;
		size_t tab_array=itr->node_ptr->array_size;
		if (n>tab_array)
		{
			n-=tab_array;
		}
		else
		{
			itr->position=n-1;
			n=0;
		}
	}
}

// forward iteration - get n-th element in the list
int get_forward(List *list, size_t n) 
{
	iterator it={list->head,0};
	skip_forward(&it, n);
	return it.node_ptr->data[it.position];
}

// set iterator to move n elements backward from its current position
void skip_backward(iterator* itr, size_t n) {
	while (n>0)
	{
		Node* new_ptr=itr->node_ptr->prev;
		itr->node_ptr=new_ptr;
		size_t tab_array=itr->node_ptr->array_size;
		if (n>tab_array)
		{
			n-=tab_array;
		}
		else
		{
			itr->position=tab_array-n;
			n=0;
		}
	}
}

// backward iteration - get n-th element from the end of the list
int get_backward(List *list, size_t n) {
	iterator it={list->tail,0};
	skip_backward(&it, n);
	return it.node_ptr->data[it.position];
}

void remove_node(Node *node_ptr) {
}

// remove n-th element; if array empty remove node
void remove_at(List *list, size_t n) 
{
	iterator it={list->head,0};
	skip_forward(&it, n);
	if (it.node_ptr->array_size>1)
	{
		for (size_t i=it.position+1; i<it.node_ptr->array_size; i++)
		{
			it.node_ptr->data[i-1]=it.node_ptr->data[i];
		}
		it.node_ptr->array_size-=1;
	}
	else
	{
		if (it.node_ptr->prev==NULL)
		{
			list->head=list->head->next;
			list->head->prev=NULL;
		}
		else if (it.node_ptr->next==NULL)
		{
			list->tail=list->tail->prev;
			list->tail->next=NULL;
		}
		else
		{
			it.node_ptr->prev->next=it.node_ptr->next;
			it.node_ptr->next->prev=it.node_ptr->prev;
		}
	}	
}

// return the number of digits of number n
size_t digits(int n) 
{
	if (n==0)
	{
		return 1;
	}
	int length=0;
	while (n!=0)
	{
		n=n/10;
		length+=1;
	}
	//printf ("a %d",length);
	return length;
}

// inserts 'value' to the node with the same digits' count
// otherwise insert new node
void put_in_order(List *list, int value) 
{
	int done=0;
	for(Node *node = list->head->next; node != list->tail; node = node->next)
	{
		if (digits(node->data[0])==digits(value) && done==0)
		{
			node->data=safe_realloc(node->data, (node->array_size+1)*sizeof(int));
			node->array_size+=1;
			for (size_t i=0; i<node->array_size-1; i++)
			{
				if (value<node->data[i] && done==0)
				{
					for (int j=node->array_size-1; j>i; j--)
					{
						node->data[j]=node->data[j-1];
					}
					node->data[i]=value;
					done=1;
				}
			}
			if (done==0)
			{
				node->data[node->array_size-1]=value;
				done=1;
			}
		}
		else if (digits(node->data[0])>digits(value) && done==0)
		{
			int *tab = (int*) safe_malloc(sizeof(int));
			tab[0]=value;
			Node *new=create_node(tab,1,node,node->prev);
			new->next->prev=new;
			new->prev->next=new;
			done=1;
		}
	}
	if (done==0)
	{
		int *tab = (int*) safe_malloc(sizeof(int));
		tab[0]=value;
		Node *new=create_node(tab,1,list->tail,list->tail->prev);
		list->tail->prev->next=new;
		list->tail->prev=new;
	}
}

// -------------------------------------------------------------
// helper functions

// print list
void dumpList(const List *list) {
	for(Node *node = list->head->next; node != list->tail; node = node->next) {
		printf("-> ");
		for (int k = 0; k < node->array_size; k++) {
			printf("%d ", node->data[k]);
		}
		printf("\n");
	}
}

// free list
void freeList(List *list) {
	Node *to_delete = list->head->next, *next;
	while(to_delete != list->tail) {
		next = to_delete->next;
		remove_node(to_delete);
		to_delete = next;
	}
}

// read int vector
void read_vector(int tab[], size_t n) {
	for (size_t i = 0; i < n; ++i) {
		scanf("%d", tab + i);
	}
}

// initialize the list and push data
void read_list(List *list) {
	int n;
	size_t size;
	scanf("%d", &n); // number of nodes
	for (int i = 0; i < n; i++) {
		scanf("%zu", &size); // length of the array in i-th node
		int *tab = (int*) safe_malloc(size * sizeof(int));
		read_vector(tab, size);
		push_back(list, tab, size);
	}
}

int main() {
	int to_do, value;
	size_t size, m;
	List list;
	init(&list);

	scanf("%d", &to_do);
	switch (to_do) {
		case 1:
			read_list(&list);
			dumpList(&list);
			break;
		case 2:
			read_list(&list);
			scanf("%zu", &size);
			for (int i = 0; i < size; i++) {
				scanf("%zu", &m);
				printf("%d ", get_forward(&list, m));
			}
			printf("\n");
			break;
		case 3:
			read_list(&list);
			scanf("%zu", &size);
			for (int i = 0; i < size; i++) {
				scanf("%zu", &m);
				printf("%d ", get_backward(&list, m));
			}
			printf("\n");
			break;
		case 4:
			read_list(&list);
			scanf("%zu", &size);
			for (int i = 0; i < size; i++) {
				scanf("%zu", &m);
				remove_at(&list, m);
			}
			dumpList(&list);
			break;
		case 5:
			scanf("%zu", &size);
			for (int i = 0; i < size; i++) {
				scanf("%d", &value);
				put_in_order(&list, value);
			}
			dumpList(&list);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	freeList(&list);

	return 0;
}
