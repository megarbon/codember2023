#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

// Evaluate if the ID or Username is correct (true if alphanumeric, false otherwise)
int isAlphanumeric(char *string)
{
    // Check if the string is alphanumeric
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!isalnum((unsigned char)string[i]))
        {
            return 0; // Not alphanumeric, return false
        }
    }
    return 1; // Alphanumeric, return true
}

// Evaluate if a string consists of letters
int isString(char *string)
{
    // Check if the string consists of letters
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)string[i]))
        {
            return 0; // Not a string, return false
        }
    }
    return 1; // String, return true
}

// Evaluate if the email is correct (true if it follows the pattern username@domain.com, false otherwise)
int isEmailValid(char *email)
{
    // Check for null or empty email
    if (!email || *email == '\0')
    {
        return 1; // Optional, consider valid
    }

    // Check for the correct email pattern
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    return at != NULL && dot != NULL && at < dot;
}

int isNumber(char *str)
{
    // Check if the string is numeric
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return 0; // Not numeric, return false
        }
    }
    return 1; // Numeric, return true
}

int isOptionalNumber(char *str)
{
    return (!str || *str == '\0') ? 1 : isNumber(str);
}

// Function to check if a string is an optional string
int isOptionalString(char *str)
{
    return (!str || *str == '\0') ? 1 : isString(str);
}

int main()
{
    char line[MAX_LINE_LENGTH];
    char **records = NULL;
    int records_count = 0;
    char final[100] = "";

    FILE *fp;
    fp = fopen("database_attacked.txt", "r");

    if (fp == NULL)
    {
        printf("Error while opening the file");
        return -1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Remove the newline character at the end if present
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
        }

        // Add the line to the records array
        records = realloc(records, (records_count + 1) * sizeof(char *));
        records[records_count] = strdup(line);

        // Increment the counter
        records_count++;

        // Print the line
        printf("%s\n", line);
    }

    // Evaluate if a record is correct by making calls to the corresponding functions
    for (int i = 0; i < records_count; i++)
    {
        char *id;
        char *username;
        char *email;
        char *age;
        char *location;

        // Split each field (id, username, email, age, and location) separated by commas
        id = strtok(records[i], ",");
        username = strtok(NULL, ",");
        email = strtok(NULL, ",");
        age = strtok(NULL, ",");
        location = strtok(NULL, ",");

        // Evaluate the validity of each field
        int idValid = isAlphanumeric(id);
        int usernameValid = isAlphanumeric(username);
        // Email is not mandatory, but if it appears, it must be valid
        int emailValid = isEmailValid(email);
        int ageValid = isOptionalNumber(age);
        // Location is not mandatory, but if it appears, it must be valid
        int locationValid = isOptionalString(location);

        // Evaluate the overall validity of the record
        int isValid = idValid && usernameValid && emailValid && ageValid && locationValid;

        // Print the result
        if (isValid)
        {
            printf("%d: Valid\n", i);
        }
        else
        {
            printf("%d: Not Valid\n", i);
            strncat(final, &username[0], 1); // Add the first letter of the username to the final string]
        }
    }

    // Free memory allocated by strdup
    for (int i = 0; i < records_count; i++)
    {
        free(records[i]);
    }
    free(records);

    // Close the file
    fclose(fp);

    // Print the final string
    printf("Final String: %s\n", final);
    return 0;
}
