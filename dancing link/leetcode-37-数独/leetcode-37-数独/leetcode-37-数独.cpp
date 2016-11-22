// leetcode-37-数独.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define RR 750
#define CC 350
#define V RR*CC
int hashx1[RR],hashx2[RR],hashx[RR],OK[90];
int U[V],D[V],L[V],R[V],C[V];
int H[RR],Row[V];
int S[CC];
int X[RR];
int size, r;
int mm[10][10];
void remove(int c)
{
	R[L[c]] = R[c];
	L[R[c]] = L[c];
	for(int i = D[c];i!=c;i = D[i])
	{
		for(int j = R[i];j!=i;j = R[j])
		{
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			--S[C[j]];
		}
	}
}
void resume(int c)
{
	for(int i = U[c];i!=c;i = U[i])
	{
		for(int j = L[i];j!=i;j = L[j])
		{
			D[U[j]] = j;
			U[D[j]] = j;
			++S[C[j]];
		}
	}
	L[R[c]] = c;
	R[L[c]] = c;
}
void Link(int r, int c)
{
	S[c]++;
	C[size] = c;
	Row[size] = r;
	U[size] = U[c];
	D[U[c]] = size;
	D[size] = c;
	U[c] = size;
	if(H[r]==-1) H[r] = L[size] = R[size] = size;
	else
	{
		L[size] = L[H[r]];
		R[L[H[r]]] = size;
		R[size] = H[r];
		L[H[r]] = size;
	}
	++size;
}
void check()
{
	int i;
	for(i = 0;i<81;i++)
		mm[hashx1[OK[i]]][hashx2[OK[i]]] = hashx[OK[i]];
}
int Dance(int k)
{
	int i,j,Min,c;
	if(R[0]==0)
	{
		check();
		return 1;
	}
	for(Min = RR,i = R[0];i!=0;i = R[i])
	{
		if(Min>S[i])
		{
			Min = S[i];
			c = i;
		}
	}
	remove(c);
	for(i = D[c];i!=c;i = D[i])
	{
		for(j = R[i];j!=i;j=R[j])
		{
			remove(C[j]);
		}
		OK[k] = Row[i];
		if(Dance(k+1)) return 1;
		for(j = L[i];j!=i;j = L[j])
			resume(C[j]);
	}
	resume(c);
	return 0;
}
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(mm,0,sizeof(mm));
		for(int i = 0;i<9;i++)
		{
			for(int j = 0;j<9;j++)
			{
				if(board[i][j]=='.')
					mm[i+1][j+1] = 0;
				else
					mm[i+1][j+1] = board[i][j]-'0';
			}
		}
		for(int i = 0;i<=324;i++)
		{
			S[i] = 0;
			R[i] = i+1;
			L[i+1] = i;
			U[i] = D[i] = i;
		}
		R[324] = 0;
		size = 325;
		memset(H,-1,sizeof(H));
		r = 0;
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				if(mm[i][j]!=0)
				{
					r++;
					hashx1[r] = i;
					hashx2[r] = j;
					hashx[r] = mm[i][j];
					Link(r,(i-1)*9+j);
					Link(r,(i-1)*9+mm[i][j]+81);
					Link(r,(j-1)*9+mm[i][j]+162);
					Link(r,((i-1)/3)*27+((j-1)/3)*9+mm[i][j]+243);
				}
				else
				{
					for(int k = 1;k<=9;k++)
					{
						r++;
						hashx1[r] = i;
						hashx2[r] = j;
						hashx[r] = k;
						Link(r,(i-1)*9+j);
						Link(r,(i-1)*9+k+81);
						Link(r,(j-1)*9+k+162);
						Link(r,((i-1)/3)*27+((j-1)/3)*9+k+243);
					}
				}
			}
		}
		Dance(0);
		board.clear();
		vector<char> sss(0);
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				char c = mm[i][j]+'0';
				sss.push_back(c);
			}
			board.push_back(sss);
			sss.clear();
		}
    }
};
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	char s[10];
	vector<vector<char>> v;
	while(scanf("%s",s)!=EOF)
	{
		vector<char> ss(s,s+9);
		v.push_back(ss);
	}
	Solution s1;
	s1.solveSudoku(v);

}