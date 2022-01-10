#include "UserActions.h"
#include "ControlFunctions.h"
#include "Utils.h"
using namespace std;

void RotateCharacter180() {
	cout << "Rotate character 180 called\n";
	TapKey('n');
}

void OpenInventory() {
	cout << "Open inventory called\n";
	TapKey('i');
}

void GoFromStartToTeleport2B(HWND gameHandle) {
	cout << "Go from start to the teleport 2B called\n";
	TapKey('m');
	Sleep(100);
	BITMAP screen = GetScreenShot(gameHandle);
	PlayerPosition position = ReadPlayerPositionFromScreen();
	
	/*
	TapKey('n');
	Sleep(10);
	INPUT straight = PressKey('w');
	Sleep(3000);
	TapKey('d', 300);
	Sleep(100);
	UnpressKey(straight);
	*/
	/*
	SetMousePosition(gameHandle, 300, 200);
	DoubleClick();
	Sleep(500);
	SetMousePosition(gameHandle, 300, 160);
	DoubleClick();
	Sleep(4000);

	INPUT straight = PressKey('w');
	Sleep(50);
	TapKey('d', 1000);
	Sleep(100);
	TapKey('a', 100);
	Sleep(5000);
	TapKey('a', 330);
	Sleep(4000);
	TapKey('a', 60);
	Sleep(12000);
	TapKey('d', 250);
	Sleep(7500);
	TapKey('d', 120);
	Sleep(12000);
	UnpressKey(straight);
	*/
}