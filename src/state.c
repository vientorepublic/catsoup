#include <stdio.h>

#include "constants.h"
#include "platform.h"
#include "utility.h"

void printState(int soupCount, int intimacy) {
  printf("==================== 현재 상태 ====================\n");
  printf("현재까지 만든 수프: %d개\n", soupCount);
  printf("집사와의 관계(0~4): %d\n", intimacy);
  switch (intimacy) {
    case 0:
      printf("곁에 오는 것조차 싫어합니다.\n");
      break;
    case 1:
      printf("간식 자판기 취급입니다.\n");
      break;
    case 2:
      printf("그럭저럭 쓸만한 집사입니다.\n");
      break;
    case 3:
      printf("훌륭한 집사로 인정 받고 있습니다.\n");
      break;
    case 4:
      printf("집사 껌딱지입니다.\n");
      break;
  }
  printf("================================================\n");
}

void moveCat(int *catPosition, int intimacy, char *catName) {
  printf("\n%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n",
         catName);
  printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - intimacy);
  printf("주사위를 굴립니다. 또르륵...\n");
  int dice = rollDice();
  sleep(1);
  printf("%d이(가) 나왔습니다!\n", dice);
  if (dice >= 6 - intimacy && *catPosition < ROOM_WIDTH - 1) {
    (*catPosition)++;
    printf("냄비 쪽으로 움직입니다.\n");
  } else if (*catPosition > 0) {
    (*catPosition)--;
    printf("집 쪽으로 움직입니다.\n");
  } else {
    printf("야옹이는 움직이지 않았습니다.\n");
  }
}
