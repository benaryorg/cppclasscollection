#ifndef __BENARYORG_THREAD__
#define __BENARYORG_THREAD__

namespace cppbenaryorg
{

class Thread
{
public:
	Thread(void *(*function)(void *)=0,void *argument=0);
	void *call(void);
	bool start(void);
	bool stop(void);
	bool join(void);

	void *(*getFunction(void))(void *);
	void setFunction(void *(*function)(void *));

	void *getArgument(void);
	void setArgument(void *argument);

	bool isRunning(void);

	unsigned long int getPThread(void);

private:
	bool running;
	unsigned long int thread;
	void *(*function)(void *);
	void *argument;
};

};

#endif /**__BENARYORG_THREAD__**/
