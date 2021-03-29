#include <iostream>
#include <memory>

struct B
{
    void Sum() {++i;}
    int i;
};

class A
{
    public:
    A(B& b) : b4{b} {}
    void doSomething() const
    {
        b1->Sum();      // pointer or references can modify
        //b2.Sum();     // not possible, pointers are treated different
        b3->Sum();      // pointer or references can modify
        b4.Sum();       // pointer or references can modify
        a++;            // mutuable member can be modified 
    }
    
    private:
    B* b1;
    B b2;
    std::unique_ptr<B> b3;
    B& b4;
    mutable int a{};
};

int main()
{
    return 0;
}
