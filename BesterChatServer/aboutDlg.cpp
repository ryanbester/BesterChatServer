#include <Windows.h>
#include <stdio.h>

#include "aboutDlg.h"
#include "resource.h"

#define _MAIN_
#include "main.h"

int AboutDialog::ShowDialog(HWND hWnd)
{
	int dialog = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_HELP_ABOUT), hWnd, AboutDialogProc);
	return dialog;
}

BOOL AboutDialog::AboutDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		HWND hTitle = CreateWindowEx(0, TEXT("STATIC"), TEXT("BesterChat Server"), WS_CHILD | WS_VISIBLE | SS_CENTER, 150, 11, 214, 23, hWnd, NULL, NULL, NULL);
		CreateWindowEx(0, TEXT("STATIC"), TEXT("(C) 2018 Ryan Bester"), WS_CHILD | WS_VISIBLE | SS_CENTER, 150, 45, 214, 23, hWnd, NULL, NULL, NULL);
		HWND hAboutDlgImage = CreateWindowEx(0, TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_ICON, 11, 11, 128, 128, hWnd, NULL, NULL, NULL);
		HICON aIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON), IMAGE_ICON, 128, 128, 0);
		SendMessage(hAboutDlgImage, STM_SETIMAGE, IMAGE_ICON, (LPARAM)aIcon);

		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(ncm));
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)CreateFontIndirect(&ncm.lfMessageFont));

		ncm.lfCaptionFont.lfHeight = 20;
		SendMessage(hTitle, WM_SETFONT, (WPARAM)CreateFontIndirect(&ncm.lfCaptionFont), true);

		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			EndDialog(hWnd, IDOK);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(hWnd, IDCANCEL);
			break;
		}
		}
		break;
	}
	default:
	{
		return FALSE;
	}
	}
	return TRUE;
}
