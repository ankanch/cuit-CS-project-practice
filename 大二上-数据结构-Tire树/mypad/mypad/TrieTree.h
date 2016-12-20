#pragma once
#include<vector>
#include<stack>
#include<utility>
#include<algorithm>
#define BUFFER_LEVEL_COUNT 20   //每一层的节点数数组的初始长度（假设会有20层）
#define BUFFER_INCREMENT_LEVEL_COUNT 10  //层节点数数组的递增量
#define INCREMENT_NEXTLIST_SIZE 7   //nextlist的递增量

//大二上-工程实践-2-Trie树
//张龙 2015051152 应用153
//mailto://kanchisme@gmail.com
//http://akakanch.com

typedef std::pair<CString,int> TFD;	//用于词频统计的自定义类型
typedef std::vector<TFD> TFDLIST;		//用于词频统计
typedef std::stack<CString> WORDSTACK;	//用于字典排序
typedef struct leafdata {
	int word_count;			//该单词出现的次数
	int word_length;		//该单词的长度
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;				//储存的字符
	int level;			//节点所在层数
	int size_nextlist;		//节点索引大小
	struct TNode* *pnextlist;	//节点索引指针数组
	int nextlist_fill;		//节点索引装填量
	PLEAFDATA pdata;			//如果是叶子节点，这里则应该包含数据
}WORDNODE,*PWORDNODE;

typedef PWORDNODE PROOT;

class CTrieTree
{
public:
	CTrieTree();
	~CTrieTree();
	//下面的函数为插入/删除接口
	const bool IncreaseWordCount();	//更新指定单词的计数，即将单词数增加1,只能在最近一次Search调用且返回true时调用
	const PWORDNODE GetLastFoundEndingChar();	//获取最近一次Search执行之后找到的单词的最后一个字符对应的节点（用来更新LEAFDATA）
	const bool Insert(CString word,PWORDNODE tg,int level=1);  //将一个单词插入Trie树。返回值：true插入或部分插入，false未插入（已存在，需要更新叶子数据）
	const bool Search(CString word,PWORDNODE tg);		//查找一个单词是否已经在Trie树中
	void Suggest(CString wordpart, CString pathword, WORDSTACK &ws, PWORDNODE tg,int matchlevel = 0);	//单词建议函数（给出单词的一部分，函数返回可能的单词（基于已有输入））
	const int Delete(CString word, PWORDNODE tg, int level = 1);	//该函数用来从树中删除一个单词，当然，是该单词计数为0才会被完全删除,返回值是删除后的单词计数
	const PROOT GetRoot();  //返回树根
	//下面的函数为绘图接口
	const int GetNodesCount();  //返回节点数
	const int GetLevelCount();  //树的深度（包括树根）
	const int*GetLLCList();		//获取每一层的节点数数组
	//下面的函数为统计/应用接口
	const TFDLIST GetTermFrequencyList(); 	//用于显示词频
	const CString Sort();		//对Trie树进行排序,按照ASCII码大小顺序
	
private:
	const bool AppendMemoryForLLCL();  //该函数用来向levelnodes_count_list追加空间
	const int GetLLCLSize();  //获取levelnodes_count_list的大小
	const int SearchForAlphabetIndex(const char ch,const WORDNODE & node); //该函数用来查找数据为ch的节点在当前node中的pnexlist索引,未找到：-1
	const PWORDNODE CreateNode(const char chr, PLEAFDATA leafdata = nullptr);   //创建新节点
	const int AddToNextList(WORDNODE * desnode,PWORDNODE srcnode);  //将一个新的节点添加到指定节点的pnextlist域中
	const void deleteTrieTree(PROOT root);   //删除所有Trie树的数据
	const int deleteFromNextList(PWORDNODE desnode, const int delindex);	//该函数用于从一个节点的nextlist列表中删除指定index的街电视剧，然后，将其他值迁移
	const int ResolveWords(PWORDNODE tg,TFDLIST &tfdlist,CString wordsuffix=" ");	//该函数的作用是从Trie中递归取出所有单词，然后放入TFDLIST中
	void sortpnextlist(PWORDNODE tg);		//递归的针对每一个节点的pnextlist来排序
	static bool compLarge( TFD a,  TFD b);	//比较函数
	void dictsort(PWORDNODE tg,WORDSTACK &ws, CString wordsuffix = " ");	//将tg按字典排序然后压栈（最后需要推栈）
	void searchOutWord(PWORDNODE tg, CString wordsuffix,WORDSTACK &ws);		//用于Suggest函数，当发现满足匹配的时候，用这个函数读取剩余的单词并接入ws中
	void log(const CString data);//调试函数

	PROOT proot;		//指向树根
	PWORDNODE lastfoundendingchar;	//记录最近一次Search执行之后找到的单词的最后一个字符对应的节点
	int diff_words_count; //记录不同单词个数
	int nodes_count;	//记录总的节点数目
	int level_count;   //记录树的深度

	int size_LLCL;   //记录levelnodes_count_list的大小
	int *levelnodes_count_list;	//记录树每一层的节点数
};

