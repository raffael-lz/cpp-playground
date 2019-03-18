#include <iostream>

#include "police.h"
#include "publisher.h"

Police::Police(Publisher* publisher) :
	publisher_(publisher)
{
	std::cout << " Police::Police() subscribe to publisher" << std::endl;
	std::function<void()> func = std::bind( &Police::Alarm, this);
	publisher_->Subscribe(func);
}

Police::~Police()
{
	std::cout << " Police::~Police() unsubscribe to publisher" << std::endl;
	//publisher_->Unsubscribe(this);
}

void Police::Alarm()
{
	//if(publisher == publisher_)
	//{
		std::cout << " Police::Alarm() event received from publisher" << std::endl;
	//}
}
