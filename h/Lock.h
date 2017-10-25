#ifndef _LOCK_H_
#define _LOCK_H_

#define lock asm pushf;asm cli; 

#define unlock asm popf;

#define PREPAREENTRY(a,b);\
	\
	Intrpt oldIntr##a = getvect(a);\
	\
	void interrupt intr##a(...);\
	IVTEntry entry##a (a,intr##a);\
	\
	void interrupt intr##a(...){\
		entry##a.fire();\
		if(b)\
			(*oldIntr##a)();\
	}\

#endif
