#ifndef __POLICE_H__
#define __POLICE_H__

#include "subscriber.h"

class Publisher; // forward declaration

class Police : public Subscriber
{
public:
	Police(Publisher* publisher);
	virtual ~Police();

	// from observer
	virtual void Update(Publisher* publisher) override;

private:
	Publisher* publisher_;
};

#endif // __POLICE_H__
