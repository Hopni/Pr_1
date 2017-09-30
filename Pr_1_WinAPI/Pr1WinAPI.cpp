// Pr1WinAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Pr1WinAPI.h"
#include "MVC.h"
#include <string>
using namespace std;

// Forward declarations of functions included in this code module:

Model<int> model_1{ 1, 5, 7 }, model_2{ 1, 5, 15 };
Controller<int> cnt(model_1, model_2);
View<int> view(cnt);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
	return NULL;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return view.ButtonEvents(hDlg, message, wParam, lParam);
}
