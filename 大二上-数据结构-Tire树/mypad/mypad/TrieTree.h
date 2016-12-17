#pragma once
#define BUFFER_LEVEL_COUNT 20   //每一层的节点数数组的初始长度（假设会有20层）
#define BUFFER_INCREMENT_LEVEL_COUNT 10  //层节点数数组的递增量
#define INCREMENT_NEXTLIST_SIZE 7   //nextlist的递增量

typedef struct leafdata {
	int word_count;			//该单词出现的次数
	int word_length;		//该单词的长度
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;				//储存的字符
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
	const bool Insert(CString word,PWORDNODE tg,int level=1);  //将一个单词插入Trie树
	const bool Search(CString word,PWORDNODE tg);		//查找一个单词是否已经在Trie树中
	const PROOT GetRoot();  //返回树根
	//下面的函数为绘图接口
	const int GetNodesCount();  //返回节点数
	const int GetLevelCount();  //树的深度（包括树根）
	const int*GetLLCList();		//获取每一层的节点数数组
private:
	const bool AppendMemoryForLLCL();  //该函数用来向levelnodes_count_list追加空间
	const int GetLLCLSize();  //获取levelnodes_count_list的大小
	const int SearchForAlphabetIndex(const char ch,const WORDNODE & node); //该函数用来查找数据为ch的节点在当前node中的pnexlist索引,未找到：-1
	const PWORDNODE CreateNode(const char chr, PLEAFDATA leafdata = nullptr);   //创建新节点
	const int AddToNextList(WORDNODE * desnode,PWORDNODE srcnode);  //将一个新的节点添加到指定节点的pnextlist域中
	const void deleteTrieTree(PROOT root);   //删除所有Trie树的数据
	void log(const CString data);//调试函数

	PROOT proot;		//指向树根
	int diff_words_count; //记录不同单词个数
	int nodes_count;	//记录总的节点数目
	int level_count;   //记录树的深度

	int size_LLCL;   //记录levelnodes_count_list的大小
	int *levelnodes_count_list;	//记录树每一层的节点数
};

