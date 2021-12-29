#include <iostream>
#include "Utils.h"
#define DEFAULT_WINDOW_HIGH 768
#define DEFAULT_WINDOW_WIDTH 1024
using namespace std;

void ShowCursorPosition(HWND hWND) {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hWND, &p);
    cout << "x-position: " << p.x << " | y-position: " << p.y << endl;
}

HWND GetGameWindowByTitle(LPCWSTR windowTitle) {
    HWND hWND = FindWindow(NULL, windowTitle);
    while (hWND == NULL) {
        hWND = FindWindow(NULL, windowTitle);
        cout << "Launch 4Ancient!" << endl;
        Sleep(1000);
    }

    return hWND;
}

void InvolveInGameProcess(HWND hWND) {
    DWORD dwThreadID = GetWindowThreadProcessId(hWND, NULL);
    AttachThreadInput(dwThreadID, GetCurrentThreadId(), true);

    SetForegroundWindow(hWND);
    SetActiveWindow(hWND);
    SetFocus(hWND);

    AttachThreadInput(GetWindowThreadProcessId(GetForegroundWindow(), NULL), GetCurrentThreadId(), TRUE);
}

HBITMAP GetScreenShot(HWND gameHandle)
{
    HDC     hScreen = GetDC(gameHandle);
    HDC     hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = BitBlt(hDC, 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH, hScreen, 0, 0, SRCCOPY);

    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);

    return hBitmap;
}