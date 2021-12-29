#include "ControlFunctions.h"
#include "Utils.h"

void TapKey(char key, int time) {
    INPUT input = PressKey(key);
    Sleep(time);
    UnpressKey(input);
}

INPUT PressKey(char key) {
    UINT mappedkey;
    INPUT input = { 0 };
    SHORT keyScan = VkKeyScan(key);
    mappedkey = MapVirtualKey(LOBYTE(keyScan), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedkey;
    SendInput(1, &input, sizeof(input));
    return input;
}

void UnpressKey(INPUT input) {
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));
}

/*
        if (GetAsyncKeyState(VK_NUMPAD2)) { // leftclick
            cout << "numpad2_click";
            INPUT iNPUT = { 0 };
            iNPUT.type = INPUT_MOUSE;
            iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &iNPUT, sizeof(iNPUT));
            ZeroMemory(&iNPUT, sizeof(iNPUT));
            iNPUT.type = INPUT_MOUSE;
            iNPUT.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &iNPUT, sizeof(iNPUT));
        }

        if (false) { // Set mouse position using SendInput
            cout << "numpad4_click";
            int x = 100;
            int y = 100;

            // Get total screen coordinates
            int screen_x = GetSystemMetrics(SM_CXSCREEN);
            int screen_y = GetSystemMetrics(SM_CYSCREEN);

            WINDOWPLACEMENT wp;
            GetWindowPlacement(hWND, &wp);

            long xConverted = (65535 * (x + wp.rcNormalPosition.left)) / screen_x;
            long yConverted = (65535 * (y + wp.rcNormalPosition.top)) / screen_y;

            INPUT iNPUT = { 0 };
            iNPUT.type = INPUT_MOUSE;
            iNPUT.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
            iNPUT.mi.dx = xConverted;
            iNPUT.mi.dy = yConverted;
            SendInput(1, &iNPUT, sizeof(iNPUT));
            }
            */