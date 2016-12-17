#pragma once
#include"TrieTree.h"
// CTrieGraph �Ի���
//����ͼ��Ľṹ
typedef struct graphnode {
	int level;	//ָʾ����ĸ��Trie�еĲ���
	char data;	//����ĸ������
	int x;	//��ͼ���xλ��
	int y;	//��ͼ���yλ��
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
	void ConvertTrieToDrawable(const CTrieTree & trie);	//�ú���������Trie�еĽڵ�ת����GRAPHNODE���������

public:
	const bool UpdateGraph(PGRAPHNODE *pdellist);   //�ú�����������ͼ��
	const bool InitGraph(const CTrieTree & trie);		//�ú����������Ƴ�ʼͼ��
	afx_msg void OnClose();
};
