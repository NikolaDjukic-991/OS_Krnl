//File: IdleThread.h

#ifndef _IDLETHREAD_H_
#define _IDLETHREAD_H_

#include "Thread.h"

class IdleThread:public Thread
{
public:
	IdleThread():Thread("idle"){}
	~IdleThread(){}


	void run();


};

#endif