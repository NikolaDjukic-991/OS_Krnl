//File: KernEv.h

#ifndef KERN_EVENT_H_
#define KERN_EVENT_H_
#include "Event.h"
#include "Thread.h"
#include "IVTList.h"
#include "IVTEntry.h"



class KernelEv
{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	IVTNo getIVTNo();

	int wait();
	void signal();

private:
	friend class PCB;
	IVTNo myIVT; //?
	PCB* myThread;
	int flag;
	
};

#endif