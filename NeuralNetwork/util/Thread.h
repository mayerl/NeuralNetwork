struct threadObj {};

void createThread(threadObj *ptr, void *(*thread_func)(void*), void *t_params);
void cancelThread(threadObj *ptr);
int Get_Key(void);