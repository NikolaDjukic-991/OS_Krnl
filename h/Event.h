// File: event.h
#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;
class KernelEv;

class Event {

public:
	Event (IVTNo ivtNo);
	~Event ();

	int wait ();
	void signal();

private:
	KernelEv* myImpl;

};


#endif