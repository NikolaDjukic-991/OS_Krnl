//file: IVTEntry.cpp

#include "IVTEntry.h"

	IVTEntry::IVTEntry(IVTNo ivt, Intrpt newEntry){
		lock
		head=0;
		tail=0;
		IVTList::array[(int)ivt]=this;
		oldEntry=getvect((int)ivt);
		setvect((int)ivt, newEntry);
		unlock
	}

	IVTEntry::~IVTEntry(){
		lock
		Elem* del=head;
		while(head!=0){
			head=head->next;
			delete del;
			del=head;
		}
		unlock
	}

	void IVTEntry::fire(){
		lock
		Elem* tek=head;
		while(tek!=0){
			tek->event->signal();
			tek=tek->next;
		}
		unlock
	}

	KernelEv* IVTEntry::remove(KernelEv* e){
		lock
		Elem* tek=head;
		Elem* pret=0;
		KernelEv* retEv=0;
		while(tek!=0){
			if(tek->event==e){
				if(pret==0){
					head=head->next;
					retEv=tek->event;
					delete tek;
					unlock
					return retEv;
				}
				else
				{
					pret->next=tek->next;
					retEv=tek->event;
					delete tek;
					unlock
					return retEv;
				}
			}
			else
			{
				pret=tek;
				tek=tek->next;
				
			}
		}
		unlock
		return 0;
	}

	void IVTEntry::put(KernelEv* e){
		lock
		if (head==0){
			head=new Elem(e);
			tail=head;
		}
		else
		{
			tail->next=new Elem(e);
			tail=tail->next;
		}
		unlock
	}

