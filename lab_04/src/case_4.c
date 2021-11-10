#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
    Задание 4:

    Написать программу, в которой предок и потомок обмениваются сообщением
    через программный канал.
*/

void check_status(const int status)
{
    if (WIFEXITED(status) != 0)
    {
        printf("Дочерний процесс завершен нормально\n\n");
        printf("Код завершения дочернего процесса: %d\n\n", WEXITSTATUS(status));
        return;
    }
    else if (WIFSIGNALED(status) != 0)
    {
        printf("Дочерний процесс завершается неперехватываемым сигналом\n\n");
        printf("Номер сигнала: %d\n\n", WTERMSIG(status));
        return;
    }
    else  //if (WIFSTOPPED(status) != 0)
    {
        printf("Дочерный процесс остановился\n\n");
        printf("Номер сигнала: %d\n\n", WSTOPSIG(status));
        return;
    }
}

int main(void)
{
    const char *msg_1 = "Hello, Dad\n";
    const char *msg_2 = "Hello, Dude\n";
    char readbuffer[100];
    char temp[100];

    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("1\n");
        perror("Can't pipe\n");
        return -1;
    }

    // Первый дочерний процесс
    int childpid_first = fork();
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

    // Второй дочерний процесс
    int childpid_second = fork();
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

    int status, childpid;
    childpid = wait(&status);
    check_status(status);
    childpid = wait(&status);
    check_status(status);

    printf("Parent: id: %d pgroup: %d first child: %d second child: %d\n\n", getpid(), getpgrp(), childpid_first, childpid_second);

    close(fd[1]);
    read(fd[0], readbuffer, sizeof(readbuffer));
    printf("%s", readbuffer);

    return 0;
}
