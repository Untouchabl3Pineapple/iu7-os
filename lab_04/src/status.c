#include "status.h"

void check_status(const int status)
{
    if (WIFEXITED(status))
    {
        printf("Дочерний процесс завершен нормально\n\n");
        printf("Код завершения дочернего процесса: %d\n\n", WEXITSTATUS(status));
        return;
    }
    else if (WIFSIGNALED(status))
    {
        printf("Дочерний процесс завершается неперехватываемым сигналом\n\n");
        printf("Номер сигнала: %d\n\n", WTERMSIG(status));
        return;
    }
    else if (WIFSTOPPED(status))
    {
        printf("Дочерный процесс остановился\n\n");
        printf("Номер сигнала: %d\n\n", WSTOPSIG(status));
        return;
    }
}
