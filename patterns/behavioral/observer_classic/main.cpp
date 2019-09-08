/* g++ -std=c++14 main.cpp publisher.cc house_security.cc landlord.cc police.cc -o bin/main */
#include <iostream>
#include <memory>

#include "house_security.h"
#include "landlord.h"
#include "police.h"

int main()
{
	std::cout << "Creating Publisher:" << std::endl;
	auto house_security = std::make_unique<HouseSecurity>();

	std::cout << "Creating Subscriber:" << std::endl;
	auto landlord = std::make_unique<LandLord>(house_security.get());
	auto police = std::make_unique<Police>(house_security.get());

	std::cout << "Launch event: " << std::endl;
	house_security->SecurityBreach();

	std::cout << "Unsubscribing" << std::endl;
}
