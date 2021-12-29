#include "Utils.h"
#include "UserActions.h"
#include <iostream>
using namespace std;

int main(){
    HWND gameHandle = GetGameWindowByTitle(L"4Ancient");
    InvolveInGameProcess(gameHandle);

    
    while (true) {
        int a;
        cout << "Press button to start";
        cin >> a;

        Sleep(1000);
        RotateCharacter180();
        GoFromStartToTeleport2B();
    }
}