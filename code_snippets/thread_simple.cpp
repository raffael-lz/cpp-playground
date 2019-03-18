/* */

/* g++ -std=c++14 -pthread thread_simple.cpp -o bin/thread_simple */

/*
 * thread join: wait until thread finishes to continue.
 * thread detach: detach thread from calling thread (carefull about lifetimes).
 * when accessing shared ressources take care of access control (mutex).
 * see alos std::async for an alternative
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

std::mutex m;

using hrc =  std::chrono::high_resolution_clock;
using seconds = std::chrono::seconds;
void access_shared_resource(std::string threadName)
{
	std::lock_guard<std::mutex> lg(m);

	std::chrono::time_point<hrc> tp = hrc::now();
	std::time_t ttp = hrc::to_time_t(tp);

	std::cout << threadName << " accessed at shared_resource at " << std::ctime(&ttp);
	auto waitSeconds = std::rand()% 10 +1;
	std::this_thread::sleep_for(seconds(waitSeconds));
}

void loose_thread()
{
	std::cout << "loose_thread enter" << std::endl;

	std::this_thread::sleep_for(seconds(3));

	std::cout << "loose_thread exit" << std::endl;
}

void start_thread()
{
	std::cout << "start_thread enter" << std::endl;

	std::thread t_loose(loose_thread);
	t_loose.detach();
	std::this_thread::sleep_for(seconds(1));

	std::cout << "start_thread exit" << std::endl;
}


int main()
{
	std::cout << "- Threads accessing shared resource -" << std::endl;
	std::cout << "Starting Thread 1" << std::endl;
	std::thread t1(access_shared_resource, "Thread 1");
	std::cout << "Starting Thread 2" << std::endl;
	std::thread t2(access_shared_resource, "Thread 2");
	std::cout << "Starting Thread 3" << std::endl;
	std::thread t3(access_shared_resource, "Thread 3");

	t1.join();
	t2.join();
	t3.join();

	std::cout << "Thread 1-3 finished" << std::endl;

	std::cout << std::endl << "- Starting thread and detaching it from calling thread -" << std::endl;

	std::thread t_start(start_thread);
	t_start.join(); // if you don't join you get "terminate called without an active exception"
	std::this_thread::sleep_for(seconds(4));

	std::cout << "Finished" << std::endl;
}
