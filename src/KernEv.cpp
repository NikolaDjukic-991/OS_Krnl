//File: KernEv.cpp


#include "PCB.h"
#include "KernEv.h"

KernelEv::KernelEv(IVTNo ivtNo){
	lock
	myIVT = ivtNo;
	myThread = PCB::running;
	IVTList::getEntryByNo((int)ivtNo)->put(this);	//adding to IVTList
	flag=0;
	unlock
}

KernelEv::~KernelEv(){
	lock
	IVTList::remove(this);
	unlock
}

int KernelEv::wait(){
	lock
	if (flag==0){
		PCB::running->eventBlock=this;
		unlock
		dispatch();
		return 1;
	}
	if (flag==1){
		flag=0;
		unlock
		return 1;
	}
	unlock
	return -1;
}

IVTNo KernelEv::getIVTNo(){return myIVT;}

void KernelEv::signal(){
	lock
	if(myThread->eventBlock){
		flag=0;
		myThread->eventBlock=0;
		Scheduler::put(myThread);
	}
	else
		flag=1;
	unlock
}