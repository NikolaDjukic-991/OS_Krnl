//File: Event.cpp

#include "Event.h"
#include "KernEv.h"
// #include "System.h"

Event::Event(IVTNo ivtNo){
	lock
	myImpl= new KernelEv(ivtNo);
	unlock
}

Event::~Event(){
	lock
	delete myImpl;
	unlock
}

int Event::wait(){return myImpl->wait();}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
}