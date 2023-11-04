#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

void convertToLower(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

bool isWordPresent(char *message, char *word)
{
    bool found = false;
    char *token = strtok(message, " ");
    while (token != NULL)
    {
        char *token_lower = strdup(token);
        convertToLower(token_lower);
        char *word_lower = strdup(word);
        convertToLower(word_lower);
        if (strcmp(token_lower, word_lower) == 0)
        {
            found = true;
            break;
        }
        free(token_lower);
        free(word_lower);
        token = strtok(NULL, " ");
    }
    return found;
}

void readWordsFromFile(char *filename, char words[100][100], int *num_words)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening words file\n");
        exit(1);
    }

    char word[100];
    while (fscanf(file, "%s", word) != EOF)
    {
        strcpy(words[*num_words], word);
        (*num_words)++;
    }
    fclose(file);
}

void decodeMessages(char *message, char words[100][100], int num_words)
{
    int counts[100] = {0};
    char solution[1000] = "";
    char *token = strtok(message, " ");
    while (token != NULL)
    {
        char *token_lower = strdup(token);
        convertToLower(token_lower);
        for (int i = 0; i < num_words; i++)
        {
            char *word_lower = strdup(words[i]);
            convertToLower(word_lower);
            if (strcmp(token_lower, word_lower) == 0)
            {
                counts[i]++;
            }
            free(word_lower);
        }
        free(token_lower);
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < num_words; i++)
    {
        if (counts[i] > 0)
        {
            char count_str[10];
            sprintf(count_str, "%d", counts[i]);
            strcat(solution, words[i]);
            strcat(solution, count_str);
        }
    }

    printf("Decoded message: %s\n", solution);
}

void printCurrentDirectory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working directory: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
    }
}

int main()
{
    FILE *file;
    char *filename = "words.txt";
    char message[1000];
    printCurrentDirectory();

    file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    if (fgets(message, sizeof(message), file) == NULL)
    {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }

    fclose(file);

    char words[100][100];
    int num_words = 0;
    readWordsFromFile("words.txt", words, &num_words);

    decodeMessages(message, words, num_words);

    return 0;
}
