// TrieGraph.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypad.h"
#include "TrieGraph.h"
#include "afxdialogex.h"
//�����-����ʵ��-2-Trie��
//���� 2015051152 Ӧ��153
//mailto://kanchisme@gmail.com
//http://akakanch.com

// CTrieGraph �Ի���
#define KDEBUGK

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
#ifdef KDEBUG
	MessageBoxA(xxx, "xxx data");
#endif
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
	graphdata->nodeslist[0].uid = 0;
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
			graphdata->nodeslist[conversenodes].uid = lastlevel->pnextlist[i]->uid;
			graphdata->nodeslist[conversenodes].parent = &graphdata->nodeslist[lastfill];  //ָ���丸�ڵ�
			if (lastlevel->pnextlist[i]->pdata != nullptr)
			{
				graphdata->nodeslist[conversenodes].wordscount = lastlevel->pnextlist[i]->pdata->word_count;
			}
			else
			{
				graphdata->nodeslist[conversenodes].wordscount = -1;
			}
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
	ON_WM_SIZING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTrieGraph ��Ϣ�������


const bool CTrieGraph::UpdateGraph()
{
	InitGraph(trie);
	return true;
}

const bool CTrieGraph::InitGraph( CTrieTree * trie)
{
	CClientDC dcd(this);
	CRect rect;
	//���öԻ��򱳾���ɫΪ��ɫ
	GetClientRect(rect);
	dcd.FillSolidRect(rect, RGB(255, 255, 255));
	//MessageBoxA("C");
	if (trie->GetNodesCount() == 0)
	{
		return false;
	}
	//MessageBoxA("D");
	CString buf = "";
	graphdata =  ConvertTrieToDrawable(trie);
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(225,0,0));
	dcd.SelectObject(&pen);
	/////////////////////////////////////////////////////////////////////////////////////////
	CString xxx;
	xxx.Format("<<<<<<<<<graphdata->nodessum=%d>>>>>>>\n", graphdata->nodessum);
	for (int i = 0; i <= graphdata->nodessum; i++)
	{
		CString buf = "";
		buf.Format("Point %d:\tx=%d,y=%d,count=%d\n", i + 1, graphdata->nodeslist[i].x, graphdata->nodeslist[i].y, graphdata->nodeslist[i].wordscount);
		xxx+=buf;
	}
#ifdef KDEBUG
	MessageBoxA(xxx, "Nodes' Point Dataset");
#endif
	xxx = "";
	/////////////////////////////////////////////////////////////////////////////////////////
	//ѭ�����Ƶ㼯��
	for (int i = 0; i <= graphdata->nodessum; i++)
	{
		dcd.Ellipse(graphdata->nodeslist[i].x - 12, graphdata->nodeslist[i].y - 12, graphdata->nodeslist[i].x + 12, graphdata->nodeslist[i].y + 12);
		if (i)
		{
			dcd.TextOutA(graphdata->nodeslist[i].x - 4, graphdata->nodeslist[i].y - 8, CString(graphdata->nodeslist[i].data));
			if (graphdata->nodeslist[i].wordscount != -1)
			{
				CString countx;
				countx.Format("%d", graphdata->nodeslist[i].wordscount);
				dcd.TextOutA(graphdata->nodeslist[i].x - 4, graphdata->nodeslist[i].y + 16, countx);
			}
			CString buf = "";
			buf.Format("Parent Point %d(%c):\tx=%d,y=%d\n", i,graphdata->nodeslist[i].data ,graphdata->nodeslist[i].parent->x, graphdata->nodeslist[i].parent->y);
			xxx += buf;
			dcd.MoveTo(CPoint(graphdata->nodeslist[i].x, graphdata->nodeslist[i].y-12));
			dcd.LineTo(CPoint(graphdata->nodeslist[i].parent->x, graphdata->nodeslist[i].parent->y+12));
		}
	}
#ifdef KDEBUG
	MessageBoxA(xxx, "Parents' PointsDataset");
#endif
	return true;
}

const bool CTrieGraph::showPocess(POCESSLIST &pl)
{
	//չʾ�����û�ɫ��ǳ�
	CClientDC dcd(this);
	if (trie->GetNodesCount() == 0)
	{
		return false;
	}
	CPen yellopen,orangepen,blackpen,greenpen;
	yellopen.CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
	orangepen.CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	blackpen.CreatePen(PS_SOLID, 2, RGB(0,0,0));
	greenpen.CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
	dcd.SelectObject(&yellopen);
	while(!pl.empty())
	{
		CHANGENODE cn;
		cn = pl.front();
		std::cout <<"cn.data=" <<cn.data << "\tcn.uid="<<cn.uid<<std::endl;
		//ѡ�񻭱���ɫ
		if (cn.type == YELLOW)
		{
			dcd.SelectObject(&yellopen);
		}
		else if (cn.type == ORANGE)
		{
			dcd.SelectObject(&orangepen);
		}
		else if (cn.type == BLACK)
		{
			dcd.SelectObject(&blackpen);
		}
		else if (cn.type == GREEN)
		{
			dcd.SelectObject(&greenpen);
		}
		for (int j = 0; j < graphdata->nodessum; j++)
		{
			//Ѱ�ҵ㣬���ı���ɫ
			if ( cn.uid == graphdata->nodeslist[j].uid && cn.data== graphdata->nodeslist[j].data)
			{
				dcd.Ellipse(graphdata->nodeslist[j].x - 12, graphdata->nodeslist[j].y - 12, graphdata->nodeslist[j].x + 12, graphdata->nodeslist[j].y + 12);
				dcd.TextOutA(graphdata->nodeslist[j].x - 4, graphdata->nodeslist[j].y - 8, CString(graphdata->nodeslist[j].data));
			}
		}
		pl.pop();
		Sleep(presentionMilesecond);
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
	vf = false;
	presentionMilesecond = 500;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTrieGraph::OnPaint()
{
	CPaintDC dcd(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	//���öԻ��򱳾���ɫΪ��ɫ
	GetClientRect(rect);
	dcd.FillSolidRect(rect, RGB(255, 255, 255));
	//���»���Trie��
	InitGraph(trie);
	
}


void CTrieGraph::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
	
}


void CTrieGraph::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
