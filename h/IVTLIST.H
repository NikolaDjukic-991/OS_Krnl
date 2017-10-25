#ifndef IVTLIST_H_
#define IVTLIST_H_

#include "KernEv.h"
#include "Event.h"

class IVTEntry;

class IVTList
{
public:


	

	static IVTEntry* getEntryByNo(IVTNo i){return array[(int)i]; }

	// IVTList();
	// ~IVTList(){
	// 	delete array;
	// }

	static void put(IVTNo ivt, KernelEv* e);

	static KernelEv* remove(KernelEv* e);

	static IVTEntry* *array;
private:
	// static IVTList* myEntries;




};






#endif