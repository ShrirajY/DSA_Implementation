#include <stdio.h>
#include<stdlib.h>
#include "Linked_List2.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size=0;
    list->head=NULL;
    list->tail=NULL;
    list->destroy=destroy;
}

void list_destroy(List *list)
{
    void *data;

    while(list->size>0)
    {
        if(list_rem_next(list, NULL, (void **)data)==0)
        {
            list_destroy(list);
        }

    }
}

void list_ins_next(List *list, ListElmt *elmt, void *data)
{
    ListElmt *new_elmt;

    if((new_elmt=(ListElmt *)malloc(sizeof(ListElmt)))==NULL)
    {
        return -1;
    }
    new_elmt->data=(void *)data;
    if(elmt==NULL)
    {
        if(list->size==0)
        {
            list->tail=new_elmt;
            new_elmt->next=NULL;
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