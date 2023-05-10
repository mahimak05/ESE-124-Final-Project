#include <stdio.h>
#include <stdbool.h>

int x = 0; //row number
int y = 0; //column number
//positions

int mark()
{
    maze[x][y]='#'; //mark the current position of the maze using a # sign 
}

bool isSafe(int maze[total_rows][total_columns], int x, int y)
{
    if (x >= '\n' && x < total_rows && y >= '\n' && y < total_columns && maze[x][y] == 1)
    {
        return true;
    }
    return false;
    //checks if the next positions are pheromone free 
}
void move_forward()
{
    x++; //move x position 1 forward
}

void move_backward()
{
    x--; //move x position 1 forward
}

void move_left()
{
    y++; //move y position 1 forward
}

void move_right()
{
    y--; //move y position 1 forward
}

int check_left(int x, int y)
{
    if(isSafe)
}

int check_right(int x, int y)
{

}

int check_forward(int x, int y)
{

}

int check_backward(int x, int y)
{

    
}



