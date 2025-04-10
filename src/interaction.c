#include <stdio.h>
#include "platform.h"
#include "utility.h"

void handleInteraction(int *choice, int *intimacy, char *catName) {
  if (*choice == 0) {
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
  } else if (*choice == 1) {
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
  } else if (*choice == 2) {
      printf("게임을 종료합니다.\n");
  } else {
      printf("잘못된 입력입니다. 다시 시도하세요.\n");
  }
}
