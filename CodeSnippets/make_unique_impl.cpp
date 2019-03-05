/*
 * Implementation of own std::make_unique using variadic template and perfect forwarding (std::forward).
 * Should accept n parameters and allocate memory.
*/

/* g++ -std=c++14 make_unique_impl.cpp -o bin/make_unique */

#include <iostream>
#include <memory>
#include <tuple>

namespace lora
{
	template <typename T, typename... Ts>
	T make_unique(Ts&&... args)
	{
		return T(std::forward<Ts>(args)...);
	}
}
class Reptile
{
	public:
		explicit Reptile(const std::string& name) : name_(name), color_(""), maxSizes_(std::make_tuple(1.0,1.0,1.0))
		{

			std::cout << " Reptile:Reptile(const std::string& name) called: name_:" << name_ << std::endl;
		}

		Reptile(const std::string&name, const std::string& color) : name_(name), color_(color), maxSizes_(std::make_tuple(1.0,1.0,1.0))
		{
			std::cout << " Reptile:Reptile(const std::string&name, const std::string& color) called: name_:" << name_ <<
			 	" color_: " << color_ << std::endl;
		}

		Reptile(const std::string&name, const std::string& color, float height, float width, float length) :
			name_(name), color_(color), maxSizes_(std::make_tuple(height,width,length))
		{
			std::cout << " Reptile:Reptile(const std::string&name, const std::string& color) called: name_:" << name_ <<
			 	" color_: " << color_ << " length from tupple: " << std::get<2>(maxSizes_)<< std::endl;
		}

	private:
		std::tuple<float, float, float> maxSizes_;
		std::string name_;
		std::string color_;
};

int main()
{
	// What we want to do:
	std::cout << "std::make_unique" << std::endl;
	std::unique_ptr<int> stdPtr = std::make_unique<int>(2);
	auto stdReptilePtr_1 = std::make_unique<Reptile>("Lagarto");
	auto stdReptilePtr_2 = std::make_unique<Reptile>("Lagarto", "Red");
	auto stdReptilePtr_3 = std::make_unique<Reptile>("Lagartija", "Blue", 1.0, 2.0, 3.0);

	std::cout << std::endl << "lora::make_unique" << std::endl;
	auto loraInt = lora::make_unique<int>(2);
	auto loraReptile1 = lora::make_unique<Reptile>("Lagarto");
	auto loraReptile2 = lora::make_unique<Reptile>("Lagarto", "Red");
	auto loraReptile3 = lora::make_unique<Reptile>("LAgartija", "Blue", 2.0, 3.0, 4.0);


}
