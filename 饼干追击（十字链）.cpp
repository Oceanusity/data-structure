// 饼干追击（十字链）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Max 2000
typedef struct ArcNode {
	int adjvex, weight, listvex;
	struct ArcNode *oarc = NULL;
	struct ArcNode *iarc = NULL;
}ArcNode, *arc;
typedef struct VNode {
	arc firstarc;
}VNode, AdjList[Max];
typedef struct {
	AdjList iver, over;
	int vexnum, arcnum;
}ALGraph;
int D[Max];
ALGraph G;
int flag_i[Max];
void Make(int a,int b,int c,ALGraph G){
	arc p = new ArcNode;
	p->adjvex = b - 1;
	p->listvex = a - 1;
	p->weight = c;
	p->oarc = G.over[a - 1].firstarc->oarc;
	G.over[a - 1].firstarc->oarc = p;
	p->iarc = G.iver[b - 1].firstarc->iarc;
	G.iver[b - 1].firstarc->iarc = p;
}
void DFS(arc a, ALGraph G) {
	if (a == NULL)
		return;
	if (a->weight == -1) {
		DFS(a->iarc, G);
		return;
	}
	if (flag_i[a->listvex] == 0) {
		flag_i[a->listvex]= 1;
		DFS(G.iver[a->listvex].firstarc, G);
		DFS(a->iarc, G);
	}
}
int flush(ALGraph G) {
	int flag = 0;
	for(int i=0;i<G.vexnum;i++)
		if (flag_i[i] == 1) {
			flag = 1;
			break;
		}
	if (flag == 0)
		return 0;
	for (int i = 0; i < G.vexnum; i++) {
		if (flag_i[i] == 0) {
			arc q = G.iver[i].firstarc;
			arc p = q->iarc;
			while (p != NULL) {
				flag_i[p->listvex] = 0;
				p = p->iarc;
			}
		}
	}
	for (int i = 0; i < G.vexnum; i++) {
		if (flag_i[i] == 0) {
			arc q = G.iver[i].firstarc;
			arc p = q->iarc;
			arc temp1, temp2;
			while (p != NULL) {
				q->iarc = p->iarc;
				temp1 = G.over[p->listvex].firstarc;
				temp2 = temp1->oarc;
				while (temp2->adjvex != i) {
					temp1 = temp1->oarc;
					temp2 = temp2->oarc;
				}
				temp1->oarc = temp2->oarc;
				p = p->iarc;
				q = q->iarc;
			}
		}
	}
	return 1;
}

int Dijkstra(int s, int t, ALGraph G) {
	arc p = G.over[s - 1].firstarc->oarc;
	int k = 0;
	flag_i[s - 1] = 0;
	if (flag_i[t-1] == 0)
		return D[t - 1];
	while (p != NULL) {
		if (D[p->adjvex] == 0 || D[p->adjvex] > D[s - 1] + p->weight)
			D[p->adjvex] = D[s - 1] + p->weight;
		p = p->oarc;
	}
	for (int i = 0; i < G.vexnum; i++) {
		if (flag_i[i] == 1) {
			k = i;
			break;
		}
	}

	for (int i = k; i < G.vexnum; i++) {
		if (D[i] != 0 && flag_i[i] == 1)
			k = D[k] < D[i] ? k : i;
	}
	return Dijkstra(k + 1, t, G);
}

int main()
{
	using namespace std;
	int s, t;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {
		arc p = new ArcNode;
		p->oarc = NULL;
		p->iarc = NULL;
		p->adjvex = -1;
		p->listvex = -1;
		p->weight = -1;
		G.iver[i].firstarc = p;
	}
	for (int i = 0; i < G.vexnum; i++) {
		arc p = new ArcNode;
		p->oarc = NULL;
		p->iarc = NULL;
		p->adjvex = -1;
		p->listvex = -1;
		p->weight = -1;
		G.over[i].firstarc = p;
	}
	for(int i = 0; i < G.arcnum; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		Make(a, b, c, G);
	}
	cin >> s >> t;
	flag_i[t - 1] = 1;
	DFS(G.iver[t - 1].firstarc, G);
	if (flag_i[s - 1] == 0 || !flush(G))
		cout << -1;
	else
		cout << Dijkstra(s, t, G);
	system("pause");
    return 0;
}

