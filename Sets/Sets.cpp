#include<iostream>
#include<vector>
#include<cstring>
class Set{
    private:
        std::vector<void *> setList;
        std::vector<int>    typeList;
    public:
        int size()
        {
            return typeList.size();
        }

        void insert(int m)
        {
            if(this->is_Member(m)==1)
            {
                std::cout<<"Found Duplicate";
                return;
            }
            typeList.push_back(1);
            std::cout<<"Added"<<m<<std::endl;
            setList.push_back((void *)&m);
        }

        void insert(char m)
        {
            if(this->is_Member(m)==1)
            {
                return;
            }
            typeList.push_back(2);
            std::cout<<"Character"<<m;
            setList.push_back((void *)&m);
        }

        void insert(char* m)
        {
            if(this->is_Member(m)==1)
            {
                return;
            }
            typeList.push_back(3);
            setList.push_back((void *)&(*m));
        }

        void insert(std::string m)
        {
            if(this->is_Member(m)==1)
            {
                return;
            }
            typeList.push_back(4);
            setList.push_back((void *)&m);
        }
        
        void insert(void *p,int type)
        {
            if(this->is_Member(p)==1)
            {
                return;
            }
            typeList.push_back(type);
            setList.push_back(p);
        }

        int is_Member(int m)
        {
            // int *p=(int *)malloc(sizeof(int));
            int p;
            for(int i=0;i<this->size();i++)
            {
                p=*((int *)setList[i]);
                if(m==p)
                {
                    std::cout<<m<<" "<<p<<i;
                    // free(p);
                    return 1;
                }
            }
            return 0;
        }

        int is_Member(char m)
        {
            char *p=(char *)malloc(sizeof(char));
            for(int i=0;i<this->size();i++)
            {
                *p=*((char *)setList[i]);
                if(m==*p)
                {
                    free(p);
                    return 1;
                }
            }
            return 0;
        }

        int is_Member(std::string m)
        {
            std::string *p=(std::string *)malloc(sizeof(m));
            for(int i=0;i<this->size();i++)
            {
                *p=*((std::string *)setList[i]);
                std::cout<<*p;
                if(p->compare(m)==0)
                {
                    free(p);
                    return 1;
                }
            }
        }

        int is_Member(char *str)
        {
            char **p=(char **)malloc(sizeof(char)*strlen(str));
            for(int i=0;i<this->size();i++)
            {
                *p=((char *)setList[i]);
                printf("%s",*p);
                if(strcmp(str,*p)==0)
                {
                    free(p);
                    return 1;
                }
            }
        }

        int is_Member(void *val)
        {
            void **p=(void **)malloc(sizeof(void *));
            for(int i=0;i<this->size();i++)
            {
                *p=((void *)setList[i]);
                if(is_Match(val,*p)==1)
                {
                    return 1;
                }
            }
        }

        int is_Match(void *key1,void *key2)
        {
            int *k1=(int *)malloc(sizeof(int));
            int *k2=(int *)malloc(sizeof(int));

            *k1=*((int *)key1);
            *k2=*((int *)key2);
            if((*k1)==(*k2))
            {
                free(k1);
                free(k2);
                return 1;
            }
            free(k1);
            free(k2);
            char *c1=(char *)malloc(sizeof(char));
            char *c2=(char *)malloc(sizeof(char));

            *c1=*((char *)key1);
            *c2=*((char *)key2);

            if((*c1)==(*c2))
            {
                free(c1);
                free(c2);
                return 1;
            }
            free(c1);
            free(c2);
        }

        Set Union(Set s2)
        {
            std::vector<void *> *set2;
            *set2=s2.get();
            int *p;
            for(int i=0;i<(*set2).size();i++)
            {
                this->insert((*set2)[i],s2.getType(i));
            }
        }

        std::vector<void *> get()
        {
            return setList;
        }

        int getType(int i)
        {
            return typeList[i];
        }

        void show()
        {
            for(int i=0;i<this->size();i++)
            {
                if(typeList[i]==1)
                {
                    std::cout<<"Integer";
                    std::cout<<*(int *)setList[i];
                }
                if(typeList[i]==2)
                {
                    std::cout<<"Character";
                    std::cout<<*(char *)setList[i];
                }
                if(typeList[i]==3)
                {
                    std::cout<<*(int *)setList[i];
                }
                if(typeList[i]==4)
                {
                    std::cout<<*(int *)setList[i];
                }
                std::cout<<"anything";
            }
        }
};

int main()
{
    Set *s=new Set;
    // int p=10;
    // s.insert((void *)&p);
    // int m=s.is_Member(10);
    // char c='a';
    // std::cout<<m<<std::endl;
    // s.insert((void *)&c);
    // m=s.is_Member('a');
    // std::cout<<m;
    // std::string str="Hello,World";
    // s.insert((void *)&str);
    // std::string o="Hello,World";
    // int n=s.is_Member(o);
    // std::cout<<"this"<<n<<"This";

    // char *str=(char *)malloc(sizeof(char)*(strlen("Hello")+1));
    // strcpy(str,"Hello");
    // s.insert(str);
    // char *str2=(char *)malloc(sizeof(char)*(strlen("Hello")+1));
    // strcpy(str2,"Hello");
    // int m=9;
    // m=s.is_Member(str2);
    // std::cout<<m;
    int m=5;
    int *p=&m;
    int l=6;
    int *p1=&l;

    s->insert((void *)p,1);
    s->insert((void *)p1,1);
    std::cout<<s->size();
    // std::cout<<s.is_Member(m);
    // s.show();
}