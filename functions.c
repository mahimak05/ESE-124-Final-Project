#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define MAX_ROW 11
#define MAX_COL 10

#define MAX_SIZE 60

//define itch
enum itch_state itch = NONE;
int itch_space = 0;

//stack
typedef struct{ //stack for position
    int mem_row[MAX_SIZE];
    int mem_col[MAX_SIZE];
    int top;
} ANTstack;
ANTstack COORD;

int current_row, current_col, row_temp = -1, col_temp = -1;
extern char maze[MAX_ROW][MAX_COL];        // used in main.c
extern int deed_pts, num_rows, num_col;

int empty_spot(int row, int col){	//return 1 if invalid spot, else return 0
	if(row>num_rows||row<0||col>num_col||col<0||maze[row][col]=='*') return 1;	
	else return 0;
}

int start(){
	if(empty_spot(current_row, current_col)){
		printf("That is not a valid starting point!\n");
		return 1;
	}
	else{
		maze[current_row][current_col]='X'; //mark the starting position of the maze using a 'X'
		return 0;
	}
}

//ANT MOVEMENT -------------------------------------------------------------------------
void mark(){
    maze[current_row][current_col]='#'; //mark the current position of the maze using a # sign 
}

//returns 1 if move is not possible, else return 0
void move_right(){
    if(empty_spot(current_row, current_col+1)){
		printf("Cannot move right!\n");
	}
	else{
		current_col++; //move position 1 right
		if(maze[current_row][current_col]>=48&&maze[current_row][current_col]<=57) deed_pts += (maze[current_row][current_col]-48);	//check for good deed
		if(maze[current_row][current_col]!='#') maze[current_row][current_col] = '+';
	}
}

void move_left(){
    if(empty_spot(current_row, current_col-1)){
		printf("Cannot move left!\n");
	}
	else{
		current_col--; //move position 1 left
		if(maze[current_row][current_col]>=48&&maze[current_row][current_col]<=57) deed_pts += (maze[current_row][current_col]-48);	//check for good deed
		if(maze[current_row][current_col]!='#') maze[current_row][current_col] = '+';
	}
}

void move_backward(){
    if(empty_spot(current_row-1, current_col)){
		printf("Cannot move backward!\n"); 
	}
	else{
		current_row--; //move position 1 backward
		if(maze[current_row][current_col]>=48&&maze[current_row][current_col]<=57) deed_pts += (maze[current_row][current_col]-48);	//check for good deed
		if(maze[current_row][current_col]!='#') maze[current_row][current_col] = '+';
	}
}

void move_forward(){
    if(empty_spot(current_row+1, current_col)){
		printf("Cannot move forward!\n");
	}
	else{
		current_row++; //move position 1 forward
		if(maze[current_row][current_col]>=48&&maze[current_row][current_col]<=57) deed_pts += (maze[current_row][current_col]-48);	//check for good deed
		if(maze[current_row][current_col]!='#') maze[current_row][current_col] = '+';
	}
}

void CWB(){
	int i = 1;
	//checks back position until wall
	while(maze[current_row-i][current_col]!='*'&&current_row-i>=0){
		if(maze[current_row-i][current_col]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row-i][current_col]=='*'){
		itch = BACKWARD;
		itch_space = i - 1;
	}
}

void CWF(){
	int i = 1;
	//checks forward position until wall
	while(maze[current_row+i][current_col]!='*'&&current_row+i<num_rows){
		if(maze[current_row+i][current_col]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row+i][current_col]=='*'){
		itch = FORWARD;
		itch_space = i - 1;
	}
}

void CWR(){
	int i = 1;
	//checks right position until wall
	while(maze[current_row][current_col+i]!='*'&&current_col+i<num_col){
		if(maze[current_row][current_col+i]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row][current_col+i]=='*'){
		itch = RIGHT;
		itch_space = i - 1;
	}
}
void CWL(){
	int i = 1;
	//checks backward position until wall
	while(maze[current_row][current_col-i]!='*'&&current_col-i>=0){
		if(maze[current_row][current_col-i]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row][current_col-i]=='*'){
		itch = LEFT;
		itch_space = i - 1;
	}
}
void BJPI(){
	switch(itch){
		case NONE:
			printf("No itch!\n");
		case LEFT:
			while(itch_space>0){
				move_left();
				itch_space--;
			}
			itch = NONE;
		case RIGHT:	
			while(itch_space>0){
				move_right();
				itch_space--;
			}
			itch = NONE;
		case FORWARD:
			while(itch_space>0){
				move_forward();
				itch_space--;
			}
			itch = NONE;
		case BACKWARD:	
			while(itch_space>0){
				move_backward();
				itch_space--;
			}
			itch = NONE;
	}
}
void CJPI(){
	switch(itch){
		case NONE:
			printf("No itch!\n");
		case LEFT:
			move_left();		
			itch = NONE;
			itch_space = 0;
		case RIGHT:	
			move_right();		
			itch = NONE;
			itch_space = 0;
		case FORWARD:
			move_forward();	
			itch = NONE;
			itch_space = 0;
		case BACKWARD:	
			move_backward();
			itch = NONE;
			itch_space = 0;	
	}
}

//ANT STACK FUNCTIONS ---------------------------------------------------------------------------
int is_full(){		//return 1 if full
    if(COORD.top>=MAX_SIZE-1) return 1;
    else return 0;
}
int is_empty(){		//return 1 if empty
    if(COORD.top==-1) return 1;
    else return 0;
}
void PUSH(){
	if(is_full()) 
		printf("Ant memory is full!\n");
	else{
		COORD.top++;
    	COORD.mem_row[COORD.top] = current_row;
    	COORD.mem_col[COORD.top] = current_col;
	}
}
void POP(){
	if(is_empty()) 
		printf("Ant memory is empty!\n");
    else{
        row_temp = COORD.mem_row[COORD.top];
        col_temp = COORD.mem_col[COORD.top];
        COORD.top--;
    }
}
void PEEK(){
	if(is_empty()) 
		printf("Ant memory is empty!\n");
    else{
        row_temp = COORD.mem_row[COORD.top];
        col_temp = COORD.mem_col[COORD.top];
    }
}
void CLEAR(){
	while(COORD.top>-1) COORD.top--;
}
void BACKTRACK(){
	if(row_temp==-1||col_temp==-1) 
		printf("Please retrieve a position from memory first!\n");
	else{
    	current_row = row_temp;
    	current_col = col_temp;
    }
}
//void RP(int n, int t);