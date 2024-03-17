#include "reversi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
void initalBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void updateBoard(char board[][26], int n);
void availableMoves(char board[][26], int n, char colour);
void flipColourInDir(char board[][26], char colour, int row, int col, int deltaRow, int deltaCol);
void userMove(char board[][26], int n);

int main(void)
{
    int n;
    char board[26][26];

    printf("Enter the board dimension: ");
    scanf("%d", &n);

    initalBoard(board, n);

    updateBoard(board, n);

    availableMoves(board, n, 'W');
    availableMoves(board, n, 'B');

    userMove(board, n);    

    return 0;
}

void printBoard(char board[][26], int n)
{
    printf("  ");
    char letter = 'a';
    for (int i = 0; i < n; ++i)
    {
        printf("%c", letter);
        letter++;
    }
    printf("\n");
    letter = 'a';
    for (int i = 0; i < n; ++i)
    {
        printf("%c ", letter);

        for (int j = 0; j < n; ++j)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
        letter++;
    }
}

void initalBoard(char board[][26], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            board[i][j] = 'U';
        }
    }
    board[n / 2][n / 2] = 'W';
    board[n / 2 - 1][n / 2 - 1] = 'W';

    board[n / 2 - 1][n / 2] = 'B';
    board[n / 2][n / 2-1] = 'B';

    printBoard(board, n);
}

bool positionInBounds(int n, int row, int col)
{
    if (row < 0 || row > n || col < 0 || col > n)
    {
        return false;
    }
    else{
        return true;
    }
    
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    if (!positionInBounds(n, row, col) || board[row][col] != 'U')
    {
        return false;
    }

    int nextRow = row + deltaRow;
    int nextCol = col + deltaCol;

    if (!positionInBounds(n, nextRow, nextCol) || board[nextRow][nextCol] == 'U' || board[nextRow][nextCol] == colour)
    {
        return false;
    }

    for (int i = 2; i < n; ++i)
    {
        if (!positionInBounds(n, row + deltaRow * i, col + deltaCol * i) || board[row + deltaRow * i][col + deltaCol * i] == 'U')
        {
            return false;
        }

        else if (board[row + deltaRow * i][col + deltaCol * i] == colour)
        {
            return true;
        }
    }


}

void updateBoard(char board[][26], int n)
{
    char colour, rowChar, colChar;
    printf("Enter board configuration:\n");

    while (colour != '!' && rowChar != '!' && colChar != '!'){

        int rowIndex = rowChar - 'a';
        int colIndex = colChar - 'a';

        if (positionInBounds(n, rowIndex, colIndex) &&  (colour == 'W' || colour == 'B'))
        {
            board[rowIndex][colIndex] = colour;
        }
        scanf(" %c %c %c", &colour, &rowChar, &colChar);
    }

    printBoard(board, n);

}
     
void availableMoves(char board[][26], int n, char colour)
{
    printf("Available moves for %c:\n", colour);
    bool available;
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            available = false;
            for (int rowDir = -1; rowDir <= 1; rowDir++)
            {
                for (int colDir = -1; colDir <= 1; colDir++)
                {
                    if (checkLegalInDirection(board, n, row, col, colour, rowDir, colDir) && !(rowDir == 0 && colDir == 0))
                    {
                        available = true;
                    }
                }

            }

            if (available) {
                printf("%c%c\n", (row + 97), (col + 97));
            }
        }
    }
}

void flipColourInDir(char board[][26], char colour, int row, int col, int deltaRow, int deltaCol)
{
    int numFlips = 1;
    while (board[row + deltaRow * numFlips][col + deltaCol * numFlips] != colour)
    {
        board[row + deltaRow * numFlips][col + deltaCol * numFlips] = colour;
        numFlips++;
    }
}

void userMove(char board[][26], int n)
{
    char colour, rowChar, colChar;
    printf("Enter a move:\n");
    scanf(" %c %c %c", &colour, &rowChar, &colChar);

    int row = rowChar - 'a';
    int col = colChar - 'a';

    bool validMoveFound = false;

    if (!positionInBounds(n, row, col) || board[row][col] != 'U')
    {
        validMoveFound = false;
    }
    
    for (int rowDir = -1; rowDir <= 1; rowDir++)
    {
        for (int colDir = -1; colDir <= 1; colDir++)
        {
            
            if (checkLegalInDirection(board, n, row, col, colour, rowDir, colDir) && !(rowDir == 0 && colDir == 0))
            {
                validMoveFound = true;
                flipColourInDir(board, colour, row, col, rowDir, colDir);
            }
        }
    }

    if (validMoveFound)
    {
        board[row][col] = colour;
        printf("Valid move.\n");
    }
    else
    {
        printf("Invalid move.\n");
        
    }

    printBoard(board, n);
}
