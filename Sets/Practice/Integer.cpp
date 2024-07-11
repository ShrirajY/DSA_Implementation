#include <iostream>
#include <cstdlib>
#include <vector>
struct IntPtr
{
    int p;
    int ref_count;
};

class Globals
{
private:
    std::vector<IntPtr> GlobalVec;

public:
    void push_BackPtr(int val)
    {
        int spare=GlobalVec.size();
        int flag = 0;
        for (int i = 0; i < GlobalVec.size(); i++)
        {
            if (val == GlobalVec[i].p)
            {
                spare = i;
                flag = 1;
                break;
            }
            if (val < GlobalVec[i].p)
            {
                spare=i;
                break;
            }
        }

        if (flag == 0)
        {
            struct IntPtr ptr;
            ptr.p = val;
            ptr.ref_count = 0;
            GlobalVec.push_back(ptr);
            for (int i = GlobalVec.size()-1; i > spare; i--)
            {
                GlobalVec[i] = GlobalVec[i - 1];
            }
            GlobalVec[spare] = ptr;
        }
        GlobalVec[spare].ref_count++;
    }
    void pop_backPtr(int val)
    {
        int spare;
        int flag = 0;
        for (int i = 0; i < GlobalVec.size(); i++)
        {
            if (val == GlobalVec[i].p)
            {
                spare = i;
                flag = 1;
                break;
            }
            if (val < GlobalVec[i].p)
            {
                break;
            }
        }

        if (flag == 0)
        {
            std::cout << "Value not found" << std::endl;
            return;
        }
        GlobalVec[spare].ref_count--;
        if (GlobalVec[spare].ref_count == 0)
        {
            for (int i = spare; i < GlobalVec.size() - 1; i++)
            {
                GlobalVec[i] = GlobalVec[i + 1];
            }
            GlobalVec.pop_back();
        }
    }
    void show()
    {
        for(int i=0;i<GlobalVec.size();i++)
        {
            std::cout<<GlobalVec[i].p<<" :: "<<GlobalVec[i].ref_count<<std::endl;
        }
    }
};

Globals gloabals;
class Int
{
    private:
        int m;
    public:
        Int()
        {
            this->m=0;
            gloabals.push_BackPtr(m);
        }

        Int(int m)
        {
            this->m=m;
            gloabals.push_BackPtr(m);
        }
        
        Int(const Int& p)
        {
            this->m=p.m;
            gloabals.push_BackPtr(m);
        }   

        Int& operator=(int n)
        {
            gloabals.pop_backPtr(this->m);
            this->m=n;
            gloabals.push_BackPtr(n);
        }

        Int& operator=(Int n)
        {
            gloabals.pop_backPtr(this->m);
            this->m=n.m;
            gloabals.push_BackPtr(n.m);
            gloabals.pop_backPtr(n.m);
            return *this;
        }
};

int main()
{
    Int p(8);
    Int o(8);
    Int z=65;
    // y=p;
    Int l;
    l=56;
    o=p;
    o=p;
    p=o;
    // Int l;
    // l=o;
    l=58;
    Int y(10);
    gloabals.show();
}