#include "Semaphore.h"
#include "lock.h"
#include "KernSem.h"

Semaphore::Semaphore(int init){
	lock
	myImpl = new KernelSem(init);
	unlock
}

Semaphore::~Semaphore(){
	delete myImpl;
}

int Semaphore::wait(){
	return myImpl->wait();
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val() const{
	return myImpl->val();
}


