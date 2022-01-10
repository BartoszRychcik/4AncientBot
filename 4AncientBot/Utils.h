#pragma once
#include <Windows.h>
#include <iostream>
#include "opencv.hpp"
#include <baseapi.h>
#include <allheaders.h>
#define DEFAULT_WINDOW_HIGH 768
#define DEFAULT_WINDOW_WIDTH 1024

struct PlayerPosition {
    double x;
    double y;
};

HWND GetGameWindowByTitle(LPCWSTR windowTitle);
void ActivateGameWindow(HWND hWND);
BITMAP GetScreenShot(HWND gameHandle);
PlayerPosition ReadPlayerPositionFromScreen();