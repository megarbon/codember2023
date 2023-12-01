
/*
2-4 f: fgff
4-6 z: zzzsg
1-6 h: hhhhhh
Each line indicates, separated by :, the key policy and the key itself.

The key policy specifies the minimum and maximum number of times a given character must appear for the key to be valid. For example, 2-4 f means that the key must contain f at least 2 times and at most 4 times.

Knowing this, in the previous example, there are 2 valid keys but one is not:

The second key, zzzsg, is not valid; it contains the letter z 3 times, but needs at least 4. The first and third keys are valid: they contain the appropriate amount of f and h, respectively, according to their policies.
*/

#include <stdio.h>

int main()
{
    int count = 0;
    int invalidCount = 0;
    int min, max;
    char key;
    char password[100];
    FILE *fp;
    fp = fopen("encryption_policies.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read each line from the file
    while (fgets(password, sizeof(password), fp) != NULL)
    {
        // Parse the line to extract min, max, key, and password
        sscanf(password, "%d-%d %c: %s", &min, &max, &key, password);

        // Check if the password adheres to the policy
        int keyCount = 0;
        for (int i = 0; password[i] != '\0'; i++)
        {
            if (password[i] == key)
            {
                keyCount++;
            }
        }

        // Increment count if the password is valid
        if (keyCount >= min && keyCount <= max)
        {
            count++;
        }
        else
        {
            // Increment invalidCount and print the invalid password
            invalidCount++;
            if (invalidCount == 13)
            {
                printf("Invalid password number 42: %s\n", password);
            }
        }
    }

    printf("Valid passwords: %d\n", count);
    printf("Invalid passwords: %d\n", invalidCount);

    fclose(fp);
    return 0;
}
