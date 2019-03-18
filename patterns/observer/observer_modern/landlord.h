#ifndef __LANDLORD_H__
#define __LANDLORD_H__


class Publisher; // forward declaration

class LandLord
{
public:
	LandLord(Publisher* publisher);
	virtual ~LandLord();
	// from observer
	void SecurityBreach(/*Publisher* publisher*/);

private:
	Publisher* publisher_;
};

#endif // __LANDLORD_H__
