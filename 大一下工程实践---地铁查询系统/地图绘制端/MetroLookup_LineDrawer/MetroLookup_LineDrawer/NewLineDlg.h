#pragma once
#include "afxcolorbutton.h"


// CNewLineDlg �Ի���

class CNewLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewLineDlg)

public:
	CNewLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewLineDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	const CString STR_FILENAME = _T("�������ļ���");
	const CString STR_STABEG = _T("���������վ");
	const CString STR_STAEND = _T("�������յ�վ��");
	const CString STR_PRICE = _T("������ȫ��Ʊ��");
public:
	afx_msg void OnEnSetfocusEditNewLineBegStation();
	afx_msg void OnEnSetfocusEditNewLineEndStation();
	afx_msg void OnEnSetfocusEditNewLinePrice();
	afx_msg void OnEnKillfocusEditNewLineBegStation();
	afx_msg void OnEnKillfocusEditNewLineEndStation();
	afx_msg void OnEnKillfocusEditNewLinePrice();
	CMFCColorButton m_clolor_new_line;
};
