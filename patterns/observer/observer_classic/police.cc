#include <iostream>

#include "police.h"
#include "publisher.h"

Police::Police(Publisher* publisher) :
	publisher_(publisher)
{
	std::cout << " Police::Police() subscribe to publisher" << std::endl;
	publisher_->Subscribe(this);
}

Police::~Police()
{
	std::cout << " Police::~Police() unsubscribe to publisher" << std::endl;
	publisher_->Unsubscribe(this);
}

void Police::Update(Publisher* publisher)
{
	if(publisher == publisher_)
	{
		std::cout << " Police::Update() event received from publisher" << std::endl;
	}
}
