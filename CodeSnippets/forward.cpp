/* */

/* g++ -std=c++14 forward.cpp -o bin/forward */

/*
 * std::move cast unconditionally to rvalue, std::forward does it conditional. move casts allways, forward
 *  only sometimes (condition).
 * One usecase is when a function template is taking an universal reference parameter and this parameter
 *  is passed to another function.
 * It only casts to an rvalue if a rvalue is passed. The information about this is encoded inside the
 *  template parameter.
 * All functions parameters are lvalues!
 * Nothing is done at runtime.
 * When dealing with universal references, then parameters passed in inside functions should be forwared.
 *  See (2) for it.
*/

#include <iostream>

namespace my
{
	struct string
	{
		string()
		{
			std::cout << " string::string default ctr" << std::endl;
		}

		string(const std::string& s)
		{
			std::cout << " string::std::string ctr" << std::endl;
		}

		string(const char* c)
		{
			std::cout << " string::char ctr" << std::endl;
		}

		string(const string& rhs)
		{
			std::cout << " string::string copy ctr" << std::endl;
		}

		string(string&& rhs)
		{
			std::cout << " string::string move ctr" << std::endl;
		}

		string& operator=(const string& s)
		{
			std::cout << " string::string copy operator" << std::endl;
			return *this;
		}

		string& operator=(string&& s)
		{
			std::cout << " string::string move operator" << std::endl;
			return *this;
		}

		std::string s_;
  };
}

// (1)
class Planet {};

// (1.1) rvalue parameter
void Test2(Planet&& param)
{
	std::cout << " Test2: rvalue reference" << std::endl;
}

// (1.2) lvalue parameter
void Test2(const Planet& param)
{
	std::cout << " Test2: lvalue reference" << std::endl;
}

template <typename T>
void Test1(T&& param)
{
	std::cout << " Test1: "  << std::endl;
	// call func and pass param
	Test2(param);
}

template <typename T>
void Test1_with_forward(T&& param)
{
	std::cout << " Test1_with_forward: "  << std::endl;
	// call func and pass param
	Test2(std::forward<T>(param));
}

// (2)
class Star
{
	public:
	template <typename T>
	void setItem(T&& name)
	{
		// forward a rvalue or lvalue depending on item
		name_ = std::forward<T>(name);
	}

	// Why not do it with two methods and no templates:
	void setItemWorse(const my::string& name)
	{
		std::cout << " setItemWorse->copy" << std::endl;
		my_item_ = name;
	}

	void setItemWorse(my::string&& item)
	{
		std::cout << " setItemWorse->move" << std::endl;
		my_item_ = std::move(item);
	}

	template <typename T>
	void setItemBetter(T&& item)
	{
		// forward a rvalue or lvalue depending on item
		my_item_ = std::forward<T>(item);
	}

	private:
	std::string name_;
	my::string my_item_;
};

int main()
{
// (1)
	{
		std::cout << "(1)" << std::endl;
		Planet d;
		Planet &rd = d;
		Test1(d);   // calls (1.2) lvalue reference
		Test1(rd);  // calls (1.2)
		Test1(std::move(d)); // calls (1.2)
	}
	{
		Planet d;
		Planet &rd = d;
		Test1_with_forward(d);   // calls (1.2) lvalue reference
		Test1_with_forward(rd);  // calls (1.2)
		Test1_with_forward(std::move(d)); // calls (1.1)
	}

// (2)
	{
		std::cout << std::endl << "(2)" << std::endl;
		std::cout << "setItem with std::forward and calls:" << std::endl;
		Star d2;
		d2.setItem("Hallo");
		std::string abc = "Hallo";
		d2.setItem(abc);
		if (abc.empty()) // not true
			std::cout << "abc empty" << std::endl;

		std::cout << std::endl;

// not doing the same calls like suggested in page 171

		std::cout << "setItemWorse with overloaded functions and std::move and calls:" << std::endl;
		Star d2_2;
		std::cout << "---" << std::endl;
		d2_2.setItemWorse(std::string("Hallo"));

		std::cout << std::endl;

		std::cout << "setItemBetter with std::forward and calls:" << std::endl;
		Star d2_3;
		std::cout << "---" << std::endl;
		d2_3.setItemBetter("Hallo");
	}
// (3)
	{
		std::cout << std::endl << "(3)" << std::endl;
		std::string s1 = "test";
		std::string s2 = std::forward<std::string>(s1);
		std::cout << "s1: " << s1 << "; s2: " << s2 << std::endl; // s1 is empty now
		// QUESTION WHY difference?
		std::string s = "test";
		std::string&& s3 = std::forward<std::string>(s);
		std::cout << "s: " << s << ": s3: " << s3 << std::endl; // s2 is not empty

		auto&& s4 = std::forward<std::string>(s);
		std::cout << "s: " << s << ": s4: " << s4 << std::endl; // s2 is not empty
	}
}
