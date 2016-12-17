#pragma once
#define BUFFER_LEVEL_COUNT 20   //ÿһ��Ľڵ�������ĳ�ʼ���ȣ��������20�㣩
#define BUFFER_INCREMENT_LEVEL_COUNT 10  //��ڵ�������ĵ�����
#define INCREMENT_NEXTLIST_SIZE 7   //nextlist�ĵ�����

typedef struct leafdata {
	int word_count;			//�õ��ʳ��ֵĴ���
	int word_length;		//�õ��ʵĳ���
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;				//������ַ�
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
	const bool Insert(CString word,PWORDNODE tg,int level=1);  //��һ�����ʲ���Trie��
	const bool Search(CString word,PWORDNODE tg);		//����һ�������Ƿ��Ѿ���Trie����
	const PROOT GetRoot();  //��������
	//����ĺ���Ϊ��ͼ�ӿ�
	const int GetNodesCount();  //���ؽڵ���
	const int GetLevelCount();  //������ȣ�����������
	const int*GetLLCList();		//��ȡÿһ��Ľڵ�������
private:
	const bool AppendMemoryForLLCL();  //�ú���������levelnodes_count_list׷�ӿռ�
	const int GetLLCLSize();  //��ȡlevelnodes_count_list�Ĵ�С
	const int SearchForAlphabetIndex(const char ch,const WORDNODE & node); //�ú���������������Ϊch�Ľڵ��ڵ�ǰnode�е�pnexlist����,δ�ҵ���-1
	const PWORDNODE CreateNode(const char chr, PLEAFDATA leafdata = nullptr);   //�����½ڵ�
	const int AddToNextList(WORDNODE * desnode,PWORDNODE srcnode);  //��һ���µĽڵ���ӵ�ָ���ڵ��pnextlist����
	const void deleteTrieTree(PROOT root);   //ɾ������Trie��������
	void log(const CString data);//���Ժ���

	PROOT proot;		//ָ������
	int diff_words_count; //��¼��ͬ���ʸ���
	int nodes_count;	//��¼�ܵĽڵ���Ŀ
	int level_count;   //��¼�������

	int size_LLCL;   //��¼levelnodes_count_list�Ĵ�С
	int *levelnodes_count_list;	//��¼��ÿһ��Ľڵ���
};

