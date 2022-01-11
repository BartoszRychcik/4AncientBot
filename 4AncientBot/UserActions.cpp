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

void SecondBattleBot(HWND gameHandle) {
	cout << "Go from teleport to the start position called\n";
	/*
	INPUT straight = PressKey('w');
	Sleep(9300);
	TapKey('d', 500);
	Sleep(4000);
	TapKey('d', 70);
	Sleep(4000);
	TapKey('d', 70);
	Sleep(5000);
	TapKey('a', 400);
	UnpressKey(straight);
	//Sleep(10000);
	*/
	
	while (true) {
		TapKey('m');
		Sleep(50);
		Mat screen = GetScreenShot(gameHandle);
		Rect crop_region(640, 808, 90, 15);
		Mat positionRegion = screen(crop_region);
		Mat grayPositionRegion,resized;
		cvtColor(positionRegion, grayPositionRegion, cv::COLOR_BGR2GRAY);
		resize(positionRegion, resized, Size(93*2, 18*2), INTER_LINEAR);
		Sleep(50);
		TapKey('m');
		PlayerPosition position = ReadPlayerPositionFromScreen(positionRegion);
		cout << position.x << " " << position.y << endl;
		Sleep(5000);
	}
	/*
	straight = PressKey('w');
	Sleep(2000);
	TapKey('d', 70);
	Sleep(2800);
	TapKey(' ');
	Sleep(1000);
	TapKey('a', 150);
	Sleep(3000);
	UnpressKey(straight);
	*/
}