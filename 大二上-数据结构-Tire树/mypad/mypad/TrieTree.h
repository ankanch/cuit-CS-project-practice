#pragma once

#define BUFFER_LEVEL_COUNT 20   //ÿһ��Ľڵ�������ĳ�ʼ���ȣ��������20�㣩
#define BUFFER_INCREMENT_LEVEL_COUNT 10  //��ڵ�������ĵ�����

typedef struct leafdata {
	int word_count;			//�õ��ʳ��ֵĴ���
	int word_length;		//�õ��ʵĳ���
}LEAFDATA,*PLEAFDATA;

typedef struct TNode{
	char ch;				//������ַ�
	int size_nextlist;		//�ڵ�������С
	struct TNode* *pnextlist;	//�ڵ�����ָ������
	PLEAFDATA pdata;			//�����Ҷ�ӽڵ㣬������Ӧ�ð�������
}WORDNODE,*PWORDNODE;

typedef PWORDNODE PROOT;

class CTrieTree
{
public:
	CTrieTree();
	~CTrieTree();
	const bool Insert(CString word);  //��һ�����ʲ���Trie��
	const bool Search(CString word);		//����һ�������Ƿ��Ѿ���Trie����
	const PROOT GetRoot();  //��������
	const int GetNodesCount();  //���ؽڵ���
	const int GetLevelCount();  //������ȣ�����������
private:
	const bool AppendMemoryForLLCL();  //�ú���������levelnodes_count_list׷�ӿռ�
	const int GetLLCLSize();  //��ȡlevelnodes_count_list�Ĵ�С
	const int SearchForAlphabetIndex(const char ch,const WORDNODE & node); //�ú���������������Ϊch�Ľڵ��ڵ�ǰnode�е�pnexlist����,δ�ҵ���-1
	
	PROOT proot;		//ָ������
	int diff_words_count; //��¼��ͬ���ʸ���
	int nodes_count;	//��¼�ܵĽڵ���Ŀ
	int level_count;   //��¼�������

	int size_LLCL;   //��¼levelnodes_count_list�Ĵ�С
	int *levelnodes_count_list;	//��¼��ÿһ��Ľڵ���
};

