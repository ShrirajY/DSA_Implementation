#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n=10;
    int *ptr=&n;
    void *key1=(void *)ptr;

    printf("%d",*((int *)key1));
}