#ifndef __JOB_BUILDER_HH__
#define __JOB_BUILDER_HH__

#include <string>

#include "person_builder.hh"

class Person; // forward declaration

class JobBuilder : public PersonBuilderBase
{
public:
	JobBuilder(Person& person);

	JobBuilder& Company(const std::string& company);
	JobBuilder& Position(const std::string& position);
	JobBuilder& Salary(int salary);
};

#endif //__ADDRESS_BUILDER_HH__
