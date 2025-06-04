#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rollDice() { return rand() % 6 + 1; }

void printMainScreen() {
  printf("**** 야옹이와 수프 ****\n\n");
  printf("      /\\_/\\\n");
  printf(" /\\  / o o \\\n");
  printf("//\\\\ \\~(*)~/\n");
  printf("`  \\/   ^ /\n");
  printf("   | \\|| ||\n");
  printf("   \\ '|| ||\n");
  printf("    \\)()-())\n\n");
}

void getCatName(char *catName) {
  while (1) {
    printf("야옹이의 이름을 지어주세요 >> ");
    fgets(catName, 20, stdin);
    catName[strcspn(catName, "\n")] = '\0';

    if (strlen(catName) == 0) {
      printf("이름은 비어 있을 수 없습니다. 다시 입력해주세요 >> ");
    } else if (strlen(catName) > 19) {
      printf("이름은 19자 이하여야 합니다. 다시 입력해주세요 >> ");
    } else {
      break;
    }
  }
  printf("야옹이의 이름은 %s 입니다.\n", catName);
}
