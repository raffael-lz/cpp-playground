#include "subject.h"
#include "observer.h"

Subject::~Subject()
{
}

Subject::Subject()
{
}

void Subject::Register(Observer* observer)
{
	observers_.push_back(observer);
}

void Subject::Unregister(Observer* observer)
{
	auto it = std::find(observers_.begin(), observers_.end(), observer);
	if (it != observers_.end())
	{
		observers_.erase(it);
	}
}
void Subject::Notify()
{
	for (auto& observer : observers_)
	{
		observer->Update(this);
	}
}
