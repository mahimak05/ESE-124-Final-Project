//ESE124 Final Project 
//Mahima Karanth, Langyuan Jia, Vincent Li

/*change MAX_ROW and MAX_COL to appropriate size in main.c and function.c

directions:
			left
		     ^
			 |
backward <- - - -> forward
	         |
    		 v
    		right
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_ROW 11
#define MAX_COL 10

char maze[MAX_ROW][MAX_COL];		//2d array that holds the maze
extern int current_row, current_col;	//current coordinates of the ant
int index_row = 0, index_col = 0;

void get_maze(FILE *input){
	char c;
	while((c = fgetc(input)) != EOF) {
		if(c!='\n'){
			maze[index_row][index_col] = c;
			index_col++;
		}
		else if (c == '\n'){
		    index_row++;
		    index_col = 0;
		}
	}
}
void print_maze(){
	int i, j;
	
	for(i = 0; i < sizeof(maze)/sizeof(maze[0]); i++){
		for(j = 0; j < sizeof(maze[0])/sizeof(maze[0][0]); j++){
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

int main (){
	FILE *inp = fopen ("maze1.txt", "r");		//inp is maze file

    if(inp== NULL){
        printf("Error, file couldn't be found.\n");
        exit(1);
    }

    get_maze(inp);
	print_maze();
	
	//Enter starting point
	printf("Please enter initial row(0-%d): ", (sizeof(maze)/sizeof(maze[0])-1));
	scanf("%d", &current_row);
	printf("Please enter initial column(0-%d): ", (sizeof(maze[0])/sizeof(maze[0][0])-1));
	scanf("%d", &current_col);
	while(start()){
		printf("Please enter initial row(0-%d): ", (sizeof(maze)/sizeof(maze[0])-1));
		scanf("%d", &current_row);
		printf("Please enter initial column(0-%d): ", (sizeof(maze[0])/sizeof(maze[0][0])-1));
		scanf("%d", &current_col);
	}
	
	print_maze();
	CWR();
	CJPI();
	mark();
	print_maze();
}