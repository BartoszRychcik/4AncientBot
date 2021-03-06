#pragma once
#include <Windows.h>
#include <iostream>
#include "opencv.hpp"
#define DEFAULT_WINDOW_HIGH 960
#define DEFAULT_WINDOW_WIDTH 1280
using namespace cv;

struct PlayerPosition {
    double x;
    double y;
    PlayerPosition(double x, double y) : x(x), y(y) {}
};

HWND GetGameWindowByTitle(LPCWSTR windowTitle);
void ActivateGameWindow(HWND hWND);
Mat GetScreenShot(HWND gameHandle);
PlayerPosition ReadPlayerPositionFromScreen(Mat screen);
void DecodePositionFromOCRString(char* text, int* index, double* variable);