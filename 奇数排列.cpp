// 奇数排列.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#define len 100010
#define R 16
#define D 4
int n;
int T[len];
void rad(int a[], int b[], int k) {
	using namespace std;
	int count[R];
	for (int i = 0; i < R; i++)
		count[i] = 0;
	for (int i = 1; i <= n; i++)
		count[a[i] >> 4 * (3 - k) & 15]++;
	for (int i = 1; i < R; i++)
		count[i] = count[i - 1] + count[i];
	for (int i = n; i >=1; i--) {
		int p = a[i] >> 4 * (3 - k) & 15;
		b[count[p]] = a[i];
		count[p]--;
	}
	for (int i = 1; i <= n; i++)
		cout << b[i]<<' ';
	cout << endl;
}




int main(){
	using namespace std;
	int temp[len];
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> T[i];
	for (int k = D - 1; k >= 0;) {
		rad(T, temp, k);
		k--;
		if (k >= 0) {
			rad(temp, T, k);
			k--;
		}
		else {
			for (int j = 1; j <= n; j++)
				T[j] = temp[j];
		}
	}
	for (int i = 1; i <= n; i++)
		cout << T[i] << ' ';
	system("pause");
    return 0;
}

