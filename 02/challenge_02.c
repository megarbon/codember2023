#include <stdio.h>

int applyOperation(char operation, int num)
{
    switch (operation)
    {
    case '#':
        return num + 1;
    case '@':
        return num - 1;
    case '*':
        return num * num;
    case '&':
        printf("%d", num);
        return num;
    default:
        return num;
    }
}

int main()
{
    int num = 0;
    char sym;

    printf("Enter a string of symbols: ");

    while ((sym = getchar()) != '\n')
    {
        if (sym != ' ' && sym != '\t')
        {
            num = applyOperation(sym, num);
        }
    }

    return 0;
}
