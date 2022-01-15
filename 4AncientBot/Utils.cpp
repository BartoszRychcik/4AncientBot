#include "Utils.h"
#include <baseapi.h>
#include <allheaders.h>

HWND GetGameWindowByTitle(LPCWSTR windowTitle) {
    HWND hWND = FindWindow(NULL, windowTitle);
    while (hWND == NULL) {
        hWND = FindWindow(NULL, windowTitle);
        printf("Launch 4Ancient!\n");
        Sleep(1000);
    }

    return hWND;
}

void ActivateGameWindow(HWND hWND) {
    SetForegroundWindow(hWND);
    SetActiveWindow(hWND);
    SetFocus(hWND);
}

Mat GetScreenShot(HWND gameHandle)
{
    HDC     hScreen = GetDC(gameHandle);
    HDC     hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH);
    BITMAPINFOHEADER  bi;
    Mat src;
    src.create(DEFAULT_WINDOW_HIGH, DEFAULT_WINDOW_WIDTH, CV_8UC4);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = DEFAULT_WINDOW_WIDTH;
    bi.biHeight = -DEFAULT_WINDOW_HIGH;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    StretchBlt(hDC, 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH, hScreen, 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HIGH, SRCCOPY);
    GetDIBits(hDC, hBitmap, 0, DEFAULT_WINDOW_HIGH, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);

    return src;
}

PlayerPosition ReadPlayerPositionFromScreen(Mat screen) {
    PlayerPosition* position = new PlayerPosition(0,0);
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("C:/Program Files/Tesseract-OCR/tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    api->SetVariable("user_defined_dpi", "300");
    api->SetImage((uchar*)screen.data, screen.size().width, screen.size().height, screen.channels(), (int)screen.step1());
    outText = api->GetUTF8Text();
    
    int index = 0;
    DecodePositionFromOCRString(outText, &index, &(position->x));
    DecodePositionFromOCRString(outText, &index, &(position->y));

    api->End();
    delete api;
    delete[] outText;

    return *position;
}

void DecodePositionFromOCRString(char* text, int* index, double* variable) {
    double multiplier = 100.0;
    int j = 0;
    while (j != 5) {
        if (isdigit(text[*index])) {
            (*variable) += (int(text[*index]) - '0') * multiplier;
            multiplier /= 10;
            j++;
        }
        (*index)++;
    }
}