#pragma once

#ifndef _ABOUT_DLG_

#define _ABOUT_DLG_

class AboutDialog
{
public:
	int ShowDialog(HWND);
	static BOOL CALLBACK AboutDialogProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
