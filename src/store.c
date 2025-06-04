#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "state.h"

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

// v2: 상점 메뉴 (CP로 아이템 구매, 중복구매 방지, 놀이기구 배치)
void openStoreV2(GameState *state) {
  int choice;
  printf("\n==================== 상점 ====================\n");
  printf("현재 CP: %d\n", state->cp);
  printf("1. 장난감 쥐: 1 CP %s\n", state->hasMouseToy ? "(품절)" : "");
  printf("2. 레이저 포인터: 2 CP %s\n", state->hasLaser ? "(품절)" : "");
  printf("3. 스크래처: 4 CP %s\n", state->hasScratcher ? "(품절)" : "");
  printf("4. 캣타워: 6 CP %s\n", state->hasTower ? "(품절)" : "");
  printf("5. 나가기\n");
  printf("=============================================\n");
  printf("구매할 항목을 선택하세요: ");
  char input[10];
  fgets(input, sizeof(input), stdin);
  choice = atoi(input);
  if (choice == 1 && !state->hasMouseToy) {
    if (state->cp >= 1) {
      state->cp -= 1;
      state->hasMouseToy = 1;
      printf("장난감 쥐를 구매했습니다!\n");
    } else
      printf("CP가 부족합니다!\n");
  } else if (choice == 2 && !state->hasLaser) {
    if (state->cp >= 2) {
      state->cp -= 2;
      state->hasLaser = 1;
      printf("레이저 포인터를 구매했습니다!\n");
    } else
      printf("CP가 부족합니다!\n");
  } else if (choice == 3 && !state->hasScratcher) {
    if (state->cp >= 4) {
      state->cp -= 4;
      state->hasScratcher = 1;
      printf("스크래처를 구매했습니다!\n");
    } else
      printf("CP가 부족합니다!\n");
  } else if (choice == 4 && !state->hasTower) {
    if (state->cp >= 6) {
      state->cp -= 6;
      state->hasTower = 1;
      printf("캣타워를 구매했습니다!\n");
    } else
      printf("CP가 부족합니다!\n");
  } else if (choice == 5) {
    printf("상점을 나갑니다.\n");
    return;
  } else {
    printf("잘못된 입력이거나 이미 구매한 상품입니다.\n");
  }
  sleep(1);
}
