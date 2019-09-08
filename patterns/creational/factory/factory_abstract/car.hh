#ifndef __CAR_HH__
#define __CAR_HH__

#include <iostream>

struct Car
{
	virtual ~Car() = default;
	virtual void Drive() = 0;
};

struct SportsCar : public Car
{
	void Drive() override
	{
			std::cout << "Driving a sportclass car." << std::endl;
	}
};

struct MiddleClassCar : public Car
{
	void Drive() override
	{
    std::cout << "Driving a middleclass car." << std::endl;
	}
};

struct HighClassCar : public Car
{
	void Drive() override
	{
    std::cout << "Driving a highclass car." << std::endl;
	}
};

#endif
