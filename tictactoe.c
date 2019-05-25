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

Game createGame(void);
void destroyGame(Game game);
void drawBoard(Game game);

Square createSquare(void);
Board createBoard(void);
void destroyBoard(Board board);

int main(void) {

    Game game = createGame();

    printf("Hello World!");

    destroyGame(game);

    return 0;
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
}

void destroyGame(Game game) {
    
    Board current = game->head;

    while(current != NULL) {

        game->head = current;
        current = current->next;
        destroyBoard(game->head);
    }

    free(game);

    return;
}

Square createSquare(void) {

    Square newSquare = malloc(sizeof(struct square));

    newSquare->down = NULL;
    newSquare->right = NULL;

    newSquare->sqrStatus = 0;

    return newSquare;
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
        current->down->down->down = NULL;

        previous = current;
        current = current->right;

    }
    
    free(current);

    previous->right = NULL;
    previous->down->right = NULL;
    previous->down->down->right = NULL;
    current->down->down->down = NULL;

    newBoard->topLeft = topLeft;
    newBoard->topRight = topLeft->right->right;
    newBoard->bottomLeft = topLeft->down->down;

    newBoard->boardState = 0;

    return newBoard;
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
