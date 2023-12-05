#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;

    // Fork a new process
    child_pid = fork();

    if (child_pid == -1)
    {
        // Forking failed
        perror("Fork failed");
        return 1;
    }
    else if (child_pid == 0)
    {
        // This code runs in the child process
        printf("Child process (PID: %d)\n", getpid());
        sleep(2); // Simulate some work in the child process
        exit(42); // Exit the child process with status 42
    }
    else
    {
        // This code runs in the parent process
        printf("Parent process (PID: %d)\n", getpid());

        // Wait for the specific child process to terminate
        int status;
        pid_t terminated_pid = waitpid(child_pid, &status, 0);

        if (terminated_pid == -1)
        {
            perror("waitpid failed");
            return 1;
        }

        if (WIFEXITED(status))
        {
            printf("Child process %d terminated with status %d\n", terminated_pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child process %d terminated by signal %d\n", terminated_pid, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("Child process %d stopped by signal %d\n", terminated_pid, WSTOPSIG(status));
        }
        else
        {
            printf("Child process %d terminated abnormally\n", terminated_pid);
        }
    }

    return 0;
}
