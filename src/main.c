#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "interaction.h"
#include "platform.h"
#include "room.h"
#include "state.h"
#include "store.h"
#include "utility.h"

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  srand(time(NULL));
  int gameMode = 2;  // 1: v1, 2: v2
  while (1) {
    printf(
        "\n플레이할 게임 버전을 선택하세요!\n1. 야옹이와 수프 v1\n2. 야옹이와 "
        "수프 v2\n>> ");
    char modeInput[10];
    fgets(modeInput, sizeof(modeInput), stdin);
    int parsed = atoi(modeInput);
    if (parsed == 1 || parsed == 2) {
      gameMode = parsed;
      break;
    } else {
      printf("잘못된 입력입니다. 1 또는 2를 입력하세요.\n");
    }
  }

  if (gameMode == 1) {
    // v1 루프 (기존 v1 코드)
    char catName[20];
    int soupCount = 0;
    int intimacy = 2;
    int choice;
    int catPosition = 0;
    printMainScreen();
    getCatName(catName);
    sleep(1);
    while (1) {
      system(CLEAR_CONSOLE);
      printState(soupCount, intimacy);
      moveCat(&catPosition, intimacy, catName);
      renderRoom(catPosition, &soupCount, catName);
      printf(
          "\n어떤 것을 하시겠습니까? 1. 상호작용 메뉴 열기 2. 상점 메뉴 열기 "
          "3. 게임 종료\n>> ");
      char input[10];
      fgets(input, sizeof(input), stdin);
      choice = atoi(input);
      if (choice == 1) {
        openInteractionMenu(&intimacy, catName);
      } else if (choice == 2) {
        openStore(&soupCount, &intimacy);
      } else if (choice == 3) {
        break;
      } else {
        printf("잘못된 입력입니다. 1, 2, 3 중에서 선택하세요.\n");
        sleep(1);
        continue;
      }
      printf("현재 친밀도 : %d\n", intimacy);
      sleep(2);
    }
  } else {
    // v2 루프 (기존 v2 코드)
    GameState state;
    char catName[20];
    initGameState(&state);
    printMainScreen();
    getCatName(catName);
    sleep(1);
    while (1) {
      system(CLEAR_CONSOLE);
      printStateV2(&state, catName);
      int dice = rollDice();
      if (dice <= (6 - state.intimacy) && state.mood > 0) {
        state.mood--;
        printf("아무 이유 없이 기분이 나빠집니다. 고양이니까? (기분 -1)\n");
        sleep(1);
      }
      moveAndAct(&state, catName);
      int producedCP = (state.mood > 0 ? state.mood - 1 : 0) + state.intimacy;
      state.cp += producedCP;
      printf("이번 턴에 CP %d를 획득했습니다!\n", producedCP);
      sleep(1);
      if (state.turn == 3 && !state.questDone) {
        suddenQuest(&state);
        state.questDone = 1;
        sleep(2);
      }
      placeToys(&state);
      renderRoomV2(&state, catName);
      printf("\n무엇을 하시겠습니까? 1. 상호작용 2. 상점 3. 종료\n>> ");
      char input[10];
      fgets(input, sizeof(input), stdin);
      int choice = atoi(input);
      if (choice == 1) {
        openInteractionMenuV2(&state, catName);
      } else if (choice == 2) {
        openStoreV2(&state);
      } else if (choice == 3) {
        break;
      }
      state.turn++;
    }
  }

  return 0;
}
