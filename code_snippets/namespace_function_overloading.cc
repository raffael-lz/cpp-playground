#include <iostream>
#include <string>

namespace bar
{
    void f(float a)
    {
        std::cout << "bar::f" << std::endl;
    }
}

namespace foo
{

    //using namespace bar; // this does not work
    using bar::f; // this works
    void f(std::string a)
    {
        std::cout << "foo:f" << std::endl;
    }

    void t()
    {
        //using bar::f; // why this does not work
        //using namepsace bar; // why this does not work
        int a {2};
        f(std::string {"t"});       // calls foo:f
        f(a);                       // calls bar:f
    }
}

int main()
{
    foo::t();
}
