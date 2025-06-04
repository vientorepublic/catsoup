#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "state.h"
#include "utility.h"

void handleInteraction(int *choice, int *intimacy, char *catName) {
  if (*choice == 1) {
    printf("아무것도 하지 않습니다.\n");
    printf("4/6의 확률로 친밀도가 떨어집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    int dice = rollDice();
    sleep(1);
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice <= 4) {
      *intimacy = (*intimacy > 0) ? *intimacy - 1 : 0;
      printf("친밀도가 떨어졌습니다.\n");
    } else {
      printf("다행히 친밀도가 떨어지지 않았습니다.\n");
    }
  } else if (*choice == 2) {
    printf("%s의 턱을 긁어주었습니다.\n", catName);
    printf("2/6의 확률로 친밀도가 높아집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    int dice = rollDice();
    sleep(1);
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice >= 5) {
      *intimacy = (*intimacy < 4) ? *intimacy + 1 : 4;
      printf("친밀도가 높아졌습니다.\n");
    } else {
      printf("친밀도는 그대로입니다.\n");
    }
  } else if (*choice == 3) {
    printf("%s에게 간식을 주었습니다.\n", catName);
    printf("3/6의 확률로 친밀도가 높아집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    int dice = rollDice();
    sleep(1);
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice >= 4) {
      *intimacy = (*intimacy < 4) ? *intimacy + 1 : 4;
      printf("친밀도가 높아졌습니다.\n");
    } else {
      printf("친밀도는 그대로입니다.\n");
    }
  } else if (*choice == 4) {
    printf("%s에게 장난감을 던졌습니다.\n", catName);
    printf(
        "2/6의 확률로 친밀도가 높아지고, 1/6의 확률로 친밀도가 떨어집니다.\n");
    printf("주사위를 굴립니다. 또르륵...\n");
    int dice = rollDice();
    sleep(1);
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice >= 5) {
      *intimacy = (*intimacy < 4) ? *intimacy + 1 : 4;
      printf("친밀도가 높아졌습니다.\n");
    } else if (dice == 1) {
      *intimacy = (*intimacy > 0) ? *intimacy - 1 : 0;
      printf("친밀도가 떨어졌습니다.\n");
    } else {
      printf("친밀도는 그대로입니다.\n");
    }
  } else {
    printf("잘못된 입력입니다. 다시 시도하세요.\n");
  }
}

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

void openInteractionMenu(int *intimacy, char *catName) {
  int choice;
  char input[10];

  printf("\n========== 상호작용 메뉴 ==========\n");
  printf("1. 아무것도 하지 않음\n");
  printf("2. 긁어 주기\n");
  printf("3. 간식 주기\n");
  printf("4. 장난감 던지기\n");
  printf("===================================\n");
  printf(">> ");

  fgets(input, sizeof(input), stdin);
  choice = atoi(input);
  handleInteraction(&choice, intimacy, catName);
}
