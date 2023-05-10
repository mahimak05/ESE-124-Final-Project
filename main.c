//ESE124 Final Project Mahima Karanth, Langyuan Jia, Vincent Li

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "functions.h"

#define MAX_LEN 30

char maze[MAX_LEN][MAX_LEN];

int main (){
	FILE *inp = fopen ("maze1.txt", "r");
	char c;
	int index_row = 0, index_col = 0, i, j;

    if(inp== NULL){
        printf("Error, file couldn't be found.\n");
        exit(1);
    }

    //read maze to 2d array
    while((c = fgetc(inp)) != EOF) {
		if(c!='\n'){
			maze[index_row][index_col] = c;
			index_col++;
		}
		else if (c == '\n'){
		    index_row++;
		    index_col = 0;
		}
	}
	
	//test: print maze
	for(i = 0; i < sizeof(maze)/sizeof(maze[0]); i++){
		for(j = 0; j < sizeof(maze[0])/sizeof(maze[0][0]); j++){
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}

}

