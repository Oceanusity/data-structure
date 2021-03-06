// 饼干追击.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Max 200
typedef struct ArcNode {
	int adjvex, weight, Listvex;
	struct ArcNode *nextarc = NULL;
	struct ArcNode *forearc = NULL;
}ArcNode,*arc;
typedef struct VNode {
	int flag = 0;
	int B_flag = 0;
	arc firstarc = NULL;
}VNode, AdjList[Max];       //对所有的函数，传入的都是点的序号，应使用数组下标时减一
typedef struct {
	AdjList iver,over;
	int vexnum, arcnum;
}ALGraph;
int Quene[Max];
int top = 0, rear = 1;

void del(int a, int b, ALGraph G) {             //没写好
	arc p = G.over[a - 1].firstarc;
	if (p->adjvex == b) {
		G.over[a - 1].firstarc->forearc->nextarc = G.over[a - 1].firstarc->nextarc;
		G.over[a - 1].firstarc = p->nextarc;
		delete p;
	}
	else {
		arc q = p->nextarc;
		while (q != NULL) {
			if (q->adjvex == b) {
				q->nextarc = p->nextarc;
				delete q;
				break;
			}
			p = p->nextarc;
			q = q->nextarc;
		}
	}
}

void DFS(arc a, ALGraph G) {
	if (a == NULL)
		return;
	if (G.iver[a->adjvex - 1].flag == 0) {
		G.iver[a->adjvex - 1].flag = 1;
		DFS(G.iver[a->adjvex - 1].firstarc, G);
		DFS(a->forearc, G);
	}
}

int flag(int s, int t, ALGraph G) {
	int judge = 0;
	G.iver[t - 1].flag = 1;
	DFS(G.iver[t - 1].firstarc, G);
	for (int i = 0; i < G.vexnum; i++) {
		if (G.iver[i].flag == 1)
			judge = 1;
	}
	if (judge == 0)
		return 0;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.iver[i].flag != 1) {
			arc p = G.over[i].firstarc;
			while (p != NULL) {
				del(p->adjvex, i, G);
				p = p->nextarc;
			}
		}
	}
	return 1;
}

void BFS(int s, int t, ALGraph G, int depth) {
	using namespace std;
	arc p = G.ver[s - 1].firstarc;
	if (s == t) {
		cout << depth << endl;
		top = rear;
	}
	if (rear - top == 0)
		return;
	while (p != NULL) {
		if (G.ver[p->adjvex - 1].B_flag == 0) {
			Quene[rear++] = p->adjvex;
			G.ver[p->adjvex - 1].B_flag = 1;
		}
		p = p->nextarc;
	}
	BFS(Quene[top++], t, G, depth + 1);
}

int main()
{
	using namespace std;
	int s, t;
	ALGraph G;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.arcnum; i++) {
		int a, b, c, j = 0;
		cin >> a >> b >> c;
		arc p = new ArcNode;
		p->adjvex = b - 1;
		p->Listvex = a - 1;
		p->weight = c;
		p->nextarc = G.over[a - 1].firstarc;
		G.iver[a - 1].firstarc = p;
		p->forearc = G.iver[b - 1].firstarc;
		G.iver[b - 1].firstarc = p;
	}
	cin >> s >> t;
	if (flag(s, t, G) == 0 && G.iver[s - 1].flag == 0)
		cout << -1;
	else {
		Quene[0] = s;
		G.over[s - 1].B_flag = 1;
		BFS(Quene[0], t, G, 0);
	}
	system("pause");
    return 0;
}

