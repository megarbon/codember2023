#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main()
{
    char line[MAX_LINE_LENGTH];
    char **checksums = NULL;       // Array para almacenar los checksum
    char **valid_checksums = NULL; // Array para almacenar los checksum válido
    size_t checksums_count = 0;
    int total_valid_checksums = 0;

    FILE *fp;
    fp = fopen("files_quarantine.txt", "r");

    if (fp == NULL)
    {
        printf("Error while opening the file");
        return -1;
    }

    // Leer cada línea del archivo
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Eliminar el salto de línea al final si está presente
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
        }

        // Añadir la línea al array de checksums
        checksums = realloc(checksums, (checksums_count + 1) * sizeof(char *));
        checksums[checksums_count] = strdup(line);

        // Incrementar el contador
        checksums_count++;

        // Imprimir la línea
        // printf("%s\n", line);
    }

    // Imprimir los checksums almacenados
    printf("\nChecksums almacenados:\n");
    for (size_t i = 0; i < checksums_count; i++)
    {
        printf("%s\n", checksums[i]);
        // free(checksums[i]); // Liberar memoria asignada por strdup
    }

    // evaluar si un checksum es válido y en caso afirmativo, guardarlo en un array de checksums válidos
    for (size_t i = 0; i < checksums_count; i++)
    {
        // separar cada entrada del array de checksums en dos partes: el nombre del archivo y el checksum delimitados por un guion

        char *filename_part = strtok(checksums[i], "-");
        char *checksum_part = strtok(NULL, "-");

        // ahora que tenemos las partes separadas evaluar si el checksum es válido
        // sera valido si el checksum se compone solo los caracteres no repetidos en el filename y en orden de aparicion
        int valid = 1; // Supongamos que es válido inicialmente

        for (size_t j = 0; j < strlen(checksum_part); j++)
        {
            if (strchr(filename_part, checksum_part[j]) == NULL)
            {
                valid = 0; // No es válido si encuentra un carácter que no está en el filename
                break;
            }
        }

        if (valid)
        {
            // Añadir el checksum válido al array de checksums válidos
            valid_checksums = realloc(valid_checksums, (i + 1) * sizeof(char *));
            valid_checksums[i] = strdup(checksums[i]);
            total_valid_checksums++; // Incrementar el contador de checksums válidos
        }
    }

    // Imprimir los checksums validos
    printf("\nChecksums Validos:\n");
    for (size_t i = 0; i < total_valid_checksums; i++)
    {
        printf("%d: %s\n", i, valid_checksums[i]);
        // free(valid_checksums[i]); // Liberar memoria asignada por strdup
    }

    // Liberar el array de checksums y el array de checksums válidos
    free(checksums);
    free(valid_checksums);

    // Cerrar el archivo
    fclose(fp);

    return 0;
}
