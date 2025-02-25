//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Variables declaration
    pid_t p, pid;
    int status;

    printf("Parent: %d\n", getpid());
    p = fork();

    if (p > 0) // Parent
    {
        printf("Parent: %d, my son has PID = %d\n", getpid(), p);

        pid = wait(&status); // The father waits the son's exit
        if (WIFSIGNALED(status)) // true if (bool)
            printf("Parent, my son is not terminated naturally. Signal caused: %d\n", WTERMSIG(status));
        else // false if
            printf("Programm terminated\n");
    }
    else if (p == 0) // Son
    {
        printf("Son: %d, my parent has PID = %d\n", getpid(), getppid());
        printf("Son, I'm giving to my parent the number 25\n");
        exit(25);
    }
    else
    {
        printf("ERROR!\n");
    }

    return 0;
}