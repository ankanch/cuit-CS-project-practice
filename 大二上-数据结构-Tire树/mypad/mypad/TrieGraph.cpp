// TrieGraph.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypad.h"
#include "TrieGraph.h"
#include "afxdialogex.h"


// CTrieGraph �Ի���

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

PGRAPHDATA CTrieGraph::ConvertTrieToDrawable( CTrieTree * trie)
{
	const int*llcl = trie->GetLLCList();
	int levelcount = trie->GetLevelCount();
	int nodes = trie->GetNodesCount();
	graphdata->nodessum = nodes;
	graphdata->level = levelcount;
	//������ر�Ҫ��ͼ����
	CRect drawarea;
	this->GetClientRect(drawarea);
	//���ݲ�������ÿһ��֮��ļ��
	int *level_height = new int[levelcount];
	int *level_node_looped = new int[levelcount];   //��¼ÿ��ѭ����ʱ��ÿһ��ѭ���˶��ٸ���
	//graphdata->y_split = drawarea.Width() / (levelcount + 1);
	graphdata->y_split = 65;
	int y = graphdata->y_split;
	for (int i = 0; i < levelcount; i++)
	{
		level_height[i] = y;
		level_node_looped[i] = 0;
		y+= graphdata->y_split;
	}
	//����������x�����������Ϊ�㣬���������ߣ�
	int max = llcl[1];
	if (nodes > 2)
	{

		for (int i = 1; i <= levelcount; i++)
		{
			if (max <= llcl[i])
			{
				max = llcl[i];
			}
		}
		graphdata->x_split = drawarea.Width() / (max + 2);
	}
	//����ÿһ�����Ŀ����ÿһ���֮��ļ��
	int x = graphdata->x_split;
	int * level_width = new int[max];
	for (int i = 0; i < max; i++)
	{
		level_width[i] = x;
		x += graphdata->y_split;
	}
	/////////////////////////////////////////////////////////////////////
	CString xxx;
	xxx.Format("<<<<llcl sum=%d>>>>\n\n", levelcount);
	for (int i = 0; i <= levelcount; i++)
	{
		CString buf = "";
		buf.Format("llcl %d:\tcount = %d\n", i, llcl[i]);
		xxx += buf;
	}
	CString buf = "";
	buf.Format("\nlevelcount=%d\nnodescount=%d(include root)\n", levelcount, nodes);
	xxx += buf;
	buf.Format("\ngraphdata->x_split=%d,graphdata->y_split=%d\n", graphdata->x_split, graphdata->y_split);
	xxx += buf;
	MessageBoxA(xxx, "xxx data");
	/////////////////////////////////////////////////////////////////////
	//��ʼִ�е㼯��ת��
	int conversenodes = 1;
	int converslevel = 1;
	CONVERSEQUEUE cq;
	PWORDNODE lastlevel = trie->GetRoot();
	graphdata->nodeslist = new GRAPHNODE[nodes+1];  //�������ڵ� 
	//���ø��ڵ�
	graphdata->nodeslist[0].level = 0;
	graphdata->nodeslist[0].data = '*';
	graphdata->nodeslist[0].x = level_width[max/2];
	graphdata->nodeslist[0].y = 14;
	graphdata->nodeslist[0].parent = nullptr;
	cq.push(lastlevel);
	int lastfill = 0;  //��¼��һ�ε�װ�ص�
	while (cq.empty() == false)
	{
		lastlevel = cq.front();
		cq.pop();
		//�����㣨rootΪ0�㣩
		for (int i = 0; i < lastlevel->nextlist_fill; i++)
		{
			graphdata->nodeslist[conversenodes].level = converslevel;
			graphdata->nodeslist[conversenodes].data = lastlevel->pnextlist[i]->ch;
			graphdata->nodeslist[conversenodes].x = level_width[level_node_looped[lastlevel->pnextlist[i]->level-1] ];
			graphdata->nodeslist[conversenodes].y = level_height[lastlevel->pnextlist[i]->level-1];
			graphdata->nodeslist[conversenodes].parent = &graphdata->nodeslist[lastfill];  //ָ���丸�ڵ�
			conversenodes++;
			level_node_looped[lastlevel->pnextlist[i]->level-1]++;
			cq.push(lastlevel->pnextlist[i]);
		}
		lastfill++;
		converslevel++;
	}
	delete[] level_height;
	delete[] level_width;
	delete[] level_node_looped;
	return graphdata;
}


BEGIN_MESSAGE_MAP(CTrieGraph, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTrieGraph ��Ϣ�������


const bool CTrieGraph::InitGraph( CTrieTree * trie)
{
	if (trie->GetNodesCount() == 0)
	{
		return false;
	}
	CString buf = "";
	graphdata =  ConvertTrieToDrawable(trie);
	CPen pen;
	CClientDC dcd(this);
	pen.CreatePen(PS_SOLID, 2, RGB(225,0,0));
	dcd.SelectObject(&pen);
	/////////////////////////////////////////////////////////////////////////////////////////
	CString xxx;
	xxx.Format("<<<<<<<<<graphdata->nodessum=%d>>>>>>>\n", graphdata->nodessum);
	for (int i = 0; i < graphdata->nodessum; i++)
	{
		CString buf = "";
		buf.Format("Point %d:\tx=%d,y=%d\n", i + 1, graphdata->nodeslist[i].x, graphdata->nodeslist[i].y);
		xxx+=buf;
	}
	MessageBoxA(xxx, "xxx data");
	/////////////////////////////////////////////////////////////////////////////////////////
	//ѭ�����Ƶ㼯��
	for (int i = 0; i < graphdata->nodessum; i++)
	{
		dcd.Ellipse(graphdata->nodeslist[i].x - 15, graphdata->nodeslist[i].y - 15, graphdata->nodeslist[i].x + 15, graphdata->nodeslist[i].y + 15);
		dcd.TextOutA(graphdata->nodeslist[i].x - 8, graphdata->nodeslist[i].y - 8, CString(graphdata->nodeslist[i].data));
	}
	return true;
}

void CTrieGraph::setTrieTree(CTrieTree *trieroot)
{
	trie = trieroot;
}

void CTrieGraph::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->ShowWindow(SW_HIDE);
}


BOOL CTrieGraph::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	graphdata = new GRAPHDATA;
	graphdata->level = 0;
	graphdata->nodeslist = nullptr;
	graphdata->nodessum = 0;
	graphdata->x_split = 0;
	graphdata->y_split = 0;
	trie = nullptr;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTrieGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	//���öԻ��򱳾���ɫΪ��ɫ
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	//���»���Trie��
	//if (!InitGraph(trie))
	//{
		//MessageBoxA("Init Graph Failed!");
	//}
}
