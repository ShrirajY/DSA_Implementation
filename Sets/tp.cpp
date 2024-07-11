#include<iostream>
#include<string>
#include<cstring>

int main()
{
    std::string p="aksckja";
    char *str=(char *)malloc(sizeof(char)*p.length());
    str=*((char **)((void *)&p));
    std::cout<<str;
}