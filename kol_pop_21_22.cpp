#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *name;
	char *surname;
	char pesel[12];	
}Person;

typedef struct PersonList{
	Person *current;
	struct PersonList *next;
	struct PersonList *prev;
}PersonList;

void init_pl(PersonList *p_pl)
{
	PersonList *nowa;
	nowa=(PersonList*)malloc(sizeof(PersonList));
	nowa->current=(Person*)malloc(sizeof(Person));
	nowa->next=NULL;
	nowa->prev=NULL;
	p_pl=nowa;
}

void free_pl(PersonList *p_pl)
{
	while (p_pl->next!=NULL)
	{
		p_pl=p_pl->next;
	}
	PersonList *earlier=p_pl->prev;
	while (p_pl->prev!=NULL)
	{
		free(p_pl->current);
		free(p_pl);
		p_pl=earlier;
		earlier=p_pl->prev;
	}
	free(p_pl->current);
	free(p_pl);
}

void fill_person_data(Person *p_p, const char *pesel, const char *name, const char *surname)
{
	Person *nowa;
	nowa=(Person*)malloc(sizeof(Person));
	nowa->name=(char*)name;
	//strcpy (nowa->name,name)
	//memcpy(nowa->name,name,sizeof(name));
	*nowa->surname=*surname;
	strcpy(nowa->pesel, pesel);
	p_p=nowa;
}

Person *find(const PersonList *p_pl, const char *pesel)
{
	Person *nowa;
	nowa=(Person*)malloc(sizeof(Person));
	PersonList *nowalist;
	nowalist=(PersonList*)malloc(sizeof(PersonList));
	nowalist=(PersonList*)p_pl;
	while (nowalist!=NULL)
	{
		if (strcmp(nowalist->current->pesel,pesel)==0)
		{
			nowa=nowalist->current;
			return nowa;
		}
		nowalist=nowalist->next;
	}
	return NULL;
}

int add(PersonList *p_pl, const char *pesel, const char *name, const char *surname)
{
	Person *checked;
	checked=(Person*)malloc(sizeof(Person));
	checked=find(p_pl,pesel);
	if (checked==NULL)
	{
		PersonList *nowalist;
		nowalist=(PersonList*)malloc(sizeof(PersonList));
		nowalist=p_pl;
		while (nowalist->next!=NULL)
		{
			nowalist=nowalist->next;
		}
		PersonList *temp;
		init_pl(temp);
		temp->prev=nowalist;
		nowalist->next=temp;
		temp->current=checked;
		return 0;
	}
	else
	{
		checked->name=(char*)name;
		checked->surname=(char*)surname;
		strcpy(checked->pesel,pesel);
		return 1;
	}
}

void merge(PersonList *p_target, const PersonList *p_src)
{
	PersonList *nowa;
	nowa=(PersonList*)malloc(sizeof(PersonList));
	nowa=(PersonList*)p_src;
	while (nowa!=NULL)
	{
		add(p_target, nowa->current->pesel, nowa->current->name, nowa->current->surname);
		nowa=nowa->next;
	}
}

int main (){
}


