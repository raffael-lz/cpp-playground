#include "publisher.h"
#include "subscriber.h"

Publisher::Publisher()
{
}

Publisher::~Publisher()
{
}

void Publisher::Subscribe(Subscriber* subscriber)
{
	subscribers_.push_back(subscriber);
}

void Publisher::Unsubscribe(Subscriber* subscriber)
{
	try
	{
		auto it = std::find(subscribers_.begin(), subscribers_.end(), subscriber);
		if (it != subscribers_.end())
		{
			subscribers_.erase(it);
		}
	}
	catch (const std::out_of_range& ex)
	{
		// error
	}
}

void Publisher::Notify()
{

	try
	{
		for (auto& s : subscribers_)
		{
			s->Update(this);
		}
	}
	catch (const std::out_of_range& ex)
	{
		// error
	}
}
