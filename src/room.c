#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "state.h"

// v2: 방 그리기(놀이기구 포함)
void renderRoomV2(const GameState *state, const char *catName) {
  (void)catName;
  printf("\n");
  for (int i = 0; i < ROOM_WIDTH + 2; i++) printf("#");
  printf("\n# H");
  for (int i = 2; i < ROOM_WIDTH - 2; i++) {
    if (state->hasScratcher && state->scratcherPos == i)
      printf("S");
    else if (state->hasTower && state->towerPos == i)
      printf("T");
    else
      printf(" ");
  }
  printf("B #\n");
  printf("#");
  for (int i = 0; i < ROOM_WIDTH; i++) {
    if (i == state->catPosition)
      printf("C");
    else
      printf(" ");
  }
  printf("#\n");
  for (int i = 0; i < ROOM_WIDTH + 2; i++) printf("#");
  printf("\n");
}