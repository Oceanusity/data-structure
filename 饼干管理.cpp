// 饼干管理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Maxsize 50000
typedef struct CStreeNode {
	int num;
	struct CStreeNode * fch, *nsb, *fsb,*pare;
}CStreeNode, *CStree;

CStree Make(int data) {
	CStree p = new CStreeNode;
	p->num = data;
	p->fch = NULL;
	p->nsb = NULL;
	p->fsb = NULL;
	p->pare = NULL;
	return p;
}

CStree biscuit[Maxsize];

void del(int a) {
	if (biscuit[a]->fch != NULL)
		if (biscuit[a]->nsb != NULL) {
			biscuit[a]->pare->fch = biscuit[a]->nsb;
			biscuit[a]->nsb->pare = biscuit[a]->pare;
			biscuit[a]->nsb->fch = biscuit[a]->fch;
			biscuit[a]->fch->pare = biscuit[a]->nsb;
			biscuit[a]->nsb->fsb = NULL;
		}
		else {
			biscuit[a]->pare->fch = biscuit[a]->fch;
			biscuit[a]->fch->pare = biscuit[a]->pare;
		}
	else {
		biscuit[a]->fsb->nsb = biscuit[a]->nsb;
		biscuit[a]->nsb->fsb = biscuit[a]->fsb;
	}
}

void insert(int a, CStree L) {
	CStree p = biscuit[a];
	while (p->num < L->fch->num)
		L = L->fch;
	if (p->num == L->fch->num) {
		L = L->fch;
		while (L->nsb != NULL)
			L = L->nsb;
		L->nsb = p;
		p->fsb = L;
	}
	else {
		p->fch = L->fch;
		p->pare = L;
		L->fch = p;
		p->fch->pare = p;
	}
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
	int t, k, a, b;
	cin >> temp;
	switch (temp) {
	case'Q':
		cin >> k; cout << judge(k, head) << endl; break;
	case'A':
		cin >> a >> b;
		if (biscuit[a]->num < b)
			del(a);
		else{
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

int num(CStree t) {
	if (t == NULL)
		return 0;
	else if (t->num == 0)
		return 0;
	return num(t->fch) + num(t->nsb);
}

int main()
{
	using namespace std;
	int n, m, temp;
	CStree L;
	CStree head = Make(0), rear = Make(0);
	head->fch = rear;
	rear->pare = head;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		CStree p;
		L = head;
		cin >> temp;
		biscuit[i] = Make(temp);
		insert(i, head);
	}
	cin >> m;
	for (int i = 0; i < m; i++)
		op(head);
	L = head->fch;
	cout<<num(head);
	system("pause");
    return 0;
}

