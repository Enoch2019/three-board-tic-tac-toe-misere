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
    // 0 is human player, 1 is computer
    int playerTurn;

} * Game;

typedef struct board {

    struct board * next;
    
    struct square * topLeft;
    struct square * topRight;
    struct square * bottomLeft;

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

void drawBoard(Game game);

Game createGame(void);
Board createBoard(void);
Square createSquare(void);

void destroyGame(Game game);
void destroyBoard(Board board);

int main(void) {

    Game game = createGame();
    intialiseGame(game);
    runGame(game);
    endGame(game);
    printf("Hello World!\n");

    destroyGame(game);

    while(1) {
        
    }
    return 0;
}

void intialiseGame(Game game) {

    int tries = 0;
    
    while (tries < 3) {

        printf("Do you want to move first? (Y/N)\n");
        char yesNo = getchar();

        switch (yesNo) {
            case 'y':

                game->playerTurn = 0;
                printf("You are starting\n");
                return;
            case 'Y':

                game->playerTurn = 0;
                printf("You are starting\n");
                return;
            case 'n':
            
                game->playerTurn = 1;   
                printf("You are not starting\n");
                return;

            case 'N':

                game->playerTurn = 1;
                printf("You are not starting\n");
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
        game->gameState  = 3;
    }

}

void endGame(Game game) {

    if (game->playerTurn == 0) {

        printf("Sorry. You lose.\n");
    } else if (game->playerTurn == 1) {

        printf("Congratulations. You Win.\n");
    }
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
    newBoard->topRight = topLeft->right->right;
    newBoard->bottomLeft = topLeft->down->down;

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
