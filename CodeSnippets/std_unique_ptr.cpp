/* g++ -std=c++14 std_unique_ptr.cpp -o bin/std_unique_ptr */

#include <iostream>
#include <memory>
#include <vector>

void func(std::unique_ptr<std::string> p)
{
	std::cout << " func_p: " << *p << std::endl;
}

struct S
{
	S(std::string s) : s_(s) { std::cout << " S::S(std::string): " << s << std::endl; }

	~S() { std::cout << " S::~S(): " << s_ << std::endl; }

	std::string s_;
};

int main()
{
// Access element
	{
		std::unique_ptr<std::string> up(new std::string("Pointer"));
		std::cout << "up: " << *up << std::endl;
	}
	{
		std::unique_ptr<std::vector<std::string>> up(new std::vector<std::string>);
		up->push_back("first string");
		std::cout << "Front element: " << up->front() << std::endl;
	}

// Try to copy (not possible)
	{
		std::unique_ptr<std::string> up(new std::string("Pointer"));
#ifdef _error_1_
		//std::unique_ptr<std::string> up2(up); // error: use of deleted function
#endif
		// move unique_ptr
		std::unique_ptr<std::string> up2(std::move(up));
#ifdef _error_2_
		//std::cout << "up after up2(up): " << *up << std::endl; // Segmentation fault (core dumped)
#endif
		std::cout << "up2: " << *up2 << std::endl;
	}
// Pass unique_ptr to function
	{
		std::unique_ptr<std::string> up(new std::string("Pointer"));
		func(std::move(up));
		func(std::make_unique<std::string>("make_unique value"));
		// func(up); // error: use of deleted function
		// std::cout << "up: " << *up << std::endl; // invalid segmentation fault
	}
// vector containing unique_ptr
	{
		std::vector<std::unique_ptr<std::string>> up_vec;
		up_vec.push_back(std::make_unique<std::string>("bla_1"));
		up_vec.push_back(std::unique_ptr<std::string>(new std::string("bla_2")));

		std::unique_ptr<std::string> up(new std::string("bla_3"));
		// up_vec.push_back(up); // error: use of deleted function
		up_vec.push_back(std::move(up));

		for (auto&& e:up_vec)
		{
			std::cout << *e << std::endl;
		}
	}
// Custom deleter (for logs, release resources, wrong implemented classes
	{
		auto custom_deleter =
			[](std::string* s)
			{
				std::cout << "Object custom deleter for " << *s << " called" << std::endl;
				delete s;
			};

		std::unique_ptr<std::string, decltype(custom_deleter)> up(new std::string("up_1"), custom_deleter);
		std::unique_ptr<std::string, decltype(custom_deleter)> up2(new std::string("up_2"), custom_deleter);
		std::unique_ptr<std::string, decltype(custom_deleter)> up3(new std::string("up_3"), custom_deleter);
	}
// Release, Reset pointer
	{
		auto up_1 = std::make_unique<S>("up_1");
		auto up_2 = std::make_unique<S>("up_2");

		up_1.reset(); // destructor for object is called
		if (up_1 == nullptr)
			std::cout << "up_1 is null after up_1.reset()" << std::endl;

		up_1.reset(new S("up_1_2")); // up_1 has new value

		std::cout << "End of scope" << std::endl;

	}
	{
		auto up_1 = std::make_unique<S>("up_1");
		S* s = up_1.release(); // now the ownership has moved to raw pointer again, no destructor called.

		if (up_1 == nullptr)
			std::cout << "up_1 is null after up_1.release()" << std::endl;

		// necessary to call delete
		delete s;
	}
}
