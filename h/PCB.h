// PCB.h

#ifndef _PCB_H_
#define _PCB_H_

#include "Thread.h"
//#include "PCBList.h"
//#include "sleepL.h"
//#include "KernSem.h"
// #include "KernEv.h"
#include "SCHEDULE.H"

class KernelEv;
class SleepList;
class PCBList;
class KernelSem;

class PCB
{
public:
	PCB(TName Name, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice, Thread* thr);
	~PCB();
	TName getName(){return myName;}
	StackSize getStackSize(){return myStackSize;}
	Time getTimeSlice(){return myTimeSlice;}
	ID getID(){return id;}

	ID start(); // returns: thread ID 
	static int waitToComplete(ID id); // returns: 1 – run completed,
	// 0 – woken up, -1 – error - no thread with given ID 

	static int sleep(Time timeToSleep); // returns: 1 – sleep completed,
	// 0 –woken up

	static int wakeUp(ID id); // returns: 1 – deblocked, 0 – no effect,
	// -1 – error - no thread with given ID

	static int waitForChildren(); // returns: 1 – finished, 0 – woken up,
	// -1 – error
	
	static Thread* getThreadById(ID id);

	static ID getIdOf(TName name);

	static TName getName(ID id);

	static PCB* getIdlePCB();

	int waitToComplete();

	int isSleeping();
	int isBlocked();

	static void PCB::wrapper();

	static PCB* running;
	static PCBList* allPCBs;
	// static SleepList* sleepPCB;
	
	KernelEv* eventBlock;

	KernelSem* blockedOnMe;
	KernelSem* myChildren;

	KernelSem* imBlockedOn;
	
	Time myTimeSlice;

	unsigned* SP;
	unsigned int sp;
	unsigned int ss;
	unsigned int bp;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	TName myName;
	int wokenUp;
	int finished;

private:
	friend class KernSem;

	static int idGen;

	int nOfChildren;




 

	ID id;
	StackSize myStackSize;
	Thread* myThread;
	PCB* myParent;




};

#endif