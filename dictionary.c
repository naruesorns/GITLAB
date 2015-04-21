/** 
 *  dictionary.c
 *
 *   Program stores multiple words and definitions. After building the dictionary,
 *   allow the user to request the definitions of words. Each time the user enters
 *   a word, look it   up in the dictionary to find its definition them.
 *   or definitions and print 
 *
 *
 *
 *  Created by Naruesorn  Sampanpaisarn (Ping) ID 55070503424
 *    18 Febuary 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListUtil.h"

int x[3] = {1,2,3};
int y[4] = {1,2,3,4};

typedef struct
	{
    char word[32];
    char definition[128];
    } DICT_ENTRY_T;

int getDictIndex(char* word)
    {
    char c = tolower(word[0]);
    return(c-'a');
    }

int buildDictionary(LIST_HANDLE*dictionary)
	{
	FILE * pInFile;
	char inputLine[150];
	int retVal = 1;
	char *pDelim = NULL;
	int i = 0;
	int insertRetVal = 0;
	DICT_ENTRY_T * pNewWord = NULL;
	pInFile = fopen("wordlist.txt","r");

	if(pInFile == NULL)
		{
 		printf("Unable to open file ");
        exit(1);
		}
	
	while(fgets(inputLine,150,pInFile) != NULL)
		{
		int len = strlen(inputLine);
		if(inputLine[len-1] == '\n')
			{
			inputLine[len-1] = '\0';
			}
        if(inputLine[0] != '\0')
            {
            printf("Read %s already \n",inputLine);
            pDelim = strpbrk(inputLine,":");
            if(pDelim != NULL)
                {
                pNewWord = (DICT_ENTRY_T*) calloc(1,sizeof(DICT_ENTRY_T));
                if (pNewWord == NULL) /* allocation error */
                    {
                    printf(" allocation error ");
                    exit(1);
                    }
                *pDelim = '\0';
                if((inputLine[0] != '\n') && (inputLine[0] != '\0'))
                    {
                    strcpy(pNewWord->word,inputLine);
                    strcpy(pNewWord->definition,(pDelim+1));
                    }
                }
            if((pNewWord->word[0] < 'a') && (pNewWord->word[0] > 'z'))
                {
                printf(" not character \n");
                exit(1);
                }
            i = getDictIndex(pNewWord->word);
            if(dictionary[i] == NULL)
                {
                dictionary[i] = newList();
                }
            insertRetVal = listInsertEnd(dictionary[i],pNewWord);
            }
        }
	fclose(pInFile);
    return retVal;
	}
int printDictionary(LIST_HANDLE *dictionary)
    {
    int i = 0;
    int j = 1;
    int resetRetval = -1;
    DICT_ENTRY_T *data = NULL;
        
    for (i=0; i<26; i++)
        {

        LIST_HANDLE *list;
        list = dictionary[i];
        if(list == NULL)
            {
            printf("No words with letter '%c' \n",i+'a');
            }
        else
            {
            resetRetval = listReset(list);
            data = listGetNext(list);
            while(data != NULL)
                {
                printf(" word is %s\n",data->word);
                printf("definition is %s\n",data->definition);
                data = listGetNext(list);
                }
            }
        }
    }

int freeDictionary(LIST_HANDLE *dictionary)
    {
    int i = 0;
    int resetRetval = -1;
    LIST_HANDLE * list = NULL;
    DICT_ENTRY_T *data = NULL;
    for(i=0;i<26;i++)
        {
        list = dictionary[i];
        if(list != NULL)
            {
            resetRetval = listReset(list);
            data = listGetNext(list);
            while(data != NULL)
                {
                free(data);
                data = listGetNext(list);
                }
            listDestroy(list);
            dictionary[i] = NULL;
            }
        }
    printf("free memory complete\n");
    }

int printDefinitions(LIST_HANDLE *dictionary,char word[])
    {
    int count = 0;
    int i = 0;
    LIST_HANDLE *list = NULL;
    DICT_ENTRY_T *data = NULL;
    char * cmpWord = NULL;
    i = getDictIndex(word);
    list = dictionary[i];
    if(list == NULL)
        {
        printf("Word '%s' not found in dictionary\n",word);
        }
    else
        {
        listReset(list);
        data = listGetNext(list);
        while(data != NULL)
            {
            cmpWord = data->word;
            if(strcmp(word,cmpWord) == 0)
                {
                printf(" definition : %s \n ",data->definition);
                count++;
                }
            data = listGetNext(list);
            }
        if(count == 0)
            {
            printf("Word '%s' not found in dictionary\n",word);
            }
        }
    }
int main(char* argv[],int argc)
	{
    char input[32];
    int exitVal = 1;
    int len = 0;
	LIST_HANDLE dictionary[26];
	memset(dictionary,0,sizeof(dictionary));
	buildDictionary(dictionary);
    printDictionary(dictionary);

    while(exitVal)
        {
        printf("what word do you want ?(leave blank to exit) : ");
        fgets(input,32,stdin);
        len = strlen(input);
        if(strcmp("\n",input) == 0)
            {
            exitVal = 0;
            }
        else
            {
            if(input[len-1] == '\n')
                {
                input[len-1] = '\0';
                }
            printDefinitions(dictionary,input);
            }
        }
    freeDictionary(dictionary);
	}












