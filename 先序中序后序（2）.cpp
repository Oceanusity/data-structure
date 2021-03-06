// 先序中序后序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Maxsize 1000000
typedef struct BiTNode {
	int lchild = 0, rchild = 0, parent = 0, size = 1, depth = 0;
}BiTNode, *Bitree;
BiTNode tree[Maxsize];
int num[Maxsize] = { 0 };
int temp[Maxsize];
int help[Maxsize];
void foreorder(int x) {
	using namespace std;
	if (x != 0 ) {
		cout << x << ' ';
		foreorder(tree[x].lchild);
		foreorder(tree[x].rchild);
		
	}
}

void Traverse(int x) {
	using namespace std;
	int front = 0, rear = 1, len = 1;
	temp[0] = x;
	cout << x<<' ';
	for (int i = front; i < front + len; i++) {
		front = (front + Maxsize + 1) % Maxsize;
		len--;
		if (tree[temp[i]].lchild != 0) {
			temp[rear] = tree[temp[i]].lchild;
			cout <<  temp[rear]<<' ';
			rear = (rear + Maxsize + 1) % Maxsize;
			len++;
		}
		if (tree[temp[i]].rchild != 0) {
			temp[rear] = tree[temp[i]].rchild;
			cout <<  temp[rear]<<' ';
			rear = (rear + Maxsize + 1) % Maxsize;
			len++;
		}
	}
}

int main()
{
	using namespace std;
	int n, m;
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> num[i];
	tree[num[n]].parent = 0;
	tree[num[n]].size = n;
	tree[num[n]].depth = 0;
	for (int i = n; i >=2; i--) {
		if (num[i - 1] > num[i]) {
			int t = num[i];
			tree[num[i]].rchild = num[i - 1];
			tree[num[i - 1]].parent = num[i];
			tree[num[i - 1]].depth = tree[num[i]].depth + 1;
			while (tree[t].parent != 0) {
				tree[t].size++;
				t = tree[t].parent;
			}
		}
		else if (num[i - 1] < num[i]) {
			int t = num[i];
			while (1) {
				if (tree[t].parent == 0) {
					tree[t].lchild = num[i-1];
					tree[num[i-1]].parent = t;
					tree[num[i-1]].depth = tree[t].depth + 1;
					break;
				}
				else if (tree[tree[t].parent].rchild == t) {
					if (tree[t].parent > num[i-1]) {
						t = tree[t].parent;
						continue;
					}
					else {
						tree[t].lchild = num[i-1];
						tree[num[i-1]].parent = t;
						tree[num[i-1]].depth = tree[t].depth + 1;
						while (tree[t].parent != 0) {
							tree[t].size++;
							t = tree[t].parent;
						}
						break;
					}
				}
				else if (tree[tree[t].parent].lchild == t) {
					int p = t;
					while (tree[tree[t].parent].lchild == t)
						t = tree[t].parent;
					if (tree[t].parent > num[i-1] && tree[t].parent != 0) {
						t = tree[t].parent;
						continue;
					}
					else {
						tree[p].lchild = num[i-1];
						tree[num[i-1]].depth = tree[p].depth + 1;
						tree[num[i-1]].parent = p;
						while (tree[p].parent != 0) {
							tree[p].size++;
							p = tree[p].parent;
						}
						break;
					}

				}
			}
		}
	}
	cin >> m;
	for (int k = 1; k <= m; k++)
		cin >> help[k];
	foreorder(num[n]);
	cout << endl;
	Traverse(num[n]);
	cout << endl;
	for (int i = 1; i <= m; i++)
		cout << tree[help[i]].parent << ' ' << tree[help[i]].lchild << ' ' << tree[help[i]].rchild << ' ' << tree[help[i]].depth << ' ' << tree[help[i]].size << endl;
	system("pause");
	return 0;
}