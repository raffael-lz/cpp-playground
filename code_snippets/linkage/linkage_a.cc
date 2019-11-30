#include <iostream>
#include "linkage_a.hh"

int a = 4;                  // global linkage, declaration + definition
constexpr int var = 44;     // constexpr is only visible for this translation unit
void f();                   // declaration of f, is linked later to linkage_b.cc::f()
void g()                    // definition of g. declaration is in header file
{
    std::cout << __FILE_NAME__ << "::"<< __FUNCTION__ << " enter: "<< std::endl << std::endl;
    std::cout << "var (44): " << var << std::endl;
    std::cout << "calling f()" << std::endl;
    f();
    bf();
    std::cout << __FILE_NAME__ << "::" << __FUNCTION__ << " exit: "<< std::endl << std::endl;
}
