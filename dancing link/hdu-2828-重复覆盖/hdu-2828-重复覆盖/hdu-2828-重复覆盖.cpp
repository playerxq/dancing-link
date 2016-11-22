// hdu-2828-重复覆盖.cpp : 定义控制台应用程序的入口点。
//n列表是n个灯  2m行表示每个开关的开关状态

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

#define N 2080  
#define M 2080  
#define maxnode N*M
int U[maxnode],D[maxnode],L[maxnode],R[maxnode],C[maxnode],X[maxnode];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针  
int H[M],S[N];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果  
int size,n,m,k;
bool vis[maxnode];  
  
void remove(int c)
{
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //恢复
{  
    for(int i = U[c]; i != c; i = U[i])  
        R[L[i]] = L[R[i]] = i;  
}

bool Dance(int dep)  
{  
    if(R[0] == 0)  //没有要考虑的列了  全部覆盖完成  结束
        return 1;  
    int i,j,tmp,c;
    for(tmp=100000,i=R[0]; i; i=R[i])  //记录1最少的列 列号为c
        if(S[i]<tmp)tmp=S[c=i];  
      
    for(i=D[c]; i!=c; i=D[i])  //对列上每个元素
    {  
		if((X[i]&1)&&(vis[X[i]+1])) continue;//奇数行代表开 偶数行是关 奇数行代表了一个开关的第一个状态 若下一行偶数行选中 表示开关已经选中 略去
		if((X[i]&1)==0&&(vis[X[i]-1])) continue;
        remove(i);
		vis[X[i]]=1;
        for(j=R[i]; j!=i; j=R[j])remove(j);  //对i行的每个1，对应的那个列也被这i所在的行覆盖了 那么这个列上的其他的1也不会对后续的计算有影响 应remove掉
        if(Dance(dep+1))return 1;  
        for(j=L[i]; j!=i; j=L[j])resume(j);//在这里我遵循的原则是先删除的后还原，后删除的先还原。  
        resume(i);  
		vis[X[i]]=0;
    }  
  
    return 0;  
} 
void Link(int r,int c)  //(r,c)处是size号节点
{  
    ++S[C[size]=c];  //C[size]即size号节点所属的列是c,列上1数目+1
	//将size插入当前的c列的循环链表中，插入的是c下面 即c头节点后
    D[size]=D[c];  //size号节点的下指针指向当前列的下指针
    U[D[c]]=size;  //当前列下指针节点的上面是size号节点
    U[size]=c;  //
    D[c]=size;  
    if(H[r]<0)H[r]=L[size]=R[size]=size;  //做横向表头
    else  
    {  
        R[size]=R[H[r]];  //插入横向表头H[r]后面
        L[R[H[r]]]=size;  
        L[size]=H[r];  
        R[H[r]]=size;  
    }  
    X[size++]=r;  //size号节点指向r行
}
void build(int m,int n)
{
        for(int i = 0;i <= n;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[n] = 0; L[0] = n;
        size = n+1;
        for(int i = 1;i <= m;i++)
            H[i] = -1;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(vis,0,sizeof(vis));
		build(2*m,n);
		for(int i = 1;i<=n;i++)
		{
			scanf("%d",&k);
			for(int j = 1;j<=k;j++)
			{
				int x;
				scanf("%d",&x);
				char op[4];
				scanf("%s",op);
				if(op[1]=='N')
				{
					Link(2*x-1,i);
				}
				else
					Link(2*x,i);
			}
		}
		if(!Dance(0))
			printf("-1\n");
		else
		{
			for(int i = 1;i<=m;i++)
			{
				if(vis[i<<1])//偶数  关
					printf("OFF");
				else
					printf("ON");
				if(i==m)
					printf("\n");
				else
					printf(" ");
			}
		}
	}
}

