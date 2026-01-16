#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char board[9];
char HUMAN, AI;
int difficulty; // 1 = Easy, 2 = Medium, 3 = Hard


/* Function Prototypes */
void initializeBoard();
void displayBoard();
int checkWinner();
int isMovesLeft();
int minimax(int depth, int isMaximizing);
int findBestMove();

/* Initialize board */
void initializeBoard() {
    for (int i = 0; i < 9; i++)
        board[i] = ' ';
}

/* Display board */
void displayBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", board[6], board[7], board[8]);
}

/* Check winner */
int checkWinner() {
    int winCombos[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        int a = winCombos[i][0];
        int b = winCombos[i][1];
        int c = winCombos[i][2];

        if (board[a] != ' ' &&
            board[a] == board[b] &&
            board[b] == board[c])
            return board[a];
    }
    return 0;
}

/* Check if moves left */
int isMovesLeft() {
    for (int i = 0; i < 9; i++)
        if (board[i] == ' ')
            return 1;
    return 0;
}

/* Minimax Algorithm */
int minimax(int depth, int isMaximizing) {
    int winner = checkWinner();

    if (winner == AI) return 10 - depth;
    if (winner == HUMAN) return depth - 10;
    if (!isMovesLeft()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = AI;
                int score = minimax(depth + 1, 0);
                board[i] = ' ';
                if (score > bestScore)
                    bestScore = score;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = HUMAN;
                int score = minimax(depth + 1, 1);
                board[i] = ' ';
                if (score < bestScore)
                    bestScore = score;
            }
        }
        return bestScore;
    }
}

/* Find best move for AI */
int findBestMove() {
    int bestScore = -1000;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = AI;
            int score = minimax(0, 0);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}
int randomMove() {
    int move;
    while (1) {
        move = rand() % 9;
        if (board[move] == ' ')
            return move;
    }
}

/* Main function */
int main() {
    int move;
    char choice;
    srand(time(NULL));
    initializeBoard();

    printf("Choose your symbol (X/O): ");
    scanf(" %c", &choice);

    if (choice == 'X' || choice == 'x') {
        HUMAN = 'X';
        AI = 'O';
    } else {
        HUMAN = 'O';
        AI = 'X';
    }
    printf("\nSelect Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter choice: ");
    scanf("%d", &difficulty);
    char currentPlayer = 'X';

    while (1) {
        displayBoard();

        if (currentPlayer == HUMAN) {
            printf("Your move (%c). Enter position (1-9): ", HUMAN);
            scanf("%d", &move);
            move--;

            if (move < 0 || move > 8 || board[move] != ' ') {
                printf("Invalid move. Try again.\n");
                continue;
            }
            board[move] = HUMAN;
        } else {
    printf("AI is making a move...\n");

    if (difficulty == 1) {
        move = randomMove();               // Easy
    }
    else if (difficulty == 2) {
        if (rand() % 2 == 0)
            move = randomMove();           // Medium (sometimes random)
        else
            move = findBestMove();
    }
    else {
        move = findBestMove();             // Hard
    }

    board[move] = AI;
}

        int winner = checkWinner();
        if (winner) {
            displayBoard();
            if (winner == HUMAN)
                printf("You win!\n");
            else
                printf("AI wins!\n");
            break;
        }

        if (!isMovesLeft()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}
