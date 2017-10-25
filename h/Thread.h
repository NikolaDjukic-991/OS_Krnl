// File: thread.h

#ifndef _thread_h_

#define _thread_h_
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;  // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
typedef char* TName;
class PCB; // Kernel's implementation of a user's thread 
class Thread {
public:
	ID start(); // returns: thread ID 
	static int waitToComplete(ID id); // returns: 1 – run completed,
	// 0 – woken up, -1 – error - no thread with given ID 

	static int sleep(Time timeToSleep); // returns: 1 – sleep completed,
	// 0 –woken up

	static int wakeUp(ID id); // returns: 1 – deblocked, 0 – no effect,
	// -1 – error - no thread with given ID

	static int waitForChildren(); // returns: 1 – finished, 0 – woken up,
	// -1 – error

	ID getId();
	
	TName getName();

	static Thread* getThreadById(ID id);

	static ID getIdOf(TName name);

	static TName getName(ID id);

	virtual ~Thread();

protected:
	friend class PCB; 

	Thread (TName name, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice); 

	virtual void run() {} 

	int waitToComplete(); //returns: 1 – completed, 0 – woken up, -1 – error

private:

	PCB* myPCB;

};
void dispatch ();


#endif