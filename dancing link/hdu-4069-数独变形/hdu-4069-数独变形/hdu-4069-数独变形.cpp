// hdu-4069-数独变形.cpp : 定义控制台应用程序的入口点。
//
// hdu-1426-数独精确覆盖.cpp : 定义控制台应用程序的入口点。
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
int size,r;
int map[10][10];
void remove(int c)
{
	R[L[c]]=R[c];
	L[R[c]]=L[c];
	for(int i = D[c];i!=c;i=D[i])
	{
		for(int j = R[i];j!=i;j=R[j])
		{
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			--S[C[j]];
		}
	}
}
void resume(int c)
{
	for(int i = U[c];i!=c;i=U[i])
	{
		for(int j = L[i];j!=i;j=L[j])
		{
			U[D[j]]=j;
			D[U[j]]=j;
			++S[C[j]];
		}
	}
	R[L[c]]=c;
	L[R[c]]=c;
}
void Link(int r, int c)
{
	S[c]++;
	C[size]=c;
	Row[size]=r;
	U[size]=U[c];
	D[U[c]]=size;
	D[size]=c;
	U[c]=size;
	if(H[r]==-1) H[r]=L[size]=R[size]=size;
	else
	{
		L[size]=L[H[r]];
		R[L[H[r]]]=size;
		R[size]=H[r];
		L[H[r]]=size;
	}
	++size;
}
void check()
{
    int i;
    for(i=0;i<81;i++)
         map[hashx1[OK[i]]][hashx2[OK[i]]]=hashx[OK[i]];
}
int cnt;
int Dance(int k)
{
	int i,j,Min,c;
	if(R[0]==0)
	{
		check();
		cnt++;
		return 1;
	}
	for(Min=RR,i=R[0];i;i=R[i])//选取最小的1数目所在的列
	{
		if(Min>S[i]) {Min=S[i];c=i;}
	}
	remove(c);
	for(i=D[c];i!=c;i=D[i])//假设i所在的行选择  则该行上的1所在的列上每个1所在的行不可能选中 因此将这些列remove掉 即去除列上1所在的行
     {
         for(j=R[i];j!=i;j=R[j])
             remove(C[j]);
         OK[k]=Row[i];//记录选择的行
         Dance(k+1);
		 if(cnt>1)
			 return 1;
         for(j=L[i];j!=i;j=L[j])
             resume(C[j]);
     }
     resume(c);
	 return 0;
}
int id[20][20];
int a[20][20];
int N = 9;
void bfs(int sx,int sy,int d)
{
	queue<pair<int,int> >q;
	q.push(make_pair(sx,sy));
	id[sx][sy] = d;//起始格的宫号
	while(!q.empty())
	{
		pair<int,int> tmp = q.front();
		int x = tmp.first;
		int y = tmp.second;
		q.pop();
		if(x > 0 && ((a[x][y]%32)/16) == 0)//依次考虑上下左右的格子
			if(id[x-1][y] == -1)
			{
				id[x-1][y] = d;
				q.push(make_pair(x-1,y));
			}
		if(x < N-1 && ((a[x][y]%128)/64) == 0)
			if(id[x+1][y] == -1)
			{
				id[x+1][y] = d;
				q.push(make_pair(x+1,y));
			}
		if(y > 0 && ((a[x][y])/128) == 0)
			if(id[x][y-1] == -1)
			{
				id[x][y-1] = d;
				q.push(make_pair(x,y-1));
			}
		if(y < N-1 && ((a[x][y]%64)/32) == 0)
			if(id[x][y+1] == -1)
			{
				id[x][y+1] = d;
				q.push(make_pair(x,y+1));
			}
	}
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int T;
	scanf("%d",&T);
	int iCase = 0;
	while(T--)
	{
		iCase++;
		for(int i = 0;i < N;i++)
			for(int j = 0;j < N;j++)
				scanf("%d",&a[i][j]);
		memset(id,-1,sizeof(id));
		int index = 0;
		for(int i = 0;i < 9;i++)
			for(int j = 0;j < 9;j++)
				if(id[i][j] == -1)//找到对应的宫
					bfs(i,j,++index);
		for(int i = 0;i<=324;i++)
		{
			S[i]=0;
			R[i]=i+1;
			L[i+1]=i;
			U[i]=D[i]=i;
		}
		R[324]=0;
		size = 325;
		memset(H,-1,sizeof(H));
		r = 0;
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				for(int k = 1;k <= 9;k++)
				{
					if(a[i-1][j-1]%16 != 0 && a[i-1][j-1]%16 != k)continue;
					map[i][j]=k;
					if(map[i][j]!=0)
					{
						r++;//新增一行
						hashx1[r]=i;
						hashx2[r]=j;
						hashx[r]=map[i][j];//记录下值
						Link(r,(i-1)*9+j);//(i,j)格填一个数 对应列(i-1)*9+j
						Link(r,(i-1)*9+map[i][j]+81);//i行填map[i][j]
						Link(r,(j-1)*9+map[i][j]+162);//j列填map[i][j]
						Link(r,243+(id[i-1][j-1]-1)*9+map[i][j]);//g宫填map[i][j]
					}
					else
					{
						//枚举(i,j)中填1:9
						for(int k = 1;k<=9;k++)
						{
							r++;
							hashx1[r]=i;
							hashx2[r]=j;
							hashx[r]=k;//记录下值
							Link(r,(i-1)*9+j);//(i,j)格填一个数 对应列(i-1)*9+j
							Link(r,(i-1)*9+k+81);//i行填map[i][j]
							Link(r,(j-1)*9+k+162);//j列填map[i][j]
							int g = int((i-1)/3*3+int((j-1)/3))+1;
							Link(r,243+(i-1)/3*27 + (j-1)/3*9 + k);//g宫填map[i][j]
						}
					}
				}
			}
		}
		cnt = 0;
		Dance(0);
		printf("Case %d:\n",iCase);
		if(cnt == 0)printf("No solution\n");
		else if(cnt > 1)printf("Multiple Solutions\n");
		else
		{
			for(int i = 1;i<=9;i++)
			{
				for(int j = 1;j<=9;j++)
				{
					printf("%d",map[i][j]);
				}
				printf("\n");
			}
		}
	}
    return 0;
}



