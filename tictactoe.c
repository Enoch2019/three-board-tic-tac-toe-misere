//Written by Enoch K (enoch7225@gmail.com)
//Project started: 2019-05-25
//Project finished:
//Three board Tic Tac Toe Misere

#include <stdio.h>
#include <stdlib.h>

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

    //0 for ' ' 1 for X
    int sqrStatus;

} * Square;

Square createSquare(void);
Board createBoard(void);

int main(int argc, char * argv[]) {

    printf("Hello World!");
    return 0;
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

        previous = current;
        current = current->right;

    }
    
    free(current);

    previous->right = NULL;
    previous->down->right = NULL;
    previous->down->down->right = NULL;

    newBoard->topLeft = topLeft;
    newBoard->topRight = topLeft->right->right;
    newBoard->bottomLeft = topLeft->down->down;

    newBoard->boardState = 0;

    return newBoard;
}