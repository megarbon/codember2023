#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Function to decode the messages
bool isWordPresent(char *message, char *word)
{
    bool found = false;
    char *token = strtok(message, " ");
    while (token != NULL)
    {
        char *token_lower = strdup(token);
        for (int i = 0; token_lower[i]; i++)
        {
            token_lower[i] = tolower(token_lower[i]);
        }
        char *word_lower = strdup(word);
        for (int i = 0; word_lower[i]; i++)
        {
            word_lower[i] = tolower(word_lower[i]);
        }

        if (strcmp(token_lower, word_lower) == 0)
        {
            printf("The word '%s' is present in the sentence.\n", word);
            found = true;
        }
        free(token_lower);
        free(word_lower);
        token = strtok(NULL, " ");
    }
    return found;
}

void decodeMessages(char *message, char *words[], int num_words)
{
    char solution[1000];
    int count = 0;

    for (int i = 0; i < num_words; i++)
    {
        if (isWordPresent(message, words[i]))
        {
            solution[count] = *words[i];
            count++;
        }
    }
    solution[count] = '\0'; // Add the null terminator at the end
    printf("Decoded message: %s\n", solution);
}

int main()
{
    FILE *file;
    char *filename = "CHANGELOG_01.txt"; // File with messages
    char message[1000];

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

    char *words[] = {"word1", "word2", "word3"}; // Replace with the actual words from the file
    int num_words = sizeof(words) / sizeof(words[0]);

    decodeMessages(message, words, num_words);

    return 0;
}
