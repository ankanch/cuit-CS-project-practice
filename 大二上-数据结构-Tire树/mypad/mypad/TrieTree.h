#pragma once

typedef struct leafdata {
	int word_count;
	int word_length;
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;
	struct TNode *pnextlist;
	PLEAFDATA pdata;
}WORDNODE,*PWORDNODE;

class CTrieTree
{
public:
	CTrieTree();
	const bool Insert(CString word);  //��һ�����ʲ���Trie��
	const bool Find(CString word);		//����һ�������Ƿ��Ѿ���Trie����
	~CTrieTree();
private:
	PWORDNODE proot;
	int diff_words_count;
	int nodes_count;
};

