/* RAII / Resource Management */
/* g++ -std=c++14 -pthread raii.cpp -o bin/raii */

/*
 * Resource Aquisition is Initialization is a paradigm / technique that binds a resource to the
 * lifetime of an object. All aquisition (open a socket, open a file, mutex) must be done before using it.
 * It guarantees that the resource is available to all functions that a accessing to it and that the
 * resources are released once the object is deleted.
 * Sometimes it needs to be possible to copy an RAII object.
 * std libs for RAII: objects: std::unique_ptr, std::shared_ptr; mutex: std::lock_guard, std::unique_lock
 * std::shared_lock
*/

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <exception>

namespace CAR
{
	class Car {};

	void assembleCar(Car & car)
	{
	// do something here which can fail
		throw std::runtime_error("bla");
	}

	void assembleCar(std::unique_ptr<Car>& car)
	{
		// do something here which can fail
		throw std::runtime_error("bla");
	}

	void bad_car()
	{
		Car *myCar = new Car;

		assembleCar(*myCar); // if here an exception is thrown myCar gets never deleted.

		delete myCar;
	}

	void good_car()
	{
		std::unique_ptr<Car> myCar = std::make_unique<Car>();
		//assembleCar(*myCar); // not good yet because you remove control from unique_ptr
		assembleCar(myCar); // Better
		// myCar is released when good_car finished even with an exception.
	}
}

namespace MUTEX
{
	std::mutex my_mutex1;
	std::mutex my_mutex2;

	void bad_mutex()
	{
		my_mutex1.lock();

		return;

		my_mutex1.unlock();
	}

  void good_mutex()
  {
		std::lock_guard<std::mutex> my_lock_guard(my_mutex2);

		return;
	}
}

int main()
{
	std::cout << std::endl;

	// car
	try
	{
		CAR::bad_car();
		CAR::good_car();
	}
	catch (std::exception& e)
	{
		std::cout << "Bad Car exception thrown\n";
	}

	try
	{
		CAR::good_car();
	}
	catch (std::exception& e)
	{
		std::cout << "Good Car exception thrown\n";
	}

	std::cout << std::endl;

	// mutex
	// Mutex makes only sense in threads (when thread owns mutex, behaviour is undefined)
	std::thread t1(MUTEX::bad_mutex);

	t1.join();

	MUTEX::my_mutex1.try_lock()	? std::cout << "Lock successfull\n"
															: std::cout << "ERROR: Lock unsuccessfull\n";

	std::thread t2(MUTEX::good_mutex);
	t2.join();

	MUTEX::my_mutex2.try_lock()	? std::cout << "Lock was unlocked - now locked again.\n"
															: std::cout << "ERROR: Lock unsuccessfull\n";

	std::cout << std::endl;
}
