#include "stdafx.h"
#include "TrieTree.h"


CTrieTree::CTrieTree()
{
	proot = new WORDNODE;
	proot->ch = '*';
	proot->pdata = nullptr;
	proot->pnextlist = nullptr;
	proot->size_nextlist = 0;
	proot->nextlist_fill = 0;
	levelnodes_count_list = new int[BUFFER_LEVEL_COUNT];  //��ʼ����ڵ�������
	for (int i = 0; i < BUFFER_LEVEL_COUNT; i++)
	{
		levelnodes_count_list[i] = 0;
	}
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

void CTrieTree::log(const CString data)
{
	CStdioFile ff;
	ff.Open("log.txt", CFile::modeNoTruncate | CFile::modeWrite|CFile::modeCreate);
	ff.SeekToEnd();
	ff.WriteString(data + "\r\n");
	ff.Close();
}

const bool CTrieTree::Insert(CString word, PWORDNODE tg,int level)
{
	//CString buf = "";
	//log("in function Insert:");
	int ll = level;
	int chindex = SearchForAlphabetIndex(word[0], *tg);
	//buf.Format("\talphabet %c 's searching result (root=%c):postion=%d at level %d", word[0],GetRoot()->ch,chindex, level);
	//log(buf);
	if (word[0] == '\0' || word[0] == ' ')
	{
		return true;
	}
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ���
	if (chindex == -1)
	{
		PWORDNODE newnode = new WORDNODE;
		newnode->ch = word[0];
		newnode->nextlist_fill = 0;
		newnode->pdata = nullptr;
		newnode->pnextlist = nullptr;
		newnode->size_nextlist = 0;
		newnode->level = ll;
		int pos = AddToNextList(tg, newnode);
		//buf.Format("\tadd to nextlist in the postion of %d at level %d", pos, level);
		//log(buf);
		//���Ӹ�����Ϣ
		nodes_count++;    //���ӽڵ����
								//����ÿһ��Ľڵ���Ŀ
		if (GetLLCLSize() == ll)  //����ÿһ����ٽڵ����������
		{
			AppendMemoryForLLCL();
			levelnodes_count_list[ll]++;
		}
		else
		{
			levelnodes_count_list[ll]++;
		}
		if (level_count < ll)   //���²���
		{
			level_count++;
		}
		//������Ϣ�������
		if (word.GetLength() == 1)
		{
			//�����Ѿ�������
			return true;
		}
		Insert(word.Mid(1), tg->pnextlist[pos],ll+1);
	}
	else//�ҵ�
	{
		if (word.GetLength() == 1)
		{
			//�����Ѿ�������
			return true;
		}
		Insert(word.Mid(1), tg->pnextlist[chindex],ll+1);
	}
	return true;
}

const bool CTrieTree::Search(CString word, PWORDNODE tg)
{
	CString buf = "";
	log("in function Search:");
	int chindex = SearchForAlphabetIndex(word[0], *tg);
	buf.Format("\talphabet %c 's searching result (root=%c):postion=%d", word[0],GetRoot()->ch,chindex);
	log(buf);
	if (word[0] == '\0' || word[0] == ' ')
	{
		return true;
	}
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
		if (!Search(word.Mid(1), tg->pnextlist[chindex]))
		{
			return false;
		}
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

const int * CTrieTree::GetLLCList()
{
	return levelnodes_count_list;
}

const bool CTrieTree::AppendMemoryForLLCL()
{
	try {
		int *buf = new int[size_LLCL + BUFFER_INCREMENT_LEVEL_COUNT];
		for (int i = 0; i < size_LLCL; i++)
		{
			buf[i] = levelnodes_count_list[i];
		}
		for (int i = size_LLCL; i < (size_LLCL + BUFFER_INCREMENT_LEVEL_COUNT); i++)
		{
			buf[i] = 0;
		}
		delete[] levelnodes_count_list;
		levelnodes_count_list = buf;
		size_LLCL += BUFFER_INCREMENT_LEVEL_COUNT;
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
	for (int i = 0; i < node.nextlist_fill; i++)
	{
		if (node.pnextlist[i]->ch == ch)
		{
			return i;
		}
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

const int CTrieTree::AddToNextList(WORDNODE * desnode, PWORDNODE srcnode)
{
	if (desnode->nextlist_fill == desnode->size_nextlist)
	{//�����Ƿ��пռ�:����ռ����ˣ��ٷ��䣬Ȼ�󣬸��ƣ�Ȼ�����
		PWORDNODE * newnextlist = new PWORDNODE[desnode->size_nextlist + INCREMENT_NEXTLIST_SIZE];
		for (int i = 0; i < desnode->size_nextlist; i++)
		{
			newnextlist[i] = desnode->pnextlist[i];
		}
		newnextlist[desnode->nextlist_fill] = srcnode;
		desnode->size_nextlist += INCREMENT_NEXTLIST_SIZE;
		for (int i = desnode->nextlist_fill+1; i < desnode->size_nextlist; i++)
		{
			newnextlist[i] = nullptr;
		}
		delete[] desnode->pnextlist;
		desnode->pnextlist = newnextlist;
		desnode->nextlist_fill++;
		return desnode->nextlist_fill-1;
	}
	//�ռ�δװ��
	desnode->pnextlist[desnode->nextlist_fill] = srcnode;
	desnode->nextlist_fill++;
	return desnode->nextlist_fill-1;
}

