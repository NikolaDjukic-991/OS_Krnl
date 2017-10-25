//File: PCB.cpp

#include "PCB.h"
#include "String.h"
#include "KernSem.h"
#include "sleepL.h"
#include "lock.h"
#include "KernEv.h"
#include "conio.h"
int PCB::idGen = 0;
PCBList* PCB::allPCBs = new PCBList();

// SleepList* PCB::sleePCB=newS
// PCB* PCB::running = 0;

PCB::PCB(TName name, StackSize stackSize, Time timeSlice, Thread* thr){
	lock
	myName = new char[30];
	strcpy(myName,name);
	myStackSize = stackSize;
	myTimeSlice = timeSlice;
	myThread = thr;
	id=++idGen;
	nOfChildren = 0;
	finished=0;

	blockedOnMe = new KernelSem(0);
	myChildren = new KernelSem(0);

	imBlockedOn = 0;

	myParent = PCB::running;
	myParent -> nOfChildren ++;

	PCB::allPCBs->put(this);

	SP=new unsigned[stackSize];
	sp=0;
	bp=0;
	unlock
}

PCB::~PCB(){
	// waitToComplete();

	lock
	
	unlock
	waitForChildren();
	lock
	delete myChildren;
	delete blockedOnMe;
	delete SP;
	delete myName;
	// delete imBlockedOn;
	unlock
}

void PCB::wrapper(){
	PCB::running->myThread->run();
	
	// delete PCB::running;
	lock
	PCB::running->finished=1;
	PCB::running->myParent->myChildren->signal();
	PCB::running->myParent->nOfChildren--;	
	while(PCB::running->blockedOnMe->val()<0){
		PCB::running->blockedOnMe->signal(); 
	}
	PCB::running=0;
	unlock
	dispatch();
}

ID PCB::start(){
	lock
	if(strcmp("idle",this->getName()))
		Scheduler::put(this);//put in queue
	//create stack frame
	SP[myStackSize-1]=0x200;
	SP[myStackSize-2]=FP_SEG(&(wrapper));
	SP[myStackSize-3]=FP_OFF(&(wrapper));
	sp=FP_OFF(SP+myStackSize-12);
	ss=FP_SEG(SP+myStackSize-12);
	unlock
	return id;
					// unsigned* st1 = new unsigned[1024];
					// st1[1023] =0x200;
					// //setovan I fleg u
					// // pocetnom PSW-u za nit
					// st1[1022] = FP_SEG(body);
					// st1[1021] = FP_OFF(body);
					// newPCB->sp = FP_OFF(st1+1012);
					// //svi sacuvani registri
					// //pri ulasku u interrupt
					// //rutinu
					// newPCB->ss = FP_SEG(st1+1012);
					// newPCB->zavrsio =0;

}

int PCB::waitToComplete(ID id){
	Thread* thr = PCB::getThreadById(id);//block on ID threads semaphore
	if(thr==0){
		return -1;
	}
	return thr->myPCB->waitToComplete();		//hang out till signalled

}

int PCB::waitToComplete(){
	if(finished==0)
	{
	PCB::running->wokenUp=0;
	
	blockedOnMe->wait();//calling thread blocks on this semaphore
	}
	if(PCB::running->wokenUp==0) return 1;
	else return 0;
}

int PCB::sleep(Time timeToSleep){
	lock//lock
			// SleepList::print();
	SleepList::put(PCB::running,timeToSleep);//put in sleep queue
			// SleepList::print();
	PCB::running->wokenUp=0;
	unlock//unlock
	dispatch();//dispatch
	return PCB::running->wokenUp;
}

int PCB::wakeUp(ID id){
	lock
	PCB* pcb = PCB::allPCBs->getById(id);
	if(pcb!=0)
	{
		if(pcb->isSleeping()){
			SleepList::removeById(id);
			Scheduler::put(pcb); // put in Scheduler
			pcb->wokenUp=1;
			unlock
			return 1;
		}
		if(pcb->isBlocked()){
			pcb->imBlockedOn->release(pcb);
			pcb->imBlockedOn=0;
			Scheduler::put(pcb); // put in Scheduler
			pcb->wokenUp=1;
			unlock
			return 1;
		}
		unlock
		return 0;
	}
	unlock
	return -1;
}

int PCB::waitForChildren(){
	int loop=PCB::running->nOfChildren;
	for(int i=0;i<loop;i++)
	{
		PCB::running->myChildren->wait();//wait na semaforu;
		PCB::running->nOfChildren--;
	}
	return PCB::running->wokenUp;
}

Thread* PCB::getThreadById(ID id){
	return PCB::allPCBs->getById(id)->myThread;//fetch this thread from a queue
}

ID PCB::getIdOf(TName name){
	return PCB::allPCBs->getByName(name)->getID();//fetch this thread from a queue
}

TName PCB::getName(ID id){
	return PCB::allPCBs->getById(id)->getName();//return threads name by its ID
}


int PCB::isSleeping(){
	lock
	if(SleepList::getById(this->id)!=0) {
		unlock
		return 1;
	}
	else {
		unlock
		return 0;
	}
}

int PCB::isBlocked(){
	if(this->imBlockedOn!=0)		return 1;
	else							return 0;
}

PCB* PCB::getIdlePCB(){
	return getThreadById(getIdOf("idle"))->myPCB;
}
