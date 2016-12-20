#pragma once
#include<vector>
#include<stack>
#include<utility>
#include<algorithm>
#define BUFFER_LEVEL_COUNT 20   //ÿһ��Ľڵ�������ĳ�ʼ���ȣ��������20�㣩
#define BUFFER_INCREMENT_LEVEL_COUNT 10  //��ڵ�������ĵ�����
#define INCREMENT_NEXTLIST_SIZE 7   //nextlist�ĵ�����

//�����-����ʵ��-2-Trie��
//���� 2015051152 Ӧ��153
//mailto://kanchisme@gmail.com
//http://akakanch.com

typedef std::pair<CString,int> TFD;	//���ڴ�Ƶͳ�Ƶ��Զ�������
typedef std::vector<TFD> TFDLIST;		//���ڴ�Ƶͳ��
typedef std::stack<CString> WORDSTACK;	//�����ֵ�����
typedef struct leafdata {
	int word_count;			//�õ��ʳ��ֵĴ���
	int word_length;		//�õ��ʵĳ���
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;				//������ַ�
	int level;			//�ڵ����ڲ���
	int size_nextlist;		//�ڵ�������С
	struct TNode* *pnextlist;	//�ڵ�����ָ������
	int nextlist_fill;		//�ڵ�����װ����
	PLEAFDATA pdata;			//�����Ҷ�ӽڵ㣬������Ӧ�ð�������
}WORDNODE,*PWORDNODE;

typedef PWORDNODE PROOT;

class CTrieTree
{
public:
	CTrieTree();
	~CTrieTree();
	//����ĺ���Ϊ����/ɾ���ӿ�
	const bool IncreaseWordCount();	//����ָ�����ʵļ�������������������1,ֻ�������һ��Search�����ҷ���trueʱ����
	const PWORDNODE GetLastFoundEndingChar();	//��ȡ���һ��Searchִ��֮���ҵ��ĵ��ʵ����һ���ַ���Ӧ�Ľڵ㣨��������LEAFDATA��
	const bool Insert(CString word,PWORDNODE tg,int level=1);  //��һ�����ʲ���Trie��������ֵ��true����򲿷ֲ��룬falseδ���루�Ѵ��ڣ���Ҫ����Ҷ�����ݣ�
	const bool Search(CString word,PWORDNODE tg);		//����һ�������Ƿ��Ѿ���Trie����
	void Suggest(CString wordpart, CString pathword, WORDSTACK &ws, PWORDNODE tg,int matchlevel = 0);	//���ʽ��麯�����������ʵ�һ���֣��������ؿ��ܵĵ��ʣ������������룩��
	const int Delete(CString word, PWORDNODE tg, int level = 1);	//�ú�������������ɾ��һ�����ʣ���Ȼ���Ǹõ��ʼ���Ϊ0�Żᱻ��ȫɾ��,����ֵ��ɾ����ĵ��ʼ���
	const PROOT GetRoot();  //��������
	//����ĺ���Ϊ��ͼ�ӿ�
	const int GetNodesCount();  //���ؽڵ���
	const int GetLevelCount();  //������ȣ�����������
	const int*GetLLCList();		//��ȡÿһ��Ľڵ�������
	//����ĺ���Ϊͳ��/Ӧ�ýӿ�
	const TFDLIST GetTermFrequencyList(); 	//������ʾ��Ƶ
	const CString Sort();		//��Trie����������,����ASCII���С˳��
	
private:
	const bool AppendMemoryForLLCL();  //�ú���������levelnodes_count_list׷�ӿռ�
	const int GetLLCLSize();  //��ȡlevelnodes_count_list�Ĵ�С
	const int SearchForAlphabetIndex(const char ch,const WORDNODE & node); //�ú���������������Ϊch�Ľڵ��ڵ�ǰnode�е�pnexlist����,δ�ҵ���-1
	const PWORDNODE CreateNode(const char chr, PLEAFDATA leafdata = nullptr);   //�����½ڵ�
	const int AddToNextList(WORDNODE * desnode,PWORDNODE srcnode);  //��һ���µĽڵ���ӵ�ָ���ڵ��pnextlist����
	const void deleteTrieTree(PROOT root);   //ɾ������Trie��������
	const int deleteFromNextList(PWORDNODE desnode, const int delindex);	//�ú������ڴ�һ���ڵ��nextlist�б���ɾ��ָ��index�Ľֵ��Ӿ磬Ȼ�󣬽�����ֵǨ��
	const int ResolveWords(PWORDNODE tg,TFDLIST &tfdlist,CString wordsuffix=" ");	//�ú����������Ǵ�Trie�еݹ�ȡ�����е��ʣ�Ȼ�����TFDLIST��
	void sortpnextlist(PWORDNODE tg);		//�ݹ�����ÿһ���ڵ��pnextlist������
	static bool compLarge( TFD a,  TFD b);	//�ȽϺ���
	void dictsort(PWORDNODE tg,WORDSTACK &ws, CString wordsuffix = " ");	//��tg���ֵ�����Ȼ��ѹջ�������Ҫ��ջ��
	void searchOutWord(PWORDNODE tg, CString wordsuffix,WORDSTACK &ws);		//����Suggest����������������ƥ���ʱ�������������ȡʣ��ĵ��ʲ�����ws��
	void log(const CString data);//���Ժ���

	PROOT proot;		//ָ������
	PWORDNODE lastfoundendingchar;	//��¼���һ��Searchִ��֮���ҵ��ĵ��ʵ����һ���ַ���Ӧ�Ľڵ�
	int diff_words_count; //��¼��ͬ���ʸ���
	int nodes_count;	//��¼�ܵĽڵ���Ŀ
	int level_count;   //��¼�������

	int size_LLCL;   //��¼levelnodes_count_list�Ĵ�С
	int *levelnodes_count_list;	//��¼��ÿһ��Ľڵ���
};

