/** strep program
 *  Christian Miller
 *  Due: February 11, 2014
 **/

// some included built-in library code, which may or may not be useful
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define SIZE 5000

int string_length(char * str);

int main(int argc, char *argv[]) {

        printf("Number of arguments: %d\n", argc);
        printf("Command: %s\n", argv[0]);
        printf("Old string: %s\n", argv[1]);
        printf("New string: %s\n", argv[2]);
        printf("File name: %s\n", argv[3]);
        /*Initializations:      create a charcter array, named inBuffer with predefined size, this is the input file's contents
                                create a character array, named outBuffer with predefined size, this is the output file's contents
                                create an integer, named file that opens the file
                                create an integer, named count, going to use this later to ensure there is something inside the file
                                create an integer, named oldLength, this going to be assigned the value of the old string's length
                                create an integer, named newLength, this is going to be assigned the value of the new string's length
                                create a character pointer, named oldString assigned to the value of argv[1], or the old string; will use at later point
                                create a character pointer, named newString assigned to the value of argv[2], or the new string; will use at later point
                                create an integer, named inIndex, it will be the input's index location; will use at a later point
                                create an integer, named outIndex, it will be the output's index location; will use at a later point
        */
        char inBuffer[SIZE];
        char outBuffer[SIZE];
        int file = open(argv[3], O_RDONLY);
        int count;
        int oldLength = string_length(argv[1]);
        int newLength = string_length(argv[2]);
        char *oldString = argv[1];
        char *newString = argv[2];
        int inIndex;
        int outIndex;
        while(1){
                /*
                  forever loop through the file
                  read through the file and assign the size of the file to count
                  for as long as index is less than count, or as long as the input index is less than count
                        initialize an int called result, and compares the inBuffer at it's location, inIndex, to oldString and its length, oldLength
                        if a result is found
                                replaces the newString and its length, newLength, to where the outBuffer at the appropriate location, outIndex
                        else there was no result found
                                outBuffer at outIndex is assigned the value of inBuffer at inIndex
                                incriment inIndex by one
                                incriment outIndex by one
                  if count == 0 then you have reached the end of the file
                        break
                */
                count = read(file, inBuffer, SIZE);
                for(inIndex = 0; inIndex < count;){
                        int result = strncmp(inBuffer + inIndex, oldString, oldLength);
                        if(result == 0){
                                strncpy(outBuffer + outIndex, newString, newLength);
                                inIndex += oldLength;
                                outIndex += newLength;
                        } else{
                                outBuffer[outIndex] = inBuffer[inIndex];
                                inIndex++;
                                outIndex++;
                        }//if else
                }//for
                if(count == 0)
                        break;
        }//while
        printf("Input file: %s \n", inBuffer);
        printf("Output file: %s \n", outBuffer);
        close(file);
        return 0;
}//main

// find the length of a null terminated string
int string_length(char *str){
        int length = 0;
        while(str[length] != '\0'){
        length++;
        }
        return length;
}
