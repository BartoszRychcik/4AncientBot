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

PlayerPosition GetPlayerPosition(HWND gameHandle) {
	Mat screen = GetScreenShot(gameHandle);
	Rect crop_region(640, 808, 90, 15);
	Mat positionRegion = screen(crop_region);
	Mat resized;
	resize(positionRegion, resized, Size(93 * 3, 18 * 3), INTER_LINEAR);
	return ReadPlayerPositionFromScreen(positionRegion);
}

void CorrectionMechanism(HWND gameHandle, list<PlayerPosition>::iterator it, bool nPressed) {
	UINT mappedKey;
	INPUT inpute = { 0 };
	SHORT keyScan = VkKeyScan('e');
	mappedKey = MapVirtualKey(LOBYTE(keyScan), 0);
	inpute.ki.dwFlags = KEYEVENTF_SCANCODE;
	inpute.ki.wScan = mappedKey;

	UINT mappedKey2;
	INPUT inputq = { 0 };
	SHORT keyScan2 = VkKeyScan('q');
	mappedKey2 = MapVirtualKey(LOBYTE(keyScan2), 0);
	inputq.ki.dwFlags = KEYEVENTF_SCANCODE;
	inputq.ki.wScan = mappedKey2;

	UINT mappedKey3;
	INPUT inputw = { 0 };
	SHORT keyScan3 = VkKeyScan('w');
	mappedKey3 = MapVirtualKey(LOBYTE(keyScan3), 0);
	inputw.ki.dwFlags = KEYEVENTF_SCANCODE;
	inputw.ki.wScan = mappedKey3;

	TapKey('m');
	while (true) {
		PlayerPosition position = GetPlayerPosition(gameHandle);
		cout << fabs(it->x - position.x) << " " << (position.y - 0.5 > it->y) << endl;

		if (fabs(it->x - position.x) < 0.5 && ((!nPressed && position.y > it->y) || (nPressed && position.y < it->y))) {
			UnpressKey(inputq);
			UnpressKey(inpute);
			UnpressKey(inputw);
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

		if ((!nPressed && position.y < it->y) || (nPressed && position.y > it->y)) {
			inputw.type = INPUT_KEYBOARD;
			SendInput(1, &inputw, sizeof(inputw));
		}

		Sleep(50);
	}
	TapKey('m');
}

void SecondBattleBot(HWND gameHandle) {
	cout << "Go from teleport to the start position called\n";
	list<PlayerPosition> path = { 
		PlayerPosition(224.00,420.00),
		PlayerPosition(260.00,473.00),
		PlayerPosition(265.00,452.00),
	};

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

	auto it = path.begin();
	CorrectionMechanism(gameHandle, it, false);
	it++;

	straight = PressKey('w');
	Sleep(2000);
	TapKey('d', 70);
	Sleep(2800);
	TapKey(' ');
	Sleep(200);
	TapKey('a', 50);
	Sleep(50);
	TapKey('d', 50);
	Sleep(8000);
	UnpressKey(straight);

	CorrectionMechanism(gameHandle, it, false);
	it++;
	
	TapKey('n');
	TapKey('q', 2000);
	straight = PressKey('w');
	TapKey('q', 2000);
	Sleep(2000);
	UnpressKey(straight);

	CorrectionMechanism(gameHandle, it, true);
	it++;

	straight = PressKey('w');
	Sleep(1000);
	TapKey('e', 500);
	UnpressKey(straight);

	TapKey('1');
	TapKey('3');
}