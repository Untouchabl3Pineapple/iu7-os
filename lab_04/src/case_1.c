#include <stdio.h>
#include <unistd.h>

/* 
    Задание 1:

    Написать программу, запускающую не мене двух новых процессов системным вызовом fork().
    В предке вывести собственный идентификатор (функция getpid()), идентификатор группы ( функция getpgrp())
    и идентификаторы потомков. В процессе-потомке вывести собственный идентификатор, идентификатор предка
    (функция getppid()) и идентификатор группы. Убедиться, что при завершении процесса-предка потомок,
    который продолжает выполняться, получает идентификатор предка (PPID), равный 1 или идентификатор процесса-посредника.
*/

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

    printf("Parent: id: %d pgroup: %d first child: %d second child: %d\n", getpid(), getpgrp(), childpid_first, childpid_second);
}