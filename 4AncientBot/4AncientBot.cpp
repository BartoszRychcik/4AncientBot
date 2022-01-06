#include "Utils.h"
#include "UserActions.h"
#include <iostream>
using namespace std;

int main(){
    HWND gameHandle = GetGameWindowByTitle(L"4Ancient");
    
    while (true) {
        string a;
        cout << "write 'start' to start";
        cin >> a;

        if (a == "start") {
            InvolveInGameProcess(gameHandle);
            Sleep(3000);
            GoFromStartToTeleport2B(gameHandle);
        }
    }
}