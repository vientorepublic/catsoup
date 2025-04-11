#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "platform.h"
#include "utility.h"
#include "constants.h"
#include "room.h"
#include "state.h"
#include "interaction.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(NULL));
    char catName[20]; // 고양이 이름
    int soupCount = 0; // 수프 개수
    int intimacy = 2; // 친밀도
    int choice; // 상호작용 선택
    int catPosition = 0; // 고양이 위치

    printMainScreen();
    getCatName(catName);
    sleep(1);

    while (1) {
        system(CLEAR_CONSOLE);
        printState(soupCount, intimacy);
        moveCat(&catPosition, intimacy, catName);
        renderRoom(catPosition, &soupCount, catName);

        printf("\n어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음 1. 긁어 주기 2. 게임 종료\n>> ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        handleInteraction(&choice, &intimacy, catName);

        if (choice == 2) break;

        printf("현재 친밀도 : %d\n", intimacy);
        sleep(2);
    }

    return 0;
}
