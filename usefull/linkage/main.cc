#include <iostream>

#include "bar.h"
#include "foo.h"

using namespace std;

void FuncFoo(); // forward declaration from foo.cc

int main()
{
    cout << GetFooConstexpr() << endl; // prints 5
    cout << GetBarConstexpr() << endl; // prints 10

    cout << GetFooConst() << endl; // prints 1
    cout << GetBarConst() << endl; // prints 2

    FuncFoo(); // prints 10
}
