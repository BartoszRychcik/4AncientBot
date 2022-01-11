#pragma once
#include <Windows.h>
#include <iostream>
#include "opencv.hpp"
#include <baseapi.h>
#include <allheaders.h>
#define DEFAULT_WINDOW_HIGH 960
#define DEFAULT_WINDOW_WIDTH 1280
using namespace std;
using namespace cv;

struct PlayerPosition {
    double x;
    double y;
};

HWND GetGameWindowByTitle(LPCWSTR windowTitle);
void ActivateGameWindow(HWND hWND);
Mat GetScreenShot(HWND gameHandle);
PlayerPosition ReadPlayerPositionFromScreen(Mat screen);
void SetPositionFromOCRString(char* text, int* index, double* variable);