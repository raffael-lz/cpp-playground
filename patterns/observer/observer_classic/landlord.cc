#include <iostream>

#include "landlord.h"
#include "publisher.h"

LandLord::LandLord(Publisher* publisher) :
	publisher_(publisher)
{
	std::cout << " LandLord::LandLord() subscribe to publisher" << std::endl;
	publisher_->Subscribe(this);
}

LandLord::~LandLord()
{
	std::cout << " LandLord::~LandLord() unsubscribe to publisher" << std::endl;
	publisher_->Unsubscribe(this);
}

void LandLord::Update(Publisher* publisher)
{
	if(publisher == publisher_)
	{
		std::cout << " LandLord::Update() event recevied from publisher" << std::endl;
	}
}
