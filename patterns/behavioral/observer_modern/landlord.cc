#include <iostream>
#include <functional>

#include "landlord.h"
#include "publisher.h"

template<typename Subscriber>
LandLord<Subscriber>::LandLord(Publisher<Subscriber>* publisher) :
	publisher_(publisher)
{
	std::cout << " LandLord::LandLord() subscribe to publisher" << std::endl;
	std::function<void()> func = std::bind( &LandLord::SecurityBreach, this);
	publisher_->Subscribe(func);
}

template <typename Subscriber>
LandLord<Subscriber>::~LandLord()
{
	std::cout << " LandLord::~LandLord() unsubscribe to publisher" << std::endl;
	//publisher_->Unsubscribe(this);
}

template <typename Subscriber>
void LandLord<Subscriber>::SecurityBreach()
{
	//if(publisher == publisher_)
	//{
		std::cout << " LandLord::SecurityBreach() event recevied from publisher" << std::endl;
	//}
}

template class LandLord<std::function<void()>>;
