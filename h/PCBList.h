#ifndef	_PCBLIST_H_
#define _PCBLIST_H_

#include "PCB.h"
#include "Thread.h"


class PCBList
{
	struct PCBElem
	{
		PCB* pcb;
		PCBElem* next;

		PCBElem(PCB* p){
			next = 0;
			pcb = p;
		}
	};

public:

	

	PCBList();
	~PCBList();

	void put(PCB* pcb);

	PCB* remove(const int index);
	PCB* removeById(const ID id);
	PCB* removeByName(const TName name);

	PCB* get(const int index)const;
	PCB* getById(const ID id)const;
	PCB* getByName(const TName name)const;

private:
	PCBElem* head;
	PCBElem* tail;

};

#endif