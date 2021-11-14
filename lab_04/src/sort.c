#include <stdio.h>

int main(void)
{
    int n;

    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    int a[n];
    printf("Введите элементы массива: ");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", (a + i));
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}