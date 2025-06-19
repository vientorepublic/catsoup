#include "state.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "platform.h"
#include "utility.h"

// v2: 기분 상태 문자열
static const char *moodDesc[] = {"매우 나쁨", "심심함", "식빵 굽기",
                                 "골골송 부르기"};

void initGameState(GameState *state) {
  memset(state, 0, sizeof(GameState));
  state->intimacy = 2;
  state->mood = 3;
  state->cp = 0;
  state->catPosition = HOME_POS;
  state->scratcherPos = -1;
  state->towerPos = -1;
  state->turn = 1;
  state->questDone = 0;
}

void printStateV2(const GameState *state, const char *catName) {
  (void)catName;
  printf("==================== 현재 상태 ====================\n");
  printf("현재까지 만든 수프: %d개\n", state->soupCount);
  printf("CP: %d\n", state->cp);
  printf("집사와의 관계(0~4): %d\n", state->intimacy);
  switch (state->intimacy) {
    case 0:
      printf("곁에 오는 것조차 싫어합니다.\n");
      break;
    case 1:
      printf("간식 자판기 취급입니다.\n");
      break;
    case 2:
      printf("그럭저럭 쓸만한 집사입니다.\n");
      break;
    case 3:
      printf("훌륭한 집사로 인정 받고 있습니다.\n");
      break;
    case 4:
      printf("집사 껌딱지입니다.\n");
      break;
  }
  printf("기분(0~3): %d - %s\n", state->mood, moodDesc[state->mood]);
  printf("보유 아이템: ");
  int any = 0;
  if (state->hasMouseToy) {
    printf("장난감 쥐 ");
    any = 1;
  }
  if (state->hasLaser) {
    printf("레이저 포인터 ");
    any = 1;
  }
  if (state->hasScratcher) {
    printf("스크래처 ");
    any = 1;
  }
  if (state->hasTower) {
    printf("캣타워 ");
    any = 1;
  }
  if (!any) printf("없음");
  printf("\n");
  printf("현재 턴: %d\n", state->turn);
  printf("================================================\n");
}

// v2: 고양이 이동(기분 기반), 행동(오브젝트와 상호작용)
void moveAndAct(GameState *state, char *catName) {
  int dest = -1;
  // 목적지 결정 및 메시지 출력
  if (state->mood == 0) {
    dest = HOME_POS;
    if (state->catPosition != HOME_POS)
      printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", catName);
  } else if (state->mood == 1) {
    int hasToy = 0;
    int toyPos = -1;
    int leftDist = 999, rightDist = 999;
    if (state->hasScratcher && state->scratcherPos != -1) {
      leftDist = abs(state->catPosition - state->scratcherPos);
      hasToy = 1;
      toyPos = state->scratcherPos;
    }
    if (state->hasTower && state->towerPos != -1) {
      rightDist = abs(state->catPosition - state->towerPos);
      if (!hasToy || rightDist < leftDist) {
        hasToy = 1;
        toyPos = state->towerPos;
      }
    }
    if (!hasToy) {
      printf("놀거리가 없어서 기분이 매우 나빠집니다.\n");
      if (state->mood > 0) state->mood = 0;
      sleep(1);
      return;
    } else {
      if (toyPos == state->scratcherPos)
        printf("%s은(는) 심심해서 스크래처쪽으로 이동합니다.\n", catName);
      else
        printf("%s은(는) 심심해서 캣타워쪽으로 이동합니다.\n", catName);
      dest = toyPos;
    }
  } else if (state->mood == 2) {
    dest = state->catPosition;
    printf("%s은(는) 기분 좋게 식빵을 굽고 있습니다.\n", catName);
  } else if (state->mood == 3) {
    dest = BOWL_POS;
    if (state->catPosition != BOWL_POS)
      printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", catName);
  }

  // 한 칸씩 이동 (이미 도착 시 대기)
  if (state->catPosition != dest) {
    if (state->catPosition < dest)
      state->catPosition++;
    else if (state->catPosition > dest)
      state->catPosition--;
  }
  // 행동 (도착지에서만)
  if (state->catPosition == HOME_POS) {
    // 집 도착 시 추가 행동 없음
  } else if (state->catPosition == BOWL_POS) {
    // 냄비 도착 시 수프 만들기
    const char *soups[] = {"감자 수프", "양송이 수프", "브로콜리 수프"};
    const char *selectedSoup = soups[rand() % 3];
    printf("%s이(가) %s를 만들었습니다!\n", catName, selectedSoup);
    state->soupCount++;
    sleep(1);
  } else if (state->hasScratcher && state->catPosition == state->scratcherPos) {
    // 스크래처 도착 시 추가 행동 없음
  } else if (state->hasTower && state->catPosition == state->towerPos) {
    // 캣타워 도착 시 추가 행동 없음
  }
  sleep(1);
}

// v2: 놀이기구 랜덤 배치 함수
void placeToys(GameState *state) {
  int used[ROOM_WIDTH] = {0};
  used[HOME_POS] = 1;
  used[BOWL_POS] = 1;
  // 스크래처
  if (state->hasScratcher) {
    int pos;
    do {
      pos = rand() % (ROOM_WIDTH - 2) + 1;
    } while (used[pos]);
    state->scratcherPos = pos;
    used[pos] = 1;
  } else {
    state->scratcherPos = -1;
  }
  // 캣타워
  if (state->hasTower) {
    int pos;
    do {
      pos = rand() % (ROOM_WIDTH - 2) + 1;
    } while (used[pos]);
    state->towerPos = pos;
    used[pos] = 1;
  } else {
    state->towerPos = -1;
  }
}

// v2: 돌발 퀘스트(3턴)
void suddenQuest(GameState *state) {
  printf("\n[돌발 퀘스트] 고양이의 마음을 사로잡아라!\n");
  printf("고양이가 갑자기 방을 뛰어다닙니다.\n");
  printf("10초 안에 아무 키나 5번 입력하세요! (엔터 포함)\n");
  int count = 0;
  time_t start = time(NULL);
  char buf[32];
  fflush(stdin);  // 입력 버퍼 비우기 (일부 시스템에서 필요)
  while (count < 5 && difftime(time(NULL), start) < 10) {
    if (fgets(buf, sizeof(buf), stdin) != NULL && buf[0] != '\0' &&
        buf[0] != '\n') {
      count++;
    } else if (buf[0] == '\n') {
      count++;
    }
  }
  if (count >= 5) {
    printf("성공! 고양이의 기분이 좋아집니다! (기분 +2)\n");
    state->mood += 2;
    if (state->mood > 3) state->mood = 3;
  } else {
    printf("실패! 고양이가 시무룩해집니다... (기분 -1)\n");
    if (state->mood > 0) state->mood--;
  }
  sleep(2);
}
