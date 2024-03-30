#include "lab8part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void bestMove(char board[][26], char validMoves[][26], int n, char colour, int bestMoveIndex[])
{
    int score = 0;
    int counter = 0;
    int bestScore = -100;

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
                    score += 50; // corner's are superior
                }
                else if (row == 0 && col == 1 || row == 0 && col == n - 2 || row == 1 && col == 0 || row == 1 && col == n - 1 || row == n - 2 && col == 0 || row == n - 2 && col == n - 1 || row == n - 1 && col == 1 || row == 0 && col == n - 2)
                {
                    score -= 10;
                }
                
                else if (row == 1 && col == 1 || row == 1 && col == n - 2 || row == n - 2 && col == 1 || row == n - 2 && col == n - 2)
                {
                    score -= 8;
                }
                else if (row < n / 2 + 2 && row > n / 2 - 2 && col < n / 2 + 2 && col > n / 2 - 2)
                {
                    score += 30;
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
                                score += 1;
                                counter++;
                            }
                        }
                    }
                }

                board[row][col] = colour;
                if (colour == 'W')
                {
                    score -= 2*countValidMove(board, n, 'B');
                }
                else
                {
                    score -= 2*countValidMove(board, n, 'W');
                }
                board[row][col] = 'U';

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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            nonConstantBoard[i][j] = board[i][j];
        }
    }

    findValidMove(nonConstantBoard, validMovesComputer, n, turn);
    bestMove(nonConstantBoard, validMovesComputer, n, turn, bestMoveIndex);
    *row = bestMoveIndex[0];
    *col = bestMoveIndex[1];

    // printf("Computer places %c at %c%c.\n", turn, bestMoveIndex[0] + 97, bestMoveIndex[1] + 97);
    return 0;
}
