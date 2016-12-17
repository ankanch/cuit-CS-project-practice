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
	delete[] graphdata->nodeslist;
	delete graphdata;
}

void CTrieGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CTrieGraph::ConvertTrieToDrawable( CTrieTree * trie)
{
	const int*llcl = trie->GetLLCList();
	int levelcount = trie->GetLevelCount();
	int nodes = trie->GetNodesCount();
	graphdata->nodessum = nodes;
	graphdata->level = levelcount;
	/////////////////////////////////////////////////////////////////////
	CString xxx;
	xxx.Format("<<<<llcl sum=%d>>>>\n\n", levelcount);
	for (int i = 0; i <= levelcount; i++)
	{
		CString buf = "";
		buf.Format("llcl %d:\tcount = %d\n", i + 1, llcl[i]);
		xxx += buf;
	}
	CString buf = "";
	buf.Format("\nlevelcount=%d\nnodescount=%d(include root)\n", levelcount, nodes);
	xxx += buf;
	MessageBoxA(xxx, "xxx data");
	/////////////////////////////////////////////////////////////////////
	//计算相关必要绘图变量
	CRect drawarea;
	this->GetClientRect(drawarea);
	graphdata->y_split = drawarea.Width() / (levelcount + 4);
	//接下来计算x间隔（以最大的为算，对齐中轴线）
	if (nodes > 2)
	{
		int max = llcl[1];
		for (int i = 1; i <= levelcount; i++)
		{
			if (max <= llcl[i])
			{
				max = llcl[i];
			}
		}
		graphdata->x_split = drawarea.Width() / (max + 4);
	}
	//开始执行点集的转换
	PWORDNODE lastlevel = trie->GetRoot();
	int conversenodes = 0;
	int converslevel = 1;
	CONVERSEQUEUE cq;
	graphdata->nodeslist = new GRAPHNODE[nodes];
	while (cq.empty() == false)
	{
		//遍历第一层（root为0层）
		for (int i = 0; i < lastlevel->nextlist_fill; i++)
		{
			graphdata->nodeslist[conversenodes].level = converslevel;
			graphdata->nodeslist[conversenodes].data = lastlevel->pnextlist[i]->ch;
			graphdata->nodeslist[conversenodes].x = graphdata->x_split*(i + 1);
			graphdata->nodeslist[conversenodes].y = graphdata->y_split*(converslevel+1);
			cq.push(lastlevel->pnextlist[i]);
		}
		converslevel++;
		//
		lastlevel = cq.front();
		cq.pop();
	}
}


BEGIN_MESSAGE_MAP(CTrieGraph, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTrieGraph 消息处理程序


const bool CTrieGraph::InitGraph( CTrieTree * trie)
{
	if (trie->GetNodesCount() == 0)
	{
		return false;
	}
	CString buf = "";
	ConvertTrieToDrawable(trie);
	CPen pen;
	CPaintDC dcd(this);
	pen.CreatePen(PS_SOLID, 2, RGB(225,0,0));
	dcd.SelectObject(&pen);
	//循环绘制点集合
	dcd.Ellipse(50,50,100,100);
	CString xxx;
	xxx.Format("<<<<<<<<<graphdata->nodessum=%d>>>>>>>\n", graphdata->nodessum);
	for (int i = 0; i < graphdata->nodessum; i++)
	{
		CString buf = "";
		buf.Format("Point %d:\tx=%d,y=%d\n", i + 1, graphdata->nodeslist[i].x, graphdata->nodeslist[i].y);
		xxx+=buf;
	}
	MessageBoxA(xxx, "xxx data");
	for (int i = 0; i < graphdata->nodessum; i++)
	{
		dcd.Ellipse(graphdata->nodeslist[i].x - 25, graphdata->nodeslist[i].y - 25, graphdata->nodeslist[i].x + 25, graphdata->nodeslist[i].y + 25);
	}
	return true;
}

void CTrieGraph::setTrieTree(CTrieTree *trieroot)
{
	trie = trieroot;
}

void CTrieGraph::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
}


BOOL CTrieGraph::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	graphdata = new GRAPHDATA;
	graphdata->level = 0;
	graphdata->nodeslist = nullptr;
	graphdata->nodessum = 0;
	graphdata->x_split = 0;
	graphdata->y_split = 0;
	trie = nullptr;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTrieGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	//设置对话框背景颜色为白色
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	//重新绘制Trie树
	if (!InitGraph(trie))
	{
		MessageBoxA("Init Graph Failed!");
	}
}
