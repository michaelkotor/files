#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Set {
    char* toFind;
    char* toWrite;
};

char* createArray();
int putChar(char** array, char temp, int index);
void printArray(char* array, int length);
char* readContentFile(FILE *file);
int countSpaces(char* toCount);
Set** parse(char* info);
int findChar(char* whereToFind, char toFind, int fromIndex);

int main() 
{
    char* infoFile = "info.txt";

    FILE *file = fopen(infoFile, "r");
    Set **array = parse(readContentFile(file));
    
    return 0;
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

Set** parse(char* info) 
{
    int size = countSpaces(info) + 1;
    Set** array = (Set**) calloc(size, sizeof(array[0]));
    int nextSymbol = 0;
    for(int i = 0; i < size; i++)
    {
        Set tempSet = {};
        tempSet.toFind = (char*) calloc(20, sizeof(char));
        tempSet.toWrite = (char*) calloc(20, sizeof(char));
        array[i] = &tempSet;
        int nextTab = nextSymbol;
        nextSymbol = findChar(info, ':', nextTab); 
        strncpy(array[i]->toFind, info + nextTab, nextSymbol++ - nextTab);
        nextTab = nextSymbol;
        nextSymbol = findChar(info, '\n', nextTab); 
        strncpy(array[i]->toWrite, info + nextTab, nextSymbol++ - nextTab);

        // char te = info[nextSymbol];
        // te = 9;
    }
    return array;
}
