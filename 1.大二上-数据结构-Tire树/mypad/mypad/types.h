#pragma once
#define YELLOW 0
#define ORANGE 1
#define BLACK 2
#define GREEN 3

typedef struct changenode {
	int type;	//这个用于标记用什么颜色来绘图 0=黄色，1=橙色，2=黑色，3=绿色
	char data;
	int uid;
}CHANGENODE;		//储存改变的节点（或者搜索过的）