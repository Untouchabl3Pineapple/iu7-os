#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    Задание 2:

    написать программу по схеме первого задания, но в процессе- предке 
    выполнить системный вызов wait(). Убедиться, что в этом случае идентификатор
    процесса потомка на 1 больше идентификатора процесса-предка.

    Чуть совмещенная программа с:
    
    Пример 2. Системный вызов wait()
    В этом упражнении вы слегка измените программу, чтобы можно было подождать
    и проверить код состояния дочернего процесса. Назовите новую программу wait.c.
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
    // Первый дочерний процесс
    int childpid_first = fork();
    if (childpid_first == -1)
    {
        // Прозошла какая-то ошибка
        perror("Can't fork\n");
        return -1;
    }
    else if (childpid_first == 0)
    {
        sleep(1); // чтобы подождать предка
        printf("\nFirst child: id: %d ppid: %d  pgroup: %d\n", getpid(), getppid(), getpgrp());
        return 0; // чтобы успешно завершить
    }

    // Второй дочерний процесс
    int childpid_second = fork();
    if (childpid_second == -1)
    {
        // Если при создании произошла ошибка
        perror("Can't fork\n");
        return -1;
    }
    else if (childpid_second == 0)
    {
        sleep(1); // чтобы подождать предка
        printf("\nSecond child: id: %d ppid: %d  pgroup: %d\n\n", getpid(), getppid(), getpgrp());
        return 0; // чтобы успешно завершить
    }

    int status, childpid;
    childpid = wait(&status);
    check_status(status);
    childpid = wait(&status);
    check_status(status);

    printf("Parent: id: %d pgroup: %d first child: %d second child: %d\n", getpid(), getpgrp(), childpid_first, childpid_second);
}