#include "Utils.h"

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
    PlayerPosition* position = new PlayerPosition();
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("C:/Program Files/Tesseract-OCR/tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    api->SetImage((uchar*)screen.data, screen.size().width, screen.size().height, screen.channels(), (int)screen.step1());
    api->Recognize(0);
    outText = api->GetUTF8Text();
    
    int index = 0;
    SetPositionFromOCRString(outText, &index, &(position->x));
    SetPositionFromOCRString(outText, &index, &(position->y));

    api->End();
    delete api;
    delete[] outText;

    return *position;
}

void SetPositionFromOCRString(char* text, int* index, double* variable) {
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