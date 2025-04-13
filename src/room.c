#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void renderRoom(int catPosition, int *soupCount, char *catName) {
  printf("\n");
  for (int i = 0; i < ROOM_WIDTH + 2; i++) {
    printf("#");
  }
  printf("\n# H");
  for (int i = 0; i < ROOM_WIDTH - 4; i++) {
    printf(" ");
  }
  printf("B #\n");

  printf("#");
  for (int i = 0; i < ROOM_WIDTH; i++) {
    if (i == catPosition) {
      printf("C");
    } else if (i < catPosition) {
      printf(".");
    } else {
      printf(" ");
    }
  }
  printf("#\n");

  for (int i = 0; i < ROOM_WIDTH + 2; i++) {
    printf("#");
  }
  printf("\n");

  if (catPosition == HOME_POS) {
    printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n", catName);
  }

  if (catPosition == BOWL_POS) {
    const char *soups[] = {"감자 수프", "양송이 수프", "브로콜리 수프"};
    const char *selectedSoup = soups[rand() % 3];
    printf("야옹이가 %s를 만들었습니다!\n", selectedSoup);
    (*soupCount)++;
    printf("현재까지 만든 수프: %d개\n", *soupCount);
  }
}