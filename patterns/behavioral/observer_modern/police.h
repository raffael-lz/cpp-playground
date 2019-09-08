#ifndef __POLICE_H__
#define __POLICE_H__

template <typename Subscriber>
class Publisher; // forward declaration

template <typename Subscriber>
class Police
{
public:
	Police(Publisher<Subscriber>* publisher);
	virtual ~Police();

	// from observer
	void Alarm(/*Publisher* publisher*/);

private:
	Publisher<Subscriber>* publisher_;
};

#endif // __POLICE_H__
