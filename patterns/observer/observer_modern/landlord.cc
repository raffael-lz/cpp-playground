#include <iostream>
#include <functional>

#include "landlord.h"
#include "publisher.h"

LandLord::LandLord(Publisher* publisher) :
	publisher_(publisher)
{
	std::cout << " LandLord::LandLord() subscribe to publisher" << std::endl;
	std::function<void()> func = std::bind( &LandLord::SecurityBreach, this);
	publisher_->Subscribe(func);
}

LandLord::~LandLord()
{
	std::cout << " LandLord::~LandLord() unsubscribe to publisher" << std::endl;
	//publisher_->Unsubscribe(this);
}

void LandLord::SecurityBreach()
{
	//if(publisher == publisher_)
	//{
		std::cout << " LandLord::SecurityBreach() event recevied from publisher" << std::endl;
	//}
}
