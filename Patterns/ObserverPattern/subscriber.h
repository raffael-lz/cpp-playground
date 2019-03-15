#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

class Publisher; // forward declaration

class Subscriber // Observer
{
public:
	virtual ~Subscriber() {};

	virtual void Update(Publisher* publisher) = 0;
protected:
	Subscriber() {};
};

#endif // __SUBSCRIBER_H__
