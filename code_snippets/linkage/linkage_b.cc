#include <iostream>

extern int a;               // links agains global declared a
constexpr int var = 2;      // constexpr is only visible for this translation unit

// f is declared here in global scope. In global there can be only one delcaration
// even linkage_b.cc is not included anywhere, only because of linking process, g() can access f()
void f()
{
    std::cout << __FILE_NAME__ <<"::"<< __FUNCTION__ << " enter: "<< std::endl;

    std::cout << "var(2): " << var << std::endl;
    std::cout << "a(4): " << a << std::endl;

    std::cout << __FILE_NAME__ << "::" << __FUNCTION__ << " exit: "<< std::endl << std::endl;
}

void bf() // no duplicate definition because other bf() is in unnamed namespace
{
    std::cout << __FILE_NAME__ << "::" << __FUNCTION__ << std::endl;
}
