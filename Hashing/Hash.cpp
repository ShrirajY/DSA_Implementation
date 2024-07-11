#include<iostream>

int matching(const void *key1, const void *key2)
{
    if(*((int *)key1)==*((int *)key2))
    {
        return 1;
    }
    return 0;
}

class ListElmt{
    public:
        void *data;
        ListElmt *next;
    public:
        ListElmt(void *_data)
        {
            this->data=(void *)_data;
            this->next=NULL;
        }
        ListElmt()
        {

        }
};

class List{
    private:   
        ListElmt *head;
        ListElmt *tail;
        int size;
    public:
        List()
        {
            head=(ListElmt *)malloc(sizeof(ListElmt));
            // tail=(ListElmt *)malloc(sizeof(ListElmt));
            head->data=(void *)0;
            size=0;
            tail=head;
        }

        List(int _data)
        {
            head=(ListElmt *)malloc(sizeof(ListElmt));
            int *data=(int *)malloc(sizeof(int));
            *data=_data;
            head->data=(void *)(&(*data));
            tail=head;
            size=1;
        }
        ListElmt Head()
        {
            return *head;
        }

        ListElmt Tail()
        {
            return tail;
        }

        int Size()
        {
            return size;
        }

        int InsNext(int _data)
        {
            int *data=(int *)malloc(sizeof(int));
            *data=_data;
            ListElmt *newElmt=new ListElmt((void *)(&(*data)));
            if(newElmt==NULL)
            {
                return -1;
            }
            tail->next=newElmt;
            tail=newElmt;
            size++;
            return 1;
        }

        int InsBetween(int _data,ListElmt *elmt)
        {
            int *data=(int *)malloc(sizeof(int));
            *data=_data;
            ListElmt *newElmt=new ListElmt((void *)(&(*data)));
            if(newElmt==NULL)
            {
                return -1;
            }

            if(elmt==NULL)
            {
                newElmt->next=head;
                head=newElmt;
                size++;
                return 1;
            }

            newElmt->next=elmt->next;
            if(newElmt->next==NULL)
            {
                tail=newElmt;
            }
            elmt->next=newElmt;
            size++;
            return 1;
        }

        int InsHead(int _data)
        {
            return InsBetween(_data,NULL);
        }

        ListElmt showIndex(int i)
        {
            int p=0;
            ListElmt *temp=head;
            while(p!=i)
            {
                temp=temp->next;
                p++;
            }
            return *temp;
        }

        void show()
        {
            ListElmt *temp=head;
            while(temp!=NULL)
            {
                std::cout<<*((int *)temp->data);
                temp=temp->next;
            }
        }
};

class cHTable{
    private:
        int buckets;
        int (*match)(const void *key1,const void *key2)=matching;
        int size;
        List **lists;
    public:
        cHTable(int _buckets)
        {
            this->buckets=_buckets;
            lists=(List **)malloc(sizeof(List *)*buckets);
            for(int i=0;i<buckets;i++)
            {
                lists[i]=(List *)malloc(sizeof(List));
                List *temp=new List(100);
                lists[i]=temp;
            }
        }

        void Insert(int _data)
        {
            int hash=_data%buckets;
            lists[hash]->InsNext(_data);
        }

        void show(int index)
        {
            lists[index]->show();
        }
};


int main()
{
    // List *list=new List(5);
    // list->InsNext(6);
    // list->InsNext(7);
    // // list->show();
    // ListElmt temp=list->showIndex(1);
    // // *temp=list->showIndex(1);
    // std::cout<<*((int *)temp.data);

    cHTable Table(5);
    Table.Insert(9);
    Table.Insert(19);
    Table.show(4);
}