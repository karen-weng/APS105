#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);
bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir, char** text);
void search(const int Size, char puzzle[][Size], const int wordSize, char* word);
bool inBounds(int row, int col, const int Size);

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

void readWordPuzzle(const int Size, char puzzle[][Size])
{
    printf("Please enter the word puzzle:\n");
    for (int row = 0; row < Size; ++row)
    {
        for (int column = 0; column < Size; ++column)
        {
            scanf("%c ", &puzzle[row][column]);
        }
    }
}

char* readWord(int* wordSize) {
  printf("How many characters are there in the word?\n");
  scanf("%d", wordSize);
  char* wordInput = malloc(*(wordSize) * sizeof(char));
  printf("What is the word that you are looking for?\n");
    scanf("%s", wordInput);
    return wordInput;
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("The word puzzle entered is\n");
  for (int row = 0; row < Size; ++row)
    {
        for (int column = 0; column < Size; ++column)
        {
            printf("%c ", puzzle[row][column]);
        }
        printf("\n");
    }
}

void printWord(char* word, const int wordSize) {
  for (int letter = 0; letter < wordSize; ++letter) {
    printf("%c", word[letter]);
  }
}

void search(const int Size, char puzzle[][Size], const int wordSize, char* word) {
  bool found = false;
  char* text = " ";
  for (int row = 0; row < Size; ++row) {
    for (int column = 0; column < Size; ++column) {
      for (int dir = 0; dir < 8; ++dir) {
        if (check1D(Size, puzzle, wordSize, word, row, column, dir, &text)) {
          printf("%s can be found at row , col = (%d, %d) in the %s direction.\n", word, (row+1), (column+1), text);
          found = true;
          break;
        }
      }
    }
  }
  if (!found) {
    printf("%s cannot be found!\n", word);
  }
}

bool inBounds(int row, int col, const int Size) {
  if (row >= 0 && row < Size && col >= 0 && col < Size) {
    return true;
  }
  return false;
}

bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir, char** text) {
  bool found = true;
  //north search
  if (dir == 0) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc - i][colLoc] != word[i] || !inBounds(rowLoc - i, colLoc, Size)) {
        found = false;
        break;
      }
    }
    if (found) {*text = "north";}
  }
  //north-east search
  else if (dir == 1) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc - i][colLoc + i] != word[i] || !inBounds(rowLoc-i, colLoc+i, Size)) {
        found = false;
        break;
      }
    }
    if (found) {*text = "north-east";}
  }
  //east search
  else if (dir == 2) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc][colLoc + i] != word[i] || !inBounds(rowLoc, colLoc + i, Size)) {
        found = false;
        break;
      }
    }
    if (found) {*text = "east";}
  } 
  //south east search
  else if (dir == 3) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc + i][colLoc + i] != word[i] || !inBounds(rowLoc+i, colLoc+i, Size)) {
        found = false;
        break;
      }
    }
    if (found) {*text = "south-east";}
  } 
  //south search
  else if (dir == 4) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc + i][colLoc] != word[i] || !inBounds(rowLoc + i, colLoc, Size)) {
        found = false;
        break;
      }
    }
    if (found) { *text = "south";}
  } 
  //south-west search
  else if (dir == 5) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc + i][colLoc - i] != word[i] ||!inBounds(rowLoc + i, colLoc - i, Size)) {
        found = false;
        break;
      }
    }
    if (found) { *text = "south-west";}
  }
  //west search
  else if (dir == 6) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc][colLoc - i] != word[i] || !inBounds(rowLoc, colLoc - i, Size)) {
        found = false;
        break;
      }
    }
    if (found) { *text = "west";}
  }
  //north west search
  else if (dir == 7) {
    for (int i = 0; i < wordSize; ++i) {
      if (puzzle[rowLoc - i][colLoc - i] != word[i] || !inBounds(rowLoc - i, colLoc - i, Size)) {
        found = false;
        break;
      }
    }
    if (found) { *text = "north-west";}
  }
  return found;
}
