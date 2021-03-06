// 快速排序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define Max 10010
int len;
int QST[Max];
void quicksort(int a, int b) {
	using namespace std;
	int i = a, j = b;
	cout << i << ' ' << j << endl;
	while (1) {
		int temp;
		while (QST[j] >= QST[i] && i != j)
			j--;
		if (i == j)
			break;
		else {
			temp = QST[i];
			QST[i] = QST[j];
			QST[j] = temp;
		}
		while (QST[i] <= QST[j] && i != j)
			i++;
		if (i > j)
			break;
		else {
			temp = QST[i];
			QST[i] = QST[j];
			QST[j] = temp;
		}
	}
	if (i - a > 1)
		quicksort(a, i - 1);
	if (b - i > 1)
		quicksort(i + 1, b);
}




int main()
{
	using namespace std;
	cin >> len;
	for (int i = 1; i <= len; i++)
		cin >> QST[i];
	quicksort(1, len);
	for (int i = 1; i <= len; i++)
		cout << QST[i] << ' ';
	system("pause");
    return 0;
}

