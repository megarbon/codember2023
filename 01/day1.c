#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to decode the messages
bool isWordPresent(char *message, char *word)
{
    bool found = false;
    char *token = strtok(message, " ");
    while (token != NULL)
    {
        if (strcmp(token, word) == 0)
        {
            printf("The word '%s' is present in the sentence.\n", word);
            found = true;
        }
        token = strtok(NULL, " ");
    }
    return found;
}

void decodeMessages(char *message)
{
    char solution[100];
    int count = 0;

    for (int i = 0; i < strlen(message); i++)
    {
        if (isWordPresent(message, "your_word_here"))
        {
            solution[count] = message[i];
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

    decodeMessages(message);

    return 0;
}
