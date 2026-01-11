#ifndef BLACK_FADE_H
#define BLACK_FADE_H

# include <Windows.h>

typedef struct {
    int keepAwake;
} BlackFadeOptions;

void RunBlackFade(HINSTANCE hInstance, const BlackFadeOptions* options);

#endif // BLACK_FADE_H
