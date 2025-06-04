#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>

// 방을 렌더링하는 함수
void renderRoom(int catPosition, int *soupCount, char *catName);

// v2 방 그리기 함수
void renderRoomV2(const GameState *state, const char *catName);

#endif