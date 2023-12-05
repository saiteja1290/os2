#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    pid_t pid;
    time_t t;
    int status;
    if ((pid = fork()) < 0)
        perror("fork() error");
    else if (pid == 0)
    {
        time(&t);
        printf("child (pid %d) started at %s", (int)getpid(), ctime(&t));
        sleep(5);
        time(&t);
        printf("child exiting at %s", ctime(&t));
        exit(42);
    }
    else
    {
        printf("parent has forked child with pid of %d\n", (int)pid);
        time(&t);
        printf("parent is starting wait at %s", ctime(&t));
        if ((pid = wait(&status)) == -1)
            perror("wait() error");
    }
}