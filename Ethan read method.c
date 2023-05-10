//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "functions.h"

#define MAX_ROW 100
#define MAX_COL 100

int main (void){

    FILE *maze;
    char line[MAX_ROW][MAX_COL];
    int row=0, col=0, c=0;
    float i=0, j=0, totalrow=0, totalcol=0;

    if((maze = fopen ("maze.txt", "r")) == NULL){
        printf("Error, file couldn't be found.\n");
        exit(1);
    }

    while (fgetc(maze)!='\n'){
        i++;
    }
    
    rewind(maze);
    
    while(fgetc(maze)!=EOF){
        j++;
    }
    
    totalcol = i-1;
    totalrow = j/(i-1);

    fprintf(stdout, "There are %f columns in the maze\n", totalcol);
    fprintf(stdout, "There are %f rows in the maze\n", totalrow);
    //read
    
    rewind(maze); //reset the pointer to the beginning of maze.txt array
    
    for (row=0; row<totalrow; row++){
        for (col=0; col<totalcol; col++){
            line[row][col] = fgetc(maze);
        }
//        fgetc(maze);
    }
    
    fclose(maze);
    
    for (row=0; row<totalrow; row++){
        for (col=0; col<totalcol; col++){
            fprintf(stdout, "%c", line[row][col]);
        }
//        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");


}
