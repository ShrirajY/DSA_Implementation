#include <stdlib.h>
#include<string.h>
#include<stdio.h>
#include "Linked_List.h"

void list_init(List *list, void (*destroy)(void *data)){
    list->size=0;
    list->destroy=destroy;
    list->head=NULL;
    list->tail=NULL;

    return;
}

void list_destroy(List *list){
    void *data;

    while(list_size(list)>0){
        if(list_rem_next(list,NULL,(void **)&data)==0 && list_destroy !=NULL){
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(List));

    return;
}

int list_ins_next(List *list, ListElmt *elmt, const void *data)
{
    ListElmt *new_elmt;

    if((new_elmt=(ListElmt *)malloc(sizeof(ListElmt)))==NULL)
    {
        return -1;
    }

    new_elmt->data=(void *)data;

    if(elmt==NULL)
    {
        if(list_size(list)==0)
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
    return 0;
}

int list_rem_next(List *list, ListElmt *elmt, void **data)
{
    ListElmt *old_elmt;

    if(list_size(list)==0)
    {
        return -1;
    }

    if(elmt==NULL)
    {
        *data=list->head->data;
        old_elmt=list->head;
        list->head=list->head->next;

        if(list_size(list)==1)
        {
            list->tail=NULL;
        }
    }

    else
    {
        if(elmt->next==NULL)
        {
            return -1;
        }

        *data=elmt->next->data;

        old_elmt=elmt->next;
        elmt->next=elmt->next->next;

        if(elmt->next==NULL)
        {
            list->tail=elmt;
        }
    }

    free(old_elmt);

    list->size--;

    return 0;
}
