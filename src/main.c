#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "platform.h"
#include "utility.h"
#include "constants.h"
#include "room.h"
#include "state.h"
#include "interaction.h"
#include "store.h"

void openInteractionMenu(int *intimacy, char *catName) {
    int choice;
    char input[10];
    printf("\n상호작용 메뉴: 1. 아무것도 하지 않음 2. 긁어 주기 3. 간식 주기 4. 장난감 던지기\n>> ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);
    handleInteraction(&choice, intimacy, catName);
}

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

        printf("\n어떤 것을 하시겠습니까? 1. 상호작용 메뉴 열기 2. 상점 메뉴 열기 3. 게임 종료\n>> ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1) {
            openInteractionMenu(&intimacy, catName);
        } else if (choice == 2) {
            openStore(&soupCount, &intimacy);
        } else if (choice == 3) {
            break;
        } else {
            handleInteraction(&choice, &intimacy, catName);
        }

        printf("현재 친밀도 : %d\n", intimacy);
        sleep(2);
    }

    return 0;
}
