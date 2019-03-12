/* g++ -std=c++14 main.cpp subject.cc house_security.cc landlord.cc police.cc -o bin/main */
#include <iostream>
#include <memory>

#include "house_security.h"
#include "landlord.h"
#include "police.h"

int main()
{
	auto house_security = std::make_unique<HouseSecurity>();
	auto landlord = std::make_unique<LandLord>(house_security.get());
	auto police = std::make_unique<Police>(house_security.get());

	house_security->SecurityBreach();
}
