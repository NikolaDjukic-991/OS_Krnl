//File: sleepList.h
#ifndef _sleepList_H_
#define _sleepList_H_

#include "PCB.h"
#include "String.h"

class SleepList
{
	struct SleepElem
	{
		PCB* pcb;
		SleepElem* next;

		Time time;

		SleepElem(PCB* p, Time t){
			next = 0;
			pcb = p;
			time = t;
		}
	};



public:
	// SleepList();
	// ~SleepList();

	static void dispose();

	static void put(PCB* pcb, Time t);

	static PCB* tick();
	static void refresh();

	// static PCB* remove(const int index);
	static PCB* removeById(const ID id);
	// static PCB* removeByName(const TName name);

	static PCB* get(const int index);
	static PCB* getById(const ID id);
	static PCB* getByName(const TName name);

	static void SleepList::print();

	static int refreshFlag;

protected:
	static PCB* removeHead();

private:
	static SleepElem* head;
	
};


#endif