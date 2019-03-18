#include <iostream>
#include <memory>

#include "house_security.h"
#include "landlord.h"
#include "police.h"

int main()
{
	std::cout << "Creating Publisher:" << std::endl;
	auto hs = std::make_unique<HouseSecurity>();

	std::cout << "Creating Subscriber:" << std::endl;
	auto ll = std::make_unique<LandLord>(hs.get());
	auto po = std::make_unique<Police>(hs.get());

	std::cout << "Launch event: " << std::endl;
	hs->SecurityBreach();

	std::cout << "Unsubscribing" << std::endl;
}
