
// MetroLookup_LineDrawerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcolorbutton.h"
#include "MDDlg.h"
#include "afxwin.h"

struct STATION_DATA {
	CString name;
	CString L_time;
	CString R_time;
	CString L_price;
	CString R_price;
};
// CMLLDDlg �Ի���
class CMLLDDlg : public CDialogEx
{
// ����
public:
	CMLLDDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_METROLOOKUP_LINEDRAWER_DIALOG };
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
	afx_msg void OnBnClickedMfcbuttonLoadMap();
	afx_msg void OnBnClickedMfcbuttonAddStation();
	afx_msg void OnBnClickedMfcbuttonNewLine();

	const MMD_HEAD GetHead();//�õ�Ԥ���ͷ����
	const CString GetFileName(); //�õ�Ҫ������ļ���
	const STATION_DATA GetStationData();//�õ�վ������
	void SetSatationData(const STATION_DATA sdta); //����վ������
	const bool IsAddStation();
	const bool IsAddBegStation();
	const bool IsAddEndStation();
	void SetAddBegStationStatus(const bool b);
	void SetAddEndStationStatus(const bool b);
	bool SetAddStationStatus(const bool status);  //�������ø����ڵ�add_station����
	void LockAll();  //������յ�վ�Ļ��ƺ�����Ҫ������ͼ
	void SetTransferStationStatus(const bool st);
	const bool IsTransferStation();
	bool IsDrawLock();  //�ж��Ƿ���ڻ滭lock״̬
	bool NoDrawStatus(); //�õ�����״̬
	const bool KSQL_Excute(const CString cmd);
	const bool KSQL_Excute(const CString cmd, _RecordsetPtr & rp);
	const bool KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp);
	CMFCColorButton m_color_button;
	//���ݿ�������
	//�õ�����access���ݿ�����Ӷ���
	const _ConnectionPtr GetConnectionPtr();
	//�õ����������
	const _RecordsetPtr GetRecordsetPtr();
	//�õ�ĳ��·���һ��վ���id
	const int GetLineStationCount();
	//�õ���ǰ�ж�������·
	const int GetLineConut();

	//����ĺ����������á�վ��ȫ�֡�����
	
	//�����ļ���
	void SetFileName(const CString fn);
	//������ʼվ������
	void SetStaBegName(const CString ne);
	//�����յ�վ����
	void SetStaEndName(const CString ne);
	//����ȫ��Ʊ��
	void SetTermPrice(const int price);
	//������·��ɫ
	void SetLineColor(const COLORREF clr);
	
	//����ĺ��������õ�վ���ȫ�ֱ���

	//�õ���ʼվ������
	const CString GetStaBegName();
	//�õ��յ�����
	const CString GetStaEndName();
	//�õ�ȫ��Ʊ��
	const CString GetTermPrice();
private:
	//������һЩ������¼״̬�ı���
	bool GV_BOOL_BEG_STATION_ADDED = false;
	bool GV_BOOL_END_STATION_ADDED = false;
	const CString STRING_BUFFER_FILENEMA = _T("line.cache");
	///վ��ȫ�ֱ������忪ʼ
	CString filename;
	CString STA_NAME_BEG;
	CString STA_NAME_END;
	int STA_TERM_PRICE;
	///վ��ȫ�ֱ��˶������
	bool add_station = false;
	bool add_station_is_transfer = false;
	STATION_DATA SD;
	CMDDlg *mddlg;
	MMD_HEAD MHE;
	bool draw_lock = false;
	bool NO_DRAW = true;
	bool HAVE_SYNC = false;
	//���ݿ�������
	_ConnectionPtr m_pConnection;//����access���ݿ�����Ӷ��� 
	_RecordsetPtr m_pRecordset;//���������
	int LineStationCount = 0;   //��¼ÿ����·�ж���վ�㣬����ʵ��ĳ��·���һ��վ���id��
	int LineConut = 0;      //��¼��ǰ�ж�������·
	
public:
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedMfcbuttonSaveMap();


	afx_msg void OnClose();
	CStatic m_static_linecount;
	afx_msg void OnBnClickedMfcbuttonLoadBlueprint();
	afx_msg void OnBnClickedButtonAddEnd();
	afx_msg void OnBnClickedButtonAddBegStation();
	afx_msg void OnBnClickedButtonUndo();
};
