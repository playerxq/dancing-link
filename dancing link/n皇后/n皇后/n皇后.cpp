//完全使用舞蹈连模拟n*n矩阵 添加斜线方向的链接
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;

int const N = 100;
int const M = 3000;

int U[M],D[M],L[M],R[M],L_U[M],L_D[M],R_U[M],R_D[M],C[M],X[M];//L_U为左上 L_D左下 R_U右上 R_D右下
int H[N],Q[N],S[N];
int n,size;
int map[100][100];
void Link(int r,int c)
{
    L_U[size] = L_D[size] = size;
    R_U[size] = R_D[size] = size;
    if( r != 1 )//对于第一行 作为斜线表头  L_U L_D R_U R_D只需指向自己即可
    {
        int i;
        if(c!=n)//不是最后一列 存在R[U[c]]
        {
			//将size插入到该列最后位置  即U[c]之后
            i = R[U[c]];//原来U[c]右侧i 插入使得size放到i的左下方
			//逐行逐列添加  此时L_D[i]应循环到表头
            R_U[L_D[i]] = size;//表头的右上循环到尾部size
            L_D[size] = L_D[i];//循环到头部
            L_D[i] = size;//
            R_U[size] = i;//
        }
        if(c!=1)//存在左上 由于逐行逐列 因此此时i的R_D为指向斜线表头
        {
            i = L[U[c]];
            L_U[R_D[i]] = size;//表头的左上循环到尾部size上
            R_D[size] = R_D[i];//size的右下就是原来i的右下 实质是指向斜线表头
            R_D[i] = size;
            L_U[size] = i;
        }
    }
	//将size放到该列尾部
    C[size] = c;
    U[size] = U[c];
    D[U[c]] = size;
    D[size] = c;
    U[c] = size;
    if(H[r] < 0) H[r] = L[size] = R[size] = size;
    else
    {//横向的尾部
        L[size] = L[H[r]];
        R[L[H[r]]] = size;
        R[size] = H[r];
        L[H[r]] = size;
    }
    X[size++] = r;//size所在的行
}
//删除(h,c)位置 将导致h行 c列以及两条斜线的删除
void remove(int h,int c)
{
    L[R[c]] = L[c];R[L[c]] = R[c];//列头去除
    for(int i = D[c]; i!=c; i = D[i])//对c列的每个元素
    {
        if(X[i] == h)//找到(h,c)元素
        {
            for(int j = L_U[i]; j!=i; j = L_U[j])//沿左上右下的斜线 将相应点的L R U D断开
            {
                U[D[j]] = U[j];D[U[j]] = D[j];//断开U D
                L[R[j]] = L[j];R[L[j]] = R[j];//断开L R
                L_D[R_U[j]] = L_D[j];R_U[L_D[j]] = R_U[j];//断开L_D R_U
                S[C[j]]--;
            }
            for(int j = R_U[i]; j!=i; j = R_U[j])//沿左下右上的斜线
            {
                U[D[j]] = U[j];D[U[j]] = D[j];
                L[R[j]] = L[j];R[L[j]] = R[j];
                R_D[L_U[j]] = R_D[j];L_U[R_D[j]] = L_U[j];
                S[C[j]]--;
            }
            for(int j = R[i]; j!=i; j = R[j])//删除这行除i以外的元素与上下行的连接（i的保存是为后续的resume）
            {
                U[D[j]] = U[j]; D[U[j]] = D[j];//不删除L R以为resume
                R_D[L_U[j]] = R_D[j];L_U[R_D[j]] = L_U[j];
                L_D[R_U[j]] = L_D[j];R_U[L_D[j]] = R_U[j];
                S[C[j]]--;
            }
        }
        else//不是h行的  只需删除c列上的元素
        {
            L[R[i]] = L[i];R[L[i]] = R[i];//只删L R不删 U D
            L_D[R_U[i]] = L_D[i];R_U[L_D[i]] = R_U[i];
            R_D[L_U[i]] = R_D[i];L_U[R_D[i]] = L_U[i];
        }
    }
	//删除后c列上的U D依然保持  为resume
}

void resume(int h,int c)
{
    L[R[c]] = R[L[c]] = c;
    for(int i = U[c]; i!=c; i = U[i])
    {
        if(X[i] == h)
        {
            for(int j = L[i]; j!=i; j = L[j])
            {
                L_D[R_U[j]] = R_U[L_D[j]] = j;
                R_D[L_U[j]] = L_U[R_D[j]] = j;
                U[D[j]] = D[U[j]] = j;
                S[C[j]]++;
            }
            for(int j = L_D[i]; j!=i; j = L_D[j])
            {
                R_D[L_U[j]] = L_U[R_D[j]] = j;
                L[R[j]] = R[L[j]] = j;
                U[D[j]] = D[U[j]] = j;
                S[C[j]]++;
            }
            for(int j = R_D[i]; j!=i; j = R_D[j])
            {
                L_D[R_U[j]] = R_U[L_D[j]] = j;
                L[R[j]] = R[L[j]] = j;
                U[D[j]] = D[U[j]] = j;
                S[C[j]]++;
            }
        }
        else
        {
            L[R[i]] = R[L[i]] = i;
            L_D[R_U[i]] = R_U[L_D[i]] = i;
            R_D[L_U[i]] = L_U[R_D[i]] = i;
        }
    }
}
int cnt;
void Dance(int k)
{
    if(!R[0])
    {
        if(k==n)
			cnt++;
		/*
		memset(map,0,sizeof(map));
		for(int i = 1;i<=n;i++)
			map[Q[i]][i]=1;
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=n;j++)
			{
				printf("%d ",map[i][j]);
			}
			printf("\n");
		}
		*/
        return;
    }
    int tmp = n+1,c;
    for(int i = R[0]; i; i = R[i])
    {
        if( S[i] == 0 ) return;//没有解
        if( S[i] < tmp ) tmp = S[i],c = i;//找到元素最少的一列
    }


    for(int i = D[c]; i!=c; i=D[i])//依次在这列的每个位置上放皇后
    {
        Q[c] = X[i];//保存c列上对应的行即(x[i],c)位置放置皇后
        remove(X[i],c);
        Dance(k+1);
        resume(X[i],c);
	}
	return;
}
//int s[11];
void init(int n)
{
	int i,j,num;cnt = 0;
	for(i = 0; i<=n; i++)//初始化n列 
    {
        C[i] = i;
        U[i] = D[i] = i;
        L_U[i] = L_D[i] = i;//列头的斜线指向自己
        R_U[i] = R_D[i] = i;
        R[i] = i+1;
        L[i+1] = i;
        S[i] = n;
    }
    R[n] = 0;
    size = n+1;

    for(i = 1; i<=n; i++)
    {
       H[i] = -1;
       for(j = 1; j<=n; j++)
            Link(i,j);
    }
    Dance(0);
	//s[n] = cnt;
}
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        init(n);
    }
};
int main()
{
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	//init();
    while(scanf("%d",&n)!=EOF&&n)
    {
		//printf("%d\n",s[n]);
    }

}