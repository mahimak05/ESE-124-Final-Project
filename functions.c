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

int empty_spot(int row, int col){	//return 1 if invalid spot, else return 0
	if(row>(sizeof(maze)/sizeof(maze[0])-1)||current_row<0||col>(sizeof(maze[0])/sizeof(maze[0][0])-1)||col<0||maze[row][col]=='*') return 1;	
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
void move_forward(){
    if(empty_spot(current_row, current_col+1)){
		printf("Cannot move forward!\n");
	}
	else{
		current_col++; //move x position 1 forward
	}
}

void move_backward(){
    if(empty_spot(current_row, current_col-1)){
		printf("Cannot move backward!\n");
	}
	else{
		current_col--; //move x position 1 backward
	}
}

void move_left(){
    if(empty_spot(current_row-1, current_col)){
		printf("Cannot move left!\n"); 
	}
	else{
		current_row--; //move y position 1 to the left
	}
}

void move_right(){
    if(empty_spot(current_row+1, current_col)){
		printf("Cannot move right!\n");
	}
	else{
		current_row++; //move y position 1 to the left
	}
}

void CWL(){
	int i = 1;
	//checks left position until wall
	while(maze[current_row-i][current_col]!='*'&&current_row-i>=0){
		if(maze[current_row-i][current_col]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row-i][current_col]=='*'){
		itch = LEFT;
		itch_space = i - 1;
	}
}

void CWR(){
	int i = 1;
	//checks right position until wall
	while(maze[current_row+i][current_col]!='*'&&current_row+i<(sizeof(maze)/sizeof(maze[0]))){
		if(maze[current_row+i][current_col]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row+i][current_col]=='*'){
		itch = RIGHT;
		itch_space = i - 1;
	}
}

void CWF(){
	int i = 1;
	//checks forward position until wall
	while(maze[current_row][current_col+i]!='*'&&current_col+i<(sizeof(maze[0])/sizeof(maze[0][0]))){
		if(maze[current_row][current_col+i]=='#'){	//stops if it detects pheromone
			itch = NONE;
			itch_space = 0;
			break;
		}
		i++;
	}
	if(i>1&&maze[current_row][current_col+i]=='*'){
		itch = FORWARD;
		itch_space = i - 1;
	}
}
void CWB(){
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
		itch = BACKWARD;
		itch_space = i - 1;
	}
}
void BJPI(){
	switch(itch){
		case NONE:
			printf("No itch!\n");
		case LEFT:
			current_row -= itch_space;		
			itch = NONE;
			itch_space = 0;
		case RIGHT:	
			current_row += itch_space;		
			itch = NONE;
			itch_space = 0;
		case FORWARD:
			current_col += itch_space;	
			itch = NONE;
			itch_space = 0;
		case BACKWARD:	
			current_col -= itch_space;
			itch = NONE;
			itch_space = 0;	
	}
}
void CJPI(){
	switch(itch){
		case NONE:
			printf("No itch!\n");
		case LEFT:
			current_row--;		
			itch = NONE;
			itch_space = 0;
		case RIGHT:	
			current_row++;		
			itch = NONE;
			itch_space = 0;
		case FORWARD:
			current_col++;	
			itch = NONE;
			itch_space = 0;
		case BACKWARD:	
			current_col--;
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
void RP(void (*n)(), int t){
	int i;
	for(i = 0; i < t; i++){
		(*n)();
	}
}
