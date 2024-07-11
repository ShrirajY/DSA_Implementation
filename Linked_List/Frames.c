#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Linked_List.h"

int alloc_frame(List *frames)
{
    int frame_number,*data;

    if(frames->size==0)
    {
        return -1;
    }

    else
    {
        if(list_rem_next(frames,NULL,(void **)&data)!=0)
        {
            return -1;
        }
        else
        {
            frame_number= *data;
            free(data);
        }
    }
    return frame_number;
}

int free_frame(List *frames, int frame_no)
{
    int *data;

    if((data==(int *)malloc(sizeof(int)))==NULL)
    {
        return -1;
    }

    *data=frame_no;

    if(list_rem_next(frames, NULL, data)!=0)
    {
        return -1;
    }
    return 0;
}