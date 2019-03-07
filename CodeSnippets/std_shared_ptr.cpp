/* g++ -std=c++14 std_shared_ptr.cpp -o bin/std_shared_ptr */

#include <iostream>
#include <memory>
#include <vector>


#define _custom_deleter_ 1
#define _ref_counts_ 0
struct Star
{
	explicit Star(const std::string& s) : s_(s) {}
	std::string s_;
};

// increments ref count, decrement after going out of scope
void func_copy(std::shared_ptr<Star> s)
{
	std::cout << " func(copy): ref count for " << s->s_ << ": " << s.use_count() << std::endl;
}

// does not affect ref count
void func_reference(std::shared_ptr<Star>& s)
{
	std::cout << " func(reference): ref count for " << s->s_ << ": " << s.use_count() << std::endl;
}

void func_vector_copy(std::vector<std::shared_ptr<Star>> vec)
{
	std::cout << " func(vector copy): ref count for " << vec.front()->s_ << ": " << vec.front().use_count() << std::endl;
}
int main()
{
// custom deleter for shared_ptr
#if _custom_deleter_
	std::cout << "### Custom deleters ###" << std::endl;
	{
		auto custom_deleter = [](Star * s) { std::cout << " custom_deleter for -" << s->s_ << "- called" << std::endl; delete s;};
		auto custom_deleter_2 = [](Star * s) { std::cout << " custom_deleter_2 for -" << s->s_ << "- called" << std::endl; delete s;};
		// unique_ptr custom deleter is part of the type.
		//std::unique_ptr<Star> up(new Star("up_1"));
		//std::unique_ptr<Star> up_2(new Star("up_2"));
		//up_2 = std::move(up); // ok

		//std::unique_ptr<Star, decltype(custom_deleter)> up(new Star("up_1"), custom_deleter);
		//std::unique_ptr<Star, decltype(custom_deleter_2)> up_2(new Star("up_2"), custom_deleter_2);
		//up_2 = std::move(up); // nok

		std::shared_ptr<Star> sp_1(new Star("sp_1"), custom_deleter);
		std::shared_ptr<Star> sp_2(new Star("sp_2"), custom_deleter_2);
		std::shared_ptr<Star> sp_3(new Star("sp_3"), custom_deleter_2);

		sp_3 = sp_1; // custom_deleter_2 is called when deleting sp_3, then sp_3 gets custom_deleter from sp_1

		std::unique_ptr<Star, decltype(custom_deleter)> up(new Star("up_1"), custom_deleter);
		std::shared_ptr<Star> sp_4 = up;



		std::cout << "Out of scope" << std::endl;
	}
#endif

// reference counts
#if _ref_counts_
	std::cout << std::endl << "### Reference Counts ###" << std::endl;
	{
		std::shared_ptr<Star> sp_1(new Star("sp_1"));
		std::shared_ptr<Star> sp_2(new Star("sp_2"));

		std::cout << "sp_1 ref count: " << sp_1.use_count() << std::endl; // use_count = 1
		std::cout << "sp_2 ref count: " << sp_2.use_count() << std::endl; // use_count = 1

		std::vector<std::shared_ptr<Star>> vec_stars {sp_1, sp_2};

		// use count 2
		std::cout << "sp_1 ref count after vector: " << sp_1.use_count() << std::endl;
		std::cout << "sp_2 ref count after vector: " << sp_2.use_count() << std::endl;

		std::cout << std::endl << "Pass sp_1 to func via copy" << std::endl;
		func_copy(sp_1); // increments ref count
		std::cout << "sp_1 ref count after func: " << sp_1.use_count() << std::endl;

		std::cout << std::endl << "Pass sp_1 to func via reference" << std::endl;
		func_reference(sp_1); // does not increment ref count
		std::cout << "sp_1 ref count after func: " << sp_1.use_count() << std::endl;

		std::cout << std::endl << "Pass vec to func via copy" << std::endl;
		func_vector_copy(vec_stars); // increments for pointers inside vector
		std::cout << "sp_1 ref count after func: " << sp_1.use_count() << std::endl;

		std::cout << std::endl << "std::move sp_1 to sp_3" << std::endl;
		std::cout << " sp_1 ref count: " << sp_1.use_count() << std::endl;
		auto sp_3 = std::move(sp_1); // sp_1 gets 0, sp_3 gets 2
		std::cout << " sp_1 ref count: " << sp_1.use_count() << std::endl;
		std::cout << " sp_3 ref count: " << sp_3.use_count() << std::endl;

		std::cout << std::endl << "copy sp_3 to sp_1" << std::endl;
		std::cout << " sp_1 ref count: " << sp_1.use_count() << std::endl;
		std::cout << " sp_3 ref count: " << sp_3.use_count() << std::endl;
		sp_1 = sp_3; // sp_1 gets 3, sp_3 is incremented from 2 to 3
		std::cout << " sp_1 ref count: " << sp_1.use_count() << std::endl;
		std::cout << " sp_3 ref count: " << sp_3.use_count() << std::endl;
	}
#endif
}
