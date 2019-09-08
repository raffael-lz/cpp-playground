#ifndef __CAR_FACTORY_HH__
#define __CAR_FACTORY_HH__

#include <memory>

#include "car.hh"

// abstract factory
struct CarFactory
{
	 virtual std::unique_ptr<Car> MakeSportClassCar() const = 0;
   virtual std::unique_ptr<Car> MakeMiddleClassCar() const = 0;
   virtual std::unique_ptr<Car> MakeHighClassCar() const = 0;
};

// concrete factory
struct GasoilCarFactory : CarFactory
{
  virtual std::unique_ptr<Car> MakeSportClassCar() const override
  {
    return std::make_unique<SportsCar>();
  }

  virtual std::unique_ptr<Car> MakeMiddleClassCar() const override
  {
    return std::make_unique<MiddleClassCar>();
  }

  virtual std::unique_ptr<Car> MakeHighClassCar() const override
  {
    return std::make_unique<HighClassCar>();
  }
};

// concrete factory
struct DieselCarFactory : CarFactory
{
  virtual std::unique_ptr<Car> MakeSportClassCar() const override
  {
    return std::make_unique<SportsCar>();
  }

  virtual std::unique_ptr<Car> MakeMiddleClassCar() const override
  {
    return std::make_unique<MiddleClassCar>();
  }

  virtual std::unique_ptr<Car> MakeHighClassCar() const override
  {
    return std::make_unique<HighClassCar>();
  }
};

#endif
