
// MetroLookUpDlg.h : ͷ�ļ�
//

#pragma once
#include "MapDlg.h"
#include "afxwin.h"


// CMLUDlg �Ի���
class CMLUDlg : public CDialogEx
{
// ����
public:
	CMLUDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_METROLOOKUP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLookUp();
	afx_msg void OnEnSetfocusBegin();
	afx_msg void OnEnSetfocusEnd();
	afx_msg void OnEnKillfocusBegin();
	afx_msg void OnEnKillfocusEnd();

	//���ݿ�������
	//�õ�����access���ݿ�����Ӷ���
	const _ConnectionPtr GetConnectionPtr();
	//�õ����������
	const _RecordsetPtr GetRecordsetPtr();
	//�����ݿ��м��ص�ͼ���ļ������ɵ�ͼ�����ļ�
	const bool CreateMapCache();
	
	//վ���ѯ���
	void SetLookupPrice(const int price);
	void SetLookupTime(const int time);
	void SetTrsstrData(const CString dta);
	void SetLUbeg(const CString name);
	void SetLUend(const CString name);
	//����2�����������������ڵ�ͼ��ѡ��վ���
	const bool IsBegFocused();
	const bool IsEndFocused();
	//�����������������������·��Ŀ
	const int GetLinecount();
	//���溯����վ��������
	const bool IsHighlightPressed();
	void SetHighlightPressedStatus(const bool sta);
private:
	const bool KSQL_Excute(const CString cmd);
	const bool KSQL_Excute(const CString cmd, _RecordsetPtr & rp);
	const bool KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp);

	CFont *GetAppFont(const CString & fontName);
	CMapDlg *mapDlg;
	STATION_DATA SD_BEG;
	STATION_DATA SD_END;
	CStdioFile csflog;
	CString logstr;
	int linecount = 0;
	//���ݿ�������
	_ConnectionPtr m_pConnection;//����access���ݿ�����Ӷ��� 
	_RecordsetPtr m_pRecordset;//���������
	int LineConut = 0;      //��¼��ǰ�ж�������·
	const CString PATH_MAP_CACHE = _T("dbmap.cache");
	const CString PATH_MOVE_MAP_CACHE = _T("offset.mmld");
	//վ���ѯ��ر���
	int LOOKUP_TIME = 0;
	int LOOKUP_PRICE = 0;
	//������������Ƿ���Ҫ���õ�ͼ�ϵ��ѡ��
	bool begfucused = false;
	bool endfocused = false;
	//�����������·�������
	bool highlightpressed = false;

public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedMfcbuttonInfoPrice();
	afx_msg void OnClose();
	CComboBox m_combobox;
	afx_msg void OnBnClickedButtonClearhighlight();
	afx_msg void OnCbnCloseupComboHighlight();
	afx_msg void OnBnClickedButtonReload();
};
