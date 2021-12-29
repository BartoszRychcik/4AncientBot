#include <iostream>
#include "UserActions.h"
#include "ControlFunctions.h"
using namespace std;

void RotateCharacter180() {
	cout << "Rotate character 180 called\n";
	TapKey('n', 20);
}

void OpenInventory() {
	cout << "Open inventory called\n";
	TapKey('n', 20);
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

void GoFromStartToTeleport2B() {
	cout << "Go from start to the teleport 2B called\n";
	INPUT straight = PressKey('w');
	Sleep(6700);
	TapKey('d', 400);
	Sleep(15000);
	TapKey('d', 300);
	Sleep(10000);
	UnpressKey(straight);
}