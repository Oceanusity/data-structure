// 二路归并.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define len 50000
int n;
int T[len];
int couple;
void marge(int a[], int b[], int s, int m, int t) {
	int i = 0, j = 0, k = 0;
	for (i = s, j = m + 1, k = s; i <= m&&j <= t;) {
		if (a[i] > a[j]) {
			b[k++] = a[j++];
			couple += (m - i + 1);
		}
		else
			b[k++] = a[i++];
	}
	for (; i <= m;)
		b[k++] = a[i++];
	for (; j <= t;)
		b[k++] = a[j++];
}
void Msort(int a[], int b[], int s) {
	int i = 0;
	while (i + 2 * s - 1 < n) {
		marge(a, b, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	if (i + s - 1 < n - 1)
		marge(a, b, i, i + s - 1, n - 1);
	else
		for (; i < n; i++)
			b[i] = a[i];
}



int main()
{
	using namespace std;
	int temp[len];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> T[i];
	for (int s = 1; s <= n;) {
		Msort(T, temp, s);
		s *= 2;
		if (s <= n)
			Msort(temp, T, s);
		else
			for (int j = 0; j < n; j++)
				T[j] = temp[j];
	}
	for (int i = 0; i < n; i++)
		cout << T[i] << ' ';
	cout << endl;
	cout << couple << endl;
	system("pause");
    return 0;
}

