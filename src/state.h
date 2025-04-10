#ifndef STATE_H
#define STATE_H

#include <stdio.h>

// 게임 상태 출력
void printState(int soupCount, int intimacy);

// 고양이 이동 함수
void moveCat(int *catPosition, int intimacy, char *catName);

#endif
