#include "UserActions.h"
#include "ControlFunctions.h"
using namespace std;

void RotateCharacter180() {
	cout << "Rotate character 180 called\n";
	TapKey('n');
}

void OpenInventory() {
	cout << "Open inventory called\n";
	TapKey('i');
}

void GoFromStoreToTeleport2B() {
	cout << "Go from the store to the teleport 2B called\n";
	INPUT straight = PressKey('w');
	Sleep(6700);
	TapKey('d', 400);
	Sleep(15000);
	TapKey('d', 300);
	Sleep(10000);
	UnpressKey(straight);
}

void GoFromStartToTeleport2B(HWND gameHandle) {
	cout << "Go from start to the teleport 2B called\n";
	//MoveMousePosition(gameHandle, 100, 100);
	DoubleClick();
	INPUT straight = PressKey('w');
	Sleep(6750);
	TapKey('a', 300);
	Sleep(10000);
	TapKey('a', 100);
	Sleep(5000);
	TapKey('d', 450);
	Sleep(12000);
	TapKey('d', 100);
	Sleep(8000);
	TapKey('d', 500);
	Sleep(5000);
	UnpressKey(straight);
}