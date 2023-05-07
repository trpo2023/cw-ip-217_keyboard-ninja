#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int randf(void)
{
    srand(time(NULL));
    return (rand() % 10) + 1;
}

void GetWords(char **words, int rand_num)
{
    FILE *file = fopen("Input.txt", "r");
    words[0] = (char *)malloc(sizeof(char) * 500);
    for (int i = 1; i <= rand_num; i++)
    {
        fgets(words[0], 500, file);
    }
}

char *getString()
{
    int rand_num = randf();
    printf("%d ", rand_num);

    char **words = (char **)malloc(500 * sizeof(char *));
    assert((words != NULL) && "Memory not allocated\n");
    GetWords(words, rand_num);
    printf("%s", words[0]);
    return words[0];
}