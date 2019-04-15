#ifndef __PERSON_BUILDER_HH__
#define __PERSON_BUILDER_HH__

#include "person.hh"

class AddressBuilder; 	// forward declaration
class JobBuilder; 			// forward declaration

class PersonBuilderBase
{
public:
	PersonBuilderBase(Person& person);

	AddressBuilder lives() const;
	JobBuilder works() const;

	operator Person()
	{
		return std::move(person_);
	}

protected:
	Person& person_;
};

class PersonBuilder : public PersonBuilderBase
{
public:
	PersonBuilder();
private:
	Person p_;

};

#endif // __PERSON_BUILDER_HH__
