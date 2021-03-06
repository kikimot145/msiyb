/*!
\file thread.h "server\desktop\src\common\thread.h"
\authors Dmitry Zaitsev
\copyright � MSiYB 2017
\license GPL license
\version 1.0
\date 02 March 2017
*/

#pragma once
#define MAX_INT 2147483646

#ifdef _WIN32
#include "../cross/windows/winthread.h"
typedef WinThread OSThread;
#elif _unix_
#include "../cross/unix/unixthread.h"
typedef UnixThread OSThread;
#endif

#include <vector>

class Thread;

/// Single thread info
typedef struct
{
	int threadID;				///< Current thread local ID.
	OSThread *threadOSPtr;		///< Thread ptr on OS implementation.
	void *result;				///< Value returned from thread function.
	Thread *thr;				///< Thread object.
} ThreadData;

/*!
\class Thread thread.h "server\desktop\src\common\thread.h"
\brief  Thread interface.
Provide interface to common thread structure and it's action.
Factory for unix/bsd/windows structure of thread.
*/
class Thread
{
public:
	static int lastThreadID;				///< ID of last thread
	static vector<ThreadData*> threadList;	///< List of launched threads

	/*!
	Initialises OS depended thread structure.
	*/
	Thread();

	/*!
	Dealocates memory of OS depended object.
	Decrease active threads count
	*/
	~Thread();

	/*!
	Try to start new thread. If number of active threads is already
	equal to max thread count, looks for completed threads and tried one more time.
	\param[in] threadFunc Pointer to a function to be executed by the thread.
	\param[in] threadFuncArgs A pointer to a variable to be passed to the thread.
	\param[out] result Value returned from thread function.
	\return Thread ID if new thread started.
	*/
	int Start(void *threadFunc, void *threadFuncArgs, void *result = nullptr);

	/*!
	Suspend programm before all threads in pool completed their work.
	*/
	void WaitToComplete();

	/*!
	Checks if thread completed it's work
	\param[in] threadID Id if thread to check.
	\return TRUE if completed, FALSE in other case
	*/
	bool IsCompleted(int threadID);

	/*!
	Looks for completed threads in threads list and free them.
	*/
	static void CheckListCompleted();

	/*!
	Looks if thread completed and deletes it from thread list.
	\param[in] ID Id of thread to check.
	*/
	static void CheckThreadCompleted(int threadID);

private:
	vector<ThreadData*> threadPool;	///< Pointers to threads launched from this object.
};

int Thread::lastThreadID = -1;
vector<ThreadData*> Thread::threadList;
