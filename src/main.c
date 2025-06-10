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
  return 0;
}
