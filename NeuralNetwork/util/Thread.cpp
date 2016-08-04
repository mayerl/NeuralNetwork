#ifdef _WIN32

#include <windows.h>
#include <conio.h>

struct threadObj {
	DWORD id;
	HANDLE thread;
};

struct threadHandler {
	void *(*thread_func)(void*);
	void *t_params;
};

DWORD WINAPI handleThread(LPVOID lpParameter)
{
	struct threadHandler *handler = (threadHandler *)lpParameter;
	void *(*thread_func)(void*) = handler->thread_func;
	void *t_params = handler->t_params;
	thread_func(t_params);
	return 0;
}

void createThread(threadObj *ptr, void *(*thread_func)(void*), void *t_params) {

	struct threadHandler * handler = new struct threadHandler;
	handler->thread_func = thread_func;
	handler->t_params = t_params;
	ptr->thread = CreateThread(0, 0, handleThread, handler, 0, &ptr->id);

}

void cancelThread(threadObj *ptr) {
	DWORD exitCode;
	GetExitCodeThread(ptr->thread, &exitCode);
	TerminateThread(ptr->thread, 0);
}

int Get_Key(void) {
	int key;
	key = _getch();
	return key;
}


#else

#include <pthread.h>
#include <unistd.h>
#include <termios.h>

struct threadObj {
	pthread_t thread;
};

void createThread(threadObj *ptr, void *(*thread_func)(void*), void *t_params) {

	pthread_create(&ptr->thread, NULL, thread_func, t_params);

}

void cancelThread(threadObj *ptr) {

	pthread_cancel(ptr->thread);

}

int Get_Key(void) {
	int key;
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt); // 1473
	memcpy((void *)&newt, (void *)&oldt, sizeof(struct termios));
	newt.c_lflag &= ~(ICANON);  // Reset ICANON
	newt.c_lflag &= ~(ECHO);    // Echo off, after these two .c_lflag = 1217
	tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 1217
	key = getchar(); // works like "getch()"
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return key;
}


#endif