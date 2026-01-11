#include <Windows.h>

#include "blackfade.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, INT nCmdShow) {
  BlackFadeOptions options = {0};

  if (lpCmdLine && strstr(lpCmdLine, "--keep-awake") != NULL) {
    options.keepAwake = 1;
  }

  RunBlackFade(hInstance, &options);
  return 0;
}
