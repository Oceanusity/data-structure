// hash（1）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
unsigned int HT[4096];
int SL1 = 0;
int SL2 = 0;
int num1 = 0;
int num2 = 0;
unsigned int H(unsigned long long x) {
	return ((x*x)>>26)&4095;
}

int h(unsigned int x) { 
	return  x % 2 == 1 ? (x % 4096) : ((x + 1) % 4096);
}
void insert(unsigned int a) {
	using namespace std;
	int t = H(a), SL = 1, m = t;
	if (HT[t] == 0 || HT[t] == 0xffffffff)
		HT[t] = a;
	else {
		while (HT[t] != 0 && HT[t] != 0xffffffff) {
			t = (m + h(a)*SL) % 4096;
			SL++;
		}
		HT[t] = a;
	}
	cout << SL << ' ' << t << endl;
}
void search(unsigned int a) {
	using namespace std;
	int t = H(a), SL = 1, m = t;
	if (HT[t] == a) {
		cout << SL << ' ' << t << endl;
		HT[t] = 0xffffffff;
		SL1 += SL;
		num1++;
	}
	else {
		while (HT[t] != a&&HT[t] != 0) {
			t = (m + h(a)*SL) % 4096;
			SL++;
		}
		if (HT[t] == a) {
			HT[t] = 0xffffffff;
			cout << SL << ' ' << t << endl;
			SL1 += SL;
			num1++;
		}
		else if (HT[t] == 0) {
			cout << SL << ' ' << -1 << endl;
			SL2 += SL;
			num2++;
		}
	}
}
int main(void) {
	using namespace std;
	int   i = 0;
	for (i = 0; i < 10000; i++) {
		unsigned int a;
		int b;
		cin >> a >> b;
		if (b == 0) {
			search(a);
		}
		else if (b == 1) {
			insert(a);
		}
	}
	cout << SL1 << '/' << num1 << endl;
	cout << SL2 << '/' << num2 << endl;
	system("pause");
	return 0;
}