// Copyright (C) 2018 Ryan Bester

#pragma once

#include <Windows.h>
#include <stdio.h>
#include <memory>
#include <CommCtrl.h>

#include "resource.h"
#include "statusBar.h"

StatusBar::StatusBar(HWND hWnd) : hParent(hWnd)
{
	printf("Status bar created\n");
}

StatusBar::~StatusBar()
{
	printf("Status bar destroyed\n");
}

BOOL StatusBar::CreateStatusBar()
{
	if (!hParent)
	{
		return FALSE;
	}

	hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hParent, (HMENU)1000, GetModuleHandle(NULL), NULL);

	if (!hStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL StatusBar::SetParts(int number, int parts[])
{
	if (!hStatus)
	{
		return FALSE;
	}

	SendMessage(hStatus, SB_SETPARTS, number, (LPARAM)parts);

	return TRUE;
}

BOOL StatusBar::SetText(LPCTSTR text)
{
	if (!hStatus)
	{
		return FALSE;
	}

	SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)text);

	return TRUE;
}

BOOL StatusBar::SetText(int part, LPCTSTR text)
{
	if (!hStatus)
	{
		return FALSE;
	}

	SendMessage(hStatus, SB_SETTEXT, MAKEWPARAM(part, 0), (LPARAM)text);
	
	return true;
}
