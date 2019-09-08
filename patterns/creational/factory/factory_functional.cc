// in functional factory, factories are represented as lambda functions i.e.

#include <map>
#include <functional>
#include <memory>
#include <string>

struct Car
{
  virtual ~Car() = default;
  virtual void Drive() const = 0;
};

struct HighClassCar : public Car
{
  void Drive() const override {}
};

struct MiddleClassCar : public Car
{
  void Drive() const override {}
};

int main()
{
  std::map<std::string, std::function<std::unique_ptr<Car>()>> functional_factories;

  functional_factories["E200"] = []()
                      {
                        return std::make_unique<MiddleClassCar>();
                      };

  functional_factories["911Carrera"] = []()
                      {
                        return std::make_unique<HighClassCar>();
                      };

  auto E200 = functional_factories.at("E200");
}
