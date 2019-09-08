#include "address_builder.hh"

AddressBuilder::AddressBuilder(Person& person) : PersonBuilderBase(person)
{
}

AddressBuilder& AddressBuilder::Street(const std::string& street)
{
	person_.street_address_ = street;
	return *this;
}
AddressBuilder& AddressBuilder::Zip(const std::string& zip)
{
	person_.zip_ = zip;
	return *this;
}
AddressBuilder& AddressBuilder::City(const std::string& city)
{
	person_.city_ = city;
	return *this;
}
