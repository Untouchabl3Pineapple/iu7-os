#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIM 1000


int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}


int damLevRecWithoutCache(char *s1, int i, char *s2, int j)
{
    if (i == 0)
        return j;
    else if (j == 0)
        return i;

    int flag;
    if (s1[i - 1] == s2[j - 1])
        flag = 0;
    else
        flag = 1;
    int res1 = damLevRecWithoutCache(s1, i - 1, s2, j) + 1;
    int res2 = damLevRecWithoutCache(s1, i, s2, j - 1) + 1;
    int res3 = damLevRecWithoutCache(s1, i - 1, s2, j - 1) + flag;

    int result = min(res1, res2, res3);
    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
        result = min(result, damLevRecWithoutCache(s1, i - 2, s2, j - 2) + 1, MAX_LIM);
    return result;
}

int main(void)
{
    char str1[100];
    char str2[100];

    printf("Введите первую строку: ");
    scanf("%s", str1);
    printf("Введите вторую строку: ");
    scanf("%s", str2);

    size_t str1_len = strlen(str1), str2_len = strlen(str2);

    int result = damLevRecWithoutCache(str1, str1_len, str2, str2_len);

    printf("Редакционное расстояние: %d\n", result);

    return 0;
}