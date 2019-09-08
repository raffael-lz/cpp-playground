// factory class nested in main class offers static methods as factory to create objects.

#include <cmath>

class Point
{
	// if it is private then you need a member or getter to access it.
	class PointFactory
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
	};
public:
	static PointFactory Factory;
private:
	Point(float x, float y) : x_(x), y_(y)
	{
	}

	float x_;
	float y_;
};

int main()
{
	auto kp = Point::Factory.NewCartessianPoints(2,4);

	auto pp = Point::Factory.NewPolarPoints(4,10);
}
