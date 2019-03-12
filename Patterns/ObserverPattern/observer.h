#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject; // forward declaration

class Observer
{
public:
	virtual ~Observer() {};
	virtual void Update(Subject* subject) = 0;
protected:
	Observer() {};
};

#endif
