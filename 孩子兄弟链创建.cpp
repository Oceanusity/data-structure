// 孩子兄弟链创建.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
using namespace std;
typedef struct CTNode {
	char data;
	struct CTNode *firstchild;
	struct CTNode *nextsibling;
}CTNode, *CTree;

CTree CreatCTree(void) {
	char temp;
	CTree p;
	cin >> temp;
	if (temp == '#')
		return NULL;
	else {
		p = new CTNode;
		p->data = temp;
		p->firstchild = CreatCTree();
		p->nextsibling = CreatCTree();
	}
	return p;
}

int main()
{
	CTree head;
	head = CreatCTree();
    return 0;
}