//ESE124 Final Project 
//Mahima Karanth, Langyuan Jia, Vincent Li

/*change MAX_ROW and MAX_COL to appropriate size in main.c and function.c
maze text file name is maze.txt, intelligence text file name is intel.txt
directions:
	  backward
	     ^
		 |
left <- - - -> right
	     |
    	 v
      forward															
'X' represents starting position
'+' represents ant's path
'#' represents pheromone mark											*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_ROW 20
#define MAX_COL 10

#define MAX_NUMBER_OF_STEPS 100
#define LENGTH 32			//for list of good deed

char maze[MAX_ROW][MAX_COL];		//2d array that holds the maze
extern int current_row, current_col;	//current coordinates of the ant
int deed_pts = 0, num_rows = 0, num_col = 0;	

void get_maze(FILE *input){
	char c;
	int index_col = 0, index_row = 0;
	while((c = fgetc(input)) != EOF) {
		if (c == '\n' && index_col!=0){
			index_row++;
		    index_col = 0;
		    if(index_row>num_rows) num_rows = (index_row + 1);
		}
		else if(c!='\n'){
			maze[index_row][index_col] = c;
			index_col++;
			if(index_col>num_col) num_col = (index_col + 1);
		}
	}
}

void print_maze(){
	int i, j;
	
	for(i = 0; i < num_rows; i++){
		for(j = 0; j < num_col; j++){
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}
//use if statements to check what it read and execute the appropriate command
int get_cmd(char *line){
	if((strcmp(line,"MARK")==0)||(strcmp(line,"MARK\n")==0)){
		mark();
		return 1;
	} 
    else if((strcmp(line,"MOVE_F")==0)||(strcmp(line,"MOVE_F\n")==0)){
		move_forward();
		return 1;
	}
    else if((strcmp(line,"MOVE_B")==0)||(strcmp(line,"MOVE_B\n")==0)){
		move_backward();
		return 1;
	}
    else if((strcmp(line,"MOVE_L")==0)||(strcmp(line,"MOVE_L\n")==0)) {
		move_left();
		return 1;
	}
    else if((strcmp(line,"MOVE_R")==0)||(strcmp(line,"MOVE_R\n")==0)){
		move_right();
		return 1;
	}
    else if((strcmp(line,"CWF")==0)||(strcmp(line,"CWF\n")==0)){
		CWF();
		return 1;
	}
    else if((strcmp(line,"CWB")==0)||(strcmp(line,"CWB\n")==0)) {
		CWB();
		return 1;
	}
    else if((strcmp(line,"CWL")==0)||(strcmp(line,"CWL\n")==0)) {
		CWL();
		return 1;
	}
    else if((strcmp(line,"CWR")==0)||(strcmp(line,"CWR\n")==0)) {
		CWR();
		return 1;
	}
    else if((strcmp(line,"BJPI")==0)||(strcmp(line,"BJPI\n")==0)) {
		BJPI();
		return 1;
	}
    else if((strcmp(line,"CJPI")==0)||(strcmp(line,"CJPI\n")==0)) {
		CJPI();
		return 1;
	}
    else if((strcmp(line,"PUSH")==0)||(strcmp(line,"PUSH\n")==0)) {
		PUSH();
		return 1;
	}
    else if((strcmp(line,"POP")==0)||(strcmp(line,"POP\n")==0)) {
		POP();
		return 1;
	}
    else if((strcmp(line,"PEEK")==0)||(strcmp(line,"PEEK\n")==0)) {
		PEEK();
		return 1;
	}
    else if((strcmp(line,"CLEAR")==0)||(strcmp(line,"CLEAR\n")==0)) {
		CLEAR();
		return 1;
	}
    else if((strcmp(line,"BACKTRACK")==0)||(strcmp(line,"BACKTRACK\n")==0)) {
		BACKTRACK();
		return 1;
	}
    else return 0;
}

void RP(int n, int t, FILE *file){
	int i, j;
	char line[11];
	fpos_t curr_pos;
	
	fgetpos(file, &curr_pos);
	for(i = 0; i < t; i++){
		for(j = 0; j < n && (fgets(line,sizeof(line),file))!=NULL; j++){
			get_cmd(line);			
		}
		fsetpos(file, &curr_pos);
	}
}

int main (){
	FILE *inp = fopen ("maze.txt", "r"), *intel = fopen("intel.txt", "r"), *actions = fopen("actions.txt", "w");
	int steps = 0;
	char line[11];
	
    if(inp== NULL){
        printf("Error, maze file couldn't be found.\n");
        exit(1);
    }
    if(intel== NULL){
        printf("Error, intelligence file couldn't be found.\n");
        exit(1);
    }
	
    get_maze(inp);
    fclose(inp);
	print_maze();
	//Enter starting point
	printf("Please enter initial row(0-%d): ", (num_rows-1));
	scanf("%d", &current_row);
	getchar();
	printf("Please enter initial column(0-%d): ", (num_col-1));
	scanf("%d", &current_col);
	getchar();
	
	//if starting point is on good deed
	if(maze[current_row][current_col]>=48&&maze[current_row][current_col]<=57) deed_pts += (maze[current_row][current_col]-48);
	//if invalid starting point
	while(start()){
		printf("Please enter initial row(0-%d): ", (num_rows-1));
		scanf("%d", &current_row);
		getchar();
		printf("Please enter initial column(0-%d): ", (num_col-1));
		scanf("%d", &current_col);
		getchar();
	}
	fprintf(actions, "Start at: (%d, %d)\n", current_row, current_col);
	printf("___________________________________________________________\n");
	
	
	while((steps<MAX_NUMBER_OF_STEPS)&&(fgets(line,sizeof(line),intel)!=NULL)){
		
		if(get_cmd(line)){
			steps++;
			fprintf(actions, line);
		}
        else if((line[0]=='R')&&(line[1]=='P')){
			RP(line[3]-48, (int)line[5]-48, intel);
			steps++;
			fprintf(actions, line);
		}
		
		print_maze();
		printf("Number of steps: %d\n", steps);
		printf("Good deed points: %d\n", deed_pts);
		printf("__________________________________________________________\n");
	}
	
	fclose(intel);
	fclose(actions);
}