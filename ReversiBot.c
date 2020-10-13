//Paula Perdomo
// 1005974313
//Lab8Part1

#include <stdio.h>
#include <stdbool.h>
//#include "lab8part2lib.h"


void printBoard(char board[26][26], int n) {

  printf("  ");

  for(int i = 0; i < n; i++) {
    printf("%c", i+97);
  }

  printf("\n");

  for(int i = 0; i < n; i++) {
    printf("%c ", i+97);
    for(int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
      }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int column) {

  if(row >= 0 && column >= 0 && row <= n-1 && column <= n-1)
    return true;
  else
    return false;
}

bool checkLegalInDirection(char board[26][26], int n, int row, int column, char colour, int deltaRow, int deltaColumn) {
    
  char opponent = '\0';
  if(colour == 'B')
    opponent = 'W';
  if(colour == 'W')
    opponent = 'B';

  int count = 1;

  while(true) {
    if(!positionInBounds(n, row+deltaRow*count, column+deltaColumn*count))
      return false;
    if(count > 1 && board[row+deltaRow*count][column+deltaColumn*count] == colour)
      return true;
    if(board[row+deltaRow*count][column+deltaColumn*count] != opponent)
      return false;
    
    count++;
  }
}

void flipTiles(char board[26][26], int n, int row, int column, char colour, int deltaRow, int deltaColumn) {

  char opponent = '\0';
  if(colour == 'B')
    opponent = 'W';
  if(colour == 'W')
    opponent = 'B';

  int count = 1;
  
  while(board[row+deltaRow*count][column+deltaColumn*count] != colour) {
    board[row+deltaRow*count][column+deltaColumn*count] = colour;
    count++;
  }
}

void counting(char board[26][26], int n, char colour, int* returnRow, int* returnColumn) {

  int highestScore = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int score = 0;
      if(board[i][j] == 'U') {
      if(checkLegalInDirection(board, n, i, j, colour, -1, -1) == true) {
        int count = 1;
        while(board[i+(-1)*count][j+(-1)*count] != colour) {
          score++;
          count++;
        }
      }
      if(checkLegalInDirection(board, n, i, j, colour, -1, 0) == true) {
        int count = 1;
        while(board[i+(-1)*count][j+(0)*count] != colour) {
          score++;
          count++;
        }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 1, 1) == true) {
        int count = 1;
        while(board[i+(1)*count][j+(1)*count] != colour) {
        score++;
        count++;
        }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 0, -1) == true) {
        int count = 1;
        while(board[i+(0)*count][j+(-1)*count] != colour) {
        score++;
        count++;
       }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 0, 1) == true) {
        int count = 1;
        while(board[i+(0)*count][j+(1)*count] != colour) {
        score++;
        count++;
        }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 1, -1) == true) {
        int count = 1;
        while(board[i+(1)*count][j+(-1)*count] != colour) {
        score++;
        count++;
       }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 1, 0) == true) {
        int count = 1;
        while(board[i+(1)*count][j+(0)*count] != colour) {
        score++;
        count++;
       }
      }
      if(checkLegalInDirection(board, n, i, j, colour, 1, 1) == true) {
        int count = 1;
        while(board[i+(1)*count][j+(1)*count] != colour) {
        score++;
        count++;
       }
      }

      if(score > highestScore) {
       highestScore = score;
       *returnRow = i;
       *returnColumn = j;
        }
      }
    }
  }
}

void direction(char board[26][26], int n, int row, int column, char colour, int direction[16]) {
  int lastIndex = 0;
  if(checkLegalInDirection(board, n, row, column, colour, -1, -1) == true) {
    direction[lastIndex] = -1;
    direction[lastIndex+1] = -1;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, -1, 0) == true) {
    direction[lastIndex] = -1;
    direction[lastIndex+1] = 0;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, -1, 1) == true) {
    direction[lastIndex] = -1;
    direction[lastIndex+1] = 1;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, 0, -1) == true) {
    direction[lastIndex] = 0;
    direction[lastIndex+1] = -1;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, 0, 1) == true) {
    direction[lastIndex] = 0;
    direction[lastIndex+1] = 1;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, 1, -1) == true) {
    direction[lastIndex] = 1;
    direction[lastIndex+1] = -1;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, 1, 0) == true) {
    direction[lastIndex] = 1;
    direction[lastIndex+1] = 0;
    lastIndex +=2;
  }
  if(checkLegalInDirection(board, n, row, column, colour, 1, 1) == true) {
    direction[lastIndex] = 1;
    direction[lastIndex+1] = 1;
    lastIndex +=2;
  }
}

bool won(char board[26][26], int n, char* winningColour) {
  int whiteCount = 0;
  int blackCount = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(board[i][j] == 'W')
        whiteCount++;
      if(board[i][j] == 'B')
        blackCount++;
       if(board[i][j] == 'U')
        return false;
    }
  }
    if(whiteCount > blackCount)
    *winningColour = 'W';
    else if(whiteCount == blackCount)
    printf("Draw!");
    else
    *winningColour = 'B';
    return true;
}

void algorithm(char board[26][26], int n, char colour, int* returnRow, int* returnColumn) {
    
  int count = 1;
  int highestScore = 0;
    
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      
      //Does this prioritize the corners?
      if((board[0][0] == 'U' && i == 0 && j == 0)  || (board[0][n-1] == 'U' && i == 0 && j == n-1)|| (board[n-1][0] == 'U' && i == n-1 && j == 0)|| (board[n-1][n-1] == 'U' && i == n-1 && j == n-1)) {
        if(checkLegalInDirection(board, n, i, j, colour, -1, -1) == true) {
         *returnRow = i;
         *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, -1, 0) == true) {
         *returnRow = i;
         *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, -1, 1) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, 0, -1) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, 0, 1) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, 1, -1) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, 1, 0) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
        if(checkLegalInDirection(board, n, i, j, colour, 1, 1) == true) {
          *returnRow = i;
          *returnColumn = j;
        }
      }
        
      else {
        if(board[i][j] == 'U') {
          int score = 0;
          if(checkLegalInDirection(board, n, i, j, colour, -1, -1) == true) {
            int count = 1;
            while(board[i+(-1)*count][j+(-1)*count] != colour) {
            score++;
            count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, -1, 0) == true) {
            int count = 1;
            while(board[i+(-1)*count][j+(0)*count] != colour) {
             score++;
             count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, 1, 1) == true) {
            int count = 1;
            while(board[i+(1)*count][j+(1)*count] != colour) {
              score++;
             count++;
            }
          }
         if(checkLegalInDirection(board, n, i, j, colour, 0, -1) == true) {
            int count = 1;
            while(board[i+(0)*count][j+(-1)*count] != colour) {
              score++;
              count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, 0, 1) == true) {
            int count = 1;
            while(board[i+(0)*count][j+(1)*count] != colour) {
             score++;
             count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, 1, -1) == true) {
            int count = 1;
            while(board[i+(1)*count][j+(-1)*count] != colour) {
              score++;
              count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, 1, 0) == true) {
           int count = 1;
           while(board[i+(1)*count][j+(0)*count] != colour) {
             score++;
             count++;
            }
          }
          if(checkLegalInDirection(board, n, i, j, colour, 1, 1) == true) {
            int count = 1;
            while(board[i+(1)*count][j+(1)*count] != colour) {
              score++;
              count++;
            }
          }
          if(score >= highestScore) {
            highestScore = score;
           *returnRow = i;
           *returnColumn = j;
          }
        }
      }
    }
  }
}

int main() {
    
  int dimension;
  char board[26][26];
  
  printf("Enter the board dimension: ");
  scanf("%d", &dimension);

   for(int i = 0; i < dimension; i++) {
    for(int j = 0; j < dimension; j++) {
      board[i][j] = 'U';
      board[dimension/2-1][dimension/2] = 'B';
      board[dimension/2][dimension/2-1] = 'B';
      board[dimension/2-1][dimension/2-1] = 'W';
      board[dimension/2][dimension/2] = 'W';
    }
  }

  char computer;
  char player;
  bool computerTurn = false;

  printf("Computer plays (B/W): ");
  scanf(" %c", &computer); //Why doesn't a string need &.

  if(computer == 'W') {
    player = 'B';
    computerTurn = false;
  }
  else if(computer == 'B') {
    player = 'W';
    computerTurn = true;
  }
 
  printBoard(board, dimension);
  
  int rRow, rColumn;
  char winningColour;
  while(true) {
    if(won(board, dimension, &winningColour) == true){
      printf("%c player wins.\n", winningColour);
      return 0;
    }
    if(computerTurn == true) {
      int direction1[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
      counting(board, dimension, computer, &rRow, &rColumn);
      direction(board, dimension, rRow, rColumn, computer, direction1);
      if(direction1[0] == 3 && direction1[1] == 3) {
        printf("%c player has no valid move.\n", computer);
        computerTurn = false;
      }
      else {
      board[rRow][rColumn] = computer;
      for(int i = 0; i < 16 && direction1[i]!= 3; i+=2) {
        flipTiles(board, dimension, rRow, rColumn, computer, direction1[i], direction1[i+1]);
      }
      printf("Computer places %c at %c%c.\n", computer, rRow+97, rColumn+97);
      printBoard(board, dimension);
      computerTurn = false;
    }
  }
  else {
      int direction2[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
      printf("Enter move for colour %c (RowCol): ", player);
      char playerMove[2];
      scanf("%s", playerMove);
      direction(board, dimension, playerMove[0]-97, playerMove[1]-97, player, direction2);
      if(direction2[0] && direction2[1] == 3) {
        printf("Invalid move.\n");
        printf("%c player wins.\n", computer);
        return 0;
      }
      board[playerMove[0]-97][playerMove[1]-97] = player;
      for(int i = 0; i < 16 && direction2[i] != 3; i+=2) {
        flipTiles(board, dimension, playerMove[0]-97, playerMove[1]-97, player,direction2[i], direction2[i+1]);
      }
      printBoard(board, dimension);
      computerTurn = true;
    }
  }
}

