#ifndef __ADDRESS_BUILDER_HH__
#define __ADDRESS_BUILDER_HH__

#include <string>

#include "person_builder.hh"

class Person; // forward declaration

class AddressBuilder : public PersonBuilderBase
{
public:
	AddressBuilder(Person& person);

	AddressBuilder& Street(const std::string& street);
	AddressBuilder& Zip(const std::string& zip);
	AddressBuilder& City(const std::string& city);
};

#endif //__ADDRESS_BUILDER_HH__
