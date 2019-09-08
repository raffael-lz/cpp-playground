#include "house_security.h"

template <typename Subscriber>
void HouseSecurity<Subscriber>::SecurityBreach()
{
	this->Notify();
}

template class HouseSecurity<std::function<void()>>;
