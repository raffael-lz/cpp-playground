#include <iostream>

#include "landlord.h"
#include "subject.h"

LandLord::LandLord(Subject* subject) :
	subject_(subject)
{
	std::cout << " LandLord::LandLord() register subject" << std::endl;
	subject_->Register(this);
}

LandLord::~LandLord()
{
	std::cout << " LandLord::~LandLord() unregister subject" << std::endl;
	subject_->Unregister(this);
}

void LandLord::Update(Subject* subject)
{
	if(subject == subject_)
	{
		std::cout << " LandLord::Update() for subject called" << std::endl;
	}
}
