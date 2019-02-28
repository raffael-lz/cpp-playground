/* noexcept.cpp - no exceptions for functions */

/* g++ -std=c++14 -pthread noexcept.cpp -o bin/noexcept */

/*
 * With the word noexcept after function name, the function guarantees that it will not throw an exception.
 * If at runtinme in the noexcept function an excecption is rised, then the stack can be unwound before
 *  program is terminated. Because of this, there is optimization potential because optimizer do not have to
 *  keep the runtime stack in an unwindable state.
 * Program is terminated directly (std::terminate) !
 * It is checked at compile time and return true if function does not throw an exception. Return is false,
 *  if inside a function is called with noexcept / throw() or if there is a dynamic_cast expression.
 * When noexcept(true) copies can be done faster because it is less strict (undo copy etc).
*/

#include <iostream>
#include <array>
#include <vector>

struct A {};
struct B : A {};

void f() { throw; };

void f_noexcept() noexcept
{
}

void f_noexcept_with_cast() noexcept
{
	auto* b = new B;
	// when dynamic_cast fails, different to pointer where it is null then, for a reference a
	// an exception is thrown.
	auto& a = dynamic_cast<A&>(*b);

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

struct CopyNoexcept
{
	std::array<int, 3> a {{0,1,2}};
};

struct CopyException
{
	std::vector<int> v {0,1,2};
};

template <typename T>
T copy(T const& src) noexcept(noexcept(T(src)))
{
	return src;
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

	{
		CopyNoexcept copyNoexcept;
		CopyException copyException;

		std::cout << "CopyNoexcept: " << noexcept(copy(copyNoexcept)) << std::endl;
		// ctor from vector can throw exception. This is why it is except(false).
		std::cout << "CopyException: " << noexcept(copy(copyException)) << std::endl;
	}
}
