// equal（初次尝试 ，多项式展开）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<string.h>
#define Maxsize 1000
char std_array[Maxsize];
typedef struct ploynode {
	int  exp;
	long long int coef;
	struct ploynode* next;
}ploynode, *ploy;
ploy Node[Maxsize];
ploy Makeploy(long long int coef, int exp) {
	ploy temp = new ploynode;
	temp->coef = coef;
	temp->exp = exp;
	temp->next = NULL;
	return temp;
}

int abs(int x) {
	return x > 0 ? x : -x;
}

ploy sum(ploy p1, ploy p2) {
	ploy La = p1->next, Lb = p2->next, Lc = Makeploy(-1, -1), Lcc = Lc;
	while (La != NULL && Lb != NULL) {
		if (La->exp > Lb->exp) {
			Lc->next = Makeploy(La->coef, La->exp);
			Lc = Lc->next;
			La = La->next;
		}
		else if (Lb->exp > La->exp) {
			Lc->next = Makeploy(Lb->coef, Lb->exp);
			Lc = Lc->next;
			Lb = Lb->next;
		}
		else if (La->exp == Lb->exp && abs(La->coef + Lb->coef) == 0) {
			La = La->next;
			Lb = Lb->next;
		}
		else if (La->exp == Lb->exp && abs(La->coef + Lb->coef) >= 0) {
			Lc->next = Makeploy(La->coef + Lb->coef, La->exp);
			La = La->next;
			Lb = Lb->next;
			Lc = Lc->next;
		}
	}
	while (La != NULL) {
		Lc->next = Makeploy(La->coef, La->exp);
		La = La->next;
		Lc = Lc->next;
	}
	while (Lb != NULL) {
		Lc->next = Makeploy(Lb->coef, Lb->exp);
		Lb = Lb->next;
		Lc = Lc->next;
	}
	return Lcc;
}

ploy divide(ploy p1, ploy p2) {
	ploy La = p1->next, Lb = p2->next, Lc = Makeploy(-1, -1), Lcc = Lc;
	while (La != NULL && Lb != NULL) {
		if (La->exp > Lb->exp) {
			Lc->next = Makeploy(La->coef, La->exp);
			Lc = Lc->next;
			La = La->next;
		}
		else if (Lb->exp > La->exp) {
			Lc->next = Makeploy(-Lb->coef, Lb->exp);
			Lc = Lc->next;
			Lb = Lb->next;
		}
		else if (La->exp == Lb->exp && abs(La->coef - Lb->coef) == 0) {
			La = La->next;
			Lb = Lb->next;
		}
		else if (La->exp == Lb->exp && abs(La->coef - Lb->coef) >= 0) {
			Lc->next = Makeploy(La->coef - Lb->coef, La->exp);
			La = La->next;
			Lb = Lb->next;
			Lc = Lc->next;
		}
	}
	while (La != NULL) {
		Lc->next = Makeploy(La->coef, La->exp);
		La = La->next;
		Lc = Lc->next;
	}
	while (Lb != NULL) {
		Lc->next = Makeploy(-Lb->coef, Lb->exp);
		Lb = Lb->next;
		Lc = Lc->next;
	}
	return Lcc;
}

ploy single_mult(ploy p1, ploy p2) {
	ploy Lb, Lc = Makeploy(-1, -1), Lcc = Lc;
	if (p1->coef == -1 && p1->exp == -1)
		return Makeploy(-1, -1);
	else {
		Lb = p2->next;
		while (Lb != NULL) {
			Lc->next = Makeploy(Lb->coef *p1->coef, p1->exp + Lb->exp);
			Lb = Lb->next;
			Lc = Lc->next;
		}
		return Lcc;
	}
}

ploy multiple(ploy p1, ploy p2) {
	ploy La = p1->next, Lb = p2;
	ploy temp[Maxsize] = { NULL };
	int t_sign = 0, i = 0;
	if (p1->next == NULL || p2->next == NULL)
		return Makeploy(-1, -1);
	while (La != NULL) {
		temp[t_sign++] = single_mult(La, Lb);
		La = La->next;
	}
	temp[t_sign] = Makeploy(-1, -1);
	for (i = 0; i < t_sign; i++)
		temp[t_sign] = sum(temp[t_sign], temp[i]);
	return temp[t_sign];
}

ploy power(ploy p1, ploy p2) {
	ploy temp = p1;
	if (p1->next == NULL)
		return Makeploy(-1, -1);
	else
		for (int i = 1; i < p2->next->coef; i++)
			temp = multiple(temp, p1);
	return temp;
}

ploy calculate(ploy p1, ploy p2, char flag) {
	ploy temp = NULL;
	switch (flag) {
	case '+':temp = sum(p1, p2); break;
	case '-':temp = divide(p1, p2); break;
	case '*':temp = multiple(p1, p2); break;
	case '^':temp = power(p1, p2); break;
	}
	return temp;
}

int flag(char ch) {
	switch (ch) {
	case '^':return 3; break;
	case '(':return 4; break;
	case '*':return 2; break;
	case '+':return 1; break;
	case '-':return 1; break;
	case')':return -1; break;
	case'\0':return -2; break;
	default:return 0;
	}
	return 0;
}

ploy read(char*ch) {
	ploy temp[Maxsize];
	char symbol[Maxsize], *p = ch;
	int t_top = 1, s_top = 1;
	int sign = 1, l_num = 0, r_num = 0, d_lr = 0, len = 0, l_sign = 0, r_sign = 0;
	symbol[0] = '\0';
	temp[0] = Makeploy(-1, -1);
	while (*p++ != '\0')
		len++;
	p = ch;
	len = 0;
	p = ch;
	while (*p != '\0') {
		if (*p == '(') {
			l_num++;
			p++;
		}
		else if (*p++ == ')')
			r_num++;
		len++;
	}
	d_lr = l_num - r_num;
	if (d_lr != 0) {
		temp[1] = Makeploy(-1, -1);
		temp[1]->next = Makeploy(0, 0);
		return temp[1];
	}
		
	while (sign) {
		if (flag(*ch)) {
			if (flag(*ch) == -2 && flag(symbol[s_top - 1]) == -2)
				break;
			if (flag(*ch) == -1 && flag(symbol[s_top - 1]) == 4)
				s_top--;
			else if (flag(*ch) > flag(symbol[s_top - 1]))
				symbol[s_top++] = *ch;
			else if (flag(*ch) <= flag(symbol[s_top - 1])) {
				if (flag(symbol[s_top - 1]) == 4)
					symbol[s_top++] = *ch;
				else {
					ploy t = calculate(temp[t_top - 2], temp[t_top - 1], symbol[s_top - 1]);
					temp[--t_top - 1] = t;
					if (t_top == 1)
						temp[t_top++] = temp[0];
					s_top--;
					continue;
				}
			}
			ch++;
		}
		else if (*ch == 'x') {
			temp[t_top] = Makeploy(-1, -1);
			temp[t_top++]->next = Makeploy(1, 1);
			ch++;
		}
		else if (*ch == '\0') {
			sign = 0;
			ch++;
		}
		else if (*ch != ' ') {
			long long int coef = 0;
			temp[t_top] = Makeploy(-1, -1);
			while (*ch >= '0'&&*ch <= '9')
				coef = coef * 10 + *ch++ - '0';
			if (coef != 0)
				temp[t_top++]->next = Makeploy(coef, 0);
			else
				t_top++;
		}
		else
			ch++;
	}
	return temp[1];
}

int equal(ploy p1, ploy p2) {
	ploy La = p1->next, Lb = p2->next;
	while (La != NULL && Lb != NULL) {
		if (La->coef != Lb->coef || La->exp != Lb->exp)
			return 0;
		else {
			La = La->next;
			Lb = Lb->next;
		}
	}
	if (La == NULL && Lb == NULL)
		return 1;
	else
		return 0;
	return 0;
}

int main()
{
	using namespace std;
	int n;
	char data[Maxsize][Maxsize];
	cin >> n;
	getchar();
	cin.getline(std_array, Maxsize);
	Node[0] = read(std_array);
	for (int i = 1; i <= n; i++)
		cin.getline(data[i], Maxsize);
	for (int i = 1; i <= n; i++) {
		Node[i] = read(data[i]);
		if (equal(Node[0], Node[i]))
			printf("%c", 'A' + i - 1);
	}
	system("pause");
	return 0;
}

