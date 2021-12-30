#pragma once
#include <Windows.h>

void TapKey(char key, int time = 5);
INPUT PressKey(char key);
void UnpressKey(INPUT input);

void DoubleClick();
void MoveMousePosition(HWND hWND, int x, int y);

void ClickLeftMouseButton(int time = 5);
INPUT PressLeftMouseButton();
void UnpressLeftMouseButton(INPUT input);

void ClickRightMouseButton(int time = 5);
INPUT PressRightMouseButton();
void UnpressRightMouseButton(INPUT input);