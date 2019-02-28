/* */

/* g++ -std=c++14 move.cpp -o bin/move */

/*
 * Replace expensive copy semantics.
 * Thanks to move std::unique_ptr, std::thread are possible (move only types).
 * Nothing is done at runtime.
*/

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

//template <typename T>
//typename std::remove_reference<T>::type&& move(T&& param)
//{
//    using ReturnType = typename std::remove_reference<T>::type&&;
//    return static_cast<ReturnType>(param);
//    //return static_cast<typename std::remove_reference<T>::type&&>(param);
//}

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
	std::cout << "lvalue reference" << std::endl;
}

void foo(X&& x)	// (3.2)
{
	std::cout << "rvalue reference" << std::endl;
}

void foo(const X& x)	// (3.3)
{
	std::cout << "const lvalue reference" << std::endl;
}

// (4)
namespace my
{
	struct string
	{
		string()
		{
			std::cout << "string default ctr" << std::endl;
		}
		string(const string& rhs)
		{
			std::cout << "string copy ctr" << std::endl;
		}

		string(string&& rhs)
		{
			std::cout << "string move ctr" << std::endl;
		}
	};
}

class Annotation2
{
	public:
		explicit Annotation2(const my::string& text) : s(std::move(text))
		{
			std::cout << "Annotation2 const lvalue reference" << std::endl;
		}

		Annotation2(my::string&& text) : s(my::move(text))
		{
			std::cout << "Annotation2 rvalue reference" << std::endl;
		}

	private:
		my::string s;
};

int main()
{
 // (1)
	{
		int* i_1 = new int(10);
		int* i_2 = my::move(i_1);

		std::cout << "(1)" << std::endl;
		if (i_1 != nullptr) // i_1 should now be null
			std::cout << "i_1 is null after move to i_2." << std::endl;
	std::cout << "Value of i_2: " <<  *i_2 << std::endl;
	}

// (2)
	{
		std::cout << std::endl << "(2)" << std::endl;
		std::string s_1 = "Hallo";
		Annotation a(s_1);
		if (!s_1.empty()) // not moved!
			std::cout << "s_1 not moved: "  << s_1 << std::endl;
	}

// (3)
	{
		std::cout << std::endl << "(3)" << std::endl;
		X x;
		const X cx;
		foo(x);		    // calls (3.1)
		foo(foobar());	    // calls (3.2)
		foo(cx);	    // calls (3.3)
	}

// (4)
	{
		std::cout << std::endl << "(4)" << std::endl;
		my::string my_string;
		my::string& my_string_ref = my_string;
		std::cout << std::endl;
		Annotation2 a2_1(my_string); // two times copy ctr is called, no move ctr!
		std::cout << std::endl;
		Annotation2 a2_2(my::move(my_string)); // move constructor is called.
	}
}
