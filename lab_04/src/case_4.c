#include "status.h"

int main(void)
{
    const char *msg_1 = "Overleaf is used by over eight million students and academics at 3,600 institutions worldwide.\n";
    const char *msg_2 = "Just want to say that I am really grateful for Overleaf, it has enabled a slew of research and teaching development in my work that would have been annoyingly difficult before. Even people who don’t know LaTeX are participating with me on research proposals and that’s saying something if you know what LaTeX is like for the uninitiated.\n";

    char readbuffer[1000];
    int fd[2];

    int status;
    int childpid_first, childpid_second;

    if (pipe(fd) == -1)
    {
        printf("1\n");
        perror("Can't pipe\n");
        return -1;
    }

    childpid_first = fork();
    if (childpid_first == -1)
    {
        perror("Can’t fork.\n");
        return -1;
    }
    else if (childpid_first == 0)
    {
        close(fd[0]);
        write(fd[1], msg_1, strlen(msg_1));

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
        close(fd[0]);
        write(fd[1], msg_2, strlen(msg_2));

        return 0;
    }

    wait(&status);
    check_status(status);
    wait(&status);
    check_status(status);

    printf("Parent: id: %d pgroup: %d first child: %d second child: %d\n\n", getpid(), getpgrp(), childpid_first, childpid_second);

    close(fd[1]);
    read(fd[0], readbuffer, sizeof(readbuffer));
    printf("%s", readbuffer);

    return 0;
}
