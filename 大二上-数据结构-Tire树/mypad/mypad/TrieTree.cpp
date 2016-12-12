#include "stdafx.h"
#include "TrieTree.h"


CTrieTree::CTrieTree()
{
	proot = new WORDNODE;
	proot->ch = '*';
	proot->pdata = nullptr;
	proot->pnextlist = nullptr;
	proot->size_nextlist = 0;
	levelnodes_count_list = new int[BUFFER_LEVEL_COUNT];  //初始化层节点数数组
	level_count = 1;
	nodes_count = 0;
	diff_words_count = 0;
	size_LLCL = 0;
}

CTrieTree::~CTrieTree()
{
	delete proot;
	delete[] levelnodes_count_list;
}

const bool CTrieTree::Insert(CString word)
{

	return false;
}

const bool CTrieTree::Search(CString word)
{
	return false;
}

const PROOT CTrieTree::GetRoot()
{
	return proot;
}

const int CTrieTree::GetNodesCount()
{
	return nodes_count;
}

const int CTrieTree::GetLevelCount()
{
	return level_count;
}

const bool CTrieTree::AppendMemoryForLLCL()
{
	try {
		int *buf = new int[size_LLCL + BUFFER_INCREMENT_LEVEL_COUNT];
		for (int i = 0; i < size_LLCL; i++)
		{
			buf[i] = levelnodes_count_list[i];
		}
		delete[] levelnodes_count_list;
		levelnodes_count_list = buf;
	}catch(...){
		//出现未知错误
		return false;
	}
	return true;
}

const int CTrieTree::GetLLCLSize()
{
	return size_LLCL;
}

const int CTrieTree::SearchForAlphabetIndex(const char ch, const WORDNODE & node)
{
	for (int i = 0; i < node.size_nextlist; i++)
	{
		node.pnextlist[i]->ch == ch;
		return i;
	}
	return -1;
}

