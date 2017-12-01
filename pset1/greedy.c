/**
 * greedy.c
 *
 * Oussema Hidri
 * d.oussema.d@gmail.com
 *
 * The program will count the minimum number of coins that equals
 * an amount of change, which the user will provide.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    // getting the amount of change
    printf("O hai! How much change is owed?\n");
    float money_return = GetFloat();

    
    // program will not accept a negative value
    while (money_return < 0 )
    { 
        printf("How much chang is owed?\n");
        money_return = GetFloat();
    }
    
    // converting the amount to cents 
    int money = round(money_return * 100); 
    
    // counting the minimum number of coins
    int number_coins = 0;       
    while (money != 0)
    {
        if (money >= 25)
        {
            money -= 25;
            number_coins++;
        }
        else if (money >= 10 && money < 25)
        {
            money -= 10;
            number_coins++;
        }
        else if (money >= 5 && money < 10)
        {  
            money -= 5;
            number_coins++;
        }
        else if (money < 5 && money >= 1)
        {
            money -= 1;
            number_coins++;
        }              
    }

    // printing the result
    printf("%d\n", number_coins);
        
    return 0;
}
