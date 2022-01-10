#pragma once
#include <Windows.h>
#define DEFAULT_PRESS_TIME 5

void TapKey(char key, int time = DEFAULT_PRESS_TIME);
INPUT PressKey(char key);
void UnpressKey(INPUT input);

void ClickLeftMouseButton(int time = DEFAULT_PRESS_TIME);
INPUT PressLeftMouseButton();
void UnpressLeftMouseButton(INPUT input);

void ClickRightMouseButton(int time = DEFAULT_PRESS_TIME);
INPUT PressRightMouseButton();
void UnpressRightMouseButton(INPUT input);

void DoubleClick();
void SetMousePosition(HWND hWND, int x, int y);
void MoveMousePosition(INPUT* input, HWND hWND, int x, int y);