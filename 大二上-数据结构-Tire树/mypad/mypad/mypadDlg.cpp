
// mypadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mypad.h"
#include "mypadDlg.h"
#include "TermFrequencyDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMypadDlg dialog


IMPLEMENT_DYNAMIC(CMypadDlg, CDialogEx);

CMypadDlg::CMypadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMypadDlg::~CMypadDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	delete triegraphdlg;
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMypadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_edit);
}

BEGIN_MESSAGE_MAP(CMypadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_CONTENT, &CMypadDlg::OnEnChangeEditContent)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENU_SHOW_TRIE, &CMypadDlg::OnMenuShowTrie)
	ON_COMMAND(ID_MENU_TF, &CMypadDlg::OnMenuTf)
	ON_COMMAND(ID_MENU_SORT, &CMypadDlg::OnMenuSort)
END_MESSAGE_MAP()


// CMypadDlg message handlers

BOOL CMypadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	last_sel_pos = 0;
	ins_avb = false;
	del_pressed = false;
	lastword = "";
	f = new CFont;
	f->CreateFont(22, // nHeight 
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
	m_edit.SetFont(f);
	//
	triegraphdlg = new CTrieGraph();
	triegraphdlg->Create(IDD_DIALOG_TRIE_GRAPH, this);
	//
	CStdioFile ff;
	ff.Open("log.txt",CFile::modeWrite);
	ff.SetLength(0);
	ff.Close();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMypadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMypadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMypadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CMypadDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMypadDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMypadDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMypadDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMypadDlg::OnEnChangeEditContent()
{
	///*/
	CString editstr = "";
	m_edit.GetWindowTextA(editstr);
	CTrieTree tpp;
	if (ins_avb == true)   //如果按下了空格，判断之前是否有未插入Trie的单词
	{
		ins_avb = false;
		//CString editstr = "";
		//m_edit.GetWindowTextA(editstr);
		WORDSTACK ws = RetriveWords(editstr);
		int i = 0;
		while (!ws.empty())
		{
			if (tpp.Search(ws.top(), tpp.GetRoot()) == false)
			{
				tpp.Insert(ws.top(), tpp.GetRoot());
			}
			else
			{
				tpp.IncreaseWordCount();
			}
			ws.pop();
			i++;
		}
		triegraphdlg->setTrieTree(&tpp);
		triegraphdlg->UpdateGraph();
		return;
	}
	if (del_pressed == true)
	{
		del_pressed = false;
		if (editstr.Right(1) == ' ')
		{
			WORDSTACK ws = RetriveWords(editstr);
			int i = 0;
			//CTrieTree tpp;
			while (!ws.empty())
			{
				if (tpp.Search(ws.top(), tpp.GetRoot()) == false)
				{
					tpp.Insert(ws.top(), tpp.GetRoot());
				}
				else
				{
					tpp.IncreaseWordCount();
				}
				ws.pop();
				i++;
			}
			triegraphdlg->setTrieTree(&tpp);
			triegraphdlg->UpdateGraph();
			return;
		}
	}
	if (false)
	{
		//下面这段代码用来测试智能提示
		//逻辑：每次编辑框内容改变的时候建立一次Trie树，然后再在Trie树查找是否有部分匹配的单词
		//当然，建立Trie树之前要判断是否可以建立（即存在空格）
		WORDSTACK ws = RetriveWords(editstr);
		int i = 0;
		CTrieTree tpp;
		while (!ws.empty())
		{
			if (tpp.Search(ws.top(), tpp.GetRoot()) == false)
			{
				tpp.Insert(ws.top(), tpp.GetRoot());
			}
			else
			{
				tpp.IncreaseWordCount();
			}
			ws.pop();
			i++;
		}
		WORDSTACK wss;
		CString partword = editstr.Mid(editstr.ReverseFind(' '));
		tpp.Suggest(partword, "", wss, tpp.GetRoot());
		CString pp;
		while (wss.empty())
		{
			pp += " " + wss.top();
			wss.pop();
		}
		SetDlgItemTextA(IDC_STATIC_TIPS, pp);
	}
}

const WORDSTACK  CMypadDlg::RetriveWords(const CString raw)
{
	WORDSTACK ws;
	
	CString word = "",mm;
	int spacebeg = 0, spaceend = -1;
	for (int i = 0; i < raw.GetLength(); i++)
	{
		if (raw[i] == ' ' && spaceend == -1)
		{
			spacebeg = i;
			continue;
		}
		else if (raw[i] != ' ')
		{
			spaceend = -2;
			continue;
		}
		if (raw[i] == ' ' && spaceend == -2)
		{
			spaceend = i;
		}
		if (!spacebeg)
		{
			word = raw.Mid(spacebeg, spaceend - spacebeg);
		}
		else
		{
			word = raw.Mid(spacebeg+1, spaceend - spacebeg-1);
		}
		spacebeg = spaceend;
		spaceend = -1;
		ws.push(word);
		//mm += "/" + word + "/\n";
	}
	//MessageBoxA(mm);
	return ws;
}


BOOL CMypadDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_SPACE)
		{
			ins_avb = true;
		}
		else if (pMsg->wParam == VK_BACK)
		{
			del_pressed = true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMypadDlg::OnMenuShowTrie()
{
	// TODO: 在此添加命令处理程序代码
	triegraphdlg->setTrieTree(&triedata);
	triegraphdlg->ShowWindow(SW_SHOW);
	triegraphdlg->InitGraph(&triedata);
}



void CMypadDlg::OnMenuTf()
{
	// TODO: 在此添加命令处理程序代码
	CTermFrequencyDlg tfdlg;
	CString raw;
	m_edit.GetWindowTextA(raw);
	WORDSTACK ws = RetriveWords(raw);
	int i = 0;
	CTrieTree *tpp = new CTrieTree;
	while (!ws.empty())
	{
		if (tpp->Search(ws.top(), tpp->GetRoot()) == false)
		{
			tpp->Insert(ws.top(), tpp->GetRoot());
		}
		else
		{
			tpp->IncreaseWordCount();
		}
		ws.pop();
		i++;
	}
	tfdlg.setTrie(tpp);
	tfdlg.DoModal();
}


void CMypadDlg::OnMenuSort()
{
	// TODO: 在此添加命令处理程序代码
	CString raw;
	m_edit.GetWindowTextA(raw);
	WORDSTACK ws = RetriveWords(raw);
	int i = 0;
	CTrieTree *tpp = new CTrieTree;
	while (!ws.empty())
	{
		if (tpp->Search(ws.top(), tpp->GetRoot()) == false)
		{
			tpp->Insert(ws.top(), tpp->GetRoot());
		}
		else
		{
			tpp->IncreaseWordCount();
		}
		ws.pop();
		i++;
	}
	CString sortstr = tpp->Sort();
	delete tpp;
	m_edit.SetWindowTextA(sortstr);
	//MessageBoxA(sortstr);
}
