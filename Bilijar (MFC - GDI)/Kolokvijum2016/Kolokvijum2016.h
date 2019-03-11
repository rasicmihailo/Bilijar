
// Kolokvijum2016.h : main header file for the Kolokvijum2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolokvijum2016App:
// See Kolokvijum2016.cpp for the implementation of this class
//

class CKolokvijum2016App : public CWinApp
{
public:
	CKolokvijum2016App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKolokvijum2016App theApp;
