#include <stdio.h>
#include <string.h>
#include <time.h>
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

int rollDice();

// 방 출력 관련 상수
#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

// 디버그 모드 설정
int DEBUG_MODE = 0;

// 게임 상태 출력
void printState(int soupCount, int intimacy, int catPosition) {
    if (DEBUG_MODE == 1) {
      printf("======================== DEBUG MODE ====================\n");
      printf("homePosition = %d\n", HOME_POS);
      printf("bowlPosition = %d\n", BOWL_POS);
      printf("roomWidth = %d\n", ROOM_WIDTH);
      printf("catPosition = %d\n", catPosition);
      printf("soupCount = %d, intimacy = %d\n", soupCount, intimacy);
      printf("========================================================\n");
    }
    printf("==================== 현재 상태 ====================\n");
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

// 방을 그리는 함수
void renderRoom(int catPosition, int *soupCount, char *catName) {
  if (DEBUG_MODE == 1) {
    printf("[DEBUG] Rendering room with catPosition=%d, soupCount=%d\n", catPosition, *soupCount);
  }
  printf("\n");
  for (int i = 0; i < ROOM_WIDTH + 2; i++) {
    printf("#");
  }
  printf("\n# H");
  for (int i = 0; i < ROOM_WIDTH - 4; i++) {
    printf(" ");
  }
  printf("B #\n");

  for (int i = 0; i < 2; i++) {
    printf("#");
    for (int j = 0; j < ROOM_WIDTH; j++) {
      printf(" ");
    }
    printf("#\n");
  }

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
    const char *selectedSoup = soups[rand() % 3]; // 수프 랜덤 선택
    printf("야옹이가 %s를 만들었습니다!\n", selectedSoup);
    (*soupCount)++;
  }
}

// 고양이 이동 함수
void moveCat(int *catPosition, int intimacy, char *catName) {
  if (DEBUG_MODE == 1) {
    printf("[DEBUG] moveCat called with catPosition=%d, intimacy=%d\n", *catPosition, intimacy);
  }
  printf("\n%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", catName);
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
  if (DEBUG_MODE == 1) {
    printf("[DEBUG] Updated catPosition=%d\n", *catPosition);
  }
}

// 메인 화면 출력 함수
void printMainScreen() {
  if (DEBUG_MODE == 1) {
    printf("[DEBUG] printMainScreen called\n");
  }
  printf("**** 야옹이와 수프 ****\n\n");
  printf(" /\\_/\\\n");
  printf("( o.o )\n");
  printf(" > ^ <\n\n");
}

// 주사위를 굴리는 함수
int rollDice() {
    int result = rand() % 6 + 1;
    if (DEBUG_MODE == 1) {
        printf("[DEBUG] rollDice result=%d\n", result);
    }
    return result;
}

int main() {
  srand(time(NULL));
  char catName[20];
  int soupCount = 0;
  int intimacy = 2;
  int choice;
  int catPosition = 0; // 0: 집, 1: 중간, 2: 냄비

  printMainScreen();
  printf("야옹이의 이름을 지어주세요 >> ");
  while (1) {
      fgets(catName, sizeof(catName), stdin);
      catName[strcspn(catName, "\n")] = '\0'; // 개행 문자 제거

      if (strlen(catName) == 0) {
          printf("이름은 비어 있을 수 없습니다. 다시 입력해주세요 >> ");
      } else if (strlen(catName) > 19) {
          printf("이름은 19자 이하여야 합니다. 다시 입력해주세요 >> ");
      } else if (strcmp(catName, "DEBUG") == 0) {
          printf("DEBUG 모드로 실행합니다.\n");
          DEBUG_MODE = 1;
          break;
      } else {
          break;
      }
  }
  printf("야옹이의 이름은 %s 입니다.\n", catName);

  sleep(1);
  system(CLEAR_CONSOLE);

  if (DEBUG_MODE == 1) {
    printf("[DEBUG] Starting main loop with initial values: soupCount=%d, intimacy=%d, catPosition=%d\n", soupCount, intimacy, catPosition);
  }

  while (1) {
      system(CLEAR_CONSOLE);
      printState(soupCount, intimacy, catPosition);
      renderRoom(catPosition, &soupCount, catName);

      moveCat(&catPosition, intimacy, catName);

      printf("\n어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음 1. 긁어 주기 2. 게임 종료\n>> ");
      char input[10];
      fgets(input, sizeof(input), stdin);
      choice = atoi(input);

      if (DEBUG_MODE == 1) {
          printf("[DEBUG] Loop iteration: choice=%d, soupCount=%d, intimacy=%d, catPosition=%d\n", choice, soupCount, intimacy, catPosition);
      }

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
      } else if (choice == 2) {
          printf("게임을 종료합니다.\n");
          break;
      } else {
          printf("잘못된 입력입니다. 다시 시도하세요.\n");
          continue;
      }

      printf("현재 친밀도 : %d\n", intimacy);
      sleep(2);

      system(CLEAR_CONSOLE);
      printState(soupCount, intimacy, catPosition);
      renderRoom(catPosition, &soupCount, catName);
  }

  return 0;
}