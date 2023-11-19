#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define GAME_OVER 120

typedef struct {
    char type;  // 동그라미(Circle), 세모(Triangle), 별(Star), 우산(Umbrella)
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
    srand((unsigned int)time(NULL));

    Dalgona board[BOARD_SIZE][BOARD_SIZE];
    int currentX = 0, currentY = 0;
    int timeRemaining = GAME_OVER;

    // 초기 보드 생성
    // (이 부분은 실제 게임 초기화 로직으로 대체되어야 합니다)
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].type = 'A' + rand() % 4;  // 랜덤 알파벳
            board[i][j].x = j;
            board[i][j].y = i;
        }
    }

    do {
        // 게임 상태 출력
        PrintBoard(board);

        // 사용자 입력 받기
        char key;
        printf("Enter a direction key (↑/↓/←/→) to move, 'Q' to quit: ");
        scanf(" %c", &key);

        // 입력에 따라 달고나 선택 및 이동
        ChooseDalgona(&currentX, &currentY, key);
        MoveDalgona(board, currentX, currentY, key);

        // 3개 이상의 달고나가 연속적으로 이어져 있을 경우 점수 획득 및 처리
        int score = ScoreDalgona(board);
        if (score > 0) {
            printf("Scored %d points!\n", score);
            FillDalgona(board);
        }

        // 터진 달고나의 공백을 채우기
        FillDalgona2(board);

        // 시간 감소
        timeRemaining--;

        // 화면을 지우는 코드 (실제로는 OS 및 컴파일러에 따라 다르게 구현되어야 함)
        system("clear");
    } while (timeRemaining > 0);

    // 제한 시간이 종료되면 게임 종료
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
        case'↑':
            (*currentX)--;
            break;
        case'↓':
            (*currentX)++;
            break;
        case'←':
            (*currentY)--;
            break;
        case'→':
            (*currentY)++;
            break;
    }

    // 좌표를 보드 내에 유지
    if (*currentX < 0) {
        *currentX = BOARD_SIZE - 1;
    } else if (*currentX >= BOARD_SIZE) {
        *currentX = 0;
    }

    if (*currentY < 0) {
        *currentY = BOARD_SIZE - 1;
    } else if (*currentY >= BOARD_SIZE) {
        *currentY = 0;
    }
}

void MoveDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE], int currentX, int currentY, char keyPressed) {
    // 선택된 달고나의 이동 방향을 결정
    switch (keyPressed) {
        case '↑':
            // 위쪽 방향키에 대한 이동 로직
            break;
        case '↓':
            // 아래쪽 방향키에 대한 이동 로직
            break;
        case '←':
            // 왼쪽 방향키에 대한 이동 로직
            break;
        case '→':
            // 오른쪽 방향키에 대한 이동 로직
            break;
    }
}

int ScoreDalgona(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;

    // 가로 방향으로 3개 이상 연속된 달고나를 찾아서 점수 획득 및 삭제
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE - 2; ++j) {
            if (board[i][j].type == board[i][j + 1].type &&
                board[i][j].type == board[i][j + 2].type) {
                // 3개 이상 연속된 달고나를 찾았을 경우
                score += 10;  // 간단한 예시로 10점씩 점수 획득
                // 찾은 달고나를 사라지게 처리 (빈 공간으로 표시)
                board[i][j].type = ' ';
                board[i][j + 1].type = ' ';
                board[i][j + 2].type = ' ';
            }
        }
    }

    // 세로 방향으로 3개 이상 연속된 달고나를 찾아서 점수 획득 및 삭제
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
    // 터진 달고나의 공백을 기존의 달고나가 내려와 채움
    // (단순히 빈 공간을 아래로 내리는 로직으로 대체될 수 있음)
    for (int j = 0; j < BOARD_SIZE; ++j) {
        for (int i = BOARD_SIZE - 1; i > 0; --i) {
            if (board[i][j].type == ' ' && board[i - 1][j].type != ' ') {
                // 빈 공간 아래에 달고나가 있는 경우
                board[i][j].type = board[i - 1][j].type;
                board[i - 1][j].type = ' ';
            }
        }
    }
}

void FillDalgona2(Dalgona board[BOARD_SIZE][BOARD_SIZE]) {
    // 달고나가 내려와 생성된 공백을 랜덤한 달고나로 채움
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[0][j].type == ' ') {
            // 맨 위에 빈 공간이 있는 경우
            // 랜덤한 달고나로 채움
            board[0][j].type = 'A' + rand() % 4;  // 랜덤 알파벳
        }
    }
}

void TimeOver() {
    printf("Game Over\n");
}