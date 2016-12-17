// TrieGraph.cpp : 实现文件
//

#include "stdafx.h"
#include "mypad.h"
#include "TrieGraph.h"
#include "afxdialogex.h"


// CTrieGraph 对话框

IMPLEMENT_DYNAMIC(CTrieGraph, CDialogEx)

CTrieGraph::CTrieGraph(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TRIE_GRAPH, pParent)
{

}

CTrieGraph::~CTrieGraph()
{
}

void CTrieGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTrieGraph, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTrieGraph 消息处理程序


void CTrieGraph::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
}
