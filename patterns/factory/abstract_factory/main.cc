/*clang++ main.cc -o main -std=c++14 -Werror */

#include <memory>
#include <vector>

#include "car.hh"
#include "car_factory.hh"

std::vector<std::shared_ptr<Car>> makeCars(CarFactory& factory)
{
    auto middle_car = factory.MakeMiddleClassCar();
    auto high_car = factory.MakeHighClassCar();
    auto sports_car = factory.MakeSportClassCar();

    return {std::move(middle_car), std::move(high_car), std::move(sports_car)};
}

int main()
{
  GasoilCarFactory g_factory;
  std::vector<std::shared_ptr<Car>> g_cars = makeCars(g_factory);
  for_each(g_cars.begin(), g_cars.end(), [](std::shared_ptr<Car> c){c->Drive();});

  GasoilCarFactory d_factory;
  std::vector<std::shared_ptr<Car>> d_cars = makeCars(d_factory);
  for_each(d_cars.begin(), d_cars.end(), [](std::shared_ptr<Car> c){c->Drive();});

}
