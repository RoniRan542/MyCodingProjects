#include <stdio.h>  /* i/o operations */
#include <unistd.h> /* for fopen */
#include <string.h> /* strlen */

#include "logger.h" /* loggeer API */

enum status
{
    SUCCESS = 0,
    FAILURE
};

int LogWrite(char *file_name, char *message)
{
    FILE *file = fopen(file_name, "a+");

    if (-1 == fputs(message, file))
    {
        fclose(file);
        perror("write failed\n");
        return FAILURE;
    }
    fclose(file);
    return SUCCESS;
}
