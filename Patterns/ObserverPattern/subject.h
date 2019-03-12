#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <memory>

class Observer; // forward declaration

class Subject
{
public:
	virtual ~Subject();

	void Register(Observer* observer);
	void Unregister(Observer* observer);
	void Notify();

protected:
	Subject();
private:
	std::vector<Observer*> observers_;
};

#endif //__SUBJECT_H__
