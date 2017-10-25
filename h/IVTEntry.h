//File : IVTEntry.h

#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "KernEv.h"
#include "System.h"


class IVTEntry
{
public:

	class Elem{
	public:
		KernelEv* event;
		Elem* next;

		Elem(KernelEv* e){
			event=e;
			next=0;
		}

		~Elem(){}



	};

	IVTEntry(IVTNo ivt, Intrpt newEntry);

	~IVTEntry();

	void fire();

	KernelEv* remove(KernelEv* e);

	void put(KernelEv* e);

	Elem* head;
	Elem* tail;
	
private:
	Intrpt oldEntry;

};




#endif