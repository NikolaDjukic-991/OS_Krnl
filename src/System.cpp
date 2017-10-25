//File: System.cpp

#include "System.h"
#include "PCB.h"
#include "SleepL.h"
// #include "Thread.h"

	// extern void tick();

	int System::contextSwitch=0;

	int System::verbose=1;

	int System::argCount=0;
	char** System::argVect=0;
	Intrpt System::oldR = 0;
	Time System::timeLeft = 0;
	PCB* PCB::running=new PCB("initialThr", 4096,1,0);
	IdleThread* System::idleThread=new IdleThread();
	StartThread* System::startThread=new StartThread();

	int main(int argc, char* argv[]){
		System::argVect=argv;
		System::argCount=argc;
		System::initializeAndStart();
		int retVal = System::startThread->getRet();
		System::kill();
		return retVal;
	}


	void interrupt System::timer(...){
		// lock
		
		static unsigned int tsp;
		static unsigned int tss;
		static PCB* next;

		
		asm cli;
		// tick(); //TODO ENABLE LATER

		if(!System::contextSwitch){
			(*System::oldR)();
			SleepList::refresh();
			System::timeLeft--;
		}
		if(System::contextSwitch || System::timeLeft<=0){
			asm{
				mov tsp, sp
				mov tss, ss
			}
			if(PCB::running){
				PCB::running->sp = tsp;
				PCB::running->ss = tss;
			}
			if(PCB::running!=PCB::getIdlePCB()
				&& PCB::running->imBlockedOn==0
				&& PCB::running->eventBlock==0
				&& !PCB::running->isSleeping()){

				Scheduler::put(PCB::running);
		}
		next=Scheduler::get();
		if(next==0)
			next=PCB::getIdlePCB();

		PCB::running=next;
		System::timeLeft=PCB::running->getTimeSlice();

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		System::contextSwitch=0;

		asm{
			mov sp, tsp
			mov ss, tss
		}
	}
	asm sti;
}

void System::initializeAndStart(){
		lock
		System::oldR= getvect(8);
		setvect(8,timer);

		// cout<<"timer interrupt set";
		// idleThread = new IdleThread();
		// startThread = new StartThread();
		System::startThread->start();
		System::idleThread->start();
		// cout<<"idleThr started";
		// cout<<"startThr started";
		unlock
		PCB::waitToComplete(startThread->getId());
	}

void System::kill(){
		// PCB::waitToComplete(startThread->getId());
		lock
		setvect(8,oldR);
		delete startThread;
		delete idleThread;
		SleepList::dispose();
		unlock
	}

	void dispatch(){
		lock
		System::contextSwitch=1;
		unlock
		System::timer();
		
	}

