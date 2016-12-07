
// MetroLookup_LineDrawerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MetroLookup_LineDrawer.h"
#include "MetroLookup_LineDrawerDlg.h"
#include "afxdialogex.h"
#include "MDDlg.h"
#include "NewLineDlg.h"
#include "AddStationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMLLDDlg �Ի���



CMLLDDlg::CMLLDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_METROLOOKUP_LINEDRAWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMLLDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LINE_COUNT, m_static_linecount);
}

BEGIN_MESSAGE_MAP(CMLLDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON_LOAD_MAP, &CMLLDDlg::OnBnClickedMfcbuttonLoadMap)
	ON_BN_CLICKED(IDC_MFCBUTTON_ADD_STATION, &CMLLDDlg::OnBnClickedMfcbuttonAddStation)
	ON_BN_CLICKED(IDC_MFCBUTTON_NEW_LINE, &CMLLDDlg::OnBnClickedMfcbuttonNewLine)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &CMLLDDlg::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDC_MFCBUTTON_SAVE_MAP, &CMLLDDlg::OnBnClickedMfcbuttonSaveMap)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MFCBUTTON_LOAD_BLUEPRINT, &CMLLDDlg::OnBnClickedMfcbuttonLoadBlueprint)
	ON_BN_CLICKED(IDC_BUTTON_ADD_END, &CMLLDDlg::OnBnClickedButtonAddEnd)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BEG_STATION, &CMLLDDlg::OnBnClickedButtonAddBegStation)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CMLLDDlg::OnBnClickedButtonUndo)
END_MESSAGE_MAP()


// CMLLDDlg ��Ϣ�������

BOOL CMLLDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	mddlg = new CMDDlg;
	mddlg->Create(IDD_DIALOG_MAP_DRAWER, GetDlgItem(IDC_TAB_MAP_FRAME));
	CRect TabRect;
	GetDlgItem(IDC_TAB_MAP_FRAME)->GetClientRect(TabRect);
	mddlg->SetWindowPos(NULL, TabRect.left, TabRect.top + 21, TabRect.Width() - 3, TabRect.Height() - 23, SWP_SHOWWINDOW);
	GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD_END)->EnableWindow(FALSE);
	CMLLDDlg::OnBnClickedButtonLock();
	//���ȵõ����ݿ��ļ���ַ
	CString dbpath, dbstr = _T("");
	CStdioFile csf;
	csf.Open(_T("config.cfg"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead);
	csf.ReadString(dbpath);
	csf.Close();
	dbstr = _T("Provider=Microsoft.ACE.OLEDB.12.0;\
Data Source=") + dbpath + _T(";");
	//�������ݿ�
	try
	{
		CoInitialize(NULL);
		m_pConnection = _ConnectionPtr(__uuidof(Connection));
		m_pConnection->ConnectionString = dbstr.GetBuffer(0);//���������ϰ������дProvider=Microsoft.Jet.OLEDB.4.0;Data
												//Source= MyAccess.mdb�ǲ��Եģ�����дֻ�ʺ�2007����ǰ��access����·�������\����ĳ�
		m_pConnection->Open("", "", "", adConnectUnspecified);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ�����ʧ�ܣ�"));
		return FALSE;
	}
	//�õ��Ѿ����ڵļ�¼������վ��ID���������������
	_variant_t rca;
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));
	m_pRecordset = m_pConnection->Execute(_T("SELECT COUNT(*)FROM STATION_DATA"), &rca, adCmdText);
	_variant_t vvt = (long)0;
	_variant_t vvc = m_pRecordset->GetCollect(vvt);
	CString fxxx;
	LineStationCount = vvc.lVal;
	//�õ��ж�������·
	if (!KSQL_Excute(_T("SELECT LINECOUNT FROM LINECOUNT WHERE ID=3"),m_pRecordset))
	{
		AfxMessageBox(_T("���ݿ��ȡ����"));
	}
	if (!KSQL_CheckRecordSetGotValue(m_pRecordset))
	{
		AfxMessageBox(_T("���ݿ��ȡ����:δ��ѯ��ָ������"));
		LineConut = 0;
	}
	else
	{
		vvc = m_pRecordset->GetCollect(_variant_t((long)0));
		LineConut = vvc.lVal;
	}
	fxxx.Format(_T("վ������: %d\n��·����: %d"), LineStationCount, LineConut);
	m_pRecordset->Close();
	//���ݿ����Ӵ������
	m_static_linecount.SetWindowTextW(fxxx);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMLLDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMLLDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMLLDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMLLDDlg::OnBnClickedMfcbuttonLoadMap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Metro Line Data Files (*.mld)|*.mld|All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //�ļ�����������FilePathName��
		filename = FilePathName;

		filename = filename.MakeReverse();
		filename = filename.Mid(0, filename.Find(_T("\\"), 0));
		filename = filename.MakeReverse();
		GetDlgItem(IDC_MFCBUTTON_NEW_LINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCBUTTON_LOAD_MAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(TRUE);

		filename = FilePathName;
		NO_DRAW = false;
		CMLLDDlg::OnBnClickedButtonLock();
		mddlg->OnOpenExistFile(filename);

		return;
	}
	else
	{
		return;
	}

}


void CMLLDDlg::OnBnClickedMfcbuttonAddStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddStationDlg dlg;
	dlg.DoModal();
}



void CMLLDDlg::OnBnClickedMfcbuttonNewLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CNewLineDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		MHE.bound = 3;
		CRect TabRect;
		GetDlgItem(IDC_TAB_MAP_FRAME)->GetClientRect(TabRect);
		mddlg->SetWindowPos(NULL, TabRect.left, TabRect.top + 21, TabRect.Width() - 3, TabRect.Height() - 23, SWP_SHOWWINDOW);
		GetDlgItem(IDC_MFCBUTTON_NEW_LINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_MFCBUTTON_LOAD_MAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(FALSE);
		NO_DRAW = false;
		CFile fff;
		fff.Open(STRING_BUFFER_FILENEMA, CFile::modeCreate | CFile::modeWrite);
		fff.Close();
		MessageBoxW(_T("----------------------------\nΪ�˷�ֹ���������������Ĭ�Ͽ���\n----------------------------"), _T("��ʾ"), MB_ICONEXCLAMATION | MB_OK);
	}
}

const MMD_HEAD CMLLDDlg::GetHead()
{

	return MHE;
}


const CString CMLLDDlg::GetFileName()
{
	return filename;
}

const STATION_DATA CMLLDDlg::GetStationData()
{
	return SD;
}

void CMLLDDlg::SetSatationData(const STATION_DATA sdta)
{
	SD = sdta;
}

const bool CMLLDDlg::IsAddStation()
{
	return add_station;
}

const bool CMLLDDlg::IsAddBegStation()
{
	return GV_BOOL_BEG_STATION_ADDED;
}

const bool CMLLDDlg::IsAddEndStation()
{
	return GV_BOOL_END_STATION_ADDED;
}

void CMLLDDlg::SetAddBegStationStatus(const bool b)
{
	GV_BOOL_BEG_STATION_ADDED = b;
}

void CMLLDDlg::SetAddEndStationStatus(const bool b)
{
	GV_BOOL_END_STATION_ADDED = b;
}

bool CMLLDDlg::SetAddStationStatus(const bool status)
{
	add_station = status;
	return add_station;
}

void CMLLDDlg::LockAll()
{
	GetDlgItem(IDC_BUTTON_LOCK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCBUTTON_LOAD_MAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCBUTTON_NEW_LINE)->EnableWindow(FALSE);
}

void CMLLDDlg::SetTransferStationStatus(const bool st)
{
	add_station_is_transfer = st;
}

const bool CMLLDDlg::IsTransferStation()
{
	return add_station_is_transfer;
}

bool CMLLDDlg::IsDrawLock()
{
	return draw_lock;
}

bool CMLLDDlg::NoDrawStatus()
{
	return NO_DRAW;
}

const bool CMLLDDlg::KSQL_Excute(const CString cmd, _RecordsetPtr & rp)
{
	CString CMD = cmd;
		try
		{
			rp = GetConnectionPtr()->Execute(CMD.GetBuffer(0), NULL, adCmdText);
		}
		catch (_com_error e)
		{
			MessageBoxW(_T("������Ϣ��") + e.Description(), _T("���ݿ��ȡ����"), MB_OK | MB_ICONERROR);
			return false;
		}
	return true;
}
const bool CMLLDDlg::KSQL_Excute(const CString cmd)
{
	CString CMD = cmd;
		try
		{
			GetConnectionPtr()->Execute(CMD.GetBuffer(0), NULL, adCmdText);
		}
		catch (_com_error e)
		{
			MessageBoxW(_T("������Ϣ��") + e.Description(), _T("���ݿ��ȡ����"), MB_OK | MB_ICONERROR);
			return false;
		}
	return true;
}

const bool CMLLDDlg::KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp)
{
	_variant_t vt;
	try
	{
		vt = rp->GetCollect((long)0);  //ֻ�жϵ�һ��¼��
	}
	catch (_com_error e)
	{
		return false;
	}
	return true;
}

const _ConnectionPtr CMLLDDlg::GetConnectionPtr()
{
	return m_pConnection;
}

const _RecordsetPtr CMLLDDlg::GetRecordsetPtr()
{
	return m_pRecordset;
}

const int CMLLDDlg::GetLineStationCount()
{
	return LineStationCount;
}

const int CMLLDDlg::GetLineConut()
{
	return LineConut;
}

void CMLLDDlg::SetFileName(const CString fn)
{
	filename = fn;
}

void CMLLDDlg::SetStaBegName(const CString ne)
{
	STA_NAME_BEG = ne;
}

void CMLLDDlg::SetStaEndName(const CString ne)
{
	STA_NAME_END = ne;
}

void CMLLDDlg::SetTermPrice(const int price)
{
	STA_TERM_PRICE = price;
}

void CMLLDDlg::SetLineColor(const COLORREF clr)
{
	MHE.RGB[0] = GetRValue(clr);
	MHE.RGB[1] = GetGValue(clr);
	MHE.RGB[2] = GetBValue(clr);
}

const CString CMLLDDlg::GetStaBegName()
{
	return STA_NAME_BEG;
}

const CString CMLLDDlg::GetStaEndName()
{
	return STA_NAME_END;
}

const CString CMLLDDlg::GetTermPrice()
{
	CString bufx;
	bufx.Format(_T("%d"), STA_TERM_PRICE);
	return bufx;
}


void CMLLDDlg::OnBnClickedButtonLock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!draw_lock)
	{
		SetDlgItemTextW(IDC_BUTTON_LOCK, _T("��������"));
		draw_lock = true;
		GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(FALSE);
	}
	else
	{
		SetDlgItemTextW(IDC_BUTTON_LOCK, _T("��������"));
		draw_lock = false;
		if (GV_BOOL_BEG_STATION_ADDED)
		{
			GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(TRUE);
			
		}
		if (!GV_BOOL_BEG_STATION_ADDED)
		{
			GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(TRUE);
		}
	}
}


void CMLLDDlg::OnBnClickedMfcbuttonSaveMap()
{
	CStdioFile csflog;
	csflog.Open(_T("db_update_log.txt"), CFile::modeCreate | CFile::modeWrite);
	csflog.WriteString(_T("start update datebase\n"));
	GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->EnableWindow(FALSE);
	//���ȴ����ǽ����ݿ��е���·����+1
	KSQL_Excute(_T("UPDATE LINECOUNT SET LINECOUNT=LINECOUNT+1"));
	CString buf;
	LineConut++;
	buf.Format(_T("%d,'"), LineConut);
	//Ȼ���line.cache�ļ��ж�ȡվ�����ݣ�Ȼ��д�����ݿ�
	CFile ff;
	ff.Open(STRING_BUFFER_FILENEMA, CFile::modeReadWrite);
	MMD_HEAD mhb;
	ff.Read(&mhb, sizeof(MMD_HEAD));
	//Ȼ�����ǰ�ͷ����д�����ݿ⣬��������ȡ��ͼ��
	CString SQLstr = _T("INSERT INTO LINE_DATA(LINEID,RGB_R,RGB_G,RGB_B) "), SQLval = _T("");
	SQLval.Format(_T(" VALUES(%d,%d,%d,%d) "), LineConut,mhb.RGB[0], mhb.RGB[1], mhb.RGB[2]);
	SQLstr += SQLval;
	csflog.WriteString(_T("UPDATE line_data : SQLstr = \n")+SQLstr +_T("\n"));
	KSQL_Excute(SQLstr);
	MMD_NODE mnb;
	while (ff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		//���������ݿ�
		SQLstr = _T(""), SQLval = _T("");
		SQLstr = _T("INSERT INTO STATION_DATA(ID,STANAME,LINE,LTIME,RTIME,LPRICE,RPRICE,POS_X,POS_Y,TRANSFER) ");
		SQLval.Format(_T(" VALUES(%d,'%s',%d,%d,%d,%d,%d,%d,%d,%d) "),mnb.id,CString(mnb.name),mnb.line,mnb.ltime,mnb.rtime,mnb.lprice,mnb.rprice,mnb.p.x,mnb.p.y,(int)mnb.transfer);
		SQLstr += SQLval;
		csflog.WriteString(_T("UPDATE station_data : SQLstr= \n")+SQLstr+_T("\n"));
		KSQL_Excute(SQLstr);
		//����ǻ���վ��
		if (mnb.transfer)
		{
				////�����ж��Ƿ����ͬ����վ��,�������������TRANSFER_STATION����ӣ�Ȼ���������Ӧ����·ID
				//������ڣ����ѯ��ǰվ����TRANSFER_STATION���Ƿ���ڵ�ǰ��·ID
				CString SQLstr;
				CString LINEIDBUF;
				LINEIDBUF.Format(_T("%d"), mnb.line);
				SQLstr = _T("SELECT * FROM TRANSFER_STATION WHERE STANAME='") + CString(mnb.name) + _T("'");
				int iib = 0;
				int x = 1;
				m_pRecordset.CreateInstance(_T("ADODB.Recordset"));
				try {
					m_pRecordset = GetConnectionPtr()->Execute(SQLstr.GetBuffer(0), NULL, adCmdText);
					_variant_t vt = m_pRecordset->GetCollect((long)0);
					iib = (int)vt.lVal;
				}
				catch (_com_error e)   //���������˵����վ��Ŀǰ�ǵ�һ�����Ϊ����վ��
				{
					SQLstr = _T("INSERT INTO TRANSFER_STATION(STANAME,PARENTLINE) VALUES('") + CString(mnb.name) + _T("','") + LINEIDBUF + _T("')");
					GetConnectionPtr()->Execute(SQLstr.GetBuffer(0), NULL, adCmdText);
					x = 0;
				}
				if (x) //TRANSFER_STATION���Ѿ�������ͬ���ֵĻ���վ�㣬��ô�����жϵ�ǰվ�����·ID�Ƿ���PARENTLINE�ֶ���
				{
					SQLstr = _T("SELECT PARENTLINE FROM TRANSFER_STATION WHERE STANAME='") + CString(mnb.name) + _T("'");
					m_pRecordset = GetConnectionPtr()->Execute(SQLstr.GetBuffer(0), NULL, adCmdText);
					_variant_t vt = m_pRecordset->GetCollect((long)0);
					CString PLD = (LPCTSTR)vt.lVal;
					if (PLD.Find(LINEIDBUF) < 0)  //δ�ҵ���˵��������Ҫ��ӵ����ݿ���
					{
						CString LXL = PLD + LINEIDBUF;
						SQLstr = _T("UPDATE TRANSFER_STATION SET PARENTLINE = '") + LXL + _T("' WHERE PARENTLINE= '") + PLD + _T("'");
						try
						{
							GetConnectionPtr()->Execute(SQLstr.GetBuffer(0), NULL, adCmdText);
						}
						catch (_com_error e)
						{
							MessageBoxW(_T("�������ݿ�ʧ��\n����ԭ��") + e.Description(), _T("����"), MB_ICONERROR | MB_OK);
						}
					}
				}
		}
	}
	ff.Close();
	//����ͳ�����ݵ���ʾ
	int a = 0, b = 0;
	KSQL_Excute(_T("SELECT COUNT(*)FROM STATION_DATA"),m_pRecordset);
	_variant_t vvc = m_pRecordset->GetCollect(_variant_t((long)0));
	a = (int)vvc.lVal;
	KSQL_Excute(_T("SELECT LINECOUNT FROM LINECOUNT WHERE ID=3"), m_pRecordset);
	vvc = m_pRecordset->GetCollect(_variant_t((long)0));
	m_pConnection->Close();
	b = (int)vvc.lVal;
	CString fxxx;
	fxxx.Format(_T("վ������: %d\n��·����: %d"), a, b);
	m_static_linecount.SetWindowTextW(fxxx);
	HAVE_SYNC = true;

	csflog.Close();
}


void CMLLDDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (NO_DRAW)
	{
		CDialogEx::OnClose();
	}
	else
	{
		if (!HAVE_SYNC)
		{
			if (MessageBoxW(_T("��ͼ�ļ��Ѿ��������޸ĵ���δͬ����ȷ���˳���\nδͬ���򲻻���Ч��"), _T("��ʾ"), MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK)
			{
				CDialogEx::OnClose();
			}
		}
		else
		{
			CDialogEx::OnClose();
		}
	}
}


void CMLLDDlg::OnBnClickedMfcbuttonLoadBlueprint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("��ͼ�ļ� (*.mmld)|*.mmld|��ͼ�ļ� (*.cache)|*.cache||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //�õ���ͼ·��
		mddlg->OnOpenExistFile(FilePathName, true);
		return;
	}
	else
	{
		return;
	}
}


void CMLLDDlg::OnBnClickedButtonAddEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GV_BOOL_END_STATION_ADDED = true;
	GetDlgItem(IDC_BUTTON_ADD_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->EnableWindow(TRUE);
	//(CMFCButton*)GetDlgItem(IDC_MFCBUTTON_SAVE_MAP)->SetBack
}


void CMLLDDlg::OnBnClickedButtonAddBegStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GV_BOOL_BEG_STATION_ADDED = true;
	GetDlgItem(IDC_BUTTON_ADD_BEG_STATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD_END)->EnableWindow(TRUE);
	GetDlgItem(IDC_MFCBUTTON_ADD_STATION)->EnableWindow(TRUE);
}


void CMLLDDlg::OnBnClickedButtonUndo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mddlg->Undo();
}
