#ifndef __POLICE_H__
#define __POLICE_H__

class Publisher; // forward declaration

class Police
{
public:
	Police(Publisher* publisher);
	virtual ~Police();

	// from observer
	void Alarm(/*Publisher* publisher*/);

private:
	Publisher* publisher_;
};

#endif // __POLICE_H__
