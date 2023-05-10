//ESE124 Final Project Mahima Karanth, Langyuan Jia, Vincent Li

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_LEN 100

int main (){

FILE *maze;
char line[MAX_LEN];

    if((maze = fopen ("maze1.txt", "r")) == NULL){
        printf("Error, file couldn't be found.\n");
        exit(1);
    }

    //read 

    while (fgets(line, MAX_LEN, maze) != EOF)
    {
        fprintf(stdout, "%s", line);
    }
    
    fclose(maze);

}


