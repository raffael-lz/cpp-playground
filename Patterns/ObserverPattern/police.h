#ifndef __POLICE_H__
#define __POLICE_H__

#include "observer.h"

class Subject; // forward declaration

class Police : public Observer
{
public:
	Police(Subject* subject);
	virtual ~Police();
	// from observer
	virtual void Update(Subject* subject) override;

private:
	Subject* subject_;
};

#endif
