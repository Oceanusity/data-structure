// 饼干管理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Maxsize 50000
typedef struct CStreeNode {
	int num;
	struct CStreeNode * fch, *pare;
}CStreeNode, *CStree;
int num = 0;

CStree Make(int data) {
	CStree p = new CStreeNode;
	p->num = data;
	p->fch = NULL;
	p->pare = NULL;
	return p;
}

CStree biscuit[Maxsize];

void del(int a) {
	biscuit[a]->pare->fch = biscuit[a]->fch;
	biscuit[a]->fch->pare = biscuit[a]->pare;
	biscuit[a]->fch = NULL;
	biscuit[a]->pare = NULL;
}

void insert(int a, CStree L) {
	CStree p = biscuit[a];
	while (p->num < L->fch->num)
		L = L->fch;
	p->fch = L->fch;
	p->pare = L;
	L->fch = p;
	p->fch->pare = p;
}

int judge(int k, CStree head) {
	CStree L = head->fch;
	while (L->fch != NULL&&k-- != 1) {
		L = L->fch;
	}
	if (k != 0)
		return -1;
	else
		return L->num;
}

void op(CStree head) {
	using namespace std;
	char temp;
	int  k, a, b;
	cin >> temp;
	switch (temp) {
	case'Q':
		cin >> k; cout << judge(k, head) << endl; break;
	case'A':
		cin >> a >> b;
		if (biscuit[a]->num <= b) {
			del(a);
			num--;
		}
		else {
			biscuit[a]->num -= b;
			del(a);
			insert(a, head);
		}
		break;
	case'C':
		cin >> a >> b;
		biscuit[a]->num += b;
		del(a);
		insert(a, head);
		break;
	}
}

int main()
{
	using namespace std;
	int n, m, temp;
	CStree L;
	CStree head = Make(0), rear = Make(0);
	head->fch = rear;
	rear->pare = head;
	cin >> num;
	for (int i = 1; i <= num; i++) {
		L = head;
		cin >> temp;
		biscuit[i] = Make(temp);
		insert(i, L);
	}
	cin >> m;
	for (int i = 0; i < m; i++)
		op(head);
	L = head->fch;
	cout << num;
	system("pause");
	return 0;
}