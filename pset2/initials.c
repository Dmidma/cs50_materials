/**
 *
 * initials.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 *
 * This program will take a string as an input (hopefully a full name) 
 * and output in uppercase only the first letters of the words in the string.
 *
 */

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	
    string name = GetString();
    if (name == NULL)
    {
        return 1;
    }
    
    if (isalpha(name[0]))
    {
        printf("%c", toupper(name[0]));
    }

    for (int i = 1; i < strlen(name); i++)
    {
        if (isspace(name[i - 1]) && isalpha(name[i]))
        {
            printf("%c", toupper(name[i]));
        }
    }

    printf("\n");
}
