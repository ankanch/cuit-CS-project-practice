#pragma once
#include"TrieTree.h"
#include<queue>

// CTrieGraph 对话框
typedef std::queue<PWORDNODE> CONVERSEQUEUE;
//绘制图点的结构
typedef struct graphnode {
	int level;	//指示该字母在Trie中的层数
	char data;	//该字母的数据
	int x;	//绘图后的x位置
	int y;	//绘图后的y位置
}GRAPHNODE,*PGRAPHNODE;

typedef struct graphdata {
	PGRAPHNODE nodeslist;	//存放节点列表
	int nodessum = 0;	//储存节点总数
	int level = 0;	//储存树的层数
	int x_split = 0;	//储存各个点之间x的距离
	int y_split = 0;	//储存每一层的距离
}GRAPHDATA,*PGRAPHDATA;

class CTrieGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CTrieGraph)

public:
	CTrieGraph(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTrieGraph();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRIE_GRAPH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	PGRAPHDATA graphdata;	//储存图的数据
	CTrieTree * trie;		//储存trie树的数据
	void ConvertTrieToDrawable( CTrieTree * trie);	//该函数用来将Trie中的节点转换成GRAPHNODE，方便绘制

public:
	const bool UpdateGraph(PGRAPHNODE *pdellist);   //该函数用来更新图画
	const bool InitGraph( CTrieTree * trie);		//该函数用来绘制初始图画
	void setTrieTree(CTrieTree * trieroot);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
