#include "blackfade.h"

const static LPCTSTR CLASS_NAME = "BlackFadeClass";
const static LPCTSTR WINDOW_NAME = "BlackFade";
const static UINT UPDATE_INTERVAL = 10;
const static int FADE_SPEED = 5;

////////////////////////////////////////////////////////////////////////
// Window procedure
////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {

  static UINT_PTR timerId = 0;
  static int windowAlpha = 0;

  switch (uMsg) {
  case WM_CREATE:
    timerId = SetTimer(hwnd, 1, UPDATE_INTERVAL, NULL);
    return 0;
  case WM_TIMER:
    // Fade in
    windowAlpha += FADE_SPEED;
    SetLayeredWindowAttributes(hwnd, 255, windowAlpha, LWA_ALPHA);
    if (windowAlpha >= 255) {
      KillTimer(hwnd, timerId);
    }
    return 0;
  case WM_KEYDOWN:   // fall through
  case WM_MOUSEMOVE: // fall through
    // skip input events in early startup
    if (windowAlpha <= 100) {
      return 0;
    }
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}

////////////////////////////////////////////////////////////////////////
/// Initialize the window
////////////////////////////////////////////////////////////////////////
BOOL Init(HINSTANCE hInstance) {

  /**
   * Register the window class.
   */
  WNDCLASS wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszClassName = CLASS_NAME;
  if (RegisterClass(&wc) == 0) {
    MessageBoxA(NULL, "Window class registration failed", "Error",
                MB_ICONERROR);
    return FALSE;
  }

  /**
   * Create the window.
   */
  HWND hwnd = CreateWindowEx(
      WS_EX_LAYERED, CLASS_NAME, WINDOW_NAME, WS_POPUP,
      GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN),
      GetSystemMetrics(SM_CXVIRTUALSCREEN),
      GetSystemMetrics(SM_CYVIRTUALSCREEN), NULL, NULL, hInstance, NULL);
  if (hwnd == NULL) {
    MessageBoxA(NULL, "Window creation failed", "Error", MB_ICONERROR);
    return FALSE;
  }


  SetLayeredWindowAttributes(hwnd, 255, 0, LWA_ALPHA);
  ShowWindow(hwnd, SW_SHOW);
  ShowCursor(FALSE);
  UpdateWindow(hwnd);
  return TRUE;
}

////////////////////////////////////////////////////////////////////////
// Start the black fade
////////////////////////////////////////////////////////////////////////
void RunBlackFade(HINSTANCE hInstance) {
  if (Init(hInstance) == FALSE) {
    return;
  }

  MSG msg;
  BOOL bRet;
  while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
    if (bRet == -1) {
      // error
      break;
    } else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}
