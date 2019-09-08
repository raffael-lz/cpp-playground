#ifndef __HOUSE_SECURITY_H__
#define __HOUSE_SECURITY_H__

#include "publisher.h"

template <typename Subscriber>
class HouseSecurity : public Publisher<Subscriber>
{
public:
	void SecurityBreach();
};

#endif // __HOUSE_SECURITY_H__
