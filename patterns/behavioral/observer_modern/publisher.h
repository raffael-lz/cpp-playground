#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#include <vector>
#include <functional>

template<typename Subscriber>
class Publisher
{
public:
	virtual ~Publisher()
	{

	}

	void Subscribe(Subscriber& subscriber)
	{
		subscribers_.emplace_back(subscriber);
	}
	void Unsubscribe(/*std::function<void()>& func*/)
	{

	}

	void Notify() const
	{
		for (const auto& subscriber : subscribers_)
		{
			subscriber();
		}
	}

protected:
	Publisher()
	{

	}

private:

	std::vector<Subscriber> subscribers_;
};

#endif // __PUBLISHER_H__
