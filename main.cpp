#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int main() 
{
    char* infoFile = "info.txt";

    FILE *file = fopen(infoFile,"r");
    char* myString = createArray();
    printArray(myString, 6);

    int counter = 0;
    
    return 0;
}