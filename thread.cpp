#include "thread.h"

#if (defined(linux)||defined(__linux)||defined(__linux__))&&!defined(_linux)
#define _linux
#elif (defined(WIN32)||defined(_WIN32)||defined(__WIN32)||defined(__WIN32__))&&!defined(_win32)
#define _win32
#endif


#if defined(_linux)
#include <pthread.h>
#include <signal.h>
#elif defined(_win32)
#include <windows.h>
#else
#error undefined platform
#endif

using namespace cppbenaryorg;

#if defined(_win32)
DWORD *helper_function(LPVOID arg)
{
	Thread *thread=reinterpret_cast<Thread *>(arg);
	return (DWORD *)thread->call();
}
#elif defined(_linux)
void *helper_function(void *arg)
{
	Thread *thread=reinterpret_cast<Thread *>(arg);
	return thread->call();
}
#endif

Thread::Thread(void *(*f)(void *),void *arg)
{
	this->setFunction(f);
	this->setArgument(arg);
	this->running=false;
	this->thread=0;
}

void *Thread::call(void)
{
	void *ret=0;
	if(this->getFunction())
	{
		this->running=true;
		ret=this->getFunction()(this->getArgument());
	}
	this->running=false;

	return ret;
}

bool Thread::start(void)
{
	if(this->isRunning()||!this->getFunction())
	{
		return false;
	}
#if defined(_linux)
	this->running=!pthread_create(&this->thread,NULL,helper_function,this);
#elif defined(_win32)
	HANDLE h=CreateThread(0,0,(LPTHREAD_START_ROUTINE)helper_function,this,0,&this->thread);
	this->running=!!h;
	this->thread=(unsigned int)h;
#endif
	return this->isRunning();
}

bool Thread::stop(void)
{
	if(!this->isRunning())
	{
		return false;
	}
	else
	{
		bool ok=true;
#if defined(_linux)
		ok=!pthread_kill(this->thread,SIGQUIT);
#elif defined(_win32)
		TerminateThread((HANDLE)this->thread,0);
#endif
		this->running=!ok;
	}
}

bool Thread::join(void)
{
	if(!this->isRunning())
	{
		return false;
	}
	else
	{
		bool ok=true;
#if defined(_linux)
		ok=!pthread_join(this->thread,NULL);
#elif defined(_win32)
		while(this->isRunning())
		{
			Sleep(1);
		}
#endif
		this->running=!ok;
		return ok;
	}
}

void *(*Thread::getFunction(void))(void *)
{
	return this->function;
}

void Thread::setFunction(void *(*f)(void *))
{
	this->function=f;
}

void *Thread::getArgument(void)
{
	return this->argument;
}

void Thread::setArgument(void *arg)
{
	this->argument=arg;
}

bool Thread::isRunning(void)
{
	return this->running;
}

unsigned long int Thread::getThreadId(void)
{
	return this->thread;
}
