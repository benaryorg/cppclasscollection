#ifndef __BENARYORG_THREAD__
#define __BENARYORG_THREAD__

namespace cppbenaryorg
{

class Thread
{
public:
	Thread(void *(*function)(void *)=0,void *argument=0);
	virtual void *call(void);
	virtual bool start(void);
	virtual bool stop(void);
	virtual bool join(void);

	virtual void *(*getFunction(void))(void *);
	virtual void setFunction(void *(*function)(void *));

	virtual void *getArgument(void);
	virtual void setArgument(void *argument);

	virtual bool isRunning(void);

	virtual unsigned long int getThreadId(void);

private:
	bool running;
	unsigned long int thread;
	void *(*function)(void *);
	void *argument;
};

};

#endif /**__BENARYORG_THREAD__**/
