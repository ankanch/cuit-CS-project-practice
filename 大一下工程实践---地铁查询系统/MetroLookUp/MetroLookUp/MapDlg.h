//��һ��-����ʵ��-1-�ɶ�������ѯϵͳ-�û���
//���� 2015051152 �ƿ�154
//mailto://kanchisme@gmail.com
//http://akakanch.com
//
#pragma once
#include <queue>
//�ýṹ�����������ͼͷ����
struct MMD_HEAD {		
	short RGB[3];       //��ͼ��·����ɫ
	short bound;		  //��·���ƴ�ϸ
};
//�ýṹ�����������ͼ�ڵ�����
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
//�ýṹ����������վ�����ݣ���Ҫ���ڻ�����·����ѯ
struct STATION_DATA {   
	int id = 0;			//վ��ID
	char name[20];		//վ������
	int line=0;			//վ��������·
	int ltime = 0;		//���к�ʱ
	int rtime = 0;		//���к�ʱ
	int lprice = 0;		//����Ʊ��
	int rprice = 0;		//����Ʊ��
	bool transfer = false;  //����Ƿ��ǻ���վ��
};
//�ýṹ�������������ݿ������л���վ�������
struct TRANSFER_STATION {
	int id = 0;
	bool checked = false;  //ȷ�ϵ�ǰ���Ƿ��Ѿ������ˣ�Ϊ����FindPathX�������жϷ��������
	char staname[30];		//���滻����·��
	char parentline[30];    //���游��·
};
 //�ýṹ����������Ѱ·�㷨�е�����
struct TRS {
	bool read_ahead = false;
	int id = 0;
	int fpos = 0;
	CString path;
};

struct READNODE {
	bool find = false;
	CString path = _T("");
};
// CMapDlg �Ի���

typedef std::queue<TRS> PROCESSqueue;

class CMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMapDlg)

public:
	CMapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMapDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	//�ú�������ִ��·����ѯ����·����
	bool LookUpPath(const STATION_DATA SD_BEG, const STATION_DATA SD_END);
	const bool HighlightLine(const int linenum);
	void ClearMapOnSceen();
	void ResetMap();

private:
	const bool LoadMaps(const CString & mapList,const bool not_looked_up=true);
	const bool MoveMap(const CString &mapList, const CPoint &mvet);
	const bool HaveBeenDrawed(const CString & staname);
	void ResetTransferStationDrawedStatus();
	const MMD_NODE GetCloseSTA(const CPoint pos, const bool no_zoom=true);
	void ShowMsg(const PROCESSqueue pq,const TRS trs,const CString processed,const CString others);
	void ResetMsg();

	//���º��������������ڶ�����·֮���·��Ѱ�ҵ�
	const int GetSTApos(const int staID, CFile &fff);
	const int GetFirstSTApos(const int staid,  CFile &fff);
	const int GetTRSids(const int trsid,  CFile &fff);
	//
	const MMD_NODE GetStation(const int id,  CFile &fff);
	const READNODE ReadNode(const int beg, const int target, const bool read_ahead, const CString bpath, CString &processed, PROCESSqueue & po, CFile &fff);
	const CString FindPathXX(const int beg, const int end);
	/////////////
	bool offset = false;
	CPoint lbeg;
	MMD_NODE TAG_METRO_LINE_SPILT;
	CStdioFile csflog;
	CString logstr;
	TRANSFER_STATION *DATA_TRANSFER_STATION;
	const CString STR_NOT_FOUND = _T("NOT FOUND");
	const CString PATH_LOOK_LOG = _T("pathlook.log");
	const CString PATH_MAP_CACHE = _T("dbmap.cache");
	const CString PATH_MOVE_MAP_CACHE = _T("offset.mmld");
	const CString PATH_LOOKEDUP_CACHE = _T("lookup.cache");
	const CString PATH_ZOOMED_CACHE = _T("zoomed.cache");
	const CString PATH_TRANSFER_STATION_CACHE = _T("ts.cache");  //���ǻ���վ��Ļ����ļ�Ŀ¼
	CFile xfx;
	CString DrawedTransferStation[30] = {'\0'};
	int GV_TRSIDS[5] = { 0 };
	int drawedtsa_no = 0;
	bool firstrun = true;
	double ZOOMX = 1;
	bool zoomed = false;

	_RecordsetPtr m_RecordsetPtr;
	//��ͼ�����ر���
	bool begpress = false;
	bool endpress = false;
	CString begpressname;
	CString endpressname;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
