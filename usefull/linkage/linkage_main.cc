#include "linkage_a.hh"
#include <iostream>
/*
 * Example for global and lokal linkage.
 * g++ -o lk linkage_main.cc linkage_a.cc linkage_b.cc -std=c++14
 */

int main()
{
    std::cout << "blabla" << std::endl;
    g();
}
