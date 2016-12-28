#include "stdafx.h"
#include "TrieTree.h"
//大二上-工程实践-2-Trie树
//张龙 2015051152 应用153
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
	levelnodes_count_list = new int[BUFFER_LEVEL_COUNT];  //初始化层节点数数组
	for (int i = 0; i < BUFFER_LEVEL_COUNT; i++)
	{
		levelnodes_count_list[i] = 0;
	}
	level_count = 0;
	nodes_count = 0;
	diff_words_count = 0;
	size_LLCL = 0;
	log(">>>Trie容器构建完毕。");
}

CTrieTree::~CTrieTree()
{
	deleteTrieTree(proot);
	delete proot;
	delete[] levelnodes_count_list;
	log(">>>Trie容器已经销毁。");
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
	buf.Format("\t函数INSERT:字符 %c 在源表中的搜索结果 (上一节点的值=%c):pnextlist中的位置=%d 层数 %d", word[0],tg->ch,chindex, level);
	//log(buf);
	if (!isAlphabert(word[0]))
	{
		//log("^^^^return:non-alphabert characters.(INSERT)");
		return true;
	}
	//在当前节点寻找字符，未找到：
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
			//如果是最后一个单词，则向最后一个字母所在节点增加叶子数据
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
		//增加辅助信息
		nodes_count++;    //增加节点计数
								//更新每一层的节点数目
		if (GetLLCLSize() == ll)  //储存每一层多少节点的数组满载
		{
			AppendMemoryForLLCL();
			levelnodes_count_list[ll]++;
		}
		else
		{
			levelnodes_count_list[ll]++;
		}
		if (level_count < ll)   //更新层数
		{
			level_count++;
		}
		//辅助信息增加完毕
		if (word.GetLength() == 1)
		{
			//单词已经添加完毕
			return true;
		}
		Insert(word.Mid(1), tg->pnextlist[pos],ll+1);
	}
	else//找到
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
			//单词已经添加完毕
			return false;
		}
		Insert(word.Mid(1), tg->pnextlist[chindex],ll+1);
	}
	return true;
}

const bool CTrieTree::Search(CString word, PWORDNODE tg)
{
	/*/
	查找逻辑，由于考虑到需要处理 诸如be和bee之类的单词，
	所以在这里，
	一个单词的定义是：从树根到一个带叶数据节点的一条路径即构成一个单词。
	带叶数据节点是指pdata域非空
	/*/
	CString buf = "";
	int chindex = SearchForAlphabetIndex(word[0], tg);
	buf.Format("\t函数SEARCH：字母 %c 的搜索结果 (上一节点值=%c):位置=%d", word[0],tg->ch,chindex);
	//log(buf);
	if (!isAlphabert(word[0]))
	{
		//log("^^^^return:non-alphabert characters.");
		return true;
	}
	//在当前节点寻找字符，未找到：则返回
	if (chindex == -1)
	{
		//log("^^^^return: no match characters.");
		return false;
	}
	else//找到，继续寻找下一个
	{
		int leftsize = word.GetLength();   //获取剩余查找长度,该长度永远大于等于1
		if(leftsize == 1)  
		{
			//还剩一个单词，注意，到这一步说明该单词已经查找过且存在，所以，这里需要判断其对应节点是否是单词结束位置
			//即 pdata为nullptr，如果是，则查找成功，否则，查找失败
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
	删除逻辑，当找到单词后删除pdata中的计数数据，然后在判断计数数据是否为0，如果为0
	且改单词非其它单词的一部分则删除所有路径节点，否则仅删除pdata，然后设置pdata为nullptr
	/*/
	int chindex = SearchForAlphabetIndex(word[0], tg);
	//在当前节点寻找字符，未找到：则返回
	if (chindex == -1)
	{
		return -1;  //返回-1代表未找到要删除的单词
	}
	else//找到，继续寻找下一个
	{
		if (tg->pnextlist[chindex]->pdata != nullptr)
		{
			tg->pnextlist[chindex]->pdata->word_count--;
			if (tg->pnextlist[chindex]->pdata->word_count == 0)
			{
				//判断该单词是否为其它单词的一部分
				if (tg->pnextlist[chindex]->nextlist_fill == 0)
				{
					//不是其它单词的一部分
					deleteFromNextList(tg, chindex);
					return 0;
				}
				else
				{
					//是其它单词的一部分
					delete tg->pnextlist[chindex]->pdata;
					tg->pnextlist[chindex]->pdata = nullptr;
					return -10;		//-10代表由于该单词是其它单词的一部分，所以接下来的所有节点都不用删除
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
			//删除当前节点且返回0
			//删除之前还是要判断下当前字母节点是否为其它单词的一部分
			if (tg->pnextlist[chindex]->nextlist_fill == 0)
			{
				//不是其它单词的一部分
				deleteFromNextList(tg, chindex);
				return 0;
			}
			else
			{
				//是其它单词的一部分
				delete tg->pnextlist[chindex]->pdata;
				tg->pnextlist[chindex]->pdata = nullptr;
				return -10;		//-10代表由于该单词是其它单词的一部分，所以接下来的所有节点都不用删除
			}
			return 0;
		}
		else
		{
			//单次数目多于1个，则返回删除该单词后剩余单词数目
			//或返回了-1
			//或者返回了-10
			return sc;
		}
	}
}

/*/
const bool CTrieTree::IncreaseWordCount()
{
	//该函数的作用是将
	//由于该函数的调用仅在一种情况下才会进行：
	//	确认改单词存在的时候，该函数才会被调用
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
		//出现未知错误
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
	{//计算是否还有空间:如果空间满了，再分配，然后，复制，然后，添加
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
	//空间未装满
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
	//退栈组合
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

