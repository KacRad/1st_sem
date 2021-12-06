#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[]){

    //Checking if the number of parameters is correct
    if(argc != 3){
        printf("Enter 2 prameters.\nUsage: ./<prog_name> <file1> <file2>\n");
        return 1;
    }
    char q[] = "q";                         //char variable to end user input
    char userInput[32], fileOutput[32];     //string variables to store user input and file output
    int counter=0;                          //counter will be incremented to check the number of user input
    FILE *fp1, *fp2;

    //opening the first file with 'write' mode  + error check
    fp1 = fopen(argv[1], "w");
    if (fp1 == NULL){
        printf("Cannot open file %s \n", argv[1]);
        return 2;
    }
    //a 'while' loop getting user input until letter 'q' is entered  
    while(strcmp(q, userInput) != 0){
        printf("Your text: ");
        scanf("%s", userInput);

        if(strcmp(q, userInput) != 0){
            fputs(userInput, fp1);
            fputs("\n", fp1);
            counter++;
        }
    }
    //closing a file when input operation is ended by typing 'q'
    fclose(fp1);

    //opening the first file again, this time with 'read' mode + error check
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL){
        printf("Cannot open file %s \n", argv[1]);
        return 3;
    }
    //opening the second file with 'write' mode + error check
    fp2 = fopen(argv[2], "w");
    if (fp2 == NULL){
        printf("Cannot open file %s \n", argv[2]);
        return 4;
    }
    /* a 'for' loop reading strings from the first file and writing them to the second file
    using fgets() function to read a string, fputs() to write the string in the second file*/
    for (int i=0; i < counter; i++){
        if (fgets(fileOutput, 32, fp1) == NULL){
            printf("Could not read from file %s", argv[1]);
            return 5;
        }
        if (fputs(fileOutput, fp2) < 0){
            printf("Could not write to file %s", argv[2]);
            return 6;
        }
    }
    fclose(fp1);
    fclose(fp2);


    return 0;
}