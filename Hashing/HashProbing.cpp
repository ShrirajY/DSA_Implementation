#include<iostream>

char Vacate='v';
class OHTable{
    private:
        int positions;
        void *vacated;
        void **table;
        int size;
    public:
        OHTable(int _pos)
        {
            size=0;
            this->positions=_pos;
            table=(void **)malloc(sizeof(void *)*positions);
            for(int i=0;i<positions;i++)
            {
                table[i]=NULL;
            }
            vacated=&Vacate;
        }

        int Hash(int a)
        {
            return a%positions;
        }

        // int Insert(int a)
        // {
        //     if(size==positions)
        //     {
        //         std::cout<<"Not enough space"<<std::endl;
        //         return -1;
        //     }
        //     if(isPresent(a)==1)
        //     {
        //         std::cout<<"Already present"<<std::endl;
        //         return 1;
        //     }


        //     int *ptr=(int *)malloc(sizeof(int));
        //     *ptr=a;
        //     int ans=Hash(a);
        //     int flag=0;

        //     for(int i=0;i<positions;i++)
        //     {
        //         if(table[ans+i]==NULL || table[ans+i]==vacated)
        //         {
        //             table[ans+i]=(void *)(&(*ptr));
        //             break;
        //         }
        //     }
        // }

        int Insert(int a)
        {
            if(size==positions)
            {
                std::cout<<"Spaces Added"<<std::endl;
                positions=positions+positions;

                table=(void **)realloc(table,sizeof(void *)*positions);
                for(int i=positions/2;i<positions;i++)
                {
                    table[i]=NULL;
                }

                // return -1;
            }
            if(isPresent(a)==1)
            {
                std::cout<<"Already present"<<std::endl;
                return 1;
            }


            int *ptr=(int *)malloc(sizeof(int));
            *ptr=a;
            int ans=Hash(a);
            int flag=0;

            for(int i=0;i<positions;i++)
            {
                if(table[(ans+i)%positions]==NULL || table[(ans+i)%positions]==vacated)
                {
                    table[(ans+i)%positions]=(void *)(&(*ptr));
                    size++;
                    break;
                }
            }
        }

        int Remove(int a)
        {
            int ans=IndexPresent(a);
            if(ans==-1)
            {
                std::cout<<"No such element present"<<std::endl;
                return -1;
            }
            table[ans]=vacated;
            return 1;
        }
        void show()
        {
            for(int i=0;i<positions;i++)
            {
                if(table[i]==vacated)
                {
                    std::cout<<"vacated"<<std::endl;
                    continue;
                }
                else if(table[i]==NULL)
                {
                    std::cout<<"NULL"<<std::endl;
                    continue;
                }
                else
                {
                    std::cout<<*((int *)table[i])<<std::endl;
                }
            }
            std::cout<<size;
        }
        int isMatch(void *ptr, int a)
        {
            int temp=*((int *)ptr);
            if(temp==a)
            {
                return 1;
            }
            return -1;
        }

        int isPresent(int a)
        {
            int ans=Hash(a);
            for(int i=0;i<positions;i++)
            {
                if(table[(ans+i)%positions]==NULL)
                {
                    return -1;
                }

                else if(isMatch(table[(ans+i)%positions],a)==1)
                {
                    return 1;
                }
            }
            return -1;
        }

        int IndexPresent(int a)
        {
            int ans=Hash(a);
            for(int i=0;i<positions;i++)
            {
                if(table[(ans+i)%positions]==NULL)
                {
                    return -1;
                }

                else if(isMatch(table[(ans+i)%positions],a)==1)
                {
                    return ans+i;
                }
            }
            return -1;
        }
};

int main()
{
    OHTable t(5);
    t.Insert(4);
    t.Insert(6);
    t.Insert(5);
    t.Insert(3);
    t.Insert(9);
    t.Insert(10);
    t.Insert(8);
    // t.Insert(6);
    // t.Remove(6);
    t.show();
}