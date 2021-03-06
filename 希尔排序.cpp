// 希尔排序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Max 100000
int SHT[Max];
int n, m;

void shellsort(int x) {
	for (int i = 0; i < x; i++) {
		int temp;
		for (int j = i + x; j < n; j += x) {
			if (SHT[j] > SHT[j - x])
				continue;
			else if (SHT[j] < SHT[j - x]) {
				for (int k = i; k < j; k+=x) {
					if (SHT[k] > SHT[j]) {
						temp = SHT[j];
						for (int p = j; p > k; p -= x)
							SHT[p] = SHT[p - x];
						SHT[k] = temp;
					}
				}
			}
		}
	}
}

int main()
{
	using namespace std;
	int shell[Max];
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> SHT[i];
	for (int i = 0; i < m; i++)
		cin >> shell[i];
	for (int i = 0; i < m; i++) {
		shellsort(shell[i]);
		for (int j = 0; j < n; j++)
			cout << SHT[j] << ' ';
		cout << endl;
	}
	system("pause");
    return 0;
}

