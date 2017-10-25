#include "PCBList.h"
#include "String.h"
#include "lock.h"

PCBList::PCBList(){
	head=0;
	tail=0;
}

PCBList::~PCBList(){
	lock
	PCBElem* tek;
	while(head!=0){
		tek=head;
		head = head->next;
		delete tek;
		tek = head;
	}
	unlock

}

void PCBList::put(PCB* pcb){
	lock
	if(head==0){
		head=tail=new PCBElem(pcb);
	}
	else{
		tail->next=new PCBElem(pcb);
		tail = tail->next;
	}
	unlock
}

PCB* PCBList::remove(const int index){
	lock
	int i=0;
	PCBElem* tek=head;
	PCBElem* pret=0;
	PCB* retVal;

	while(tek!=0)
	{
		if(index==i)
		{
			if(pret==0)
			{
				head = tek->next;
				retVal=tek->pcb;
				delete tek;
				unlock
				return retVal;
			}
			else
			{
				pret->next=tek->next;
				retVal=tek->pcb;
				delete tek;
				unlock
				return retVal;
			}
		}
		else
		{
			pret = tek;
			tek = tek->next;
			i++;
		}
	}
	unlock
	return 0;
}

PCB* PCBList::removeById(const ID id){
	lock
	PCBElem* tek=head;
	PCBElem* pret=0;
	PCB* retVal;

	while(tek!=0)
	{
		if(tek->pcb->getID()==id)
		{
			if(pret==0)
			{
				head = tek->next;
				retVal = tek->pcb;
				delete tek;
				unlock
				return retVal;
			}	
			else
			{
				pret->next=tek->next;
				retVal=tek->pcb;
				delete tek;
				unlock
				return retVal;
			}
		}
		else
		{
			pret = tek;
			tek = tek->next;
		}
	}
	unlock
	return 0;
}


PCB* PCBList::removeByName(const TName name){
	lock
	PCBElem* tek=head;
	PCBElem* pret=0;
	PCB* retVal;

	while(tek!=0)
	{
		if(strcmp(tek->pcb->getName(),name)==0)
		{
			if(pret==0)
			{
				head = tek->next;
				retVal = tek->pcb;
				delete tek;
				unlock
				return retVal;
			}	
			else
			{
				pret->next=tek->next;
				retVal=tek->pcb;
				delete tek;
				unlock
				return retVal;
			}
		}
		else
		{
			pret = tek;
			tek = tek->next;
		}
	}
	unlock
	return 0;
}


//not locked
PCB* PCBList::get(const int index)const{
	PCBElem* tek = head;
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
	return 0;
}

PCB* PCBList::getById(const ID id)const{
	PCBElem* tek = head;
	while(tek!=0)
	{
		if(tek->pcb->getID()==id){
			return (tek->pcb);
		}
		else
		{
			tek=tek->next;
		}
	}
	return 0;

}

PCB* PCBList::getByName(const TName name)const{
	PCBElem* tek = head;
	while(tek!=0)
	{
		if(strcmp(tek->pcb->getName(),name)==0)
		{
			return (tek->pcb);
		}
		else
		{
			tek=tek->next;
		}
	}
	return 0;
}