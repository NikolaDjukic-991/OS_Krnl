//File: StartThr.cpp

#include "StartThr.h"
#include "System.h"
extern int userMain(int argCount, char* argVect[]);

	void StartThread::run(){
		retVal=userMain(System::argCount, System::argVect);

	}