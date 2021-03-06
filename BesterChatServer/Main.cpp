// Copyright (C) 2018 Ryan Bester

#define WIN32_LEAN_AND_MEAN

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#include <stdio.h>
#include <CommCtrl.h>
#include <memory>

#include "main.h"
#include "resource.h"
#include "statusBar.h"
#include "aboutDlg.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID GetClientArea(HWND hWnd, RECT &rcArea);

std::unique_ptr<StatusBar> statusBar;

bool CALLBACK SetFont(HWND child, LPARAM font)
{
	SendMessage(child, WM_SETFONT, font, true);
	return true;
}

VOID GetClientArea(HWND hWnd, RECT &rcArea)
{
	RECT rcClient;
	RECT rcStatus;
	int iStatusHeight;

	GetClientRect(hWnd, &rcClient);

	if (statusBar)
	{
		SendMessage(statusBar->hStatus, WM_SIZE, 0, 0);

		GetWindowRect(statusBar->hStatus, &rcStatus);
		iStatusHeight = rcStatus.bottom - rcStatus.top;

		rcClient.bottom = rcClient.bottom - iStatusHeight;
	}

	rcArea = rcClient;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream = stdout;
	freopen_s(&stream, "CON", "w", stream);
#endif

	HWND hWnd;
	WNDCLASSEX wcex;
	MSG msg;

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_STANDARD_CLASSES;

	InitCommonControlsEx(&icex);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWndClassName;
	wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APP_ICON), IMAGE_ICON, 16, 16, 0);
	
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, TEXT("Could not start BesterChat Server. The window class could not be registered"), TEXT("BesterChat Server"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindowEx(0, szWndClassName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Could not start BesterChat Server. The window could not be created"), TEXT("BesterChat Server"), MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_CREATE:
	{
		HMENU hMenu;

		hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDM_MAIN_MENU));

		SetMenu(hWnd, hMenu);

		statusBar = std::make_unique<StatusBar>(hWnd);

		statusBar->CreateStatusBar();

		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(ncm));
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)CreateFontIndirect(&ncm.lfMessageFont));
		break;
	}
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case IDM_FILE_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		case IDM_HELP_ABOUT:
		{
			AboutDialog aboutDialog = AboutDialog();
			int dialog = aboutDialog.ShowDialog(hWnd);
			break;
		}
		}
		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 300;
		break;
	}
	case WM_SIZE:
	{
		RECT rcClient;

		GetClientArea(hWnd, rcClient);

		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		COLORREF colorref;
		colorref = RGB(255, 255, 255);
		HBRUSH hBrushBtn = CreateSolidBrush(colorref);
		return ((LRESULT)hBrushBtn);
		break;
	}
	case WM_CTLCOLORBTN:
	{
		COLORREF colorref;
		colorref = RGB(255, 255, 255);
		HBRUSH hBrushBtn = CreateSolidBrush(colorref);
		return ((LRESULT)hBrushBtn);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}
