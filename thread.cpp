#include "thread.h"

#if defined(linux)||defined(__linux)||defined(__linux__)
#define _linux
#elif defined(WIN32)||defined(_WIN32)||defined(__WIN32)||defined(__WIN32__)
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

#ifdef _win32
DWORD *windows_helper_function(LPVOID arg)
{
	Thread *thread=reinterpret_cast<Thread *>(arg);
	return (DWORD *)thread->call();
}
#endif /**_win32**/

Thread::Thread(void *(*f)(void *),void *arg)
{
	this->setFunction(f);
	this->setArgument(arg);
	this->running=false;
	this->thread=0;
}

void *Thread::call(void)
{
	if(this->getFunction()&&!this->isRunning())
	{
		return this->getFunction()(this->getArgument());
	}
	else
	{
		this->running=false;
		return 0;
	}
}

bool Thread::start(void)
{
	if(this->isRunning()||!this->getFunction())
	{
		return false;
	}
#if defined(_linux)
	this->running=!pthread_create(&this->thread,NULL,this->getFunction(),this->getArgument());
#elif defined(_win32)
	this->running=CreateThread(0,0,(LPTHREAD_START_ROUTINE)windows_helper_function,this,0,&this->thread);
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
		ExitThread(this->thread);
#endif
		if(ok)
		{
			this->running=false;
		}
		return ok;
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
		if(ok)
		{
			this->running=false;
		}
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

unsigned long int Thread::getPThread(void)
{
	return this->thread;
}
