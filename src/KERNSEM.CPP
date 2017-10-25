#include "KernSem.h"

#include "SCHEDULE.H"
#include "lock.h"

extern int semPreempt;

KernelSem::KernelSem(int init){
	lock
	blockedOnMe = new PCBList();
	myVal=init;
	unlock
}

KernelSem::~KernelSem(){
	lock
	while(myVal<0){
		signal();
	}
	delete blockedOnMe;
	unlock
}

int KernelSem::wait(){
	lock
	myVal--;
	PCB::running->wokenUp=0;
	if(myVal<0){
		if(blockedOnMe==0) blockedOnMe=new PCBList();
		blockedOnMe->put(PCB::running);//block
		PCB::running->imBlockedOn = this;
		unlock
		dispatch();
		if(PCB::running->wokenUp==1) return 0;
		return 1;
	}else{
		unlock
		if(semPreempt) dispatch();
		return 1;
	}
}

void KernelSem::signal(){
	lock
	myVal++;
	if(myVal>=0){
		PCB* pcb = blockedOnMe->remove(0);
		if(pcb!=0)
		{
			pcb->imBlockedOn = 0;
			Scheduler::put(pcb);
		}
	}
	unlock

}

int KernelSem::val()const{
	return myVal;
}

void KernelSem::release(PCB* pcb){
	blockedOnMe->removeById(pcb->getID());
}