#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>

#include "state.h"

// 상호작용 핸들링 함수
void handleInteraction(int *choice, int *intimacy, char *catName);

// 상호작용 메뉴 여는 함수
void openInteractionMenu(int *intimacy, char *catName);

// v2 상호작용 메뉴 함수 선언
void openInteractionMenuV2(GameState *state, char *catName);

#endif