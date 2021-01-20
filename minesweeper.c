#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
#define MAXLIMIT 25
#define MAXMINES 100
#define MOVESIZE 100

int limit ;
int mine ;
int isValid(int row, int col)
{
    return (row >= 0) && (row < limit) &&(col >= 0) && (col < limit);
}
int isMine (int row, int col, char board[][MAXLIMIT])
{
    if (board[row][col] == '*')
        return 1;
    else
        return 0;
}
void makeMove (int *x, int *y)
{
printf("\n\n(row,column) : ");

      scanf("%d %d", x, y);

    return;
}
void printBoard(char playboard[][MAXLIMIT])
{
    int i,j;

    printf ("\n\n\n                   ");

    for (i=0; i<limit; i++)
{
        printf ("%d  ", i);}

    printf ("\n\n");

    for (i=0; i<limit; i++)
    {
        printf ("\t\t%d  ", i);
        printf("");
        for (j=0; j<limit; j++){
            printf ("%c  ", playboard[i][j]);}
        printf ("\n");
    }
}
int countMines(int row ,int col ,int mines[][2], char gameboard[][MAXLIMIT])
{

    int i;
    int count = 0;
        if (isValid (row-1, col) == 1)
        {
               if (isMine (row-1, col, gameboard) == 1)
               count++;
        }
        if (isValid (row+1, col) == 1)
        {
               if (isMine (row+1, col, gameboard) == 1)
               count++;
        }
        if (isValid (row, col+1) == 1)
        {
            if (isMine (row, col+1, gameboard) == 1)
               count++;
        }
        if (isValid (row, col-1) == 1)
        {
               if (isMine (row, col-1, gameboard) == 1)
               count++;
        }
        if (isValid (row-1, col+1) == 1)
        {
            if (isMine (row-1, col+1, gameboard) == 1)
               count++;
        }
        if (isValid (row-1, col-1) == 1)
        {
             if (isMine (row-1, col-1, gameboard) == 1)
               count++;
        }
        if (isValid (row+1, col+1) == 1)
        {
               if (isMine (row+1, col+1, gameboard) == 1)
               count++;
        }
        if (isValid (row+1, col-1) == 1)
        {
            if (isMine (row+1, col-1, gameboard) == 1)
               count++;
        }

    return count;
}
int playMinesweeper(char playboard[][MAXLIMIT], char gameboard[][MAXLIMIT],
            int mines[][2], int row, int col, int *movesLeft)
{
    if (playboard[row][col]!='-')
        return 0;
int i, j;
    if (gameboard[row][col] == '*')
    {
        playboard[row][col]='*';

        for (i=0; i<mine; i++)
            playboard[mines[i][0]][mines[i][1]]='*';

        printBoard (playboard);
        printf ("\nYou lost!\n");
        return 1 ;
    }

    else
    {
        int count = countMines(row, col, mines, gameboard);
        (*movesLeft)--;

        playboard[row][col] = count + '0';

        if (!count)
        {
            if (isValid (row-1, col) == 1)
            {
                   if (isMine (row-1, col, gameboard) == 0)
                   playMinesweeper(playboard, gameboard, mines, row-1, col, movesLeft);
            }
            if (isValid (row+1, col) == 1)
            {
                   if (isMine (row+1, col, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row+1, col, movesLeft);
            }
            if (isValid (row, col+1) == 1)
            {
                if (isMine (row, col+1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row, col+1, movesLeft);
            }
            if (isValid (row, col-1) == 1)
            {
                   if (isMine (row, col-1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row, col-1, movesLeft);
            }
            if (isValid (row-1, col+1) == 1)
            {
                if (isMine (row-1, col+1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row-1, col+1, movesLeft);
            }
            if (isValid (row-1, col-1) == 1)
            {
                 if (isMine (row-1, col-1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row-1, col-1, movesLeft);
            }
            if (isValid (row+1, col+1) == 1)
            {
                   if (isMine (row+1, col+1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row+1, col+1, movesLeft);
            }
            if (isValid (row+1, col-1) == 1)
            {
                if (isMine (row+1, col-1, gameboard) == 0)
                    playMinesweeper(playboard, gameboard, mines, row+1, col-1, movesLeft);
            }
        }

        return 0;
    }
}
void placeMines(int mines[][2], char gameboard[][MAXLIMIT])
{
    int flag[MAXLIMIT*MAXLIMIT];

    memset (flag, 0, sizeof (flag));
    for (int i=0; i<mine; )
     {
        int random = rand() % (limit*limit);
        int x = random / limit;
        int y = random % limit;
        if (flag[random] == 0)
        {
            mines[i][0]= x;
            mines[i][1] = y;
            gameboard[mines[i][0]][mines[i][1]] = '*';
            flag[random] = 1;
            i++;
        }
    }

    return;
}
void initialise (char gameboard[][MAXLIMIT], char playboard[][MAXLIMIT])
{
    //srand (time (NULL));
    for (int i=0; i<limit; i++)
    {
        for (int j=0; j<limit; j++)
        {
            playboard[i][j] = gameboard[i][j] = '-';
        }
    }

    return;
}
void replaceMine (int row, int col, char board[][MAXLIMIT])
{
    for (int i=0; i<limit; i++)
    {
        for (int j=0; j<limit; j++)
            {
                if (board[i][j] != '*')
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
    }
    return;
}
void startplaying()
{
    int end= 0;
    char gameboard[MAXLIMIT][MAXLIMIT], playboard[MAXLIMIT][MAXLIMIT];
     int movesLeft = limit * limit - mine, x, y;
    int mines[MAXMINES][2];
      int moves[MOVESIZE][2];
   initialise (gameboard, playboard);
    placeMines (mines, gameboard);
      int currentMoveIndex = 0;
    while (end == 0)
     {
        printBoard (playboard);
        makeMove (&x, &y);
        if (currentMoveIndex == 0)
        {
            if (isMine (x, y, gameboard) == 1)
                replaceMine (x, y, playboard);
        }

        currentMoveIndex ++;

        end = playMinesweeper(playboard, gameboard, mines, x, y, &movesLeft);

        if ((end == 0) && (movesLeft == 0))
         {
            printf ("\nYou won !\n");
            end = 1;
         }
    }

    return;
}
void selectthelevel()
{
    int level;
    printf("\n\n\n\n");
    printf("                                      press 1 for Beginner Level\n");
    printf("                                      press 2 for Intermediate Level\n");
    printf("                                      press 3 for Advanced Level\n");
    printf("                                      select the level:");
    scanf("%d",&level);

    if (level == 1)
    {
        limit = 8;
        mine = 10;
    }

    if (level == 2)
    {
        limit= 16;
        mine = 40;
    }

    if (level == 3)
    {
        limit = 24;
        mine = 99;
    }

    return;
}
void gamedisplay(){
printf("                                                         \n");
printf("                                                                ***M***\n");
printf("                                                                ***I***\n");
printf("                                                                ***N***\n");
printf("                                                                ***E***\n");
printf("                                                                ***S***\n");
printf("                                                                ***W***\n");
printf("                                                                ***E***\n");
printf("                                                                ***E***\n");
printf("                                                                ***P***\n");
printf("                                                                ***E***\n");
printf("                                                                ***R***");
}
int main()
{
    printf("\n\n\n                                                          ******WELCOME TO******\n\n");
     gamedisplay();
     selectthelevel();
     startplaying();
}
