#ifndef __LANDLORD_H__
#define __LANDLORD_H__

#include "subscriber.h"

class Publisher; // forward declaration

class LandLord : public Subscriber
{
public:
	LandLord(Publisher* publisher);
	virtual ~LandLord();
	// from observer
	virtual void Update(Publisher* publisher) override;

private:
	Publisher* publisher_;
};

#endif // __LANDLORD_H__
