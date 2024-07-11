#include <iostream> 
#include <cstdlib> 

struct IntPtr{
    int* p; 
    int ref_count; 
}; 

class HasPtr{
    private: 
        int n; 
        struct IntPtr* pIntPtr; 
    public: 
        HasPtr(int _n, int _val) : n(_n){
            pIntPtr = (struct IntPtr*)malloc(sizeof(struct IntPtr)); 
            if(pIntPtr == 0){
                std::cout << "AllocationError:struct IntPtr" << std::endl; 
                exit(EXIT_FAILURE); 
            }
            pIntPtr->p = (int*)malloc(sizeof(int)); 
            if(pIntPtr->p == 0){
                std::cout << "AllocationError:int" << std::endl; 
                exit(EXIT_FAILURE); 
            }
            pIntPtr->ref_count = 1;
            *pIntPtr->p = _val; 
        }
        void showRef()
        {
            std::cout<<pIntPtr->ref_count;
        }
        HasPtr(const HasPtr& other) : n(other.n), pIntPtr(other.pIntPtr){
            pIntPtr->ref_count += 1; 
        }

        HasPtr& operator=(const HasPtr& other){
            if(this != &other){
                this->pIntPtr->ref_count -= 1; 
                if(this->pIntPtr->ref_count == 0){
                    free(this->pIntPtr->p); 
                    free(this->pIntPtr); 
                }

                this->n = other.n; 
                this->pIntPtr = other.pIntPtr; 
                this->pIntPtr->ref_count += 1; 
            }
            return *this; 
        }

        

        ~HasPtr(){
            this->pIntPtr->ref_count -= 1; 
            if(this->pIntPtr->ref_count == 0){
                free(this->pIntPtr->p); 
                free(this->pIntPtr);
            }
        }
}; 

void test(void); 

int main(void){
    test(); 
    return EXIT_SUCCESS; 
}

void test()
{
    HasPtr p1(100,200);
    HasPtr p2(p1);
    HasPtr p3(300,400);
    p3=p1;
    p1.showRef();
    p3.showRef();
    HasPtr p4=p1;
    p1.showRef();
}

/*
    CLAIRTY IS BETTETER THAN CLEVERNESS! 
*/