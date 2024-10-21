#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    double *results;
    int len;
}Data;

typedef struct tagQueueElement{
    Data *data;
    struct tagQueueElement *next;
}QueueElement;

typedef struct{
	QueueElement *head;
	QueueElement *tail;
}Queue;


void free_queue(Queue *pqueue)
{
	QueueElement *nowa=pqueue->head;
	QueueElement *nowa_next;
	while (nowa!=NULL)
	{
		nowa_next=nowa->next;
		free(nowa);
		nowa=nowa_next;
	}
	free (pqueue);
}

void push_copy(Queue *pqueue, const Data *pdata)
{
	QueueElement *nowa;
	nowa=(QueueElement*)malloc(sizeof(QueueElement));
	pqueue->tail->next=nowa;
	nowa->next=NULL;
	nowa->data=(Data*)pdata;	
}

int peek(const  Queue *pqueue, Data *pdata)
{
    if(pqueue->head==NULL)
    {
        return 0;
    }
    pdata=(Data*)pqueue->head->data;
    return 1;
}


int pop(Queue *pqueue, Data *pdata)
{
	if (peek(pqueue,pdata)==0)
	{
		return -1;
	}
	QueueElement *to_delete=pqueue->head;
	pqueue->head=pqueue->head->next;
	free (to_delete);
	if (pqueue->head==NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int get_total_count(const Queue *pqueue)
{
	int result=0;
	QueueElement *nowa=(QueueElement*)pqueue->head;
	while (nowa!=NULL)
	{
		result+=nowa->data->len;
		nowa=nowa->next;
	}
	return result;
}

int main()
{
	
}
