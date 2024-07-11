#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct ListElmt_{
    void *data;
    struct ListElmt_ *next;
}ListElmt;

typedef struct List_{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    ListElmt *head;
    ListElmt *tail;
}List;

void List_init(List *list,void (*destroy)(void *data));

void List_destroy(List *list);

void List_ins_next(List *list, ListElmt *elmt,void *data);

int List_rem_next(List *list, ListElmt *elmt, void **data);

int main()
{

}

void List_init(List *list,void (*destroy)(void *data)){
    list->destroy=destroy;
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
}

void List_destroy(List *list)
{
    void *data;

    while(list->size>0)
    {
        if(List_rem_next(list,NULL,(void **)data)==0)
        {
            List_destroy(list);
        }
    }

    memset(list,0,sizeof(list));
}

void List_ins_next(List *list, ListElmt *elmt, void *data)
{
    ListElmt *new_elmt;
    if((new_elmt=(ListElmt *)malloc(sizeof(ListElmt)))==NULL)
    {
        return;
    }

    if(elmt==NULL)
    {
        if(list->size==0)
        {
            list->tail=new_elmt;
        }
        new_elmt->next=list->head;
        list->head=new_elmt;
    }

    else
    {
        if(elmt->next==NULL)
        {
            list->tail=new_elmt;
        }
        new_elmt->next=elmt->next;
        elmt->next=new_elmt;
    }

    list->size++;
    return;
}

int List_rem_next(List *list, ListElmt *elmt, void **data)
{
    ListElmt *old_elmt;
    if(list->size==0)
    {
        return -1;
    }

    if(elmt==NULL)
    {
        *data=list->head->data;
        old_elmt=list->head;
        list->head=list->head->next;
    }

    else
    {
        if(elmt->next==NULL)
        {
            return -1;
        }

        old_elmt=elmt->next;
        *data=old_elmt->data;
        elmt->next=old_elmt->next;
        if(elmt->next==NULL)
        {
            list->tail=elmt;
        }
    }

    free(old_elmt);
    list->size--;
    return;
}