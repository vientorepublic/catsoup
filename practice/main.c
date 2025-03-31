#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <windows.h>
  #define sleep(seconds) Sleep((seconds) * 1000)
#elif defined(__linux__) || defined(__APPLE__)
  #include <unistd.h>
#else
  #error "Unsupported OS"
#endif

#ifdef _WIN32
  #define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__APPLE__)
  #define CLEAR_CONSOLE "clear"
#else
  #define CLEAR_CONSOLE ""
#endif

int main() {
  char catName[20];

  // Print the title
  printf("** 야옹이와 수프 **\n\n");
  // Cat ASCII art
  printf(" /\\_/\\\n");
  printf("( o.o )\n");
  printf(" > ^ <\n\n");
  // Prompt the user for input
  printf("야옹이의 이름을 지어주세요 >> ");
  scanf("%s", catName);
  // Print the cat's name
  printf("야옹이의 이름은 %s 입니다.\n", catName);
  sleep(1);
  // Clear the console
  system(CLEAR_CONSOLE);
  // Start the game
  while(1) {
    static int hunger = 5; // Hunger level (0-10, where 10 is full)
    static int happiness = 5; // Happiness level (0-10, where 10 is very happy)
    int choice;

    // Display the cat's status
    printf("\n%s의 상태:\n", catName);
    printf("배고픔: %d/10\n", hunger);
    printf("행복: %d/10\n", happiness);

    // Display interaction menu
    printf("\n무엇을 하시겠습니까?\n");
    printf("1. 밥 주기\n");
    printf("2. 놀아주기\n");
    printf("3. 아무것도 안 하기\n");
    printf("선택 >> ");
    scanf("%d", &choice);

    // Handle user choice
    switch (choice) {
      case 1:
      if (hunger < 10) {
        hunger += 2;
        if (hunger > 10) hunger = 10;
        printf("\n%s에게 밥을 줬습니다. 배고픔이 줄어들었습니다!\n", catName);
      } else {
        printf("\n%s는 이미 배가 부릅니다!\n", catName);
      }
      break;
      case 2:
      if (happiness < 10) {
        happiness += 2;
        if (happiness > 10) happiness = 10;
        printf("\n%s와 놀아줬습니다. 행복도가 올라갔습니다!\n", catName);
      } else {
        printf("\n%s는 이미 매우 행복합니다!\n", catName);
      }
      break;
      case 3:
      printf("\n%s를 가만히 두었습니다.\n", catName);
      break;
      default:
      printf("\n잘못된 선택입니다. 다시 시도해주세요.\n");
      continue;
    }

    // Update the cat's status over time
    hunger -= 1;
    happiness -= 1;
    if (hunger < 0) hunger = 0;
    if (happiness < 0) happiness = 0;

    // Check if the cat is in a critical state
    if (hunger == 0) {
      printf("\n%s가 너무 배고파요! 게임 오버!\n", catName);
      break;
    }
    if (happiness == 0) {
      printf("\n%s가 너무 슬퍼요! 게임 오버!\n", catName);
      break;
    }

    // Wait for 2 seconds before the next update
    sleep(2);
    system(CLEAR_CONSOLE);
  }
  return 0;
}