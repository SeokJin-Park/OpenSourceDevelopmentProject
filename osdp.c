#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define FULL_TIME 120

typedef struct {
    char type;
    int x, y;
} Dalgona;

void PrintBoard(Dalgona board[BOARD_SIZE][BOARD_SIZE]);
void ChooseDalgona(int *currentX, int *currentY, char keyPressed);
void MoveDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE], int currentX, int currentY, char keyPressed);
int ScoreDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE]);
void FillDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE]);
void FillDalgona2(Dalgona board[BOARD_SIZE][BOARD_SIZE]);
void TimeOver();

int main() {
    Dalgona board[BOARD_SIZE][BOARD_SIZE];
    int currentX = 0, currentY = 0;
    int timeRemaining = FULL_TIME;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].type = 'A' + rand() % 8;
            board[i][j].x = i;
            board[i][j].y = j;
        }
    }
    do {
        PrintBoard(board);
        char key;
        printf("방향키를 사용하여 달고나를 선택하세요.\n");
        scanf("%c", &key);

        ChooseDalgona(&currentX, &currentY, key);
        MoveDalgona(board, currentX, currentY, key);

        int score = ScoreDalgona(board);
        if (score > 0) {
            printf("획득한 점수: %d\n", score);
            FillDalgona(board);
        }

        FillDalgona2(board);

        timeRemaining--;
        
        system("clear");
    } while (timeRemaining > 0);

    TimeOver();
    return 0;
}

void PrintBoard(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("%c\t", board[i][j].type);
        }
        printf("\n");
    }
    printf("\n");
}

void ChooseDalgona(int *currentX, int *currentY, char keyPressed) {
    switch (keyPressed) {
        case '↑':
            (*currentX)--;
            break;
        case '↓':
            (*currentX)++;
            break;
        case '←':
            (*currentY)--;
            break;
        case '→':
            (*currentY)++;
            break;
    }

    if (*currentX < 0) {
        *currentX = BOARD_SIZE - 1;
    } 
    else if (*currentX >= BOARD_SIZE) {
        *currentX = 0;
    }

    if (*currentY < 0) {
        *currentY = BOARD_SIZE - 1;
    } 
    else if (*currentY >= BOARD_SIZE) {
        *currentY = 0;
    }
}

void MoveDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE], int currentX, int currentY, char keyPressed) {
    switch (keyPressed) {
        case '↑':
            break;
        case '↓':
            break;
        case '←':
            break;
        case '→':
            break;
    }
}

int ScoreDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE - 2; ++j) {
            if (board[i][j].type == board[i][j + 1].type &&
                board[i][j].type == board[i][j + 2].type) {
                score += 10;

                board[i][j].type = ' ';
                board[i][j + 1].type = ' ';
                board[i][j + 2].type = ' ';
            }
        }
    }
    for (int j = 0; j < BOARD_SIZE; ++j) {
        for (int i = 0; i < BOARD_SIZE - 2; ++i) {
            if (board[i][j].type == board[i + 1][j].type &&
                board[i][j].type == board[i + 2][j].type) {
                score += 10;

                board[i][j].type = ' ';
                board[i + 1][j].type = ' ';
                board[i + 2][j].type = ' ';
            }
        }
    }
    return score;
}

void FillDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    for (int j = BOARD_SIZE - 1; j > 0; j--) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j].type == ' ' && board[i][j-1].type != ' ') {
                board[i][j].type = board[i][j-1].type;
                board[i][j-1].type = ' ';
            }
        }
    }
}

void FillDalgona2(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == ' '){
                 board[i][j].type = 'A' + rand() % 8;
            }
        }
    }
}

void TimeOver() {
    printf("종료\n");
}