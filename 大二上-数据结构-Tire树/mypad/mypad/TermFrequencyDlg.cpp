// TermFrequencyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mypad.h"
#include "TermFrequencyDlg.h"
#include "afxdialogex.h"


// CTermFrequencyDlg 对话框

IMPLEMENT_DYNAMIC(CTermFrequencyDlg, CDialogEx)

CTermFrequencyDlg::CTermFrequencyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TERMFREQUENCY, pParent)
{

}

CTermFrequencyDlg::~CTermFrequencyDlg()
{
}

void CTermFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TERMFREQUENCY, m_tflist);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_tipsx);
}


BEGIN_MESSAGE_MAP(CTermFrequencyDlg, CDialogEx)
END_MESSAGE_MAP()


// CTermFrequencyDlg 消息处理程序


BOOL CTermFrequencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_tflist.InsertColumn(0, "单词",LVCFMT_CENTER, 140);
	m_tflist.InsertColumn(1, "频次", LVCFMT_CENTER, 60);
	m_tflist.InsertColumn(2, "频率", LVCFMT_CENTER, 60);

	CString buf;
	TFDLIST tl = pt->GetTermFrequencyList();
	CString longest;
	int len = 0;
	longest = tl.at(0).first;
	len = longest.GetLength();
	int sum = 0;
	for (int i = 0; i < tl.size(); i++)
	{
		TFD tfd = tl.at(i);
		if (tfd.first.GetLength() > len)
		{
			longest = tfd.first;
			len = longest.GetLength();
		}
		buf.Format("%s,%d\n", tfd.first, tfd.second);
		m_tflist.InsertItem(i,buf.Mid(2));
		buf.Format("%d", tfd.second);
		m_tflist.SetItemText(i, 0, tfd.first.Mid(2));
		m_tflist.SetItemText(i, 1, buf);
		sum += tfd.second;
	}
	for (int i = 0; i < tl.size(); i++)
	{
		double t = tl.at(i).second / sum* 100;
		buf.Format("%.2f", t);
		m_tflist.SetItemText(i, 2, buf);
	}
	CString pp;
	pp.Format("共 %d 个单词，其中最长的为 %s 长度为 %d ，频率最高的为 %s ,共出现 %d 次。", tl.size(),longest.Mid(2) ,len, tl.at(0).first.Mid(2), tl.at(0).second);
	m_tipsx.SetWindowTextA(pp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CTermFrequencyDlg::setTrie(CTrieTree * tt)
{
	pt = tt;
}

void CTermFrequencyDlg::setRaw(CString raw)
{
	rawdata = raw;
}
