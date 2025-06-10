#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "state.h"
#include "utility.h"

// v2: 상호작용 메뉴 (장난감 보유 여부에 따라)
void openInteractionMenuV2(GameState *state, char *catName) {
  int choice = -1;
  char input[10];
  printf("\n========== 상호작용 메뉴 ==========");
  printf("\n0. 아무것도 하지 않음\n1. 긁어 주기");
  if (state->hasMouseToy) printf("\n2. 장난감 쥐로 놀아 주기");
  if (state->hasLaser) printf("\n3. 레이저 포인터로 놀아 주기");
  printf("\n===================================\n>> ");
  fgets(input, sizeof(input), stdin);
  choice = atoi(input);
  int dice = rollDice();
  if (choice == 0) {
    printf("아무것도 하지 않음. (기분 -1)\n");
    if (state->mood > 0) state->mood--;
    if (dice <= 5 && state->intimacy > 0) {
      printf("주사위 %d → 친밀도 -1!\n", dice);
      state->intimacy--;
    }
  } else if (choice == 1) {
    printf("%s의 턱을 긁어주었습니다.\n", catName);
    if (dice >= 5 && state->intimacy < 4) {
      printf("주사위 %d → 친밀도 +1!\n", dice);
      state->intimacy++;
    } else {
      printf("주사위 %d → 친밀도 변화 없음\n", dice);
    }
  } else if (choice == 2 && state->hasMouseToy) {
    printf("장난감 쥐로 놀아주기! (기분 +1)\n");
    if (state->mood < 3) state->mood++;
    if (dice >= 4 && state->intimacy < 4) {
      printf("주사위 %d → 친밀도 +1!\n", dice);
      state->intimacy++;
    }
  } else if (choice == 3 && state->hasLaser) {
    printf("레이저 포인터로 놀아주기! (기분 +2)\n");
    state->mood += 2;
    if (state->mood > 3) state->mood = 3;
    if (dice >= 2 && state->intimacy < 4) {
      printf("주사위 %d → 친밀도 +1!\n", dice);
      state->intimacy++;
    }
  } else {
    printf("잘못된 입력입니다.\n");
  }
  sleep(1);
}
