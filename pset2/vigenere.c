/**
 *
 * vigenere.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * This program encrypt's a text using vigenère's cipher.
 * It needs one argument in the command-line, which will be the keyword.
 * Then, the user will have to enter the text that will get encrypted.
 * Finally, the program will print the crypted text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>



int main(int argc, string argv[])
{
    
    // accepting only one argument in the command-line
    if (argc != 2)
    {
        printf("The program must be lunched with ");
        printf("a single command-line argument!\n");
        return 1;
    }
    else
    {
        // stocking the command-line argument (string) as a key (string)
        string key = argv[1];
        
        // saving the size of the keyword
        int sizeKey = strlen(key);
        
        // keyword must only contains aplhabetical characters 
        for (int i = 0; i < sizeKey; i++)
        {
            if ((key[i] < 'a' || key[i] > 'z') && 
                (key[i] < 'A' || key[i] > 'Z'))
            {
                printf("The argument which is the key must be composed ");
                printf("entirely of alphabetical characters!\n");
                return 1;
            }
        }
        
        
        
        // capitalizing all letters of the keyword
        // 'A' and 'a' have the same index
        for (int i = 0; i < sizeKey; i++)
        {
            key[i] = toupper(key[i]);
        }
        
        
        // user enters the text that will be encrypted
        string text = GetString();
        if (text == NULL)
        {
            return 1;
        }
        
        // index used for the keyword
        int keyIndex = 0;
        
        // rotating each alphabetic character using the keyword
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                text[i] = (char) (((int) text[i] - ((int) 'a')
                                + (int) key[keyIndex] - ((int) 'A'))
                                % 26 + (int) 'a');
                keyIndex++;
                
                // go back to the start of the keyword when reaching the end
                if (keyIndex == sizeKey)
                {
                    keyIndex = 0;
                }
            }  
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                text[i] = (char) (((int) text[i] - ((int) 'A')
                                + (int) key[keyIndex] - ((int) 'A'))
                                % 26 + (int) 'A');
                keyIndex++;
                
                // go back to the start of the keyword when reaching the end
                if (keyIndex == sizeKey)
                {
                    keyIndex = 0;
                }
            }  
        }
            
        // Printing the ciphertext, then returning 0
        printf("%s\n", text);
            
        return 0;    
    }
}
