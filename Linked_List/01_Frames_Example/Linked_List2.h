#ifndef LINKED_LIST2_H
#define LINKED_LIST2_H

typedef struct _ListElmt{
    void *data;
    struct _ListElmt *next;
}ListElmt;

typedef struct _List{
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    int size;

    struct ListElmt *head;
    struct ListElmt *tail;
}List;

void list_init(List *list);

void list_destroy(List *list);

void list_ins_next(List *list, ListElmt *elmt, void *data);

int list_rem_next(List *list, ListElmt *elmt, void **data);

#endif