#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to decode the messages
void decodeMessages(char *message)
{
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
