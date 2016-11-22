// hdu-5046-重复覆盖.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define maxnode 4000
#define N 70  
#define M 70  
int U[maxnode],D[maxnode],L[maxnode],R[maxnode],C[maxnode],X[maxnode];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针  
int H[N],S[M];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果  
int size,n,m,K;
bool vis[maxnode];  
  
void remove(int c)  //删除一列，与精确覆盖的区别是：精确覆盖要求每列只在某行出现一次，而重复覆盖要求最少的行使得每列至少出现一次
{ //重复覆盖的remove只将当前列的每个元素移除 不改变移除元素所在行的元素那个列
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //恢复
{  
    for(int i = U[c]; i != c; i = U[i])  
        R[L[i]] = L[R[i]] = i;  
}
int h()  //计算一个上限
{  
    int i,j,c;  
    memset(vis,0,sizeof(vis));  
    int ans = 0;  
    for(c = R[0] ; c ; c = R[c])  //考虑当前剩余的每个列
    {  
        if(!vis[c])  
        {  
            ans++;  //至少还要一步 解决这个c列的覆盖问题 解决一列覆盖问题的方法是选定列上一个元素 将其所在行作为解  行上元素所在的列被改行覆盖 列可以被标记
            for(i = D[c]; i != c; i = D[i])  //列上的每个元素
                for(j = R[i]; j != i; j = R[j])  //元素所在的行
                    vis[C[j]] = true;  //对应的列标记  说明已经被覆盖
        }  
    }  
    return ans;  
} 

bool Dance(int dep)  
{  
    if(R[0] == 0)  //没有要考虑的列了  全部覆盖完成  结束
        return dep<=K;  
    if(dep + h() > K)       //A_Star剪枝  
        return false;  
  
    int i,j,tmp,c;  
  
    for(tmp=100000,i=R[0]; i; i=R[i])  //记录1最少的列 列号为c
        if(S[i]<tmp)tmp=S[c=i];  
      
    for(i=D[c]; i!=c; i=D[i])  //对列上每个元素
    {  
        remove(i);  //remove(i)将删除c列上除i以外的其他1，即将i所在的行作为解的一部分 则已经包含了当前c列 c列其他的1不需要再考虑了 remove掉 
        for(j=R[i]; j!=i; j=R[j])remove(j);  //对i行的每个1，对应的那个列也被这i所在的行覆盖了 那么这个列上的其他的1也不会对后续的计算有影响 应remove掉
        if(Dance(dep+1))return 1;  
        for(j=L[i]; j!=i; j=L[j])resume(j);//在这里我遵循的原则是先删除的后还原，后删除的先还原。  
        resume(i);  
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
struct Point
{
    int x,y;
    void input()
    {
        scanf("%d%d",&x,&y);
    }
}city[M];
long long dis(Point a,Point b)
{
    return (long long)abs(a.x-b.x)+(long long)abs(a.y-b.y);
}
void build(int _n,int _m)
{
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m+1;
        for(int i = 1;i <= n;i++)
            H[i] = -1;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int T;
    int n;
    scanf("%d",&T);
    int iCase = 0;
    while(T--)
    {
        iCase++;
        scanf("%d%d",&n,&K);
        assert(n >= 1 && n <= 60 && K >= 1 && K <= n);
        for(int i = 0;i < n;i++){
            city[i].input();
            assert(abs(city[i].x) <= 1000000000);
            assert(abs(city[i].y) <= 1000000000);
        }
        long long l = 0, r = 100000000000LL;
        long long ans = 0;
        while(l <= r)
        {
            long long mid = (l+r)/2;
			build(n,n);
			for(int i=0;i<n;i++)
			{  
				for(int j=0;j<n;j++)
				{  
					if(dis(city[i],city[j]) <= mid)
					   Link(i+1,j+1); 
				}  
			}
            if(Dance(0)){r = mid-1;ans = mid;}
            else l = mid+1;
        }
        printf("Case #%d: %I64d\n",iCase,ans);
    }
    return 0;
}
