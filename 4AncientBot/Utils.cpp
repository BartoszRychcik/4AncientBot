#include "Utils.h"
using namespace std;

HWND GetGameWindowByTitle(LPCWSTR windowTitle) {
    HWND hWND = FindWindow(NULL, windowTitle);
    while (hWND == NULL) {
        hWND = FindWindow(NULL, windowTitle);
        cout << "Launch 4Ancient!" << endl;
        Sleep(1000);
    }

    return hWND;
}

void ActivateGameWindow(HWND hWND) {
    SetForegroundWindow(hWND);
    SetActiveWindow(hWND);
    SetFocus(hWND);
}

BITMAP GetScreenShot(HWND gameHandle)
{
    HDC     hScreen = GetDC(gameHandle);
    HDC     hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = BitBlt(hDC, 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH, hScreen, 0, 0, SRCCOPY);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);

    return bitmap;
}

PlayerPosition ReadPlayerPositionFromScreen() {
    PlayerPosition position;
    position.x = 5;
    position.y = 5;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    if (api->Init("C:/Program Files/Tesseract-OCR/tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    char* outText;
    // Open input image with leptonica library
    Pix* image = pixRead("C:/Users/wyima/Desktop/4AncientBot/4AncientBot/x64/Debug/sample_line.png");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return position;
}