
/* */

/* g++ -std=c++14 values.cpp -o bin/values */

/*
 *
*/

#include <iostream>
#include <set>
#include <vector>

// Just a dummy class.
class Dummy {};

// (1)
template <typename T>
void f(T&& param)
{
    // param is a universal reference (deduction to lvalue or rvalue).
}

// (2)
void DoNothingWithDummy(Dummy&& param)
{
    // param is only a rvalue reference
}

// (4)
// Example like std::vector<T>::push_back()
template <typename T>
class BetterDummy
{
	public:
		// No type deduction happens here because push_back is created dependening on class type.
		// Effective Modern C++ page 166
		void push_back(T&& t) // (4.1)
		{
			std::cout << " BetterDummy<T>.push_back rvalue reference" << std::endl;
		}

		void push_back(const T& t) // (4.2)
		{
			std::cout << " BetterDummy<T>.push_back const lvalue reference" << std::endl;
		}

    // Type deduction happens here
		template <typename InsideT>
		void special_push_back(InsideT&& it) // (4.3)
		{
			std::cout << " BetterDummy<T>.special_push_back<InsideT>() rvalue and lvalue" << std::endl;
		}
};

// (5) OVERLOADING ERRORS
// Error calling perfect forwarding ctr instead of copy constructor.
class Planet
{
	public:
		template <typename T>
		explicit Planet(T&& name) : name_(std::forward<T>(name))
		{
			std::cout << " Planet: perfect foward ctr" << std::endl;
		}

		explicit Planet(int rank) : name_(""), rank_(rank)
		{
			std::cout << " Planet: int ctr" << std::endl;
		}

		// These two ctor are constructed automatically when copy happens.
		// Planet(const Planet& cplanet);	(5.1) copy ctor for const objects.
		// Planet(Planet&& uplanet);	(5.2) rvalue copy ctor

	private:
		std::string name_;
		int rank_;
};

// (6)
// Overloading functions which are universal referenecs is dangerous:
std::multiset<std::string> myGlobalMultiset;
std::string getName(int index)
{
	std::vector<std::string> v {"abc", "def", "ghi"};
	return v.at(index);
}

template <typename T>
void doSomething(T&& t)
{
	std::cout << " doSomething universal reference" << std::endl;
	myGlobalMultiset.emplace(std::forward<T>(t));
}

// Overload it
void doSomething(int i)
{
	std::cout << " doSomething int overload" << std::endl;
	myGlobalMultiset.emplace(getName(i));
}

// (7)
// Solutions to (6):
// Make a function which accepts all and then inside call specialized overloads.

// Overloaded functions

template <typename T>
void doSomething2Impl(T&& t, std::false_type)
{
	std::cout << " doSomething2Impl universal reference" << std::endl;
	myGlobalMultiset.emplace(std::forward<T>(t));
}

// std::true_type and std::false_type are tags

void doSomething2Impl(int i, std::true_type)
{
	std::cout << " doSomething2Impl int overload" << std::endl;
	myGlobalMultiset.emplace(getName(i));
}

// Base function
template <typename T>
void doSomething2(T&& t)
{
	// When passing a lvalue to doSomething2 it gets to a lvalue reference. lvalue references are no
	//  integral type. Thats why the reference part has to be removed.
	doSomething2Impl(std::forward<T>(t),
		std::is_integral<typename std::remove_reference<T>::type>());
}

int main()
{
// (1)
	{
		std::cout << "(1)" << std::endl;
		int x {2};
		f(x);		    // lvalue reference
		f(std::move(x));    // rvalue reference
	}

// (2)
	{
		std::cout << std::endl << "(2)" << std::endl;
		Dummy d;
#ifdef _error_
		DoNothingWithDummy(d); // error: cannot bind ‘Dummy’ lvalue to ‘Dummy&&
#endif
		DoNothingWithDummy(std::move(d));
	}

// (3)
	{
		std::cout << std::endl << "(3)" << std::endl;
		Dummy&& d = Dummy();	// rvalue reference
#ifdef _error_
		Dummy&& dl = d;		// cannot bind ‘Dummy’ lvalue to ‘Dummy&&’
#endif
		auto&& dll = d;		// dll is a universal reference (type deduction)
	}

// (4)
	{
		std::cout << std::endl << "(4)" << std::endl;
		BetterDummy<int> d;
		auto a = 2;
		d.push_back(a);		    // (4.1) lvalue
		d.push_back(std::move(a));  // (4.2) rvalue
		d.push_back(2);		    // (4.2) rvalue

		d.special_push_back(a);	    // (4.3) lvalue
		d.special_push_back(2);	    // (4.3) rvalue
	}

// (5)
  {
		std::cout << std::endl << "(5)" << std::endl;
		Planet pluto("Pluto");	    // create object
#ifdef _error_
		// error: no matching function for call to ‘std::__cxx11::basic_string<char>::basic_string(Planet&)
		auto pluto_copy(pluto);     // copy it to other object won't
		// This error shows the tricky part: The compiler thinks that because it is a non const object
		//  it can be copied wrong. Look at (5.1) and (5.2).
#endif
	}
	{
		const Planet pluto("Pluto");	    // create object
		auto pluto_copy(pluto);		    // copy it to other object works because pluto is const
	}
	{
// (6)
		std::cout << std::endl << "(6)" << std::endl;
		std::string s = "testo";
		doSomething("test");	// correct behaviour (6.1)
		doSomething(s);		// correct behaviour (6.1)
		doSomething(1);		// correct behaviour (6.2)
#ifdef _error_
		short index=2;
		doSomething(index); // error: invalid conversion from ‘short int’ to ‘const char*’
		// wrong overload chosen, (6.1) but there is no constructor for std::string which can take
		//  a short so compilation fails!. Only because T is a pefect match for short.
#endif
	}
// (7)
	{
		std::cout << std::endl << "(7)" << std::endl;
		std::string s = "testo";
		doSomething2("test");	// correct behaviour (6.1)
		doSomething2(s);	// correct behaviour (6.1)
		doSomething2(1);	// correct behaviour (6.2)
		short index=2;
		doSomething2(index);	// works now, calling the right overloaded function.
	}
}
