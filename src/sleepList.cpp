#include "conio.h"
#include "lock.h"
#include "SleepL.h"

SleepList::SleepElem* SleepList::head = 0;

// SleepList::SleepList(){
// 	head=0;
// 	tail=0;
// }

void SleepList::dispose(){
	lock
	SleepElem* tek;
	while(SleepList::head!=0){
		tek=SleepList::head;
		SleepList::head = SleepList::head->next;
		delete tek;
		tek = SleepList::head;
	}
	unlock

}

void SleepList::put(PCB* pcb, Time t){
	lock
	SleepElem* tek=head;
	SleepElem* pret=0;
	SleepElem* novi=0;
	// cprintf("put to sleep:%s\n",pcb->myName);
	// SleepList::print();
	if(SleepList::head==0){
		SleepList::head=new SleepElem(pcb,t);
		tek=head->next;
		// cprintf("put to sleep:%s\n",head->pcb->myName);
	}
	else{
		while (tek!=0){
			if(tek->time>t)
			{
				novi = new SleepElem(pcb, t);
				if(pret==0){
					novi->next = tek;
					SleepList::head=novi;	
				}
				else
				{
					pret->next=novi;
					novi->next=tek;
				}
				break;
			}
			else
			{
				t-=tek->time;
				if(tek->next)
					{
					pret=tek; //!!!!!!!!!!
					tek=tek->next;
					}
				else
				{
					tek->next=new SleepElem(pcb,t);
					// cprintf("put to sleep:%s\n",tek->pcb->myName);
					unlock
					return;
				}
			}
		// cprintf("put to sleep:%s\n",tek->pcb->myName);
		}
		if(tek!=0)
		{
			tek->time-=t;
			tek=tek->next;
		}

	}
	unlock
}

void SleepList::print(){
	lock
	SleepElem* tek=head;
	// cprintf("s:");
	while(tek!=0){
		cprintf("%d(%d), ",tek->pcb->getID(),tek->time);
		tek=tek->next;
	}
	cprintf("\n");
	unlock
}

// PCB* SleepList::remove(const int index){
// 	lock
// 	int i=0;
// 	SleepElem* tek=SleepList::head;
// 	SleepElem* pret=0;
// 	PCB* retVal=0;
// 	Time t;

// 	while(tek!=0)
// 	{
// 		if(index==i)
// 		{
// 			if(pret==0)
// 			{
// 				SleepList::head = tek->next;
// 				retVal=tek->pcb;
// 				t=tek->time;
// 				pret=tek->next;
// 				delete tek;
// 				break;
// 			}
// 			else
// 			{
// 				pret->next=tek->next;
// 				retVal=tek->pcb;
// 				t=tek->time;
// 				pret=tek->next;
// 				delete tek;
// 				break;
				
// 			}
// 		}
// 		else
// 		{
// 			pret = tek;
// 			tek = tek->next;
// 			i++;
// 		}
// 	}
// 	tek=pret;
// 	while(tek!=0){
// 		tek->time+=t;
// 		tek=tek->next;
// 	}
// 	unlock
// 	return retVal;
// }

PCB* SleepList::removeById(const ID id){
	lock
	SleepElem* tek=SleepList::head;
	SleepElem* pret=0;
	PCB* retVal=0;
	Time t;

	while(tek!=0)
	{
		if(tek->pcb->getID()==id)
		{
			if(pret==0)
			{
				SleepList::head = tek->next;
				retVal=tek->pcb;
				t=tek->time;
				pret=tek->next;
				delete tek;
				break;
			}
			else
			{
				pret->next=tek->next;
				retVal=tek->pcb;
				t=tek->time;
				pret=tek->next;
				delete tek;
				break;
				
			}
		}
		else
		{
			pret = tek;
			tek = tek->next;
		}
	}
	tek=pret;
	if(tek!=0){
		tek->time+=t;
		tek=tek->next;
	}
	unlock
	return retVal;
}


// PCB* SleepList::removeByName(const TName name){
// 	lock
// 	SleepElem* tek=SleepList::head;
// 	SleepElem* pret=0;
// 	PCB* retVal;
// 	Time t;

// 	while(tek!=0)
// 	{
// 		if(strcmp(tek->pcb->getName(),name)==0)
// 		{
// 			if(pret==0)
// 			{
// 				SleepList::head = tek->next;
// 				retVal=tek->pcb;
// 				t=tek->time;
// 				pret=tek->next;
// 				delete tek;
// 				break;
// 			}
// 			else
// 			{
// 				pret->next=tek->next;
// 				retVal=tek->pcb;
// 				t=tek->time;
// 				pret=tek->next;
// 				delete tek;
// 				break;
				
// 			}
// 		}
// 		else
// 		{
// 			pret = tek;
// 			tek = tek->next;
// 		}
// 	}
// 	tek=pret;
// 	while(tek!=0){
// 		tek->time+=t;
// 		tek=tek->next;
// 	}
// 	unlock
// 	return retVal;
// }

PCB* SleepList::get(const int index){
	lock
	SleepElem* tek = SleepList::head;
	int i=0;
	while(tek!=0){
		if(index==i){
			return (tek->pcb);
		}
		else
		{
			tek=tek->next;
			i++;
		}
	}
	unlock
	return 0;
}

PCB* SleepList::getById(const ID id){
	lock
	SleepElem* tek = SleepList::head;
	while(tek!=0)
	{
		if(tek->pcb->getID()==id){
			unlock
			return (tek->pcb);
		}
		else
		{
			tek=tek->next;
		}
	}
	unlock
	return 0;

}

PCB* SleepList::getByName(const TName name){
	lock
	SleepElem* tek = SleepList::head;
	while(tek!=0)
	{
		if(strcmp(tek->pcb->getName(),name)==0)
		{
			unlock
			return (tek->pcb);
		}
		else
		{
			tek=tek->next;
		}
	}
	unlock
	return 0;
}

PCB* SleepList::removeHead(){
	lock
	PCB* ret;
	SleepElem* del;
	if(SleepList::head!=0){
		ret=SleepList::head->pcb;
		del=SleepList::head;
		SleepList::head=SleepList::head->next;
		delete del;
		unlock
		return ret;
	}
	unlock
	
	return 0;
}

PCB* SleepList::tick(){
	lock
	PCB* retVal=0;
	SleepElem* tek;
	if(SleepList::head!=0){
		if(SleepList::head->time==0){
			retVal=removeHead();
			// cprintf("remH: %d\n",retVal->getID());
		}
		else{
			if(refreshFlag){
				SleepList::head->time--;
				refreshFlag=0;
			}
			// while(tek!=0){
			// 	tek->time-=1;
			// 	tek=tek->next;
			// }
		}
	}
	unlock
	return retVal;
}

int SleepList::refreshFlag=1;

void SleepList::refresh(){
	lock
		refreshFlag=1;
		PCB* putInQue=SleepList::tick();
		// refreshFlag=0;
		while(putInQue!=0)
		{
			// cprintf("sth in list");
			Scheduler::put(putInQue);
			putInQue=SleepList::tick();
		}
		// refreshFlag=1;	
		// cprintf("tick");
	unlock

}