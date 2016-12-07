#pragma once
#include "afxwin.h"


// CAddStationDlg �Ի���

class CAddStationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddStationDlg)

public:
	CAddStationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddStationDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_STATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnSetfocusEditStationName();
	afx_msg void OnEnSetfocusEditStationLtime();
	afx_msg void OnEnSetfocusEditStationRtimr();
	afx_msg void OnEnSetfocusEditStationPriceFromL();
	afx_msg void OnEnSetfocusEditStationPriceFromR();
	afx_msg void OnEnKillfocusEditStationName();
	afx_msg void OnEnKillfocusEditStationLtime();
	afx_msg void OnEnKillfocusEditStationRtimr();
	afx_msg void OnEnKillfocusEditStationPriceFromL();
	afx_msg void OnEnKillfocusEditStationPriceFromR();
	afx_msg void OnBnClickedOk();
private:
	const CString STRING_EDIT_STATION_NAME = _T("������վ����");
	const CString STRING_EDIT_LTIME = _T("���е�վ��ʱ");
	const CString STRING_EDIT_RTIME = _T("���е�վ��ʱ");
	const CString STRING_EDIT_LPRICE = _T("�����վ������Ʊ��");
	const CString STRING_EDIT_RPRICE = _T("���յ�վ������Ʊ��");
	int term_price = 0;
public:
	virtual BOOL OnInitDialog();
	CButton m_checkbox;
	afx_msg void OnEnChangeEditStationPriceFromL();
};
