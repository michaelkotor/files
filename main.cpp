#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Set {
    char* toFind;
    char* toWrite;
};

char* createArray();
int putChar(char** array, char temp, int index);
int putChar2(char** array, char temp, int index);
void printArray(char* array, int length);
char* readContentFile(FILE *file);
char* readContentFile2(FILE *file);
int countSpaces(char* toCount);
Set** parse(char* info, int* length);
int findChar(char* whereToFind, char toFind, int fromIndex);
int findCharWithException(char* whereToFind, char toFind, int fromIndex);
void changeContentFile(Set ** array, char *content, int number);
char* findWordToWrite(Set** array, char* toFind, int number, int size);
int checkTwoStr(char* str1, char* str2, int size);

int main() 
{
    int number = 0;
    char* infoFile = "info.txt";
    FILE *info = fopen(infoFile, "r");
    Set **array = parse(readContentFile(info), &number);
    FILE* content = fopen("content.txt", "r");
    char* bigContent = readContentFile2(content);
    changeContentFile(array, bigContent, number);
    return 0;
}

void changeContentFile(Set **array, char *content, int number)
{
    FILE *resultFile = fopen("result.txt", "w");
    int size = strlen(content);
    
    int startToSkip = 0;
    int startWord = 0;

    for(int i = 0; i < size; i++)
    {
        char checkSymbol = content[i];
        if(checkSymbol == '$')
        {
            startToSkip = 1;
            startWord = i;
        }
        if(checkSymbol == '}')
        {
            int sizeOfNewWord = i - startWord - 2;
            char* newWord = findWordToWrite(array, content + startWord, number, sizeOfNewWord);
            if(newWord == NULL) 
            {
                printf("\nERROR\n");
            }   
            fputs(newWord, resultFile);
            startToSkip = 0;
        }
        if(startToSkip == 0 && checkSymbol != '}')
        {
            putc(checkSymbol, resultFile);
        }
    }
}

int findChar(char* whereToFind, char toFind, int fromIndex)
{
    int index = fromIndex;
    while(whereToFind[index] != toFind)
    {
        index++;
    }
    return index;
}

int findCharWithException(char* whereToFind, char toFind, int fromIndex)
{
    int index = fromIndex;
    while(whereToFind[index] != toFind)
    {
        index++;
        if(whereToFind[index] == '\0') return -1;
    }
    return index;
}

char* createArray()
{
    char* someArray = (char*) calloc(1, sizeof(someArray[0]));
    someArray[1] = '\0';
    return someArray;
}

int putChar(char** array, char temp, int index)
{
    static int size;
    if(index > size)
    {
        array[0] = (char*) realloc(array[0], sizeof(array[0][0]) * index * 2);
    }
    array[0][index] = temp;
    size++;
    return size;
}

int putChar2(char** array, char temp, int index)
{
    static int size;
    if(index > size)
    {
        array[0] = (char*) realloc(array[0], sizeof(array[0][0]) * index * 2);
    }
    array[0][index] = temp;
    size++;
    return size;
}

void printArray(char* array, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%c", array[i]);
    }
}

char* readContentFile(FILE *file)
{
    char* myString = createArray();
    int counter = 0;
    char temp = fgetc(file);
    while(temp != EOF)
    {
        putChar(&myString, temp, counter++);
        temp = fgetc(file);
    }
    putChar(&myString, '\0', counter);
    return myString;
}

char* readContentFile2(FILE *file)
{
    char* myString = createArray();
    int counter = 0;
    char temp = fgetc(file);
    while(temp != EOF)
    {
        putChar2(&myString, temp, counter++);
        temp = fgetc(file);
    }
    putChar2(&myString, '\0', counter);
    return myString;
}

int countSpaces(char* toCount)
{
    int length = strlen(toCount);
    int counter = 0;
    for(int  i = 0; i < length; i++)
    {
        if(toCount[i] == '\n')
        {
            counter++;
        }
    }
    return counter;
}

Set** parse(char* info, int* length) 
{
    int size = countSpaces(info) + 1;
    *length = size;
    Set** array = (Set**) calloc(size, sizeof(array[0]));
    int nextSymbol = 0;
    for(int i = 0; i < size; i++)
    {
        Set *tempSet = (Set*) calloc(1, sizeof(Set));
        tempSet->toFind = (char*) calloc(20, sizeof(char));
        tempSet->toWrite = (char*) calloc(20, sizeof(char));
        array[i] = tempSet;
        int nextTab = nextSymbol;
        nextSymbol = findChar(info, ':', nextTab); 
        strncpy(array[i]->toFind, info + nextTab, nextSymbol++ - nextTab);
        nextTab = nextSymbol;
        nextSymbol = findChar(info, '\n', nextTab); 
        strncpy(array[i]->toWrite, info + nextTab, nextSymbol++ - nextTab);
    }
    return array;
}

char* findWordToWrite(Set** array, char* toFind, int number, int size)
{
    for(int i = 0; i < number; i++) 
    {
        printf("%s : %s : %d\n", array[i]->toFind, toFind + 2, size);
        if(checkTwoStr(array[i]->toFind, toFind + 2, size) == 0)
        {
            return array[i]->toWrite;
        }
    }
    return NULL;
}

int checkTwoStr(char* str1, char* str2, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}