#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

void toLower(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

struct WordCount
{
    char word[MAX_WORD_LENGTH];
    int count;
};

int main()
{
    FILE *file;
    char word[MAX_WORD_LENGTH];
    char filename[] = "data_01.txt";
    struct WordCount *words = malloc(sizeof(struct WordCount));
    if (words == NULL)
    {
        fprintf(stderr, "Memory allocation failed");
        return 1;
    }
    int maxWords = 1;
    int wordCount = 0;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Could not open file %s", filename);
        free(words);
        return 1;
    }

    while (fscanf(file, "%s", word) == 1)
    {
        toLower(word);
        int found = 0;
        for (int i = 0; i < wordCount; i++)
        {
            if (strcmp(words[i].word, word) == 0)
            {
                words[i].count++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            if (wordCount == maxWords)
            {
                maxWords *= 2;
                words = realloc(words, maxWords * sizeof(struct WordCount));
                if (words == NULL)
                {
                    fprintf(stderr, "Memory reallocation failed");
                    return 1;
                }
            }
            strcpy(words[wordCount].word, word);
            words[wordCount].count = 1;
            wordCount++;
        }
    }

    fclose(file);

    for (int i = 0; i < wordCount; i++)
    {
        printf("%s%d", words[i].word, words[i].count);
    }

    free(words);
    return 0;
}
