/* g++ -std=c++14 main.cc house_security.cc landlord.cc police.cc -o bin/main */
#include <iostream>
#include <memory>

#include "house_security.h"
#include "landlord.h"
#include "police.h"

int main()
{
	std::cout << "Creating Publisher:" << std::endl;
	auto hs = std::make_unique<HouseSecurity<std::function<void()>>>();

	std::cout << "Creating Subscriber:" << std::endl;
	auto ll = std::make_unique<LandLord<std::function<void()>>>(hs.get());
	auto po = std::make_unique<Police<std::function<void()>>>(hs.get());

	std::cout << "Launch event: " << std::endl;
	hs->SecurityBreach();

	std::cout << "Unsubscribing" << std::endl;
}
