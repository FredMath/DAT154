// exercise1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "exercise1.h"
#include "Draw.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
bool** state;
int eastState = 0;
int southState = 2;
int timerCounter = 0;
int numberCarsNorth = 0;
int numberCarsWest = 0;
Car *carsWest[50];
Car *carsNorth[50];
bool lightState1[] = { TRUE, FALSE, FALSE };
bool lightState2[] = { TRUE, TRUE, FALSE };
bool lightState3[] = { FALSE, FALSE, TRUE };
bool lightState4[] = { FALSE, TRUE, FALSE };
int pw = 50;
int pn = 50;
HWND hwndEdit;
HWND hWestSpawnRateEdit;
HWND hNorthSpawnRateEdit;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				addCarNorth();
void				addCarWest();
void				drawCars(const HDC &hdc);
void				updateNorthPosition();
void				updateWestPosition();
void				updateState();
INT_PTR CALLBACK	SpawnRateEdit(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_EXERCISE1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXERCISE1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXERCISE1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXERCISE1);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   state = new bool*[4];
   state[0] = lightState1;
   state[1] = lightState2;
   state[2] = lightState3;
   state[3] = lightState4;

   SetTimer(hWnd, IDT_TRAFFICLIGHTTIMER, 5000, (TIMERPROC)NULL);
   SetTimer(hWnd, IDT_UPDATECAR, 85, (TIMERPROC)NULL);
   SetTimer(hWnd, IDT_CARSPAWNER, 3500, (TIMERPROC)NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void updateState() {
	eastState++;
	southState++;

	if (eastState == 4)
		eastState = 0;
	if (southState == 4)
		southState = 0;
}

void drawCars(const HDC &hdc) {
	if (numberCarsWest > 0) {
		for (int i = 0; i < numberCarsWest; i++) {
			drawCar(hdc, *carsWest[i]);
		}
	}

	if (numberCarsNorth > 0) {
		for (int i = 0; i < numberCarsNorth; i++) {
			drawCar(hdc, *carsNorth[i]);
		}
	}
}

void addCarWest() {
	Car *car = new Car(25, 330, 50, 50, rand() % 7);
	
		carsWest[numberCarsWest] = car;
		numberCarsWest++;
	
}

void addCarNorth() {
	Car *car = new Car(575, 30, 70, 25, rand() % 7);
	carsNorth[numberCarsNorth] = car;
	numberCarsNorth++;
}

void updateWestPosition() {
	bool eastStopSignal = eastState != 0;
	
		for (int i = 0; i < numberCarsWest; i++) {
			bool collision = false;
			bool westStop = (carsWest[i]->x_pos > 490) && (carsWest[i]->x_pos < 550);
			if (i >= 1) {
				if ((carsWest[i - 1]->x_pos - carsWest[i]->x_pos) < 60) 
					collision = true;
			}
				
				if (!((eastStopSignal) && (westStop)))
					if (!collision)
						carsWest[i]->x_pos = carsWest[i]->x_pos + 4;
			}
		}
	



void updateNorthPosition() {
	bool southStopSignal = southState != 0;
	
	for (int i = 0; i < numberCarsNorth; i++) {
		bool collision = false;
		bool southStop = (carsNorth[i]->y_pos > 210 && carsNorth[i]->y_pos < 250);
		
		if (i >= 1) {
			if (carsNorth[i - 1]->y_pos - carsNorth[i]->y_pos < 60)
				collision = true;
		}

		if (!((southStopSignal) && (southStop))) {
			if (!collision)
				carsNorth[i]->y_pos = carsNorth[i]->y_pos + 4;
		}
	}

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
			
			drawRoad(hdc);
			drawTrafficLight(hdc, 525, 85, state[eastState]);
			drawTrafficLight(hdc, 675, 225, state[southState]);
			drawCars(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
		
	case WM_TIMER:
		switch(wParam)
		{
		case IDT_TRAFFICLIGHTTIMER:
			updateState();
			InvalidateRect(hWnd, NULL, true);

			break;

		case IDT_UPDATECAR:
			updateWestPosition();
			updateNorthPosition();
			InvalidateRect(hWnd, NULL, true);
			
			break;

		case IDT_CARSPAWNER:
			double randWest = rand() % 100;
			double randNorth = rand() % 100;
			bool addWCar = randWest >= pw;
			bool addNCar = randNorth >= pn;

			if (addWCar && numberCarsWest < 50)
				addCarWest();
			if (addNCar && numberCarsNorth < 50)
				addCarNorth();

			break;
		}
		
		InvalidateRect(hWnd, NULL, true);
		//UpdateWindow(hWnd);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_SPACE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SpawnRateEdit);
			break;
		case VK_RIGHT:
			if (pw + 10 <= 100) {
				pw += 10;
				InvalidateRect(hWnd, 0, true);
			}
			break;
		case VK_LEFT:
			if (pw - 10 >= 0) {
				pw -= 10;
				InvalidateRect(hWnd, 0, true);
			}
			break;
		case VK_UP:
			if (pn + 10 <= 100) {
				pn += 10;
				InvalidateRect(hWnd, 0, true);
			}
			break;
		case VK_DOWN:
			if (pn - 10 >= 0) {
				pn -= 10;
				InvalidateRect(hWnd, 0, true);
			}
			break;
		}
	case WM_MOUSEMOVE:
	{
		WCHAR s[100];
		int x = (short)LOWORD(lParam);
		int y = (short)HIWORD(lParam);
		wsprintf(s, L"Koordiantes (%d, %d)", x, y);
		SetWindowTextW(hWnd, s);
		break;

	}
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

INT_PTR CALLBACK SpawnRateEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		static HWND hEdit;
	case WM_INITDIALOG:
		hWestSpawnRateEdit = CreateWindow(
			L"EDIT",
			L"",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			170, 50, 50, 20,
			hDlg, NULL, NULL, NULL
		);
		hNorthSpawnRateEdit = CreateWindow(
			L"EDIT",
			L"",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			170, 50, 50, 20,
			hDlg, NULL, NULL, NULL
		);
		SetWindowTextA(hWestSpawnRateEdit, "pw");
		SetWindowTextA(hNorthSpawnRateEdit, "pn");
		hEdit = GetDlgItem(hDlg, IDC_EDIT1);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR northRate[3];
			TCHAR westRate[3];
			GetWindowText(hNorthSpawnRateEdit, northRate, 3);
			GetWindowText(hWestSpawnRateEdit, westRate, 3);

			pn = _tstoi(northRate);
			pw = _tstoi(westRate);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}




