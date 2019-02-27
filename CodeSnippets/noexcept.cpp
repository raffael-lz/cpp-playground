/* noexcept.cpp - no exceptions for functions */

/* g++ -std=c++14 -pthread raii.cpp -o bin/raii */

/*
 * With the word noexcept after function name, the function guarantees that it will not throw an exception.
 * If at runtinme in the noexcept function an excecption is rised, then the stack can be unwound before
 *  program is terminated. Because of this, there is optimization potential because optimizer do not have to
 *  keep the runtime stack in an unwindable state. 
 * Program is terminated directly (std::terminate) !
 * It is checked at compile time and return true if function does not throw an exception. Return is false,
 *  if inside a function is called with noexcept / throw() or if there is a dynamic_cast expression.
*/

#include <iostream>

struct A {};
struct B : A {};

void f() { throw; };

void f_noexcept() noexcept
{
}

void f_noexcept_with_cast() noexcept
{
    auto* b = new B;
    auto* a = dynamic_cast<A*>(b);

    delete b;
}

void f_noexcept_with_function() noexcept
{
    f();
}
void f_possiblethrow()
{
    throw std::runtime_error("bla");
}

int main()
{
    try
    {
	std::cout << std::boolalpha << "f_noexcept() noexcept: " << noexcept(f_noexcept()) << std::endl;
#ifdef _error_
	f_noexcept(); // when called like this then program will be terminated directly. 
#endif
    }
    catch (std::exception& e)
    {
	std::cout << "exception from f_noexcept()" << std::endl;
    }

    try
    {
	std::cout << "f_possiblethrow() noexcept: " << noexcept(f_possiblethrow()) << std::endl;
	f_possiblethrow();
    }
    catch (std::exception& e)
    {
	std::cout << "exception from f_possiblethrow()" << std::endl;
    }


    std::cout << "f_noexcept_with_cast() noexcept: " << noexcept(f_noexcept_with_cast()) << std::endl;
    std::cout << "f_noexcept_with_function() noexcept: " << noexcept(f_noexcept_with_function()) << std::endl;
}
