#ifndef __LANDLORD_H__
#define __LANDLORD_H__

template <typename Subscriber>
class Publisher; // forward declaration

template <typename Subscriber>
class LandLord
{
public:
	LandLord(Publisher<Subscriber>* publisher);
	virtual ~LandLord();
	// from observer
	void SecurityBreach(/*Publisher* publisher*/);

private:
	Publisher<Subscriber>* publisher_;
};

#endif // __LANDLORD_H__
