// IEActiveXVoicerecCtrl.cpp : Implementation of the CIEActiveXVoicerecCtrl ActiveX Control class.

#include "stdafx.h"
#include "IEActiveXVoicerec.h"
#include "IEActiveXVoicerecCtrl.h"
#include "IEActiveXVoicerecPropPage.h"
#include "afxdialogex.h"
#include "atlsafe.h"
#include "AudioHandler.h"
#include "AudioFormatEncoder.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIEActiveXVoicerecCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CIEActiveXVoicerecCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CIEActiveXVoicerecCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CIEActiveXVoicerecCtrl, COleControl)
	DISP_FUNCTION_ID(CIEActiveXVoicerecCtrl, "startRecording", dispidstartRecording, startRecording, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIEActiveXVoicerecCtrl, "stopRecording", dispidstopRecording, stopRecording, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CIEActiveXVoicerecCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CIEActiveXVoicerecCtrl, 1)
	PROPPAGEID(CIEActiveXVoicerecPropPage::guid)
END_PROPPAGEIDS(CIEActiveXVoicerecCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CIEActiveXVoicerecCtrl, "MFCACTIVEXCONTRO.IEActiveXVoicerecCtrl.1",
	0x75943fab,0xf874,0x4a9d,0xa4,0x82,0x65,0x40,0x34,0xae,0x19,0x28)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CIEActiveXVoicerecCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DIEActiveXVoicerec = {0x4e9894d3,0x9f1b,0x481d,{0x83,0xec,0xa0,0x95,0xff,0x68,0x48,0xb7}};
const IID IID_DIEActiveXVoicerecEvents = {0x3bb1bd89,0xdd24,0x4a48,{0x92,0x8d,0x67,0x41,0x68,0x11,0xfb,0xc5}};

// Control type information

static const DWORD _dwIEActiveXVoicerecOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CIEActiveXVoicerecCtrl, IDS_IEACTIVEXVOICEREC, _dwIEActiveXVoicerecOleMisc)

// CIEActiveXVoicerecCtrl::CIEActiveXVoicerecCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CIEActiveXVoicerecCtrl

BOOL CIEActiveXVoicerecCtrl::CIEActiveXVoicerecCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_IEACTIVEXVOICEREC,
			IDB_IEACTIVEXVOICEREC,
			afxRegApartmentThreading,
			_dwIEActiveXVoicerecOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CIEActiveXVoicerecCtrl::CIEActiveXVoicerecCtrl - Constructor

CIEActiveXVoicerecCtrl::CIEActiveXVoicerecCtrl()
{
	InitializeIIDs(&IID_DIEActiveXVoicerec, &IID_DIEActiveXVoicerecEvents);
	initializePa();
}

// CIEActiveXVoicerecCtrl::~CIEActiveXVoicerecCtrl - Destructor

CIEActiveXVoicerecCtrl::~CIEActiveXVoicerecCtrl()
{
	terminatePa();
}

// CIEActiveXVoicerecCtrl::OnDraw - Drawing function

void CIEActiveXVoicerecCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	DoSuperclassPaint(pdc, rcBounds);
}

// CIEActiveXVoicerecCtrl::DoPropExchange - Persistence support

void CIEActiveXVoicerecCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}


// CIEActiveXVoicerecCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CIEActiveXVoicerecCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control will not be redrawn when making the transition
	// between the active and inactivate state.
	dwFlags |= noFlickerActivate;
	return dwFlags;
}


// CIEActiveXVoicerecCtrl::OnResetState - Reset control to default state

void CIEActiveXVoicerecCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CIEActiveXVoicerecCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CIEActiveXVoicerecCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	BOOL bRet = COleControl::PreCreateWindow(cs);
	cs.hMenu = nullptr;
	return bRet;
}

// CIEActiveXVoicerecCtrl::IsSubclassedControl - This is a subclassed control

BOOL CIEActiveXVoicerecCtrl::IsSubclassedControl()
{
	return TRUE;
}

// CIEActiveXVoicerecCtrl::OnOcmCommand - Handle command messages

LRESULT CIEActiveXVoicerecCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);

	// TODO: Switch on wNotifyCode here.

	return 0;
}

void CIEActiveXVoicerecCtrl::startRecording()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	openStreamPa();
	startStreamPa();
}


BSTR CIEActiveXVoicerecCtrl::stopRecording()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PaTestData* sptr = stopStreamPa();
	VIO_DATA* wav = convertRawToWav(sptr);
	CString strResult(convertWavToBase64(wav->data, sptr->recordedSamples.size() * 2 + 44).c_str());
	return strResult.AllocSysString();
}

