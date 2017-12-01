/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// definition of a node
typedef struct node
{
    bool isWord;
    char value;
    struct node* next;
    struct node* child;
}node;

// head of dictionary
node* dict = NULL;

// To calculate the nubmer of words in dictionary
unsigned int wordsNbr = 0;

// to check if the dictionary is loaded
bool isLoaded = false;



/**
 * add_to_list() adds @param value to @param list keeping the list sorted.
 */
node* add_to_list(node** list, char value)
{
    
    
    // list is empty
    if (*list == NULL)
    {
        
        // create a node and give it the value
        node* elem = malloc(sizeof(node));
        if (elem == NULL)
        {
            return NULL;
        }
        elem->isWord = false;
        elem->value = value;
        elem->next = NULL;
        elem->child = NULL;


        // set the list to point to the created element
        *list = elem;

        return elem;
    }
    else
    {
        
        // inserting at the head of the list
        if ((*list)->value > value)
        {
            
            // create a node and give it the value
            node* elem = malloc(sizeof(node));
            if (elem == NULL)
            {
                return NULL;
            }
            elem->isWord = false;
            elem->value = value;
            elem->next = NULL;
            elem->child = NULL;




            elem->next = *list;
            *list = elem;

            return elem;
        }

        // inserting at the middle/end 
        else
        {
            // trackers of list
            node* follo = *list;
            node* prev = *list;
            
            // find the right place to insert the new node
            while (follo != NULL && follo->value <= value)
            {
                // exit when finding occurence
                if (follo->value == value)
                {
                    return follo;
                }
                
                follo = follo->next;
            }
            while (prev->next != follo)
            {
                prev = prev->next;
            }

            // create a node and give it the value
            node* elem = malloc(sizeof(node));
            if (elem == NULL)
            {
                return NULL;
            }
            elem->isWord = false;
            elem->value = value;
            elem->next = NULL;
            elem->child = NULL;



            // insert the node in its right place
            prev->next = elem;
            elem->next = follo;

            return elem;
        }
    }

    return NULL;
}




/**
 * Determines the node that will be freed.
 * The node that will be freed must have poth next and child pointers
 * point to NULL.
 */
node* nodeToFree(node* dic)
{
    // repeat, until we find the node
    while (dic->child != NULL ||
        dic->next != NULL)
    {   
        // found ya
        if (dic->child == NULL && 
            dic->next == NULL)
        {
            return dic;
        }
        // if next pointer is NULL, we take another path
        else if (dic->next == NULL &&
            dic->child != NULL)
        {
            dic = dic->child;
        }
        // the usual path
        else
        {
            dic = dic->next;
        }
    }

    return dic;
}


/**
 * Finds the node that points to @param toFollow in the dictionary.
 */
node* followIt(node* dic, node* toFollow)
{
    // repeat until we find it
    while (dic->next != toFollow ||
        dic->child != toFollow)
    {   
        // found you
        if (dic->next == toFollow || 
            dic->child == toFollow)
        {
            return dic;
        }
        // if next pointer is NULL, we take another path
        else if (dic->next == NULL &&
            dic->child != NULL)
        {
            dic = dic->child;
        }
        // the usual path
        else
        {
            dic = dic->next;
        }
    }
    
    return dic;
}


/**
 * Finds the node that contains the @param alpha.
 * It will only looks from the starting node @param dic,
 * until it reachs a dead end (NULL), passing by next pointers.
 */
node* findNodeInRow(char alpha, node* dic)
{
    // until we reach a dead end   
    while (dic != NULL)
    {   
        // finding the character. case-insensitive
        if (dic->value == tolower(alpha))
        {
            return dic;
        }
        else
        {
            // next node
            dic = dic->next;
        }
    }

    // sorry, not here
    return NULL;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* foundIt = dict;
    
    // iterate over the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {   
        // does it exists in the dictionary?
        foundIt = findNodeInRow(word[i], foundIt);
        if (foundIt == NULL)
        {
            return false;
        }
        else if (i < (n - 1))
        {   
            // check the other characters of the word
            foundIt = foundIt->child;
        }
    }

    // last character exists but not as word of the dictionary
    if (foundIt != NULL && !foundIt->isWord)
    {
        return false;
    }

    // good to go
    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary
    FILE* dicFile = fopen(dictionary, "r");
    if (dicFile == NULL)
    {
    	return false;
    }

    // read the first character and store it, keeping track of the last node
    int c = fgetc(dicFile);
    node* cursor = add_to_list(&dict, c);
    if (cursor == NULL)
    {
        return false;
    }

    bool isNewWord = false;

    // iterate over the file
    for (c = fgetc(dicFile); c != EOF; c = fgetc(dicFile))
    {   
        // reaching the end of a word
        if (c == '\n')
        {
            cursor->isWord = true;
            wordsNbr++;
            cursor = dict;
            isNewWord = true;
        }
        else
        {   
            // adding at the first row of dictionnary if it is a new word
            if (isNewWord)
            {
                cursor = add_to_list(&dict, c);
                if (cursor == NULL)
                {
                    unload();
                    return false;
                }
                isNewWord = false;
            }
            // adding at the next row of the pointed node
            else
            {
                cursor = add_to_list(&(cursor->child), c);
                if (cursor == NULL)
                {
                    unload();
                    return false;
                }
            }
        }
    }

    // oufff, dictionary is loaded
    isLoaded = true;

    // close the file and good to go
    fclose(dicFile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{   
    // return the number of words in dictionary, if it is loaded
    if (isLoaded)
    {
        return wordsNbr;
    }

    return 0;

}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // if the dictionary contains one node
    if (dict->next == NULL && 
        dict->child == NULL)
    {
        free(dict);
        return true;
    }
    
    // to trackers, one follows the other
    node* jerry = dict;
    node* tom = dict;

    // we repeat until the dictionary is unloaded
    while (1)
    {
        // find Tom & Jerry
        jerry = nodeToFree(jerry);
        tom = followIt(dict, jerry);
        
        // exit if one of the pointers fail to point
        if (jerry == NULL ||
            tom == NULL)
        {
            return false;
        }
        
        // dictionary contains only two nodes
        if ((jerry == dict || tom == dict) && 
            (((jerry->next == NULL && jerry->child == NULL) && 
                (tom->next == NULL || tom->child == NULL)) || 
            ((tom->next == NULL && tom->child == NULL) && 
                (jerry->next == NULL || jerry->child == NULL))))
        {
            free(jerry);
            free(tom);
            dict = NULL;
            return true;
        }
        // more than two
        else
        {
            if (tom->next == jerry)
            {
                tom->next = NULL;
            }
            else
            {
                tom->child = NULL;
            }


            free(jerry);
            
            // so we don't iterate from the beginning
            jerry = tom;
        }
    }

    return false;
}
