//File: System.h
#ifndef _SYSTEM_H_
#define _SYSTEM_H_


#include "lock.h"

#include "IdleThr.h"
#include "StartThr.h"
#include "dos.h"




typedef void interrupt (*Intrpt)(...);


class System
{
public:
	static int contextSwitch;

	static void initializeAndStart();

	static void kill();

	


	static int verbose;


	static int argCount;
	static char** argVect;

	static void interrupt timer(...);


	static IdleThread* idleThread;
	static StartThread* startThread;
	static Time timeLeft;
private:
	static Intrpt oldR;
};





#endif