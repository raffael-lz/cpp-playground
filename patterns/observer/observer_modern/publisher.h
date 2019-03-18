#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#include <vector>
#include <functional>

class Publisher
{
public:
	virtual ~Publisher()
	{

	}

	void Subscribe(std::function<void()>& func)
	{
		subscribers_.push_back(func);
	}
	void Unsubscribe(/*std::function<void()>& func*/)
	{

	}

	void Notify()
	{
		for (auto& subscriber : subscribers_)
		{
			subscriber();
		}
	}

protected:
	Publisher()
	{

	}

private:

	std::vector<std::function<void()>> subscribers_;
};

#endif // __PUBLISHER_H__
