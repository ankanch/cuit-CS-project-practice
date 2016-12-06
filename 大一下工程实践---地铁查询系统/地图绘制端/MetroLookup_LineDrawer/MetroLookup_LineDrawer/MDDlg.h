#pragma once


 struct MMD_HEAD {
	short RGB[3];       //��ͼ��·����ɫ
	short bound;		  //��·���ƴ�ϸ
};
 struct MMD_NODE {
	CPoint p;  		 //��·��ÿ�����λ��
	int id;			//���ԓ��Ϊվ̨����������б�ţ�����Ϊ0
	char name[30];   //����վ����
	int line = 0;     //���游��·
	int ltime = 0;   //����ʱ��
	int rtime = 0;
	int lprice = 0;   //����Ʊ��
	int rprice = 0;
	bool transfer = false;  //����Ƿ��ǻ���վ��
};
// CMDDlg �Ի���

class CMDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMDDlg)

public:
	CMDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMDDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAP_DRAWER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	const bool OnOpenExistFile(const CString filename, const bool blueprint = false);
	const void Undo();
private:
	CPoint lbeg;
	CPoint lend;
	int station_id = 0;
	CString LINEIDBUF = _T("");
	int lineid = 0;
	bool RunOnceFuncTimer = true;
	bool FIRST_TIME_L_BUTTON_DOWN = true;
	//����2������������һ��������·�����վ���յ�վ��λ��
	//��2���������ڵ�һ������WM_LBUTTONUP��Ϣ��ʱ��д���ļ�
	//���ݿ���»ᷢ���ڵ�һ����ӦWM_LBUTTONDOWN��WM_LBUTTONUP��ʱ��
	MMD_NODE STA_BEG;

	MMD_HEAD MAP_HEAD;
    MMD_NODE TAG_METRO_LINE_SPILT;
	//�������������������жϷ�Χ
	const int RANGE_X = 111;
	const int RANGE_Y = 111;
	bool CheckStationVaild(const CPoint p,int *offbyte=nullptr);//�ú������������ӵ�վ���Ƿ�Ϸ�
	const bool SetStationANDWrite(const CPoint p,const int stationid,const int offbyte=0); //�ú�������������û������������CPoint
	const bool LoadMaps(const CString & path, const bool load_unfinished=true, const bool load_bule_print=false);
	const bool KSQL_Excute(const CString cmd);
	const bool KSQL_Excute(const CString cmd, _RecordsetPtr & rp);
	const bool KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp);
	//ִ��һ�Σ��Ա�Ӹ����ڻ�ùؼ�����
	void RunOnceFunction();
	CStdioFile csflog;
	CString logstr;
	const CString STRING_BUFFER_FILENEMA = _T("line.cache");
	//���ݿ���ر���
	_RecordsetPtr m_RecordsetPtr;
};
