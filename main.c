#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Add the function prototype for rollDice
int rollDice();

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

void printState(int soupCount, int intimacy) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("집사와의 관계(0~4): %d\n", intimacy);
    switch (intimacy) {
        case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
        case 1: printf("간식 자판기 취급입니다.\n"); break;
        case 2: printf("그럭저럭 쓸만한 집사입니다.\n"); break;
        case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
        case 4: printf("집사 껌딱지입니다.\n"); break;
    }
    printf("================================================\n");
}

void renderRoom(int catPosition, int soupCount) {
    printf("\n##########\n");
    printf("#H B     #\n");
    for (int i = 0; i < 10; i++) {
        if (i == catPosition) {
            printf("C");
        } else {
            printf(" ");
        }
    }
    printf("#\n##########\n");
    if (catPosition == 2) {
        const char *soups[] = {"감자 수프", "양송이 수프", "브로콜리 수프"};
        const char *selectedSoup = soups[rand() % 3]; // Randomly select a soup
        printf("야옹이가 %s를 만들었습니다!\n", selectedSoup);
        soupCount++;
    }
}

void moveCat(int *catPosition, int intimacy, char *catName) {
    printf("\n%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", catName);
    printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - intimacy);
    printf("주사위를 굴립니다. 또르륵...\n");
    int dice = rollDice();
    sleep(1);
    printf("%d이(가) 나왔습니다!\n", dice);
    if (dice >= 6 - intimacy && *catPosition < 2) {
        (*catPosition)++;
        printf("냄비 쪽으로 움직입니다.\n");
    } else if (*catPosition > 0) {
        (*catPosition)--;
        printf("집 쪽으로 움직입니다.\n");
    } else {
        printf("야옹이는 움직이지 않았습니다.\n");
    }
}

int rollDice() {
    return rand() % 6 + 1; // Random number between 1 and 6
}

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
  int soupCount = 0;
  int intimacy = 2;
  int choice;
  int catPosition = 0; // 0: 집, 1: 중간, 2: 냄비

  while (1) {
      system(CLEAR_CONSOLE);
      printState(soupCount, intimacy);
      renderRoom(catPosition, soupCount);

      moveCat(&catPosition, intimacy, catName);

      printf("\n어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음 1. 긁어 주기\n>> ");
      scanf("%d", &choice);

      if (choice == 0) {
          printf("아무것도 하지 않습니다.\n");
          printf("4/6의 확률로 친밀도가 떨어집니다.\n");
          printf("주사위를 굴립니다. 또르륵...\n");
          int dice = rollDice();
          sleep(1);
          printf("%d이(가) 나왔습니다!\n", dice);
          if (dice <= 4) {
              intimacy = (intimacy > 0) ? intimacy - 1 : 0;
              printf("친밀도가 떨어졌습니다.\n");
          } else {
              printf("다행히 친밀도가 떨어지지 않았습니다.\n");
          }
      } else if (choice == 1) {
          printf("%s의 턱을 긁어주었습니다.\n", catName);
          printf("2/6의 확률로 친밀도가 높아집니다.\n");
          printf("주사위를 굴립니다. 또르륵...\n");
          int dice = rollDice();
          sleep(1);
          printf("%d이(가) 나왔습니다!\n", dice);
          if (dice >= 5) {
              intimacy = (intimacy < 4) ? intimacy + 1 : 4;
              printf("친밀도가 높아졌습니다.\n");
          } else {
              printf("친밀도는 그대로입니다.\n");
          }
      } else {
          printf("잘못된 입력입니다. 다시 입력해주세요.\n");
          sleep(1);
          continue;
      }

      printf("현재 친밀도: %d\n", intimacy);
      sleep(2);
  }

  return 0;
}