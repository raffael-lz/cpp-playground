#ifndef __PERSON_H_H__
#define __PERSON_H_H__

#include <string>
#include <iostream>

class PersonBuilder; // forward declaration

class Person
{

public:
    friend class PersonBuilder;
    friend class AddressBuilder;
    friend class JobBuilder;

    static PersonBuilder create();

		friend std::ostream& operator<<(std::ostream& os, const Person& p)
		{
    	os << "Person" << std::endl;
			os << "Address: " << p.street_address_ << " zip: " << p.zip_ << " city: " << p.city_ << std::endl;
			os << "Work: " << p.company_ << " position: " << p.position_ << " annual salary: " << p.annual_salary_ << std::endl;
    	return os;
		}

private:
    // address
    std::string street_address_;
    std::string zip_;
    std::string city_;

    // job
    std::string company_;
    std::string position_;
    int annual_salary_;
};

#endif // __PERSON_H_H__
