#include <iostream>
#include <cstring>
#include <vector>

class Set
{
private:
    std::vector<void *> setList;
    std::vector<int> typeList;

public:
    int size()
    {
        return setList.size();
    }

    int type(int i)
    {
        return typeList[i];
    }

    void* val(int i)
    {
        return setList[i];
    }


    void insert(int m)
    {
        int *y=(int *)malloc(sizeof(int));
        *y=m;
        // int *p=&(*y);
        this->insert((void *)(&(*y)),1);
    }
    void insert(char c)
    {
        char *y=(char *)malloc(sizeof(char));
        *y=c;
        this->insert((void *)(&(*y)),2);
    }

    void insert(char *s)
    {
        // char **y=(char **)malloc(sizeof(char *)*strlen(s));
        this->insert((void *)s,3);
    }
    
    void insert(void *p, int type)
    {
        if (is_Member(p, type) == 1)
        {
            return;
        }
        // std::cout<<"added";
        setList.push_back(p);
        typeList.push_back(type);
    }

    int match(void *p1, void *p2, int type)
    {
        if (type == 1)
        {
            int v1 = *((int *)p1);
            int v2 = *((int *)p2);
            // std::cout<<"Trying  "<<v1<<"  "<<v2<<std::endl;
            if (v1 == v2)
            {
                // std::cout<<"rejected\n";
                return 1;
            }
            return 0;
        }
        else if (type == 2)
        {
            char v1 = *((char *)p1);
            char v2 = *((char *)p2);

            if (v1 == v2)
            {
                return 1;
            }
            return 0;
        }

        else if (type == 3)
        {
            char *v1 = ((char *)p1);
            char *v2 = ((char *)p2);
            if (strcmp(v1, v2) == 0)
            {
                return 1;
            }
            return 0;
        }
    }

    int is_Member(void *p, int type)
    {
        // std::cout<<"\nSize"<<setList.size()<<"\n";
        for (int i = 0; i < setList.size(); i++)
        {
            if (typeList[i] == type)
            {
                if(match(setList[i], p, type)==1)
                {
                    return 1;
                }
            }
        }
        return 0;
    }

    Set Union(Set other)
    {
        Set s3;
        for(int i=0;i<other.size();i++)
        {
            s3.insert(other.val(i),other.type(i));
        }
        for(int i=0;i<this->size();i++)
        {
            s3.insert(this->val(i),this->type(i));
        }
        return s3;
    }

    Set Intersection(Set other)
    {
        Set s3;
        for(int i=0;i<other.size();i++)
        {
            if((this->is_Member(other.val(i),other.type(i)))==1)
            {
                s3.insert(other.val(i),other.type(i));
            }
        }
        return s3;
    }

    Set Set_Difference(Set other)
    {
        Set s3;
        for(int i=0;i<this->size();i++)
        {
            if(other.is_Member(this->val(i),this->type(i))==1)
            {
                continue;
            }

            else
            {
                s3.insert(this->val(i),this->type(i));
            }
        }
        return s3;
    }
    void show()
    {
        for (int i = 0; i < setList.size(); i++)
        {
            if (typeList[i] == 1)
            {
                std::cout << *((int *)setList[i]) << "\t";
            }
            else if (typeList[i] == 2)
            {
                std::cout << *((char *)setList[i]) << "\t";
            }
            else if (typeList[i] == 3)
            {
                std::cout << ((char *)setList[i]) << "\t";
            }
            else if(typeList[i]==4)
            {
                std::cout<<*((std::string *)setList[i])<<"\t";
                // std::cout<<*((char **)typeList[i]);
                // std::cout << ((char *)setList[i]) << "\t";
                // *((char **)((void *)&p));
            }
        }
        std::cout<<std::endl<<std::endl;
    }
};

class TypeId
{
    int Identify(char *input)
    {
        

        std::cin >> input;
        int type = 0;
        if (strlen(input) == 1 && (input[0] < 48 || input[0] > 57))
        {
            type = 2;
        }
        for (int i = 0; i < strlen(input); i++)
        {
            if (input[i] < 48 || input[i] > 57)
            {
                type = 3;
            }
        }
        // std::cout<<strlen(input);
        return type;
    }
};
int main()
{
    Set s;
    char *io=(char *)malloc(sizeof(char)*strlen("Hello"));
    strcpy(io,"Hello");
    s.insert(io);
    // s.insert(p);
    Set s2;

    s2.insert(5);
    s2.insert(500);
    s.insert(600);
    s.insert('c');
    s2.insert('c');
    s2.insert(600);
    s.insert('a');
    s2.insert('a');
    // s.show();

    Set s3=s.Union(s2);
    Set s4=s.Intersection(s2);
    Set s5=s.Set_Difference(s2);
    std::cout<<"Set1  ";
    s.show();
    std::cout<<"Set2  ";
    s2.show();
    std::cout<<"Set3  ";
    s3.show();
    std::cout<<"Set4  ";
    s4.show();
    std::cout<<"Set5  ";
    s5.show();
}