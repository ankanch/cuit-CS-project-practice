#pragma once
#include"TrieTree.h"
#include "types.h"
#include<queue>
//�����-����ʵ��-2-Trie��
//���� 2015051152 Ӧ��153
//mailto://kanchisme@gmail.com
//http://akakanch.com
// CTrieGraph �Ի���

typedef std::queue<PWORDNODE> CONVERSEQUEUE;
typedef std::queue<CHANGENODE> POCESSLIST;
//����ͼ��Ľṹ
typedef struct graphnode {
	int level;	//ָʾ����ĸ��Trie�еĲ���
	char data;	//����ĸ������
	int x;	//��ͼ���xλ��
	int y;	//��ͼ���yλ��
	int wordscount;	//���pdata�ǿգ������¼���ʼ���
	struct graphnode*parent;	//�����Ӧ��ָ��˭
}GRAPHNODE,*PGRAPHNODE;

typedef struct graphdata {
	PGRAPHNODE nodeslist;	//��Žڵ��б�
	int nodessum = 0;	//����ڵ�����
	int level = 0;	//�������Ĳ���
	int x_split = 0;	//���������֮��x�ľ���
	int y_split = 0;	//����ÿһ��ľ���
}GRAPHDATA,*PGRAPHDATA;


class CTrieGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CTrieGraph)

public:
	CTrieGraph(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTrieGraph();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRIE_GRAPH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	PGRAPHDATA graphdata;	//����ͼ������
	CTrieTree * trie;		//����trie��������
	PGRAPHDATA  ConvertTrieToDrawable( CTrieTree * trie);	//�ú���������Trie�еĽڵ�ת����GRAPHNODE���������
	bool vf;
public:
	const bool UpdateGraph();   //�ú�����������ͼ��
	const bool InitGraph( CTrieTree * trie);		//�ú����������Ƴ�ʼͼ��
	const bool showPocess(POCESSLIST& pl);		//�ú����������ǻ��Ƴ���Ĵ������
	void setTrieTree(CTrieTree * trieroot);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
