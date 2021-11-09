#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int childpid = fork();
    // printf("CP %d\n", childpid);

    if (childpid == -1)
    {
        perror("Can’t fork.\n");

        return 1;
    }
    else if (childpid == 0)
    {
        while (1)
        {
            // printf("Потомок\n");
            printf("PID: %d\n", getpid());
        }

        return 0;
    }
    else
    {
        while (1)
        {
            // printf("Родитель\n");
            printf("PID: %d\n", getpid());
        }

        return 0;
    }
}