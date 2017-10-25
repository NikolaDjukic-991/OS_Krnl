#ifndef _STARTTHREAD_H_
#define _STARTTHREAD_H_

#include "Thread.h"


class StartThread : public Thread {
public:
	StartThread():Thread("Starting"){}
	~StartThread(){}

	int getRet(){return retVal;}

protected:
	void run();

private:
	int retVal;

};


#endif