#pragma once

// IEActiveXVoicerec.h : main header file for IEActiveXVoicerec.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CIEActiveXVoicerecApp : See IEActiveXVoicerec.cpp for implementation.

class CIEActiveXVoicerecApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

