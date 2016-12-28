#include "stdafx.h"
#include "TrieTree.h"
//�����-����ʵ��-2-Trie��
//���� 2015051152 Ӧ��153
//mailto://kanchisme@gmail.com
//http://akakanch.com

CTrieTree::CTrieTree()
{
	proot = new WORDNODE;
	proot->ch = '*';
	proot->pdata = nullptr;
	proot->pnextlist = nullptr;
	proot->size_nextlist = 0;
	proot->nextlist_fill = 0;
	proot->level = 0;
	levelnodes_count_list = new int[BUFFER_LEVEL_COUNT];  //��ʼ����ڵ�������
	for (int i = 0; i < BUFFER_LEVEL_COUNT; i++)
	{
		levelnodes_count_list[i] = 0;
	}
	level_count = 0;
	nodes_count = 0;
	diff_words_count = 0;
	size_LLCL = 0;
	log(">>>Trie����������ϡ�");
}

CTrieTree::~CTrieTree()
{
	deleteTrieTree(proot);
	delete proot;
	delete[] levelnodes_count_list;
	log(">>>Trie�����Ѿ����١�");
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

const int CTrieTree::deleteFromNextList(PWORDNODE desnode, const int delindex)
{
	if (desnode->pnextlist[delindex]->pdata != nullptr)
	{
		if (desnode->pnextlist[delindex]->pdata->word_count == 0)
		{
			delete desnode->pnextlist[delindex]->pdata;
		}
	}
	delete desnode->pnextlist[delindex];
	for (int i = 0; i < desnode->nextlist_fill; i++)
	{
		if (i > delindex)
		{
			desnode->pnextlist[i - 1] = desnode->pnextlist[i];
		}
	}
	desnode->nextlist_fill--;
	desnode->pnextlist[desnode->nextlist_fill] = nullptr;
	return desnode->nextlist_fill;
}

void CTrieTree::log(const CString data)
{
	std::cout << data << std::endl;
}

const bool CTrieTree::Insert(CString word, PWORDNODE tg,int level)
{
	CString buf = "";
	int ll = level;
	int chindex = SearchForAlphabetIndex(word[0], tg);
	buf.Format("\t����INSERT:�ַ� %c ��Դ���е�������� (��һ�ڵ��ֵ=%c):pnextlist�е�λ��=%d ���� %d", word[0],tg->ch,chindex, level);
	//log(buf);
	if (!isAlphabert(word[0]))
	{
		//log("^^^^return:non-alphabert characters.(INSERT)");
		return true;
	}
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ���
	if (chindex == -1)
	{
		PWORDNODE newnode = new WORDNODE;
		newnode->ch = word[0];
		newnode->nextlist_fill = 0;
		newnode->pnextlist = nullptr;
		newnode->size_nextlist = 0;
		newnode->level = ll;
		if (word.GetLength() == 1)
		{
			//��������һ�����ʣ��������һ����ĸ���ڽڵ�����Ҷ������
			PLEAFDATA lfd = new LEAFDATA;
			lfd->word_count = 1;
			lfd->word_length = ll;
			newnode->pdata = lfd;
		}
		else
		{
			newnode->pdata = nullptr;
		}
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
			buf.Format("///INSERT: found alphabert,current node:%c", tg->ch);
			//log(buf);
			if (tg->pnextlist[chindex]->pdata == nullptr)
			{
				PLEAFDATA lfd = new LEAFDATA;
				lfd->word_count = 1;
				lfd->word_length = ll;
				tg->pnextlist[chindex]->pdata = lfd;
				return false;
			}
			tg->pnextlist[chindex]->pdata->word_count++;
			//�����Ѿ�������
			return false;
		}
		Insert(word.Mid(1), tg->pnextlist[chindex],ll+1);
	}
	return true;
}

const bool CTrieTree::Search(CString word, PWORDNODE tg)
{
	/*/
	�����߼������ڿ��ǵ���Ҫ���� ����be��bee֮��ĵ��ʣ�
	���������
	һ�����ʵĶ����ǣ���������һ����Ҷ���ݽڵ��һ��·��������һ�����ʡ�
	��Ҷ���ݽڵ���ָpdata��ǿ�
	/*/
	CString buf = "";
	int chindex = SearchForAlphabetIndex(word[0], tg);
	buf.Format("\t����SEARCH����ĸ %c ��������� (��һ�ڵ�ֵ=%c):λ��=%d", word[0],tg->ch,chindex);
	//log(buf);
	if (!isAlphabert(word[0]))
	{
		//log("^^^^return:non-alphabert characters.");
		return true;
	}
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ����򷵻�
	if (chindex == -1)
	{
		//log("^^^^return: no match characters.");
		return false;
	}
	else//�ҵ�������Ѱ����һ��
	{
		int leftsize = word.GetLength();   //��ȡʣ����ҳ���,�ó�����Զ���ڵ���1
		if(leftsize == 1)  
		{
			//��ʣһ�����ʣ�ע�⣬����һ��˵���õ����Ѿ����ҹ��Ҵ��ڣ����ԣ�������Ҫ�ж����Ӧ�ڵ��Ƿ��ǵ��ʽ���λ��
			//�� pdataΪnullptr������ǣ�����ҳɹ������򣬲���ʧ��
			if (tg->pnextlist[chindex]->pdata != nullptr)
			{
				lastfoundendingchar = tg->pnextlist[chindex];
				buf.Format("^^^^return:  word found,next alphabert:%c", tg->pnextlist[chindex]->ch);
				//log(buf);
				return true;
			}
			buf.Format("^^^^return:  word found but not the ending of word,next alphabert:%c", tg->pnextlist[chindex]->ch);
			//log(buf);
			return false;
		}
		else
		{
			if (!Search(word.Mid(1), tg->pnextlist[chindex]))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

void CTrieTree::Suggest(CString wordpart,CString pathword ,WORDSTACK &ws, PWORDNODE tg, int matchlevel)
{
	CString word = "";
	if (matchlevel == wordpart.GetLength())
	{
		searchOutWord(tg, word, ws);
		return;
	}
	if (tg->ch != '*')
	{
		word = pathword + tg->ch;
	}
	else
	{
		word = " ";
	}
	if (tg->ch != wordpart[matchlevel])
	{
		for (int i = 0; i < tg->nextlist_fill; i++)
		{
			Suggest(wordpart, word,ws, tg->pnextlist[i], matchlevel);
		}
	}
	else
	{
		for (int i = 0; i < tg->nextlist_fill; i++)
		{
			Suggest(wordpart, word, ws, tg->pnextlist[i], matchlevel+1);
		}
	}
	return;
}

const int CTrieTree::Delete(CString word, PWORDNODE tg, int level)
{
	/*/
	ɾ���߼������ҵ����ʺ�ɾ��pdata�еļ������ݣ�Ȼ�����жϼ��������Ƿ�Ϊ0�����Ϊ0
	�Ҹĵ��ʷ��������ʵ�һ������ɾ������·���ڵ㣬�����ɾ��pdata��Ȼ������pdataΪnullptr
	/*/
	int chindex = SearchForAlphabetIndex(word[0], tg);
	//�ڵ�ǰ�ڵ�Ѱ���ַ���δ�ҵ����򷵻�
	if (chindex == -1)
	{
		return -1;  //����-1����δ�ҵ�Ҫɾ���ĵ���
	}
	else//�ҵ�������Ѱ����һ��
	{
		if (tg->pnextlist[chindex]->pdata != nullptr)
		{
			tg->pnextlist[chindex]->pdata->word_count--;
			if (tg->pnextlist[chindex]->pdata->word_count == 0)
			{
				//�жϸõ����Ƿ�Ϊ�������ʵ�һ����
				if (tg->pnextlist[chindex]->nextlist_fill == 0)
				{
					//�����������ʵ�һ����
					deleteFromNextList(tg, chindex);
					return 0;
				}
				else
				{
					//���������ʵ�һ����
					delete tg->pnextlist[chindex]->pdata;
					tg->pnextlist[chindex]->pdata = nullptr;
					return -10;		//-10�������ڸõ������������ʵ�һ���֣����Խ����������нڵ㶼����ɾ��
				}
			}
			else
			{
				return tg->pnextlist[chindex]->pdata->word_count;
			}
		}
		int sc = Delete(word.Mid(1), tg->pnextlist[chindex]);
		if ( sc== 0)
		{
			//ɾ����ǰ�ڵ��ҷ���0
			//ɾ��֮ǰ����Ҫ�ж��µ�ǰ��ĸ�ڵ��Ƿ�Ϊ�������ʵ�һ����
			if (tg->pnextlist[chindex]->nextlist_fill == 0)
			{
				//�����������ʵ�һ����
				deleteFromNextList(tg, chindex);
				return 0;
			}
			else
			{
				//���������ʵ�һ����
				delete tg->pnextlist[chindex]->pdata;
				tg->pnextlist[chindex]->pdata = nullptr;
				return -10;		//-10�������ڸõ������������ʵ�һ���֣����Խ����������нڵ㶼����ɾ��
			}
			return 0;
		}
		else
		{
			//������Ŀ����1�����򷵻�ɾ���õ��ʺ�ʣ�൥����Ŀ
			//�򷵻���-1
			//���߷�����-10
			return sc;
		}
	}
}

/*/
const bool CTrieTree::IncreaseWordCount()
{
	//�ú����������ǽ�
	//���ڸú����ĵ��ý���һ������²Ż���У�
	//	ȷ�ϸĵ��ʴ��ڵ�ʱ�򣬸ú����Żᱻ����
	PWORDNODE p =  GetLastFoundEndingChar();
	p->pdata->word_count++;
	return true;
}
/*/

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

const PWORDNODE CTrieTree::GetLastFoundEndingChar()
{
	return lastfoundendingchar;
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

const int CTrieTree::SearchForAlphabetIndex(const char ch, const PWORDNODE node)
{
	for (int i = 0; i < node->nextlist_fill; i++)
	{
		if (node->pnextlist[i]->ch == ch)
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

const TFDLIST CTrieTree::GetTermFrequencyList()
{
	TFDLIST ld;
	ResolveWords(GetRoot(),ld);
	std::sort(ld.begin(), ld.end(), &(CTrieTree::compLarge));
	return ld;
}


const int CTrieTree::ResolveWords(PWORDNODE tg,TFDLIST &tfdlist,CString wordsuffix)
{
	CString word = wordsuffix+tg->ch;
	if(tg->nextlist_fill == 0 || tg->pdata != nullptr)
	{
		TFD p(word,tg->pdata->word_count);
		tfdlist.push_back(p);
	}
		for(int i=0;i<tg->nextlist_fill;i++)
		{
			ResolveWords(tg->pnextlist[i],tfdlist,word);
		}
	return 0;
}

const CString CTrieTree::Sort()
{
	WORDSTACK ws;
	sortpnextlist(GetRoot());
	dictsort(GetRoot(), ws);
	//��ջ���
	CString dictstr = "";
	while (!ws.empty())
	{
		dictstr = ws.top() + dictstr;
		ws.pop();
	}
	return dictstr;
}

void CTrieTree::sortpnextlist(PWORDNODE tg)
{
	if (tg->pnextlist != nullptr)
	{
		PWORDNODE p1;
		for (int i = 0; i < tg->nextlist_fill; i++)
		{
			int minpos = i;
			for (int t = i; t < tg->nextlist_fill; t++)
			{
				if (tg->pnextlist[t]->ch <= tg->pnextlist[minpos]->ch)
				{
					minpos = t;
				}
			}
			p1 = tg->pnextlist[i];
			tg->pnextlist[i] = tg->pnextlist[minpos];
			tg->pnextlist[minpos] = p1;
		}
	}
	for (int i = 0; i < tg->nextlist_fill; i++)
	{
		sortpnextlist(tg->pnextlist[i]);
	}
	return;
}

 bool CTrieTree::compLarge( TFD a,  TFD b)
{
	return (a.second > b.second);
}

void CTrieTree::dictsort(PWORDNODE tg,WORDSTACK &wg, CString wordsuffix)
{
	CString word = "";
	if (tg->ch != '*')
	{
		word = wordsuffix + tg->ch;
	}
	else
	{
		word = " ";
	}
	if (tg->nextlist_fill == 0 || tg->pdata != nullptr)
	{
		wg.push(word);
	}
	for (int i = 0; i<tg->nextlist_fill; i++)
	{
		dictsort(tg->pnextlist[i], wg, word);
	}
	return ;
}

void CTrieTree::searchOutWord(PWORDNODE tg, CString wordsuffix, WORDSTACK &ws)
{
	CString word = "";
	if (tg->ch != '*')
	{
		word = wordsuffix + tg->ch;
	}
	else
	{
		word = " ";
	}
	if (tg->nextlist_fill == 0 || tg->pdata != nullptr)
	{
		ws.push(word);
	}
		for (int i = 0; i < tg->nextlist_fill; i++)
		{
			searchOutWord(tg->pnextlist[i], word, ws);
		}
		return;
}

