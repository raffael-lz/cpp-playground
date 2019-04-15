#include "person_builder.hh"
#include "job_builder.hh"
#include "address_builder.hh"

PersonBuilderBase::PersonBuilderBase(Person& person) : person_(person)
{
}

AddressBuilder PersonBuilderBase::lives() const
{
	return {person_};
}
JobBuilder PersonBuilderBase::works() const
{
	return {person_};
}

PersonBuilder::PersonBuilder() : PersonBuilderBase(p_)
{
}
