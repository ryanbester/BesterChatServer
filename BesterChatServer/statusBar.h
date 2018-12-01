// Copyright (C) 2018 Ryan Bester

#pragma once

#ifndef _STATUS_BAR_

#define _STATUS_BAR_

class StatusBar
{
public:
	HWND hStatus;
	HWND hParent;

	StatusBar(HWND);
	~StatusBar();

	BOOL CreateStatusBar();

	BOOL SetParts(int number, int parts[]);

	BOOL SetText(LPCTSTR text);
	BOOL SetText(int part, LPCTSTR text);	
};

#endif
