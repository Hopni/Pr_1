// Pr1WinAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Pr1WinAPI.h"
#include "KSet.h"
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_PR1WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PR1WINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PR1WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PR1WINAPI);
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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
KSet<int> kset{ 1, 5, 10 }, kset1{ 1, 7, 15 }, res1, res2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_EXIT:
			res2 = kset;
			kset += kset1;
			res1 = kset;
			kset = res2;
			res2 *= kset1;
			InvalidateRect(hWnd, NULL, true);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		int s = 0;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, L"KSet 1", 6);
		TextOut(hdc, 100, 0, L"KSet 2", 6);
		for (int i = 0; i < kset.Size(); i++)
		{
			TextOut(hdc, 0, i*20 + 20, to_wstring(kset.Get_Pos(i)).c_str(), to_wstring(kset.Get_Pos(i)).size());
		}
		for (int i = 0; i < kset1.Size(); i++)
		{
			TextOut(hdc, 100, i * 20 + 20, to_wstring(kset1.Get_Pos(i)).c_str(), to_wstring(kset1.Get_Pos(i)).size());
		}
		TextOut(hdc, 200, 0, L"Union", 6);
		for (int i = 0; i < res1.Size(); i++)
		{
			TextOut(hdc, 200, i * 20 + 20, to_wstring(res1.Get_Pos(i)).c_str(), to_wstring(res1.Get_Pos(i)).size());
		}
		TextOut(hdc, 300, 0, L"Intersection", 12);
		for (int i = 0; i < res2.Size(); i++)
		{
			TextOut(hdc, 300, i * 20 + 20, to_wstring(res2.Get_Pos(i)).c_str(), to_wstring(res2.Get_Pos(i)).size());
		}
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
	switch (LOWORD(wParam))
	{
	case ID_ENTER1:
	{
		auto a = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, true);
		kset.Insert(a);
		InvalidateRect(GetParent(hDlg), NULL, true);
		break;
	}
	case ID_ENTER2:
	{
		auto b = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, true);
		kset1.Insert(b);
		InvalidateRect(GetParent(hDlg), NULL, true);
		break;
	}
	case IDCANCEL:
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
	}
	break;
	}
	return (INT_PTR)FALSE;
}
