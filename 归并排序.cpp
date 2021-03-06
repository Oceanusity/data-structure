// 归并排序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define len 50000
int n, couple;
int MST1[len], MST2[len], MST3[len];
void merge(int a[], int b[], int s, int m, int t) {
	int i = 0, j = 0, k = 0;
	for (i = s, j = m + 1, k = i; i <= m&&j <= t; k++) {
		if (a[i] > a[j]) {
			b[k] = a[j++];
			couple += m - i + 1;
		}
		else {
			b[k] = a[i++];
		}
	}
	for (; i <= m; i++, k++)
			b[k] = a[i];
	for (; j <= t; j++, k++)
		b[k] = a[j];
}

void Msort(int a[], int b[], int s, int t) {
	if (s == t) {
		b[s] = a[s];
		return;
	}
	int m = (s + t) / 2;
	int Rtemp[len];
	Msort(a, Rtemp, s, m);
	Msort(a, Rtemp, m + 1, t);
	merge(Rtemp, b, s, m, t);

}

int main()
{
	using namespace std;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> MST1[i];
	Msort(MST1, MST2, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << MST2[i] << ' ';
	cout << endl;
	cout << couple << endl;
	system("pause");
    return 0;
}

