#include "stdafx.h"
#include "TrieTree.h"


CTrieTree::CTrieTree()
{
	proot = new WORDNODE;
	proot->ch = '*';
	proot->pdata = nullptr;
	proot->pnextlist = nullptr;
	proot->size_nextlist = 0;
	levelnodes_count_list = new int[BUFFER_LEVEL_COUNT];  //��ʼ����ڵ�������
	level_count = 0;
	nodes_count = 0;
	diff_words_count = 0;
	size_LLCL = 0;
}

CTrieTree::~CTrieTree()
{
	deleteTrieTree(proot);
	delete proot;
	delete[] levelnodes_count_list;
}
const void CTrieTree::deleteTrieTree(PROOT root)
{
	if (root->size_nextlist == 0)
	{
		return;
	}
	for (int i = 0; i < root->nextlist_fill; i++)
	{
		deleteTrieTree(root->pnextlist[i]);
		delete root->pnextlist[i];
	}
	delete[] root->pnextlist;
	return;
}

const bool CTrieTree::Insert(CString word, PWORDNODE tg)
{
	int chindex = SearchForAlphabetIndex(word[0], *tg);
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ���
	if (chindex == -1)
	{
		PWORDNODE newnode = new WORDNODE;
		newnode->ch = word[0];
		newnode->nextlist_fill = 0;
		newnode->pdata = nullptr;
		newnode->pnextlist = nullptr;
		newnode->size_nextlist = 0;
		int pos = AddToNextList(*tg, newnode);
		if (word.GetLength() == 1)
		{
			//�����Ѿ�������
			return true;
		}
		Insert(word.Mid(1), tg->pnextlist[pos]);
	}
	else//�ҵ�
	{
		if (word.GetLength() == 1)
		{
			//�����Ѿ�������
			return true;
		}
		Insert(word.Mid(1), tg->pnextlist[chindex]);
	}
	return true;
}

const bool CTrieTree::Search(CString word, PWORDNODE tg)
{
	int chindex = SearchForAlphabetIndex(word[0], *tg);
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ����򷵻�
	if (chindex == -1)
	{
		return false;
	}
	else//�ҵ�������Ѱ����һ��
	{
		if (tg->size_nextlist == 0)
		{
			//���ӽڵ�
			return true;
		}
		Search(word.Mid(1), tg->pnextlist[chindex]);
	}
	return true;
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
		//����δ֪����
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

const PWORDNODE CTrieTree::CreateNode(const char chr,PLEAFDATA leafdata)
{
	PWORDNODE  newnode = new WORDNODE;
	newnode->ch = chr;
	newnode->pdata = leafdata;
	newnode->pnextlist = nullptr;
	newnode->size_nextlist = 0;
	return newnode;
}

const int CTrieTree::AddToNextList(WORDNODE & desnode, PWORDNODE srcnode)
{
	int pos = desnode.nextlist_fill;  //��¼����ӵĽڵ�λ��
	if (desnode.nextlist_fill == desnode.size_nextlist)
	{//�����Ƿ��пռ�:����ռ����ˣ��ٷ��䣬Ȼ�󣬸��ƣ�Ȼ�����
		PWORDNODE * newnextlist = new PWORDNODE[desnode.size_nextlist + INCREMENT_NEXTLIST_SIZE];
		for (int i = 0; i < desnode.size_nextlist; i++)
		{
			newnextlist[i] = desnode.pnextlist[i];
		}
		newnextlist[desnode.nextlist_fill] = srcnode;
		for (int i = desnode.nextlist_fill+1; i < desnode.size_nextlist; i++)
		{
			newnextlist[i] = nullptr;
		}
		delete[] desnode.pnextlist;
		desnode.pnextlist = newnextlist;
		desnode.nextlist_fill++;
		desnode.size_nextlist += INCREMENT_NEXTLIST_SIZE;
		return pos;
	}
	//�ռ�δװ��
	desnode.pnextlist[desnode.nextlist_fill + 1] = srcnode;
	desnode.nextlist_fill++;
	return ++pos;
}

