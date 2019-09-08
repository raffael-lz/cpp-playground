/* clang++ main.cc address_builder.cc person.cc person_builder.cc job_builder.cc -o builder -std=c++14 -Werror */
#include <iostream>

#include "person_builder.hh"
#include "address_builder.hh"
#include "job_builder.hh"

int main()
{
	Person p = Person::create()
			.lives().Street("abcStreet 123").Zip("123456789").City("barCity")
			.works().Company("fooCorp").Position("cc").Salary(9999);
			
	std::cout << p;
}
