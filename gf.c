#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <menu.h>
#include <time.h>

// Cell

struct cell 
{ 
    int current; 
    int future; 
};

// Point

typedef struct point 
{ 
    int x; 
    int y; 
} point;

// Function declarations.

void printWorld(struct cell board [30] [90]);
void updateWorld(struct cell board [30] [90]);
void copyWorldToNext(struct cell board [30] [90]);
void readRandomWorld(struct cell board [30] [90]);
void readWorldFromFile(struct cell board [30] [90]);

// Main.

int main() {
    struct cell board [30] [90] = {0, 0};

    initscr();
    clear();
    nodelay(stdscr, TRUE);

    start_color ();
    init_pair (1, COLOR_GREEN, COLOR_BLUE);
    init_pair (2, COLOR_RED, COLOR_RED);
    init_pair (3, COLOR_BLUE, COLOR_GREEN);
    bkgd (COLOR_PAIR (1));

    curs_set(0);
    noecho();
    readRandomWorld(board);
    
    int i = 0;
    int count = 0;

    while ( i < 100 ) 
    {
        printWorld(board);
        updateWorld(board);
    
        count += 1;
        i++;
    
        mvprintw(32, 0, "Count: %d", count);
    }
    
    nodelay(stdscr, FALSE); 

    getch();
    endwin();
}

// readWorldFromFile.

void readWorldFromFile(struct cell board [30] [90]) 
{
    FILE *fPointer;
    char state_column;
    int state;
    int column = 0;
    int row = 0;

    fPointer = fopen("gof.txt", "r");

    while ( !feof(fPointer) ) 
    {
        fscanf(fPointer, "%c", &state_column);
    
        if ( state_column != '\n' ) 
        {
            state = state_column - '0';
            board[row][column].current = state;
            column++;
        }
        
        else 
        {
            row++;
            column = 0;
        }
    }
}

// readRandomWorld.

void readRandomWorld(struct cell board [30] [90]) 
{
    int row;
    int column;
    int number;

    srand(time(0));

    for ( row = 0; row < 30; row++ ) 
    {
        for ( column = 0; column < 90; column++ ) 
        {
            number = rand() % 10;

            if ( number == 1 )
                board[row][column].current = 1;
            else 
                board[row][column].current = 0;
            
        }
    }    
}

// printWorld.

void printWorld(struct cell board [30] [90]) {

    int row;
    int column;

    for ( row = 0; row < 30; row++ ) 
    {
        for ( column = 0; column < 90; column++ ) 
        {
            move(row, column);

            if ( board[row][column].current == 1 )
            {
                attron(COLOR_PAIR(3));
                mvaddch(row, column, ' ');
                attroff(COLOR_PAIR(3));
            }
            else {
                attron(COLOR_PAIR(1));
                mvaddch(row, column, ' ');
                attroff(COLOR_PAIR(1));
            } 
        }
    }
    refresh();
    usleep(250000);
}

// updateWorld.

void updateWorld(struct cell board [30] [90]) 
{
    int row;
    int column;
    int neighbours = 0;

    for ( row = 0; row < 30; row++ ) 
    {
        for ( column = 0; column < 90; column++ ) 
        {
            if ( board[row][column].current == 1 ) 
            {
                if ( board[row][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row][column-1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column-1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column-1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( neighbours == 2 || neighbours == 3 ) 
                {
                    board[row][column].future = 1;
                    neighbours = 0;
                }
                else {
                    board[row][column].future = 0;
                    neighbours = 0;
                }
            }
            if ( board[row][column].current == 0 ) 
            {
                if ( board[row][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row][column-1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row-1][column-1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column+1].current == 1 ) 
                {
                    neighbours++;
                } 
                if ( board[row+1][column-1].current == 1 )
                {
                    neighbours++;
                } 
                if ( neighbours == 3 ) 
                {
                    board[row][column].future = 1;
                    neighbours = 0;
                }
                else 
                {
                    board[row][column].future = 0;
                    neighbours = 0;
                }
            }
        }
    }

    for ( row = 0; row < 30; row++ ) 

        for(column = 0; column < 90; column++) 
            board[row][column].current = board[row][column].future;

}
