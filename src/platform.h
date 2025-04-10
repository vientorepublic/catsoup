#ifndef PLATFORM_H
#define PLATFORM_H

// 크로스 플랫폼 컴파일을 위한 헤더 파일
// Windows와 Linux/macOS에서 sleep과 clear 명령어를 정의합니다.
// Windows에서는 Sleep() 함수를 사용하고, Linux/macOS에서는 usleep() 함수를 사용합니다.
// 콘솔 화면을 지우기 위한 명령어를 정의합니다.
// Windows에서는 cls 명령어를 사용하고, Linux/macOS에서는 clear 명령어를 사용합니다.

#ifdef _WIN32
  #include <windows.h>
  #define sleep(seconds) Sleep((seconds) * 1000)
  #define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__APPLE__)
  #include <unistd.h>
  #define CLEAR_CONSOLE "clear"
#else
  #error "Unsupported OS"
#endif

#endif