#include "thread.h"
#include <pthread.h>
#include <signal.h>

using namespace cppbenaryorg;

Thread::Thread(void *(*f)(void *),void *arg)
{
	this->setFunction(f);
	this->setArgument(arg);
	this->running=false;
	this->thread=0;
}

void *Thread::call(void)
{
	if(this->getFunction())
	{
		return this->getFunction()(this->getArgument());
	}
	else
	{
		return 0;
	}
}

bool Thread::start(void)
{
	if(this->isRunning()||!this->getFunction())
	{
		return false;
	}
	this->running=!pthread_create(&this->thread,NULL,this->getFunction(),this->getArgument());
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
		bool ok=!pthread_kill(this->thread,SIGQUIT);
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
		bool ok=!pthread_join(this->thread,NULL);
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
