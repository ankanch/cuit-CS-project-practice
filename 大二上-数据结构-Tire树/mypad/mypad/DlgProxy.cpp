
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "mypad.h"
#include "DlgProxy.h"
#include "mypadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmypadDlgAutoProxy

IMPLEMENT_DYNCREATE(CmypadDlgAutoProxy, CCmdTarget)

CmypadDlgAutoProxy::CmypadDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMypadDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMypadDlg)))
		{
			m_pDialog = reinterpret_cast<CMypadDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CmypadDlgAutoProxy::~CmypadDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CmypadDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CmypadDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CmypadDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_Imypad to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {EA04B42F-9750-4F0C-928C-271FA4902396}
static const IID IID_Imypad =
{ 0xEA04B42F, 0x9750, 0x4F0C, { 0x92, 0x8C, 0x27, 0x1F, 0xA4, 0x90, 0x23, 0x96 } };

BEGIN_INTERFACE_MAP(CmypadDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CmypadDlgAutoProxy, IID_Imypad, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {D73F77BF-CD7F-49B2-888B-0F303438D597}
IMPLEMENT_OLECREATE2(CmypadDlgAutoProxy, "mypad.Application", 0xd73f77bf, 0xcd7f, 0x49b2, 0x88, 0x8b, 0xf, 0x30, 0x34, 0x38, 0xd5, 0x97)


// CmypadDlgAutoProxy message handlers
