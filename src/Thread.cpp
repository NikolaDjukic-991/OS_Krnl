#include "Thread.h"
#include "PCB.h"
#include "lock.h"

ID Thread::start(){
	return myPCB->start();
}

int Thread::sleep(Time timeToSleep){
	return PCB::sleep(timeToSleep);
}

int Thread::wakeUp(ID id){
	return PCB::wakeUp(id);
}

int Thread::waitForChildren(){
	return PCB::waitForChildren();
}

ID Thread::getId(){
	return myPCB->getID();
}

TName Thread::getName(){
	return myPCB->getName();
}

Thread* Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}

ID Thread::getIdOf(TName name){
	return PCB::getIdOf(name);
}

TName Thread::getName(ID id){
	return PCB::getName(id);
}

Thread::~Thread(){
	delete myPCB;
} 

Thread::Thread(TName name, StackSize stackSize,Time timeSlice){
	lock
	myPCB=new PCB(name,stackSize,timeSlice,this);
	unlock
}

int Thread::waitToComplete(){
	return myPCB->waitToComplete();
}

