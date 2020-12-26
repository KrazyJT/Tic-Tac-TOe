#include <stdio.h>

#define EMPTY 0
#define CIRCLE 1
#define CROSS 2


void initGameBoard(int gameBoard[3][3]) {
int i,j;

for (i = 0; i < 3; i++){
  for (j = 0; j < 3; j++) {
    gameBoard[i][j] = 0;
  }
}

}


typedef struct{
  int x;
  int y;
}cor;

void printGameBoard(int gameBoard[3][3]) {
  printf("=========\n");
  int i,j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (gameBoard[i][j] == 0) {
        printf("|%d|", 3*(2-i) + j + 1);
      }
      else if (gameBoard[i][j] == 1) {
        printf("|%c|", 'O');
      }
      else if (gameBoard[i][j] == 2) {
        printf("|%c|", 'X');
      }
    }
    printf("\n");
  }
  printf("=========\n");
}

void placeMarkByHumanPlayer(int gameBoard[3][3], int mark, cor *go) {
int enter;
int i,j; 
scanf("%d",&enter);

if (enter == 1) {
  i = 2, j = 0;
} 

if (enter == 2) {
  i = 2, j = 1;
}

if (enter == 3) {
   i = 2, j = 2;
}

if (enter == 4) {
    i = 1, j = 0;
}

if (enter == 5) {
    i = 1, j = 1;
}

if (enter == 6) {
    i = 1, j = 2;
}

if (enter == 7) {
    i = 0, j = 0;
}

if (enter == 8) {
  i = 0, j = 1;
}

if (enter == 9) {
  i = 0, j = 2;
}
gameBoard[i][j]=mark;
go -> x = i;
go -> y = j;
}

void undo(cor *go,int gameBoard[3][3]){
   gameBoard[go -> x][go -> y] = 0;
}

int hasWinner(int gameBoard[3][3]) {
  int i;
  int j;
  for (i = 0; i < 3; i++) {
    int count = 0;
    for (j = 1; j < 3; j++) { 
      if (gameBoard[i][j] == 0) {
        break;
      }
      if (gameBoard[i][j] == gameBoard[i][j-1] ) {
        count++;
      }
    }
  if (count == 2) {
    return 1;
  }
  }
  
    for (j = 0; j < 3; j++) {
    int count = 0;
    for (i = 1; i < 3; i++) { 
      if (gameBoard[i][j] == 0) {
        break;
      }
      if (gameBoard[i][j] == gameBoard[i-1][j] ) {
        count++;
      }
    }
  if (count == 2) {
    return 1;
  }
  }

  if ((gameBoard[0][0] != 0 && gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) || (gameBoard[2][0] != 0 && gameBoard[2][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[0][2])) {
    return 1;
  }

  return 0;
  }

int isFull(int gameBoard[3][3]) {
int count = 0;
int i,j;
for (i = 0; i < 3; i++) {
  for (j = 0; j < 3; j++) {
    if (gameBoard[i][j] == 1 || gameBoard[i][j] == 2) {
      count++;
    }
  }
  if (count == 9) {
    return 1;
  }
}
return 0;
}

int checking(int gameBoard[3][3]){
    int Board[3][3];
    for(int i = 0 ; i < 3 ; i++){
      for(int j = 0;j < 3; j++){
        Board[i][j]=gameBoard[i][j];
      }
    }

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(Board[i][j] == EMPTY) {
          Board[i][j] = CIRCLE;
        if(hasWinner(Board)) {
          gameBoard[i][j] = CROSS;
          return 1;
        }
        else Board[i][j] = EMPTY;
      }
    }
  }
    return 0;
}



void placeMarkByComputerPlayer(int gameBoard[3][3]) {
int i,j;
int count = 0;
for (i = 2; i >= 0; i--) {
  for (j = 0; j < 3; j++) {
  if (gameBoard[i][j] == 0) {
    gameBoard[i][j] = CROSS;
    count++;
    break;
  } 
  }
  if (count == 1) {
    break;
}
}
}

void ImprovedAI(int gameBoard[3][3]){
   static int count = 0;

   if(count == 0){
      if(gameBoard[1][1] == CIRCLE)gameBoard[2][2]= CROSS;
      else gameBoard[1][1]=CROSS;
  }
  
   
   else if(count == 1 &&((gameBoard[2][0]== CIRCLE && gameBoard[0][2] == CIRCLE)||(gameBoard[0][0] == CIRCLE &&gameBoard[2][2] == CIRCLE))){
    gameBoard[2][1] = CROSS;
   }

   else {
     if(checking(gameBoard) == 0){
       placeMarkByComputerPlayer(gameBoard);
     }
   }
   count++;
}


/* The main function */
int main() {
    /* Local variables */
    int gameBoard[3][3];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player
    int gameEnds;           // 0: The game continues   1: The game ends
    int numOfHumanPlayers;  // 1 or 2
    cor go[50];

    int i = 0;

    int choice;

    int p1chance = 1,p2chance = 1;
   
    
   
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameEnds = 0;
    printf("How many human players [1-2]?\n");
    scanf("%d", &numOfHumanPlayers);
    
    printGameBoard(gameBoard);

    while (numOfHumanPlayers == 2) {
      printf("Player 1, please place your mark [1-9]:\n");
      placeMarkByHumanPlayer(gameBoard, CIRCLE, go+i);
      printGameBoard(gameBoard);
    if(p1chance != 0){
      printf("*Player 1, what do you what to do?*\nType 1 if you want to undo your move\nType 2 if you don't want to undo your move\n");
      scanf("%d",&choice);
      if(choice == 1){
        undo((go+i),gameBoard);
        printGameBoard(gameBoard);
        printf("Player 1, please place your mark [1-9]:\n");
        placeMarkByHumanPlayer(gameBoard,CIRCLE,go+i);
        printGameBoard(gameBoard);
        p1chance = 0;
      }
     }
      if (hasWinner(gameBoard) == 1) {
        printf("Player 1 wins! Congratulations! ");
        break;
      i++;
      }
      if (isFull(gameBoard) == 1) {
        printf("Draw game!");
        break;
      }
    printf("Player 2, please place your mark [1-9]:\n");
    placeMarkByHumanPlayer(gameBoard, CROSS, go+i);
    printGameBoard(gameBoard);
    hasWinner(gameBoard);

    if(p2chance != 0){
      printf("*Player 2, what do you what to do?*\nType 1 if you want to undo your move\nType 2 if you don't want to undo your move\n");
      scanf("%d",&choice);
      if(choice == 1){
      undo((go+i),gameBoard);
      printGameBoard(gameBoard);
      printf("Player 2, please place your mark [1-9]:\n");
      placeMarkByHumanPlayer(gameBoard,CROSS,go+i);
      printGameBoard(gameBoard);
      p2chance=0;
      }
    }
    if (hasWinner(gameBoard) == 1) {
        printf("Player 2 wins! Congratulations! ");
        break;
      }
      if (isFull(gameBoard) == 1) {
        printf("Draw game!");
        break;
        }
        i++;

        
    }

  while (numOfHumanPlayers == 1) {
      printf("Player 1, please place your mark [1-9]:\n");
      placeMarkByHumanPlayer(gameBoard, CIRCLE,go+i);
      printGameBoard(gameBoard);
      if(p1chance == 1){
      printf("*Player 1, What do you what to do?*\nType 1 if you want to undo your move\nType 2 if you don't want to undo your move\n");
      scanf("%d",&choice);
      if(choice == 1){
        undo((go+i),gameBoard);
        printGameBoard(gameBoard);
        printf("Player 1, please place your mark [1-9]:\n");
        placeMarkByHumanPlayer(gameBoard,CIRCLE,go+i);
        printGameBoard(gameBoard);
        p1chance=0;
      }
      }
      if (hasWinner(gameBoard) == 1) {
        printf("Player 1 wins! Congratulations! ");
        break;
      }
      if (isFull(gameBoard) == 1) {
        printf("Draw game!");
        break;
      }
  printf("Computer places the mark:\n");
    ImprovedAI(gameBoard);
    printGameBoard(gameBoard);
      if (hasWinner(gameBoard) == 1) {
        printf("Computer wins! ");
        break;
      }
      if (isFull(gameBoard) == 1) {
        printf("Draw game!");
        break;
  
  }
  }
      return 0;
}

 