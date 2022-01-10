#include "ControlFunctions.h"
#include "Utils.h"

void TapKey(char key, int time) {
    INPUT input = PressKey(key);
    Sleep(time);
    UnpressKey(input);
}

INPUT PressKey(char key) {
    UINT mappedKey;
    INPUT input = { 0 };
    SHORT keyScan = VkKeyScan(key);
    mappedKey = MapVirtualKey(LOBYTE(keyScan), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedKey;
    SendInput(1, &input, sizeof(input));
    return input;
}

void UnpressKey(INPUT input) {
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));
}

void ClickLeftMouseButton(int time) {
    INPUT input = PressLeftMouseButton();
    Sleep(time);
    UnpressLeftMouseButton(input);
}

INPUT PressLeftMouseButton() {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(input));
    return input;
}

void UnpressLeftMouseButton(INPUT input) {
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(input));
}

void ClickRightMouseButton(int time) {
    INPUT input = PressRightMouseButton();
    Sleep(time);
    UnpressRightMouseButton(input);
}

INPUT PressRightMouseButton() {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(input));
    return input;
}

void UnpressRightMouseButton(INPUT input) {
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(input));
}

void DoubleClick() {
    ClickLeftMouseButton(5);
    ClickLeftMouseButton(5);
}

void SetMousePosition(HWND hWND, int x, int y) {
    WINDOWPLACEMENT wp;
    GetWindowPlacement(hWND, &wp);

    long xConverted = (65535 * (x + wp.rcNormalPosition.left)) / DEFAULT_WINDOW_WIDTH;
    long yConverted = (65535 * (y + wp.rcNormalPosition.top)) / DEFAULT_WINDOW_HIGH;

    INPUT iNPUT = { 0 };
    iNPUT.type = INPUT_MOUSE;
    iNPUT.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    iNPUT.mi.dx = xConverted;
    iNPUT.mi.dy = yConverted;
    SendInput(1, &iNPUT, sizeof(INPUT));
}

void MoveMousePosition(INPUT* input, HWND hWND, int x, int y) {
    WINDOWPLACEMENT wp;
    GetWindowPlacement(hWND, &wp);

    long xConverted = (65535 * (x + wp.rcNormalPosition.left)) / DEFAULT_WINDOW_WIDTH;
    long yConverted = (65535 * (y + wp.rcNormalPosition.top)) / DEFAULT_WINDOW_HIGH;

    input->mi.dwFlags = MOUSEEVENTF_MOVE;
    input->mi.dx = xConverted;
    input->mi.dy = yConverted;
    SendInput(1, input, sizeof(INPUT));
}