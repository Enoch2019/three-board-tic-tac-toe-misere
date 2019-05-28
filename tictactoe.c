//Written by Enoch K (enoch7225@gmail.com)
//Project started: 2019-05-25
//Project finished:
//Three board Tic Tac Toe Misere

#include <stdio.h>
#include <stdlib.h>

typedef struct game {
    
    struct board * head;

    // number of playable boards
    int gameState;
    // number of boards
    // note: this element is only for future implementations
    int nBoards;
    // 0 is human player, 1 is computer/second player
    int playerTurn;

} * Game;

typedef struct board {

    struct board * next;
    
    struct square * topLeft;

    // 0 for playable 1 for unplayable
    int boardState;

} * Board;

typedef struct square {

    struct square * down;
    struct square * right;

    // 0 for ' ', 1 for X
    int sqrStatus;

} * Square;

void intialiseGame(Game game);
void runGame(Game game);
void endGame(Game game);
void playAgain(void);

void gameStatus(Game game);
//If board is dead than changes boardStatus to 1;
void boardStatus(Board board);

void playerMove(Game game);
Board selectBoard(Game game);
Square selectSquare(Board board);

void drawBoard(Game game);
void printRow(Square firstSquare, char row);
void printSquare(Square square);

Game createGame(void);
Board createBoard(void);
Square createSquare(void);

void destroyGame(Game game);
void destroyBoard(Board board);

int numberString(char * input);
int abcString(char * input);

int main(void) {

    Game game = createGame();
    intialiseGame(game);
    runGame(game);
    endGame(game);
    destroyGame(game);
    playAgain();


    return 0;
}

void intialiseGame(Game game) {

    int tries = 0;
    
    while (tries < 3) {

        printf("Do you want to move first? (Y/N)\n");
        char yesNo[64];
        fgets(yesNo, 64, stdin);

        switch (yesNo[0]) {
            case 'y':

                game->playerTurn = 0;
                printf("You are starting.\n");
                return;
            case 'Y':

                game->playerTurn = 0;
                printf("You are starting.\n");
                return;
            case 'n':
            
                game->playerTurn = 1;   
                printf("You are not starting.\n");
                return;

            case 'N':

                game->playerTurn = 1;
                printf("You are not starting.\n");
                return;
            default:

                printf("Sorry, I don't understand that.\n");
                tries++;
        }

    }

    game->playerTurn = 0;
    printf("I'll take that for a yes.\n");
    printf("You are starting\n");
    

    return;
}

void runGame(Game game) {

    while (game->gameState != game->nBoards) {

        drawBoard(game);
        playerMove(game);
        gameStatus(game);

    }

    drawBoard(game);

}

void endGame(Game game) {

    printf("Player %d wins.\n", game->playerTurn + 1);
    printf("Sorry Player %d. Better luck next time.\n", game->playerTurn + 1);

    /*
    if (game->playerTurn == 0) {

        printf("Sorry. You lose.\n");
    } else if (game->playerTurn == 1) {

        printf("Congratulations. You Win.\n");
    }
    */
}

void playAgain(void) {

    static int nGames = 0;
    nGames++;

    if (nGames == 16) {
        printf("Sorry. You have played too many games.\n");
        printf("Please take a break.");
        printf("Exiting game.\n");
        printf("Goodbye. Stay Healthy.\n");
        return;
    }

    int tries = 0;

    while (tries < 3) {

        printf("Would you like to play again? (Y/N)\n");
        char yesNo[64];
        fgets(yesNo, 64, stdin);

        switch(yesNo[0]) {
            case 'y':

                printf("New game commencing.\n");
                main();
                return;
            case 'Y':

                printf("New game commencing.\n");
                main();
                return;
            case 'n':

                printf("Exiting game.\n");
                printf("Goodbye.\n");
                return;
            case 'N':

                printf("Exiting game.\n");
                printf("Goodbye.\n");
                return;
            default:

                printf("Sorry, I don't understand that.\n");
                tries++;
        }
    }

    printf("I'll take that for a no.\n");
    printf("Exiting game.\n");
    printf("Goodbye.\n");
    return;
}

void playerMove(Game game) {

    printf("Player %d turn.\n", game->playerTurn + 1);

    Board board = selectBoard(game);

    while (board->boardState == 1) {
        printf("Sorry. That board is dead. Please choose another one.\n");
        board = selectBoard(game);
    }

    Square square = selectSquare(board);

    while (square->sqrStatus == 1) {
        printf("Sorry. That square already has an X in it. Please choose another one.\n");
        square = selectSquare(board);
    }

    square->sqrStatus = 1;
    
    game->playerTurn = (game->playerTurn == 1) ? 0 : 1;

    return;
}

Board selectBoard(Game game) {

    Board selectBoard = game->head;

    int number = -1;

    while (number == -1) {
        
        printf("What board do you want to play on?\n");
        char input[32];
        fgets(input, 32, stdin);
        number = numberString(input);

        if (number == -1) {
            printf("Sorry. I do not understand.\n");
        }
    }

    for (int i = 1; i < number; i++) {

        selectBoard = selectBoard->next;

    }

    return selectBoard;
}

Square selectSquare(Board board) {

    Square selectSquare = board->topLeft;

    int number = -1;
    int abc = -1;

    while (number == -1 || abc == -1) {
        
        printf("What square do you want to play on?\n");
        char input[32];
        fgets(input, 32, stdin);
        number = numberString(input);
        abc = abcString(input);

        if (number == -1 || abc == -1) {
            printf("Sorry. I do not understand.\n");
        }
    }

    for (int i = 1; i < number; i++) {

        selectSquare = selectSquare->right;

    }

    for (int i = 1; i < abc; i++) {

        selectSquare = selectSquare->down;

    }

    return selectSquare;
} 

void gameStatus(Game game) {
    
    Board currentBoard = game->head;
    game->gameState = 0;

    while (currentBoard != NULL) {

        if (currentBoard->boardState == 0) {
            boardStatus(currentBoard);
        }
        if (currentBoard->boardState == 1) {
            game->gameState++;
        }

        currentBoard = currentBoard->next;
    }

    return;
}

void boardStatus(Board board) {

    Square currentRow = board->topLeft;

    //Checking horizontal 3 in a row;

    while (currentRow != NULL) {

        Square currentColumn = currentRow;

        for (int i = 0; currentColumn != NULL; ) {

            if (currentColumn->sqrStatus == 1) {
                i++;
            }

            if (i == 3) {

                board->boardState = 1;
                return;
            }

            currentColumn = currentColumn->right;
        }

        currentRow = currentRow->down;
    }

    Square currentColumn = board->topLeft;

    //Check verticle 3 in a row;

    while (currentColumn != NULL) {

        currentRow = currentColumn;

        for (int i = 0; currentRow != NULL; ) {

            if (currentRow->sqrStatus == 1) {
                i++;
            }

            if (i == 3) {

                board->boardState = 1;
                return;
            }

            currentRow = currentRow->down;
        }

        currentColumn = currentColumn->right;
    }

    //Check diagonal 3 in a row;
    
    Square currentSquare = board->topLeft;

    for (int j = 0; currentSquare != NULL; ) {

        if (currentSquare->sqrStatus == 1) {
            j++;
        }

        if (j == 3) {

            board->boardState = 1;
            return;
        }

        if (currentSquare->right != NULL) {
            currentSquare = currentSquare->down->right;
        } else {
            currentSquare = NULL;
        }
    }

    int j = 0;

    currentSquare = board->topLeft;

    if (currentSquare->right->right->sqrStatus == 1) {
        j++;
    }
    if (currentSquare->right->down->sqrStatus == 1) {
        j++;
    }
    if (currentSquare->down->down->sqrStatus == 1) {
        j++;
    }

    if (j == 3) {
        board->boardState = 1;
        return;
    }

    return;
}


void drawBoard(Game game) {

    printf("\n");

    for (int i = 0; i < 35; i++) {
        printf("=");
    }
    printf("\n\n");

    printf("   Board 1    Board 2    Board 3   \n");
    printf("   |1|2|3     |1|2|3     |1|2|3    \n");
    printf("  -+-+-+-    -+-+-+-    -+-+-+-    \n");
    
    Board currentBoard = game->head;
    char row = 'A';

    for (int i = 0; i < 9; i++) {

        Square currentSquare = currentBoard->topLeft;

        if (i >= 6) {

            currentSquare = currentSquare->down->down;
        } else if (i >= 3) {

            currentSquare = currentSquare->down;
        }
        
        printRow(currentSquare, row);
        currentBoard = currentBoard->next;

        if (currentBoard == NULL) {

            row += 1;
            currentBoard = game->head;
            printf("\n");
            printf("  -+-+-+-    -+-+-+-    -+-+-+-    \n");
        }

    }

    printf("\n");
    currentBoard = game->head;

    while (currentBoard != NULL) {

        if (currentBoard->boardState == 0) {
            printf("  PLAYABLE ");
        } else if (currentBoard->boardState == 1) {
            printf("   DEAD    ");
        }

        currentBoard = currentBoard->next;
    }

    printf("\n\n");

    for (int i = 0; i < 35; i++) {
        printf("=");
    }
    printf("\n\n");

    return;
}

void printRow(Square firstSquare, char row)  {

    printf("  ");
    printf("%c", row);

    while (firstSquare != NULL) {

        printSquare(firstSquare);
        firstSquare = firstSquare->right;
    }

    printf("  ");

    return;
}

void printSquare(Square square) {
    if (square->sqrStatus == 0) {

        printf("| ");
    } else if (square->sqrStatus == 1) {

        printf("|X");
    }
    
    return;
}

Game createGame(void) {

    Game newGame = malloc(sizeof(struct game));

    newGame->head = createBoard();
    Board current = newGame->head;

    for (int i = 0; i < 2; i++) {

        current->next = createBoard();
        current = current->next;

    }

    current->next = NULL;
    newGame->nBoards = 3;
    newGame->playerTurn = 0;

    return newGame;
}

Board createBoard(void) {

    Board newBoard = malloc(sizeof(struct board));

    newBoard->next = NULL;

    Square topLeft = createSquare();
    
    Square current = topLeft;
    Square previous = current;

    for (int i = 0; i < 3; i++) {

        current->down = createSquare();
        current->down->down = createSquare();
        current->right = createSquare();

        previous->down->right = current->down;
        previous->down->down->right = current->down->down;
        previous->down->down->down = NULL;

        previous = current;
        current = current->right;

    }
    
    free(current);
    current = NULL;

    previous->right = NULL;
    previous->down->right = NULL;
    previous->down->down->right = NULL;
    previous->down->down->down = NULL;

    newBoard->topLeft = topLeft;
    newBoard->boardState = 0;

    return newBoard;
}

Square createSquare(void) {

    Square newSquare = malloc(sizeof(struct square));

    newSquare->down = NULL;
    newSquare->right = NULL;

    newSquare->sqrStatus = 0;

    return newSquare;
}

void destroyGame(Game game) {
    
    Board current = game->head;

    while (current != NULL) {

        game->head = current;
        current = current->next;
        destroyBoard(game->head);
    }

    free(game);

    return;
}

void destroyBoard(Board board) {

    Square row = board->topLeft;

    while (row != NULL) {

        Square column = row;
        row = row->down;

        while (column != NULL) {

            Square prevColumn = column;
            column = column->right;
            free(prevColumn);

        }
    }

    free(board);

    return;
}

//Takes input from stdin and returns first integer in string
//Return -1 if no integer is found
int numberString(char * input) {

    //Assuming there will always be a '\n' terminating the string
    //Max length for input will be 32
    for (int i = 0; i < 32 && input[i] != '\n'; i++) {

        if ('1' <= input[i] && input[i] <= '3') {

            int number = input[i] - '0';
            return number;
        }
        
    }
    return -1;
}

//Takes input from stdin and returns first a/b/c as 1/2/3 respectfully in string
//Return -1 otherwise.
int abcString(char * input) {
    //Assuming there will always be a '\n' terminating the string
    //Max length for input will be 32
    for (int i = 0; i < 32 && input[i] != '\n'; i++) {

        if ('a' <= input[i] && input[i] <= 'c') {

            int abc = input[i] - ('a' - 1);
            return abc;
        } else if ('A' <= input[i] && input[i] <= 'C') {

            int abc = input[i] - ('A' - 1);
            return abc;
        }
    }
    return -1;
}
