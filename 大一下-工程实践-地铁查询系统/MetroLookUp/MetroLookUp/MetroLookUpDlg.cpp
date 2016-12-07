
// MetroLookUpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MetroLookUp.h"
#include "MetroLookUpDlg.h"
#include "afxdialogex.h"

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


// CMLUDlg �Ի���



CMLUDlg::CMLUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_METROLOOKUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMLUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HIGHLIGHT, m_combobox);
}

BEGIN_MESSAGE_MAP(CMLUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_LOOK_UP, &CMLUDlg::OnBnClickedLookUp)
	ON_EN_SETFOCUS(EDIT_BEGIN, &CMLUDlg::OnEnSetfocusBegin)
	ON_EN_SETFOCUS(EDIT_END, &CMLUDlg::OnEnSetfocusEnd)
	ON_EN_KILLFOCUS(EDIT_BEGIN, &CMLUDlg::OnEnKillfocusBegin)
	ON_EN_KILLFOCUS(EDIT_END, &CMLUDlg::OnEnKillfocusEnd)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MFCBUTTON_INFO_PRICE, &CMLUDlg::OnBnClickedMfcbuttonInfoPrice)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEARHIGHLIGHT, &CMLUDlg::OnBnClickedButtonClearhighlight)
	ON_CBN_CLOSEUP(IDC_COMBO_HIGHLIGHT, &CMLUDlg::OnCbnCloseupComboHighlight)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CMLUDlg::OnBnClickedButtonReload)
END_MESSAGE_MAP()


// CMLUDlg ��Ϣ�������

BOOL CMLUDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	csflog.Open(_T("MLU_log.txt"), CFile::modeWrite | CFile::modeCreate);
	csflog.WriteString(_T("-----in-----[FUNCTION]----OnInitDialog------BEG\n"));
	//��ʼ����ʾ��Ϣ
	SetDlgItemTextW(EDIT_BEGIN, _T("�����ѯ���"));
	SetDlgItemTextW(EDIT_END, _T("�����յ�"));
	///////////////////////////////////////////////////////////////////////////////////////
	//����
	GetDlgItem(EDIT_BEGIN)->SetFont(GetAppFont(_T("EDIT")));
	GetDlgItem(EDIT_END)->SetFont(GetAppFont(_T("EDIT")));
	//��ʼ�����ݿ�����
	//���ȵõ����ݿ��ļ���ַ
	CString dbpath,dbstr=_T("");
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
	//���ݿ�������ϣ������ȡһЩ������Ϣ
	CString fxxx;
	//�õ��ж�������·
	_variant_t vvc;
	m_pRecordset = m_pConnection->Execute(_T("SELECT LINECOUNT FROM LINECOUNT WHERE ID=3"),NULL, adCmdText);
	vvc = m_pRecordset->GetCollect(_variant_t((long)0));
	LineConut = vvc.lVal;
	fxxx.Format(_T("\t-line count: %d\n"),LineConut);
	csflog.WriteString(fxxx);
	m_pRecordset->Close();
	//���ݿ����Ӵ������
	//���ص�ͼ���
	mapDlg = new CMapDlg;
	mapDlg->Create(IDD_DIALOG_MAPS, GetDlgItem(TAB_MAP_FRAME));
	GetDlgItem(TAB_MAP_FRAME);
	CRect TabRect;
	GetDlgItem(TAB_MAP_FRAME)->GetClientRect(TabRect);
	mapDlg->SetWindowPos(NULL, TabRect.left, TabRect.top + 21, TabRect.Width() - 3, TabRect.Height() - 23, SWP_SHOWWINDOW);
	//

	csflog.WriteString(_T("-----in-----[FUNCTION]----OnInitDialog------END\n\n\n"));
	csflog.Close();
	//������ͼ�����ļ�
	if (!CreateMapCache())
	{
		MessageBoxW(_T("�޷��������ݿ��е����ݹ�����·���棡"), _T("����"), MB_OK | MB_ICONERROR);
	}
	//Ƥ��
	SkinH_Attach();
	//����ComboBox������
	for (int i = 0; i < GetLinecount(); i++)
	{
		logstr.Format(_T("%d"), i+1);
		m_combobox.AddString(logstr);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMLUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMLUDlg::OnPaint()
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
HCURSOR CMLUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMLUDlg::OnBnClickedLookUp()
{
	CString begname, endname;
	GetDlgItemTextW(EDIT_BEGIN, begname);
	GetDlgItemTextW(EDIT_END, endname);
	//���ļ��ж�ȡ��㣬�յ�վ������
	CFile fff;
	MMD_NODE mnb;
	fff.Open(PATH_MAP_CACHE, CFile::modeRead);
	bool begfound = false, endfound = false;
	while (fff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == -1)
		{
			fff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		CString name(mnb.name);
		if (name == begname)
		{
			SD_BEG.id = mnb.id;
			SD_BEG.line = mnb.line;
			SD_BEG.ltime = mnb.ltime;
			SD_BEG.rtime = mnb.rtime;
			SD_BEG.lprice = mnb.lprice;
			SD_BEG.rprice = mnb.rprice;
			strcpy_s(SD_BEG.name, mnb.name);
			SD_BEG.transfer = mnb.transfer;
			begfound = true;
		}
		if (name == endname)
		{
			SD_END.id = mnb.id;
			SD_END.line = mnb.line;
			SD_END.ltime = mnb.ltime;
			SD_END.rtime = mnb.rtime;
			SD_END.lprice = mnb.lprice;
			SD_END.rprice = mnb.rprice;
			strcpy_s(SD_END.name, mnb.name);
			SD_END.transfer = mnb.transfer;
			endfound = true;
		}
	}
	fff.Close();
	//����������յ���һ��û�鵽���ͱ���Ȼ���˳�����
	if (!(begfound && endfound)) 
	{
		MessageBoxW(_T("��������ȷ�����վ�������յ�վ��"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	if (!mapDlg->LookUpPath(SD_BEG, SD_END))
	{
		MessageBoxW(_T("��������ȷ�����վ�������յ�վ��"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	//������غ�ɢ
	CString  lsd;
	lsd.Format(_T("Ʊ�ۣ�%d Ԫ"), LOOKUP_PRICE);
	SetDlgItemTextW(IDC_MFCBUTTON_INFO_PRICE, lsd);
	lsd.Format(_T("Ԥ�ƺ�ʱ��%d ����"), LOOKUP_TIME);
	SetDlgItemTextW(IDC_MFCBUTTON_INFO_time, lsd);
	SetDlgItemTextW(STATIC_CURRENT, _T(""));
}


void CMLUDlg::OnEnSetfocusBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString raw = _T("");
	GetDlgItemTextW(EDIT_BEGIN, raw);
	if (raw == _T("�����ѯ���"))
	{
		SetDlgItemTextW(EDIT_BEGIN, _T(""));
	}
	begfucused = true;
	SetDlgItemTextW(STATIC_CURRENT, _T("����վ�����������ڵ�ͼ��ѡ��"));
}


void CMLUDlg::OnEnSetfocusEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString raw = _T("");
	GetDlgItemTextW(EDIT_END, raw);
	if (raw == _T("�����յ�"))
	{
		SetDlgItemTextW(EDIT_END, _T(""));
	}
	endfocused = true;
	SetDlgItemTextW(STATIC_CURRENT, _T("����վ�����������ڵ�ͼ��ѡ��"));
}


void CMLUDlg::OnEnKillfocusBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString raw = _T("");
	GetDlgItemTextW(EDIT_BEGIN, raw);
	if (raw == _T("") || raw == _T(" "))
	{
		SetDlgItemTextW(EDIT_BEGIN, _T("�����ѯ���"));
	}
	begfucused = false;
}


void CMLUDlg::OnEnKillfocusEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString raw = _T("");
	GetDlgItemTextW(EDIT_END, raw);
	if (raw == _T("") || raw == _T(" "))
	{
		SetDlgItemTextW(EDIT_END, _T("�����յ�"));
	}
	endfocused = false;
}

const _ConnectionPtr CMLUDlg::GetConnectionPtr()
{
	return m_pConnection;
}

const _RecordsetPtr CMLUDlg::GetRecordsetPtr()
{
	return m_pRecordset;
}

const bool CMLUDlg::CreateMapCache()
{
	//��������Ҫ�õ��ж�������·(��LineCount��)
	//Ȼ��һ���Զ�����·���ݺ�����վ������
	_RecordsetPtr LINEDATA, STATIONDATA;
	LINEDATA.CreateInstance(_T("ADODB.Recordset"));
	STATIONDATA.CreateInstance(_T("ADODB.Recordset"));
	if (!KSQL_Excute(_T("SELECT * FROM LINE_DATA"), LINEDATA))
	{
		MessageBoxW(_T("�����ݿ��ж�ȡ��·���ݳ���"), _T("����"), MB_OK | MB_ICONERROR);
		return false;
	}
	if (!KSQL_Excute(_T("SELECT * FROM STATION_DATA"), STATIONDATA))
	{
		MessageBoxW(_T("�����ݿ��ж�ȡվ�����ݳ���"), _T("����"), MB_OK | MB_ICONERROR);
		return false;
	}
	//�����ƽ�ƻ���ĵ�ͼ��ʽд���ļ�
	MMD_HEAD mhb;
	MMD_NODE mnb,SPILT_NODE;
	_variant_t vbb;
	SPILT_NODE.id = -1;
	CFile mcf;
	mcf.Open(PATH_MAP_CACHE, CFile::modeCreate | CFile::modeWrite);
	for (int i = 0; i < LineConut; i++)
	{
		//����Ҫд��һ���ָ���
		mcf.Write(&SPILT_NODE, sizeof(MMD_NODE));
		//Ȼ��д����·ͷ����
		vbb = LINEDATA->GetCollect(_T("RGB_R"));
		mhb.RGB[0] = (int)vbb.lVal;
		vbb = LINEDATA->GetCollect(_T("RGB_G"));
		mhb.RGB[1] = (int)vbb.lVal;
		vbb = LINEDATA->GetCollect(_T("RGB_B"));
		mhb.RGB[2] = (int)vbb.lVal;
		mhb.bound = 3;
		vbb = LINEDATA->GetCollect(_T("LINEID"));
		int plid = (int)vbb.lVal;
		mcf.Write(&mhb, sizeof(MMD_HEAD));
		linecount++;
		//��ʼѭ��Ѱ�����ڵ�ǰ��·��վ��
		while (!STATIONDATA->adoEOF)
		{
			vbb = STATIONDATA->GetCollect(_T("LINE"));
			int lli = (int)vbb.lVal;
			//�ж��Ƿ����ڵ�ǰ��·
			if (lli == plid)
			{
				mnb.line = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("ID"));
				mnb.id = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("STANAME"));
				USES_CONVERSION;
				char *p = W2A((LPCTSTR)vbb.lVal);
				strcpy_s(mnb.name, p);
				vbb = STATIONDATA->GetCollect(_T("LTIME"));
				mnb.ltime = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("RTIME"));
				mnb.rtime = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("LPRICE"));
				mnb.lprice = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("RPRICE"));
				mnb.rprice = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("POS_X"));
				mnb.p.x = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("POS_Y"));
				mnb.p.y = (int)vbb.lVal;
				vbb = STATIONDATA->GetCollect(_T("TRANSFER"));
				mnb.transfer = (bool)vbb.lVal;
				//д���ļ�
				mcf.Write(&mnb, sizeof(MMD_NODE));
			}
			STATIONDATA->MoveNext();
		}
		STATIONDATA->MoveFirst();
		LINEDATA->MoveNext();
	}
	mcf.Close();
	STATIONDATA->Close();
	LINEDATA->Close();
	return true;
}

void CMLUDlg::SetLookupPrice(const int price)
{
	LOOKUP_PRICE = price;
}

void CMLUDlg::SetLookupTime(const int time)
{
	LOOKUP_TIME = time;
}

void CMLUDlg::SetTrsstrData(const CString dta)
{
	SetDlgItemTextW(IDC_MFCBUTTON_INFO_TRANSFER, dta);
}

void CMLUDlg::SetLUbeg(const CString name)
{
	SetDlgItemText(EDIT_BEGIN, name);
}

void CMLUDlg::SetLUend(const CString name)
{
	SetDlgItemText(EDIT_END, name);
}

const bool CMLUDlg::IsBegFocused()
{
	return begfucused;
}

const bool CMLUDlg::IsEndFocused()
{
	return endfocused;
}

const int CMLUDlg::GetLinecount()
{
	return linecount;
}

const bool CMLUDlg::IsHighlightPressed()
{
	return highlightpressed;
}

void CMLUDlg::SetHighlightPressedStatus(const bool sta)
{
	highlightpressed = sta;
}

//�ú���������ȡһЩ�Զ�������
CFont * CMLUDlg::GetAppFont(const CString & fontName)
{
	CFont * f;
	f = new CFont;
	if (fontName == _T("EDIT"))
	{
		f->CreateFont(20, // nHeight 
			0, // nWidth 
			0, // nEscapement 
			0, // nOrientation 
			FW_BOLD, // nWeight 
			FALSE, // bItalic 
			FALSE, // bUnderline 
			0, // cStrikeOut 
			DEFAULT_CHARSET, // nCharSet 
			OUT_DEFAULT_PRECIS, // nOutPrecision 
			CLIP_DEFAULT_PRECIS, // nClipPrecision 
			DEFAULT_QUALITY, // nQuality 
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
			_T("Arial")); // lpszFac 
	}
	else if (fontName == _T("BORAD"))
	{
		f->CreateFont(25, // nHeight 
			0, // nWidth 
			0, // nEscapement 
			0, // nOrientation 
			FW_BOLD, // nWeight 
			TRUE, // bItalic 
			FALSE, // bUnderline 
			0, // cStrikeOut 
			ANSI_CHARSET, // nCharSet 
			OUT_DEFAULT_PRECIS, // nOutPrecision 
			CLIP_DEFAULT_PRECIS, // nClipPrecision 
			DEFAULT_QUALITY, // nQuality 
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
			_T("Arial")); // lpszFac 
	}
	else
	{
		f->CreateFont(10, 0, 0, 0, FW_BOLD, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	}

	return f;
}


void CMLUDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
	CRect TabRect;
	GetDlgItem(TAB_MAP_FRAME)->GetClientRect(TabRect);
	mapDlg->SetWindowPos(NULL, TabRect.left, TabRect.top + 21, TabRect.Width() - 3, TabRect.Height() - 23, SWP_SHOWWINDOW);
}


void CMLUDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//****��һ�ε���OnSize��ʱ��ؼ���δ������������Ҫ�������ж�
	if (GetDlgItem(TAB_MAP_FRAME) != NULL && IsWindow(GetDlgItem(TAB_MAP_FRAME)->m_hWnd))
	{
		CRect TabRect;
		CWnd * p = GetDlgItem(TAB_MAP_FRAME);
		p->GetClientRect(TabRect);
		mapDlg->SetWindowPos(NULL, TabRect.left, TabRect.top + 21, TabRect.Width() - 3, TabRect.Height() - 23, SWP_SHOWWINDOW);
	}
}

//�ú�������ִ��SQL��䣬
const bool CMLUDlg::KSQL_Excute(const CString cmd, _RecordsetPtr & rp)
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
const bool CMLUDlg::KSQL_Excute(const CString cmd)
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

//�ú�����������¼�����Ƿ��������
//�����������¼������
//����ֵ��������������򷵻�true������false
const bool CMLUDlg::KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp)
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

void CMLUDlg::OnBnClickedMfcbuttonInfoPrice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMLUDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}

void CMLUDlg::OnBnClickedButtonClearhighlight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_CLEARHIGHLIGHT)->EnableWindow(FALSE);
	mapDlg->ClearMapOnSceen();
	mapDlg->OnPaint();
}


void CMLUDlg::OnCbnCloseupComboHighlight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_combobox.GetCurSel();
	if (index < 0)
	{
		return;
	}
	CString selstr;
	m_combobox.GetLBText(index, selstr);
	int lid = _ttoi(selstr);
	if (lid >= GetLinecount() || lid < 0)
	{
		return;
	}
	//���濪ʼ����ָ����·
	GetDlgItem(IDC_BUTTON_CLEARHIGHLIGHT)->EnableWindow(TRUE);
	mapDlg->HighlightLine(lid);

}


void CMLUDlg::OnBnClickedButtonReload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mapDlg->ResetMap();
}





