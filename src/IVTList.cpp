//File IVTList.cpp

#include "IVTList.h"
#include "IVTEntry.h"

// IVTList::IVTList(){
// 		array = new IVTEntry*[256];
// 		myEntries=this;
// 	}

IVTEntry** IVTList::array = new IVTEntry*[256];


KernelEv* IVTList::remove(KernelEv* e){
		lock
			KernelEv* ret=getEntryByNo(e->getIVTNo())->remove(e);
		unlock

		return  ret;
	}

void IVTList::put(IVTNo ivt, KernelEv* e){
	lock
	IVTList::array[(int)ivt] -> put(e);
	unlock
	}