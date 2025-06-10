#ifndef STATE_H
#define STATE_H

#include <stdio.h>

// 게임 상태 구조체 (v2)
typedef struct {
  int soupCount;     // 수프 개수
  int intimacy;      // 친밀도 (0~4)
  int mood;          // 기분 (0~3)
  int cp;            // Cute Point
  int turn;          // 현재 턴
  int catPosition;   // 고양이 위치(열)
  int hasMouseToy;   // 장난감 쥐 보유 여부
  int hasLaser;      // 레이저 포인터 보유 여부
  int hasScratcher;  // 스크래처 보유 여부
  int hasTower;      // 캣타워 보유 여부
  int scratcherPos;  // 스크래처 위치(열, -1이면 없음)
  int towerPos;      // 캣타워 위치(열, -1이면 없음)
  int questDone;     // 돌발퀘스트 완료 여부
} GameState;

// 상태 출력 (v2)
void printStateV2(const GameState *state, const char *catName);

// 상태 초기화
void initGameState(GameState *state);

// v2 이동/행동 함수
void moveAndAct(GameState *state, char *catName);

// v2 놀이기구 랜덤 배치 함수
void placeToys(GameState *state);

// v2 돌발 퀘스트 함수
void suddenQuest(GameState *state);

#endif
