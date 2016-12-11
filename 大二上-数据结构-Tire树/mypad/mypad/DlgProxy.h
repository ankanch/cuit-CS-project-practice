
// DlgProxy.h: header file
//

#pragma once

class CMypadDlg;


// CmypadDlgAutoProxy command target

class CmypadDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CmypadDlgAutoProxy)

	CmypadDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMypadDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CmypadDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CmypadDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

