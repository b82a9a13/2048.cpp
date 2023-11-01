// 2048.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "2048.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int gameWidth = 600;
int gameHeight = 600;
int windowWidth = gameWidth+200;
int windowHeight = gameHeight+200;
int gridValues[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};
HWND upButton;
HWND downButton;
HWND rightButton;
HWND leftButton;
bool newGame = TRUE;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2048, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2048));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2048));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2048);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   //Create the window and set the options available and set the width and height of the window
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);
   //Draw buttons
   upButton = CreateWindow(L"BUTTON", L"Up", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (gameWidth / 2) - 50, gameHeight, 100, 50, hWnd, NULL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
   leftButton = CreateWindow(L"BUTTON", L"Left", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (gameWidth / 2) - 150, gameHeight + 50, 100, 50, hWnd, NULL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
   downButton = CreateWindow(L"BUTTON", L"Down", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (gameWidth / 2) - 50, gameHeight + 50, 100, 50, hWnd, NULL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
   rightButton = CreateWindow(L"BUTTON", L"Right", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (gameWidth / 2) + 50, gameHeight + 50, 100, 50, hWnd, NULL, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//Check if there is a zero in the gridValues array
bool containsZero() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (gridValues[x][y] == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

//Function is called to interact with the game and move the values in the direction provided and add adjacent values if they are the same
void buttonClicked(int param, HWND hWnd) {
    bool newValue = FALSE;
    if (param == 0 || param == 1 || param == 2 || param == 3) {
        for (int i = 0; i < 3; i++) {
            for (int x = 0; x < 4; x++) {
                int tmpArray[4] = { 0,0,0,0 };
                int arrPos = 0;
                if (param == 0) {
                    for (int y = 0; y < 4; y++) {
                        if (gridValues[x][y] != 0) {
                            tmpArray[arrPos] = gridValues[x][y];
                            arrPos++;
                        }
                    }
                }
                else if (param == 1) {
                    for (int y = 3; y >= 0; y--) {
                        if (gridValues[x][y] != 0) {
                            tmpArray[arrPos] = gridValues[x][y];
                            arrPos++;
                        }
                    }
                }
                else if (param == 2) {
                    for (int y = 0; y < 4; y++) {
                        if (gridValues[y][x] != 0) {
                            tmpArray[arrPos] = gridValues[y][x];
                            arrPos++;
                        }
                    }
                }
                else if (param == 3) {
                    for (int y = 3; y >= 0; y--) {
                        if (gridValues[y][x] != 0) {
                            tmpArray[arrPos] = gridValues[y][x];
                            arrPos++;
                        }
                    }
                }
                for (int y = 0; y < 3; y++) {
                    if (tmpArray[y] != 0 && tmpArray[y + 1] != 0) {
                        if (tmpArray[y] == tmpArray[y + 1]) {
                            tmpArray[y] += tmpArray[y + 1];
                            tmpArray[y + 1] = 0;
                        }
                    }
                }
                if (param == 0) {
                    for (int y = 0; y < 4; y++) {
                        gridValues[x][y] = tmpArray[y];
                    }
                }
                else if (param == 1) {
                    for (int y = 0; y < 4; y++) {
                        gridValues[x][y] = tmpArray[3 - y];
                    }
                }
                else if (param == 2) {
                    for (int y = 0; y < 4; y++) {
                        gridValues[y][x] = tmpArray[y];
                    }
                }
                else if (param == 3) {
                    for (int y = 0; y < 4; y++) {
                        gridValues[y][x] = tmpArray[3 - y];
                    }
                }
            }
        }
        newValue = TRUE;
    }
    //Add a 2 if NewValue is set to true and there is a zero in the gridValues array
    if ((newValue) && (containsZero())){
        int x = rand() % 4;
        int y = rand() % 4;
        while (gridValues[x][y] != 0) {
            x = rand() % 4;
            y = rand() % 4;
        }
        gridValues[x][y] = 2;
    }
    InvalidateRect(hWnd, NULL, TRUE);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            //If statements calls the button clicked function with the relevant parameter
            if (HIWORD(wParam) == BN_CLICKED) {
                if ((HWND)lParam == upButton) {
                    buttonClicked(0, hWnd);
                }
                else if ((HWND)lParam == downButton) {
                    buttonClicked(1, hWnd);
                }
                else if ((HWND)lParam == leftButton) {
                    buttonClicked(2, hWnd);
                }
                else if ((HWND)lParam == rightButton) {
                    buttonClicked(3, hWnd);
                }
            }
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //Draw the 2048 grid
            for (int i = 0; i < 4; i++) {
                for (int y = 0; y < 4; y++) {
                    Rectangle(hdc, (gameWidth/4)*i, (gameHeight/4)*y, (gameWidth/4)+((gameWidth/4)*i), (gameHeight/4)+((gameHeight/4)*y));
                }
            }
            if (newGame) {
                //Draw three 2 in a empty square
                for (int i = 0; i < 3; i++) {
                    int x = rand() % 4;
                    int y = rand() % 4;
                    while (gridValues[x][y] == 2) {
                        x = rand() % 4;
                        y = rand() % 4;
                    }
                    gridValues[x][y] = 2;
                    TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("2"), 1);
                }
            }
            else {
                for (int x = 0; x < 4; x++) {
                    for (int y = 0; y < 4; y++) {
                        if (gridValues[x][y] != 0) {
                            if (gridValues[x][y] == 2) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("2"), 1);
                            }
                            else if (gridValues[x][y] == 4) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("4"), 1);
                            }
                            else if (gridValues[x][y] == 8) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("8"), 1);
                            }
                            else if (gridValues[x][y] == 16) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("16"), 2);
                            }
                            else if (gridValues[x][y] == 32) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("32"), 2);
                            }
                            else if (gridValues[x][y] == 64) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("64"), 2);
                            }
                            else if (gridValues[x][y] == 128) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("128"), 3);
                            }
                            else if (gridValues[x][y] == 256) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("256"), 3);
                            }
                            else if (gridValues[x][y] == 512) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("512"), 3);
                            }
                            else if (gridValues[x][y] == 1024) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("1024"), 4);
                            }
                            else if (gridValues[x][y] == 2048) {
                                TextOut(hdc, ((x + 1) * (gameWidth / 4)) - 75, ((y + 1) * (gameHeight / 4)) - 75, TEXT("2048"), 4);
                            }
                        }
                    }
                }
            }
            newGame = FALSE;
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}