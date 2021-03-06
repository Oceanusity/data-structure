// 堆排.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
int HST[100000];

void heapadjust(int s, int n) {
	for (int i = 2 * s; i <= n; i *= 2) {
		if (HST[i] < HST[i + 1] && i + 1 <= n)
			i++;
		if (HST[i / 2] < HST[i]) {
			HST[0] = HST[i];
			HST[i] = HST[i / 2];
			HST[i / 2] = HST[0];
		}
		else
			break;
	}
}


int main()
{
	using namespace std;
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> HST[i];
	for (int i = n / 2; i >= 1; i--)
		heapadjust(i, n);
	for (int i = 1; i <= n; i++)
		cout << HST[i] << ' ';
	cout << endl;
	for (int i = n; i > 1; i--) {
		HST[0] = HST[i];
		HST[i] = HST[1];
		HST[1] = HST[0];
		heapadjust(1, i - 1);
		if (i == m + 1) {
			for (int j = 1; j <= n; j++)
				cout << HST[j] << ' ';
			cout << endl;
		}
	}
	for (int i = 1; i <= n; i++)
		cout << HST[i] << ' ';
	cout << endl;
	system("pause");
	return 0;
}

