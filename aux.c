
#include "main.h"

void check_error(int nbr)
{
    if (nbr < 0)
    {
        printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
    }
}