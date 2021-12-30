#pragma once
#include <Windows.h>
#define DEFAULT_WINDOW_HIGH 768
#define DEFAULT_WINDOW_WIDTH 1024

HWND GetGameWindowByTitle(LPCWSTR windowTitle);
void InvolveInGameProcess(HWND hWND);
HBITMAP GetScreenShot(HWND gameHandle);