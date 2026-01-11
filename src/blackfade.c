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
  static LPARAM startMousePos = 0;

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
  case WM_MOUSEMOVE: // fall through
    if (startMousePos == 0) {
      startMousePos = lParam;
    }
    if (startMousePos == lParam) {
      // Mouse not moved
      return 0;
    }
  case WM_KEYDOWN:   // fall through
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
BOOL Init(HINSTANCE hInstance, const BlackFadeOptions* options) {

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

  if (options->keepAwake) {
    // スリープ防止
    EXECUTION_STATE state = SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
    if (state == 0) {
      MessageBoxA(NULL, "Failed to set execution state", "Error", MB_ICONERROR);
      return FALSE;
    }
  }

  return TRUE;
}

////////////////////////////////////////////////////////////////////////
/// Cleanup function
////////////////////////////////////////////////////////////////////////
void Cleanup(const BlackFadeOptions* options) {
  if (options->keepAwake) {
    // スリープ防止解除
    SetThreadExecutionState(ES_CONTINUOUS);
  }
}
////////////////////////////////////////////////////////////////////////
// Start the black fade
////////////////////////////////////////////////////////////////////////
void RunBlackFade(HINSTANCE hInstance, const BlackFadeOptions* options) {
  if (Init(hInstance, options) == FALSE) {
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
  Cleanup(options);
}
