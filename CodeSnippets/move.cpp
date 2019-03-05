/*
 * Replace expensive copy semantics.
 * Thanks to move std::unique_ptr, std::thread are possible (move only types).
 * Nothing is done at runtime.
*/

/* g++ -std=c++14 move.cpp -o bin/move */

#include <iostream>

// (1)
// move operator from Scott Meyers
namespace my
{
	template <typename T>
	decltype(auto) move(T&& param)
	{
		std::cout << "Moving" << std::endl;
		using ReturnType = typename std::remove_reference<T>::type&&;
		return static_cast<ReturnType>(param);
	}
}

// (2)

// wrong example from Scott Meyers
class Annotation
{
	public:
		explicit Annotation(const std::string text) : value(std::move(text)) {}

	private:
		std::string value;
};

// (3)
struct X {};

X foobar()
{
	X x;
	return x;
}

void foo(X& x)	// (3.2)
{
	std::cout << " lvalue reference parameter call" << std::endl;
}

void foo(X&& x)	// (3.2)
{
	std::cout << " rvalue reference parameter call" << std::endl;
}

void foo(const X& x)	// (3.3)
{
	std::cout << " const lvalue reference parameter call" << std::endl;
}

// (4)
namespace my
{
	struct string
	{
		explicit string()
		{
			std::cout << " string::string()" << std::endl;
		}
		string(const string& rhs)
		{
			std::cout << " string::string(const string& rhs)" << std::endl;
		}

		string(string&& rhs)
		{
			std::cout << " string::string(string&& rhs)" << std::endl;
		}
	};
}

class M
{
	public:
		explicit M()
		{
			std::cout << " M::M() " << std::endl;
		}

		M(const M& rhs) : s(rhs.s)
		{
			std::cout << " M::M(const M& rhs) " << std::endl;
		}

		M(M&& rhs) : s(std::move(rhs.s))
		{
			std::cout << " M::M(M&& rhs) " << std::endl;
		}

		//M(my::string&& text) : s(my::move(text))
		//{
		//	std::cout << "M::M(my::string&& text)" << std::endl;
		//}

		my::string s;
};

int main()
{
 // (1)
 std::cout << "(1)" << std::endl;
	{
		int* i_1 = new int(10);
		int* i_2 = my::move(i_1);

		if (i_1 != nullptr) // i_1 should now be null
			std::cout << "i_1 is null after move to i_2." << std::endl;
		std::cout << "Value of i_2: " <<  *i_2 << std::endl;
	}

// (2)
std::cout << std::endl << "(2) wrong use of move" << std::endl;
	{
		std::string s_1 = "Hallo";
		Annotation a(s_1);
		if (!s_1.empty()) // not moved because of const!
			std::cout << "Annotation a(s_1) did not call move copy: "  << s_1 << std::endl;
	}

// (3)
std::cout << std::endl << "(3) function calls" << std::endl;
	{
		X x;
		const X cx;
		std::cout << "foo(x) -> ";
		foo(x);		    // calls (3.1)

		std::cout << "foo(foobar()) -> ";
		foo(foobar());	    // calls (3.2)

		std::cout << "foo(cx) -> ";
		foo(cx);	    // calls (3.3)

		std::cout << "foo(std::move(cx)) -> ";
		foo(std::move(x));

		std::cout << "foo(X()) -> ";
		foo(X());
	}

// (4)
std::cout << std::endl << "(4)" << std::endl;
	{
		std::cout << "M a;" << std::endl;
		M a;
		std::cout << "M b(a);" << std::endl;
		M b(a);

		std::cout << "M c(std::move(a));" << std::endl;
		M c(std::move(a));
	}
}
