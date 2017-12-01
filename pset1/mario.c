/**
 * mario.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * This program will demand from the user a height of mario pyramid.
 * It will not accept a negative value, neither a value greater than 23.
 * If the user enters the right value, the program will print 
 * the half-pyramid at the screen.
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
 
    // getting the first value of height
    printf("Height: ");
    int height_hpy = GetInt();
    
    // height must be less than 0, and greater than 23
    while (height_hpy < 0 || height_hpy > 23) 
    {
        printf("Retry: ");
        height_hpy = GetInt();
    }
    
    // printing the half-pyramid with the entered height
    int j;
    for (int i = 0; i < height_hpy; i++) 
    {
        for (j = 0; j < height_hpy - i - 1; j++) 
        {
            printf(" ");
        }
        for (int k = 0; k < height_hpy - j + 1; k++) 
        {    
            printf("#");
        }
        printf("\n"); 
    }  
    
    return 0;
}
