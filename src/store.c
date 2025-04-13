#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

void openStore(int *soupCount, int *intimacy) {
    int choice;
    printf("\n==================== 상점 ====================\n");
    printf("현재 수프 개수: %d개\n", *soupCount);
    printf("1. 친밀도 증가 아이템 (수프 3개) - 친밀도 +1\n");
    printf("2. 나가기\n");
    printf("=============================================\n");
    printf("구매할 항목을 선택하세요: ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    if (choice == 1) {
        if (*soupCount >= 3) {
            *soupCount -= 3;
            *intimacy = (*intimacy < 4) ? *intimacy + 1 : 4;
            printf("친밀도가 증가했습니다! 현재 친밀도: %d\n", *intimacy);
        } else {
            printf("수프가 부족합니다. 더 많은 수프를 만드세요!\n");
        }
    } else if (choice == 2) {
        printf("상점을 나갑니다.\n");
    } else {
        printf("잘못된 입력입니다. 다시 시도하세요.\n");
    }
    sleep(1);
}
