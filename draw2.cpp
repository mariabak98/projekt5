// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <cmath>
#include <deque>
#include <time.h>
#include <cstdlib>

struct passenger {

	int waga;
	int wysiada; 


};

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// buttons
HWND hwndButton;
HWND okienko; 

// sent data
int ile, weight=0; //ile- ile pasazerow wsiada
int poziom = 520; //520-parter,0-4 pietro
std::vector<Point> data;
std::deque<passenger> pasazerowie; 
std::deque<int> kolejkapieter;
RECT drawArea1 = { 0, 0, 150, 200 };
RECT drawArea2 = { 140, 40, 250, 630};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint2(HDC hdc) // obraz pieter i winda
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));

	graphics.DrawLine(&pen, data[1].X, data[1].Y, data[10].X, data[10].Y);
	for (int i = 0; i < 11; i += 2)
		graphics.DrawLine(&pen, data[i].X, data[i].Y, data[i + 1].X, data[i + 1].Y);

	graphics.DrawLine(&pen, data[12].X, data[12].Y, data[23].X, data[23].Y);
	for (int i = 12; i < 23; i += 2)
		graphics.DrawLine(&pen, data[i].X, data[i].Y, data[i + 1].X, data[i + 1].Y);

	graphics.DrawRectangle(&pen, 140, 520 + value, 100, 100);
}


void MyOnPaint(HDC hdc) // sama winda
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	graphics.DrawRectangle(&pen, 140, 520 + value, 100, 100);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea, bool power=false)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	( power ? MyOnPaint2(hdc) : MyOnPaint(hdc));
	EndPaint(hWnd, &ps);
}
//NATALIA
void InputData()
{
	data.push_back(Point(30, 30));
	data.push_back(Point(130, 30));
	data.push_back(Point(130, 150));
	data.push_back(Point(30, 150));
	data.push_back(Point(30, 270));
	data.push_back(Point(130, 270));
	data.push_back(Point(130, 390));
	data.push_back(Point(30, 390));
	data.push_back(Point(30, 510));
	data.push_back(Point(130, 510));
	data.push_back(Point(130, 630));
	data.push_back(Point(30, 630));

	data.push_back(Point(250, 30));
	data.push_back(Point(350, 30));
	data.push_back(Point(350, 150));
	data.push_back(Point(250, 150));
	data.push_back(Point(250, 270));
	data.push_back(Point(350, 270));
	data.push_back(Point(350, 390));
	data.push_back(Point(250, 390));
	data.push_back(Point(250, 510));
	data.push_back(Point(350, 510));
	data.push_back(Point(350, 630));
	data.push_back(Point(250, 630));
}
//NATALIA
void sprawdzkolejke(int wysiada)
{
	bool znaleziono = false; 
	for (int i = 0; i < kolejkapieter.size(); i++)
	{
		if (kolejkapieter[i] == wysiada)
		{
			znaleziono = true;
			break;
		}
	}

	if (!znaleziono)
		kolejkapieter.push_back(wysiada);
}
//NATALIA
void int2char() {

	char tekscik[50];
	sprintf(tekscik, "%d", weight);

		SetWindowTextA(okienko, tekscik); 
}
//MARIA
void znajdzpoziom()
{
	switch (kolejkapieter[0])
	{
	case 0: poziom = 0; break;
	case 1: poziom = 120; break;
	case 2: poziom = 240; break;
	case 3: poziom = 360; break;
	case 4: poziom = 480; break;
	}
}
//NATALIA
void wyrzucpasazerow(int gdzie)
{
	int rozmiar = pasazerowie.size(); 

	kolejkapieter.erase(kolejkapieter.begin());

	for (int k = 0; k < rozmiar; k++)
	{
		for (int i = 0; i < pasazerowie.size(); i++)
		{
			if (pasazerowie[i].wysiada == gdzie)
			{
				pasazerowie.erase( pasazerowie.begin() + i);
				break; 
			}
		}

	}
}
//NATALIA
void gdziewysiada(int gdzie) //ostatni pasazer wysiada tam gdzie nacisniety guzik na interfejsie
{
	int ktory = pasazerowie.size() - 1; 
	pasazerowie[ktory].wysiada = gdzie; 

	sprawdzkolejke(gdzie);


}
//MARIA
void policzwage()
{
	weight = 0;
	for (int i = 0; i< pasazerowie.size(); i++)
		weight += pasazerowie[i].waga;
		
}
//MARIA
void generujwage()
{
	passenger pasazer; 
	
	if (pasazerowie.size() < 6)
	{
		pasazer.waga = rand() % 71 + 40;
		pasazer.wysiada = rand() % 5;
		pasazerowie.push_back(pasazer);
	}
}

int OnCreate(HWND window)
{	
	InputData();
	return 0;
}



// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	srand(time(NULL));

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	//okno do pokazywania wagi
	HWND hStatic = CreateWindowEx(0, TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 
		400, 80, 100, 40, hWnd, NULL, hInstance, NULL);
	okienko = hStatic; 
//NATALIA I MARIA
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("power"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		400, 40,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("(*)"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		40, 100,                                  // the left and top co-ordinates
		15, 15,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONP4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("(*)"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		40, 220,                                  // the left and top co-ordinates
		15, 15,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONP3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("(*)"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		40, 340,                                  // the left and top co-ordinates
		15, 15,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONP2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("(*)"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		40, 465,                                  // the left and top co-ordinates
		15, 15,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONP1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL); 

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("(*)"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		40, 580,                                  // the left and top co-ordinates
		15, 15,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONP,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);


	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		410, 150,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONW4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		410, 190,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONW3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		410, 230,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONW2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		410, 270,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONW1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("P"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		410, 310,                                  // the left and top co-ordinates
		30, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTONW,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		
		//NATALIA
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON2 :
			repaintWindow(hWnd, hdc, ps, NULL,1);
			int2char();
			break;
		case ID_BUTTONP:
			sprawdzkolejke(0);
			SetTimer(hWnd, TMR_1, 25, 0);
			ile = rand() % 3 + 1;
			for(int i=0; i<ile; i++)
			generujwage();
			break;
		case ID_BUTTONP1:
			sprawdzkolejke(1);
			SetTimer(hWnd, TMR_1, 25, 0);
			ile = rand() % 3 + 1;
			for (int i = 0; i<ile; i++)
				generujwage();
			break;
		case ID_BUTTONP2:
			sprawdzkolejke(2);
			SetTimer(hWnd, TMR_1, 25, 0);
			ile = rand() % 3 + 1;
			for (int i = 0; i<ile; i++)
				generujwage();
			break;
		case ID_BUTTONP3:
			sprawdzkolejke(3);
			SetTimer(hWnd, TMR_1, 25, 0);
			ile = rand() % 3 + 1;
			for (int i = 0; i<ile; i++)
				generujwage(); 
			break;
		case ID_BUTTONP4:
			sprawdzkolejke(4);
			SetTimer(hWnd, TMR_1, 25, 0);
			ile = rand() % 3 + 1;
			for (int i = 0; i<ile; i++)
				generujwage();
			break; 
		case ID_BUTTONW:

			if (weight != 0)
			{
				SetTimer(hWnd, TMR_1, 25, 0);
				gdziewysiada(0);
				poziom = 0;
			}
			break;
		case ID_BUTTONW1:

			if (weight != 0)
			{
				SetTimer(hWnd, TMR_1, 25, 0);
				gdziewysiada(1);
				poziom = 120;
			}
			break;
		case ID_BUTTONW2:

			if (weight != 0)
			{
				SetTimer(hWnd, TMR_1, 25, 0);
				gdziewysiada(2);
				poziom = 240;
			}
			break;
		case ID_BUTTONW3:

			if (weight != 0)
			{
				SetTimer(hWnd, TMR_1, 25, 0);
				gdziewysiada(3);
				poziom = 360;
			}
			break;
		case ID_BUTTONW4:

			if (weight != 0)
			{
				SetTimer(hWnd, TMR_1, 25, 0);
				gdziewysiada(4);
				poziom = 480;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			znajdzpoziom();
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			if (abs(value) < poziom)
				value--;
			else if (abs(value) > poziom)
				value++; 
			else
			{
				wyrzucpasazerow(kolejkapieter[0]);
				policzwage();
				int2char();
				if (kolejkapieter.size() == 0)
					KillTimer(hWnd, TMR_1);
				else
				{
					Sleep(2000);
					znajdzpoziom();
				}
			}
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
