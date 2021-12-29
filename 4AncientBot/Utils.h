#pragma once
#include <Windows.h>

void ShowCursorPosition(HWND hWND);
HWND GetGameWindowByTitle(LPCWSTR windowTitle);
void InvolveInGameProcess(HWND hWND);
HBITMAP GetScreenShot(HWND gameHandle);