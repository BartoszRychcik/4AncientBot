#include "UserActions.h"
#include "ControlFunctions.h"
#include "Utils.h"

PlayerPosition GetPlayerPosition(HWND gameHandle) {
	Mat screen = GetScreenShot(gameHandle);
	Rect crop_region(640, 808, 90, 15);
	Mat positionRegion = screen(crop_region);
	return ReadPlayerPositionFromScreen(positionRegion);
}

void CorrectionMechanism(HWND gameHandle, list<PlayerPosition>::iterator it, bool nPressed) {
	INPUT inpute = { 0 }, inputq = { 0 }, inputw = { 0 }, inputs = { 0 };
	inputs.ki.dwFlags = inputw.ki.dwFlags = inputq.ki.dwFlags = inpute.ki.dwFlags = KEYEVENTF_SCANCODE;

	SHORT keyScan = VkKeyScan('e');
	inpute.ki.wScan = MapVirtualKey(LOBYTE(keyScan), 0);

	SHORT keyScan2 = VkKeyScan('q');
	inputq.ki.wScan = MapVirtualKey(LOBYTE(keyScan2), 0);

	SHORT keyScan3 = VkKeyScan('w');
	inputw.ki.wScan = MapVirtualKey(LOBYTE(keyScan3), 0);

	SHORT keyScan4 = VkKeyScan('s');
	inputs.ki.wScan = MapVirtualKey(LOBYTE(keyScan4), 0);

	TapKey('m');
	while (true) {
		PlayerPosition position = GetPlayerPosition(gameHandle);
		//cout << fabs(it->x - position.x) << " " << (position.y - 0.5 > it->y) << endl;

		if (fabs(it->x - position.x) <= 1 && fabs(it->y - position.y) <= 1) {
			UnpressKey(inputq);
			UnpressKey(inpute);
			UnpressKey(inputw);
			UnpressKey(inputs);
			break;
		}

		if (fabs(it->x - position.x) >= 0.5) {
			if (nPressed) {
				if (position.x + 0.5 < it->x) {
					UnpressKey(inpute);
					inputq.type = INPUT_KEYBOARD;
					SendInput(1, &inputq, sizeof(inputq));
				}
				if (position.x - 0.5 > it->x) {
					UnpressKey(inputq);
					inpute.type = INPUT_KEYBOARD;
					SendInput(1, &inpute, sizeof(inpute));
				}
			}
			else {
				if (position.x + 0.5 < it->x) {
					UnpressKey(inputq);
					inpute.type = INPUT_KEYBOARD;
					SendInput(1, &inpute, sizeof(inpute));
				}
				if (position.x - 0.5 > it->x) {
					UnpressKey(inpute);
					inputq.type = INPUT_KEYBOARD;
					SendInput(1, &inputq, sizeof(inputq));
				}
			}
		}

		if (fabs(it->y - position.y) >= 0.5) {
			if (nPressed) {
				if (position.y + 0.5 < it->y) {
					UnpressKey(inputw);
					inputs.type = INPUT_KEYBOARD;
					SendInput(1, &inputs, sizeof(inputs));
				}
				if (position.y - 0.5 > it->y) {
					UnpressKey(inputs);
					inputw.type = INPUT_KEYBOARD;
					SendInput(1, &inputw, sizeof(inputw));
				}
			}
			else {
				if (position.y + 0.5 < it->y) {
					UnpressKey(inputs);
					inputw.type = INPUT_KEYBOARD;
					SendInput(1, &inputw, sizeof(inputw));
				}
				if (position.y - 0.5 > it->y) {
					UnpressKey(inputw);
					inputs.type = INPUT_KEYBOARD;
					SendInput(1, &inputs, sizeof(inputs));
				}
			}
		}

		Sleep(50);
	}
	TapKey('m');
}

void KillThemAll(HWND gameHandle) {
	SetMousePosition(gameHandle, 436, 470);

	for (int i = 0; i < 2; i++) {
		TapKey('1');
		Sleep(200);
		
		for (int j = 0; j < 3; j++) {
			TapKey('2');
			Sleep(300);
			ClickLeftMouseButton();
			Sleep(1200);
		}

		for (int j = 0; j < 3; j++) {
			TapKey('3');
			Sleep(100);
		}
		
		Sleep(1000);
	}
	Sleep(10000);
}

void SecondBattleBotLastSpot(HWND gameHandle) {
	list<PlayerPosition> path = {
		PlayerPosition(338.75,205.15)
	};

	while (true) {
		CorrectionMechanism(gameHandle, path.begin(), false);
		Sleep(100);
		TapKey('w', 9500);
		Sleep(100);
		TapKey('e', 7800);
		Sleep(100);
		TapKey('q', 4300);
		Sleep(100);
		TapKey('n');

		KillThemAll(gameHandle);
		Sleep(100);
		TapKey('e', 3600);
		Sleep(100);
		TapKey('w', 9500);
		
		TapKey('w', 5200);
		Sleep(100);
		TapKey('n');
		Sleep(10000);
		TapKey('5');
		Sleep(30000);
		TapKey('5');
		Sleep(60000);
		TapKey('w', 4000);
		Sleep(100);
	}
}