#include "liblab8part2.h"
#include "lab8part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
void initalBoard(char board[][26], int n);
bool fullBoard(char board[][26], int n);
void findWinner(char board[][26], int n);
void setupValidMoves(char validMoves[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void updateBoard(char board[][26], int n, char colour, int rowIndex, int colIndex);
void flipColourInDir(char board[][26], char colour, int row, int col, int deltaRow, int deltaCol);
void findValidMove(char board[][26], char validMoves[][26], int n, char colour);
bool noMoves(char validMoves[][26], int n);
bool checkValidMove(char validMoves[][26], char row, char col);
int countValidMove(char board[][26], int n, char colour);
void bestMove(char board[][26], char validMoves[][26], int n, char colour, int bestMoveIndex[]);
int makeMove(const char board[][26], int n, char turn, int *row, int *col);

// int makeMove(int bestMoveIndex[], int index)
// {
//     return bestMoveIndex[index];
// }

int main(void)
{
    char computerColour, userColour, userRow, userCol;
    int n;
    int turn = 0; // 0 comp , 1 user
    char board[26][26];
    char validMovesUser[26][26];
    char validMovesComputer[26][26];
    int bestMoveIndex[2] = {-1, -1};
    int row, col;

    printf("Enter the board dimension: ");
    scanf("%d", &n);
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);

    if (computerColour == 'B')
    {
        userColour = 'W';
    }
    else
    {
        userColour = 'B';
        turn++;
    }

    initalBoard(board, n);

    bool continueplaying = true;
    while (continueplaying)
    {
        if (fullBoard(board, n))
        {
            findWinner(board, n);
            continueplaying = false;
            break;
        }

        if (turn % 2 == 1)
        {
            findValidMove(board, validMovesUser, n, userColour);
            if (noMoves(validMovesUser, n))
            {
                printf("%c player has no valid move.\n", userColour);
            }
            else
            {
                findSmartestMove(board, n, userColour, &row, &col);
                printf("Testing AI move (row, col): %c%c\n", row + 'a', col + 'a');

                // printf("Enter move for colour %c (RowCol): ", userColour);
                // scanf(" %c %c", &userRow, &userCol);
                if (checkValidMove(validMovesUser, row + 'a', col + 'a'))
                {
                    updateBoard(board, n, userColour, row, col);
                }
                else
                {
                    printf("Invalid move.\n");
                    printf("%c player wins.\n", computerColour);
                    continueplaying = false;
                    break;
                }

                // if (checkValidMove(validMovesUser, userRow, userCol))
                // {
                //     updateBoard(board, n, userColour, userRow - 'a', userCol - 'a');
                // }
                // else
                // {
                //     printf("Invalid move.\n");
                //     printf("%c player wins.\n", computerColour);
                //     continueplaying = false;
                //     break;
                // }
            }
        }
        else
        {
            findValidMove(board, validMovesComputer, n, computerColour);
            if (noMoves(validMovesComputer, n))
            {
                printf("%c player has no valid move.\n", computerColour);
            }
            else
            {
                // bestMove(board, validMovesComputer, n, computerColour, bestMoveIndex);
                // printf("Computer places %c at %c%c.\n", computerColour, makeMove(bestMoveIndex, 0) + 97, makeMove(bestMoveIndex, 1) + 97);
                // updateBoard(board, n, computerColour, makeMove(bestMoveIndex, 0), makeMove(bestMoveIndex, 1));

                bestMove(board, validMovesComputer, n, computerColour, bestMoveIndex);
                printf("Computer places %c at %c%c.\n", computerColour, bestMoveIndex[0] + 97, bestMoveIndex[1] + 97);
                updateBoard(board, n, computerColour, bestMoveIndex[0], bestMoveIndex[1]);
            }
        }
        turn++;
    }
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
    board[n / 2][n / 2 - 1] = 'B';

    printBoard(board, n);
}

bool fullBoard(char board[][26], int n)
{
    bool ifFull = true;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 'U')
            {
                ifFull = false;
                break;
            }
        }
    }
    return ifFull;
}

void findWinner(char board[][26], int n)
{
    int blackCounter = 0;
    int whiteCounter = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 'B')
            {
                blackCounter++;
            }
            else
            {
                whiteCounter++;
            }
        }
    }

    if (blackCounter > whiteCounter)
    {
        printf("B player wins.");
    }
    else
    {
        printf("W player wins.");
    }
}

void setupValidMoves(char validMoves[][26], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            validMoves[i][j] = 'N';
        }
    }
}

bool positionInBounds(int n, int row, int col)
{
    if (row < 0 || row > n || col < 0 || col > n)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{

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
    return 0;
}

void updateBoard(char board[][26], int n, char colour, int rowIndex, int colIndex)
{

    board[rowIndex][colIndex] = colour;

    for (int rowDir = -1; rowDir <= 1; rowDir++)
    {
        for (int colDir = -1; colDir <= 1; colDir++)
        {
            if ((checkLegalInDirection(board, n, rowIndex, colIndex, colour, rowDir, colDir)) && !(rowDir == 0 && colDir == 0))
            {
                flipColourInDir(board, colour, rowIndex, colIndex, rowDir, colDir);
            }
        }
    }
    printBoard(board, n);
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

void findValidMove(char board[][26], char validMoves[][26], int n, char colour)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            validMoves[i][j] = 'N';
        }
    }

    bool available;
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (board[row][col] == 'U')
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

                if (available)
                {
                    validMoves[row][col] = 'Y';
                }
            }
        }
    }
}

int countValidMove(char board[][26], int n, char colour)
{
    bool available;
    int counter = 0;
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (board[row][col] == 'U')
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

                if (available)
                {
                    counter++;
                }
            }
        }
    }
    return counter;
}

bool noMoves(char validMoves[][26], int n)
{
    bool moveFound = true;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (validMoves[row][col] == 'Y')
            {
                moveFound = false;
                break;
            }
        }
    }
    return moveFound;
}

bool checkValidMove(char validMoves[][26], char row, char col)
{
    if (validMoves[row - 97][col - 97] == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void bestMove(char board[][26], char validMoves[][26], int n, char colour, int bestMoveIndex[])
{
    int score = 0;
    int counter = 0;
    int bestScore = -20;

    char validMovesSchool[26][26];

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            score = 0;
            if (validMoves[row][col] == 'Y')
            {
                if (row == 0 && col == 0 || row == 0 && col == n - 1 || row == n - 1 && col == 0 || row == n - 1 && col == n - 1)
                {
                    score += 30;
                }
                else if (row == 0 && col == 1 || row == 0 && col == n - 2 || row == 1 && col == 0 || row == 1 && col == n - 1 || row == n - 2 && col == 0 || row == n - 2 && col == n - 1 || row == n - 1 && col == 1 || row == 0 && col == n - 2)
                {
                    score -= 8;
                }
                else if (row == 1 && col == 1 || row == 1 && col == n - 2 || row == n - 2 && col == 1 || row == n - 2 && col == n - 2)
                {
                    score -= 6;
                }
                else if (row < n / 2 + 2 && row > n / 2 - 2 && col < n / 2 + 2 && col > n / 2 - 2)
                {
                    score += 10;
                }

                for (int rowDir = -1; rowDir <= 1; rowDir++)
                {
                    for (int colDir = -1; colDir <= 1; colDir++)
                    {

                        counter = 0;
                        if (checkLegalInDirection(board, n, row, col, colour, rowDir, colDir) && !(rowDir == 0 && colDir == 0))
                        {
                            while (board[row + rowDir * (counter + 1)][col + colDir * (counter + 1)] != colour && positionInBounds(n, row + rowDir * (counter + 1), col + colDir * (counter + 1)))
                            {
                                score+= 2;
                                counter++;
                            }
                        }
                    }
                }

                board[row][col] = colour;
                if (colour == 'W') {
                    score -= countValidMove(board, n, 'B');
                }
                else{
                    score -= countValidMove(board, n, 'W');
                }

                if (score > bestScore)
                {
                    bestMoveIndex[0] = row;
                    bestMoveIndex[1] = col;
                    bestScore = score;
                }
            }
        }
    }
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col)
{
    char validMovesComputer[26][26];
    char nonConstantBoard[26][26];
    int bestMoveIndex[2] = {-1, -1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nonConstantBoard[i][j] = board[i][j];
        }    
    }

    findValidMove(nonConstantBoard, validMovesComputer, n, turn);

    bestMove(nonConstantBoard, validMovesComputer, n, turn, bestMoveIndex);
    printf("Computer places %c at %c%c.\n", turn, bestMoveIndex[0] + 97, bestMoveIndex[1] + 97);
    return 0;
}
