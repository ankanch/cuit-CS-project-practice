#pragma once
#define YELLOW 0
#define ORANGE 1
#define BLACK 2
#define GREEN 3

typedef struct changenode {
	int type;	//������ڱ����ʲô��ɫ����ͼ 0=��ɫ��1=��ɫ��2=��ɫ��3=��ɫ
	char data;
	int uid;
}CHANGENODE;		//����ı�Ľڵ㣨�����������ģ�