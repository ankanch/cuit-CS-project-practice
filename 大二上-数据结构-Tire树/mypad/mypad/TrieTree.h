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
	const bool Insert(CString word);  //将一个单词插入Trie树
	const bool Find(CString word);		//查找一个单词是否已经在Trie树中
	~CTrieTree();
private:
	PWORDNODE proot;
	int diff_words_count;
	int nodes_count;
};

