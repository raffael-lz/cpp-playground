#ifndef __LANDLORD_H__
#define __LANDLORD_H__

#include "observer.h"

class Subject; // forward declaration

class LandLord : public Observer
{
public:
	LandLord(Subject* subject);
	virtual ~LandLord();
	// from observer
	virtual void Update(Subject* subject) override;

private:
	Subject* subject_;
};

#endif
