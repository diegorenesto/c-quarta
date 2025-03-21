// PROCESS ID

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Variables declaration
    pid_t id = fork();
    int res;

    if (id == 0)
    {
        sleep(1);
    }
    printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());

    res = wait(NULL);
    if (res == -1)
    {
        printf("No children to wait for\n");
    }
    else
    {
        printf("%d finished execution\n", res);
    }

    return 0;
}