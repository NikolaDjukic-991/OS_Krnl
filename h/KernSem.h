//File: KernSem.h
#ifndef _KERNELSEM_H_
#define _KERNELSEM_H_

#include "PCBList.h"

class KernelSem
{
public:
	KernelSem(int init=0);
	~KernelSem();
	int wait();
	void signal();

	int val() const;

	void release(PCB* pcb);

private:
	int myVal;
	PCBList* blockedOnMe;
	
};

#endif