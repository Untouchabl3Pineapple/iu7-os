#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int childpid_first = fork(), childpid_second;
    
    if (childpid_first == -1)
    {
        perror("Can't fork\n");
        return -1;
    }
    else if (childpid_first == 0)
    {
        sleep(1);
        printf("\nFirst child: id: %d ppid: %d  pgroup: %d\n", getpid(), getppid(), getpgrp());
        return 0;
    }

    childpid_second = fork();
    if (childpid_second == -1)
    {
        perror("Can't fork\n");
        return -1;
    }
    else if (childpid_second == 0)
    {
        sleep(1);
        printf("\nSecond child: id: %d ppid: %d  pgroup: %d\n\n", getpid(), getppid(), getpgrp());
        return 0;
    }

    printf("Parent: id: %d pgroup: %d first child: %d second child: %d\n", getpid(), getpgrp(), childpid_first, childpid_second);

    return 0;
}
