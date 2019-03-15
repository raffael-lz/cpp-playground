#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#include <vector>

class Subscriber; // forward declaration

class Publisher
{

public:
	virtual ~Publisher();

	void Subscribe(Subscriber* subscriber);

	void Unsubscribe(Subscriber* subscriber);

	void Notify();

protected:
	Publisher();

private:

	std::vector<Subscriber*> subscribers_;
};

#endif //__PUBLISHER_H__
