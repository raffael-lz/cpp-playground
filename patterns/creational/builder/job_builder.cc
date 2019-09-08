#include "job_builder.hh"

JobBuilder::JobBuilder(Person& person) : PersonBuilderBase(person)
{
}

JobBuilder& JobBuilder::Company(const std::string& company)
{
	person_.company_ = company;
	return *this;
}
JobBuilder& JobBuilder::Position(const std::string& position)
{
	person_.position_ = position;
	return *this;
}
JobBuilder& JobBuilder::Salary(int salary)
{
	person_.annual_salary_ = salary;
	return *this;
}
