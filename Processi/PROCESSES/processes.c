// MORE THAN ONE PROCESS ID
// the fork call is done by the parent process and child too.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Variables declaration
    pid_t id1 = fork();
    pid_t id2 = fork();

    if (id1 == 0)
    {
        if (id2 == 0) // child of child
        {
            printf("We are the process y\n");
        }
        else // child of parent
        {
            printf("We are the process x\n");
        }
    }
    else
    {
        if (id2 == 0) // other child of parent
        {
            printf("We are process z\n");
        }
        else
        {
            printf("We are the parent process!\n");
        }
    }

    // wait for every child process to finish
    while (wait(NULL) != -1 || errno != ECHILD)
    {
        printf("Waiting for a child to finish\n");
    }

    return 0;
}