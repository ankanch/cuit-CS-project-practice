#pragma once
#include"TrieTree.h"
#include "types.h"
#include<queue>
//大二上-工程实践-2-Trie树
//张龙 2015051152 应用153
//mailto://kanchisme@gmail.com
//http://akakanch.com
// CTrieGraph 对话框

typedef std::queue<PWORDNODE> CONVERSEQUEUE;
typedef std::queue<CHANGENODE> POCESSLIST;
//绘制图点的结构
typedef struct graphnode {
	int level;	//指示该字母在Trie中的层数
	char data;	//该字母的数据
	int x;	//绘图后的x位置
	int y;	//绘图后的y位置
	int wordscount;	//如果pdata非空，这里记录单词计数
	struct graphnode*parent;	//标记它应该指向谁
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
	PGRAPHDATA  ConvertTrieToDrawable( CTrieTree * trie);	//该函数用来将Trie中的节点转换成GRAPHNODE，方便绘制
	bool vf;
public:
	const bool UpdateGraph();   //该函数用来更新图画
	const bool InitGraph( CTrieTree * trie);		//该函数用来绘制初始图画
	const bool showPocess(POCESSLIST& pl);		//该函数的作用是绘制程序的处理进程
	void setTrieTree(CTrieTree * trieroot);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
