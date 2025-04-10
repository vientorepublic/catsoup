#ifndef CONSTANTS_H
#define CONSTANTS_H

// 방 크기와 위치 관련 상수
// HOME_POS와 BOWL_POS 사이에 최소한 고양이가 이동할 수 있는 공간이 필요하므로,
// 최소 ROOM_WIDTH는 4 (HOME_POS + 1칸 이동 공간 + BOWL_POS) 이상이어야 합니다.
#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

#endif