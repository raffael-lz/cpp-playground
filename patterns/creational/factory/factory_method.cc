// factory method offers static methods as factory to create objects.

#include <cmath>

class Point
{
public:
	static Point NewCartessianPoints(float x, float y)
	{
		return {x, y};
	}

	static Point NewPolarPoints(float rho, float theta)
	{
		return {rho * std::cos(theta), rho * std::sin(theta)};
	}

private:
	Point(float x, float y) : x_(x), y_(y)
	{
	}

	float x_;
	float y_;
};

int main()
{
	auto kp = Point::NewCartessianPoints(2,4);

	auto pp = Point::NewPolarPoints(4,10);
}
