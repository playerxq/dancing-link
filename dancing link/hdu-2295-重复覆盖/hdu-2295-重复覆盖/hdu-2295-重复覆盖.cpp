// hdu-2295-重复覆盖.cpp : 定义控制台应用程序的入口点。
//重复覆盖要求是在0/1矩阵中选择最少的行使每一列至少有一个1
/*
DLX重复覆盖对于当前矩阵的处理是，将当前列去掉，并将选作当前列的解的行能够覆盖到的列全部去掉（这些行做解的时候已经包含了这些列的1，因此不用再考虑这些列了）。
因为不需要每列仅由一个1去覆盖（可以若干个），因此不必要把能够覆盖某一列的所有行全部去掉。
因此remove和resume函数的写法将会有所不同
*/
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
#define N 55  
#define M 55*55  
int U[M],D[M],L[M],R[M],C[M],X[M];//x代表M所属的行，c代表M所属的列，U，D，L，R为一个元素的上下左右指针  
int H[N],S[N];//H是水平循环链表的头指针，S代表每一列的元素个数，Q存储一个可能结果  
int size,n,m,k;  
double city[N][2];  
double radar[N][2];  
double dis[N][N];       //dis[i][j]表示雷达i到cityj的距离  
int mx[N][N];  
bool vis[N];  
  
void remove(int c)  //删除一列，与精确覆盖的区别是：精确覆盖要求每列只在某行出现一次，而重复覆盖要求最少的行使得每列至少出现一次
{ //重复覆盖的remove只将当前列的每个元素移除 不改变移除元素所在行的元素那个列
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //恢复
{  
    for(int i = D[c]; i != c; i = D[i])  
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
        return true;  
    if(dep + h() > k)       //A_Star剪枝  
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
bool build(double mid){  //建链
    memset(mx,0,sizeof(mx));  
    for(int i=1;i<=n;i++){  //城市做列
        int flag=0;  
        for(int j=1;j<=m;j++){  //雷达做行  即选出若干行使得每列至少被一行覆盖
            if(dis[j][i] - mid < 1e-8){  //距离允许
                mx[j][i] = 1;  
                flag=1;  
            }  
        }  
        if(!flag)  //全为0
            return 0;  
    }  
  
    for(int i=0; i<=n; ++i)  
    {  
        S[i]=0;  
        D[i]=U[i]=i;  
        L[i+1]=i;  
        R[i]=i+1;  
    }  
    R[n]=0;  
    size=n+1;  //0为头 1:n个列 表中节点从n+1开始标记
    for(int i=1; i<=m; ++i)  
        H[i]=-1;  
  
    for(int i=1;i<=m;i++){  
        for(int j=1;j<=n;j++){  
            if(mx[i][j])  
                Link(i,j);  
        }  
    }  
    return 1;  
}
bool OK(double mid)  
{  
    if(build(mid))  
        return Dance(0);  
    else  
        return false;  
}
double solve()  //2分答案
{  
    double low = 0;  
    double high = 1500;  
    while(low+1e-8<high)  
    {  
        double mid = (low+high)/2.0;  
        if(OK(mid))  
            high = mid;  
        else  
            low = mid;  
    }  
    return high;  
} 
double Dis(int i, int j)  //计算距离
{  
    return sqrt((double)(radar[i][0]-city[j][0])*(radar[i][0]-city[j][0])+(radar[i][1]-city[j][1])*(radar[i][1]-city[j][1]));  
}  
  
void Init()  
{  
    int i,j;  
    for(i = 1; i <= m; i++)  
        for(j = 1; j <= n; j++)  
            dis[i][j] = Dis(i,j);  
} 
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int i,t;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d %d %d",&n,&m,&k);  
        for(i = 1; i <= n; i++)  
            scanf("%lf %lf",&city[i][0],&city[i][1]);  
        for(i = 1; i <= m; i++)  
            scanf("%lf %lf",&radar[i][0],&radar[i][1]);  
        Init();  
        printf("%.6lf\n",solve());  
    }  
    return 0; 
}

