#pragma once

// IEActiveXVoicerecPropPage.h : Declaration of the CIEActiveXVoicerecPropPage property page class.


// CIEActiveXVoicerecPropPage : See IEActiveXVoicerecPropPage.cpp for implementation.

class CIEActiveXVoicerecPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CIEActiveXVoicerecPropPage)
	DECLARE_OLECREATE_EX(CIEActiveXVoicerecPropPage)

// Constructor
public:
	CIEActiveXVoicerecPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_IEACTIVEXVOICEREC };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

