/**
 *
 * caesar.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * This program encrypt's a text using caesar's cipher.
 * It needs one argument in the command-line, which will be the key.
 * Then, the user will have to enter the text that will get encrypted.
 * Finally, the program will print the crypted text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        // stocking the command-line argument (string) as a key (int)
        int key = atoi(argv[1]);
        
        // accepting only strictly positif keys
        if (key <= 0)
        {
            printf("The argument must be strictly positif\n");
            return 1;
        }
        else
        {
            // if the key is a positive integer, we will apply (k mod 26)
            key = key % 26;
            
            // user enters the text that will be encrypted
            string text = GetString();
            if (text == NULL)
            {
                return 1;
            }
            
            // rotating each alphabetic character using the key
            for (int i = 0, n = strlen(text); i < n; i++)
            {
                if (text[i] >= 'a' && text[i] <= 'z')
                {
                    text[i] = (char) (((int) text[i] - ((int) 'a') + key)
                                        % 26 + ((int) 'a'));
                }
                else if (text[i] >= 'A' && text[i] <= 'Z')
                {
                    text[i] = (char) (((int) text[i] - ((int) 'A') + key)
                                        % 26 + ((int) 'A'));
                }
            }
            
            // printing the ciphertext
            printf("%s\n", text);
            
            return 0;    
        }
    }
}
