#include <iostream>
#include "linkage_a.hh"
/*
 * Example for global and lokal linkage.
 * g++ -o lk linkage_main.cc linkage_a.cc linkage_b.cc -std=c++14
 */

void bf()   // no multiple definition because of unnamed namespace
{
}

int main()
{
    std::cout << "blabla" << std::endl;
    g();
}
