//行为方案，列为限制

//选择一些城市供电时间区间，使得所有城市在D个天数内都可以得到供电
//行是方案，方案就是计算城市的发电区间，因此行就是发电区间，进行拆分成小区间
//对每个城市可以供电的区间[si,ei],可以拆分为不超过D的小区间，由于si,ei最大是[1，5]，因此共可以拆成D<=5的16个小区间（最大[1,5],最小[0,0]）
//n个城市可以构成n*16行，每一行代表城市可能的供电区间 (i-1)16+j行代表了第i个城市选择第j个区间

//列是限制，2个限制，一个是每个城市发电一次，一个是D天连续被覆盖
//前n列代表n个城市，即每个城市必须且只能被覆盖一次，即发电一次。之后每个城市D列，表示其每天是否被某个供电城市覆盖，故一共n*D+n列
//第(i-1)D+j列表示第i个城市第j天覆盖情况
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
# define RR 1000
# define CC 400
# define V RR*CC
int U[V],D[V];
int L[V],R[V];
int C[V];
int S[CC],H[RR];
int OK[65],mark[65][65];
int Row[V];
int n,m,d,size,flag,ak;
int dir[6]={1,2,4,7,11,16};
struct node{
    int st,ed;
}s[155],s3[65];
struct node4{
    int num,st,ed;
	friend int operator < (node4 a, node4 b)
	{
		return a.num<b.num;
	}
}s4[65];
struct node1{
    int num,st,ed;
}s1[RR];
struct node2{
    int num,day;
}s2[CC];
void Link(int r,int c)
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
    size++;
}
void remove(int c)
{
    int i,j;
    L[R[c]]=L[c];
    R[L[c]]=R[c];
    for(i=D[c];i!=c;i=D[i])
    {
        for(j=R[i];j!=i;j=R[j])
        {
            S[C[j]]--;
            U[D[j]]=U[j];
            D[U[j]]=D[j];
        }
    }
}
void resume(int c)
{
    int i,j;
    for(i=U[c];i!=c;i=U[i])
    {
        for(j=L[i];j!=i;j=L[j])
        {
            S[C[j]]++;
            U[D[j]]=D[U[j]]=j;
        }
    }
    L[R[c]]=R[L[c]]=c;
}
void Dance(int k)
{
    int i,j,c,Min;
    if(!R[0])
    {
        ak=k;//选择的供电城市数目
        flag=1;//找到一个方案
        return;
    }
    for(Min=RR,i=R[0];i;i=R[i])
        if(Min>S[i]) Min=S[i],c=i;
    remove(c);
    for(i=D[c];i!=c;i=D[i])
    {
        OK[k]=Row[i];//选择的行号
        for(j=R[i];j!=i;j=R[j])
            remove(C[j]);
        Dance(k+1);
        if(flag) return;
        for(j=L[i];j!=i;j=L[j])
            resume(C[j]);
    }
    resume(c);
}
int cmp(const void* _a, const void* _b)
{
	node4* a = (node4*)_a;
	node4* b = (node4*)_b;
	return a->num-b->num;
}
int main()
{
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int i,j,i1,i2,ans1,ans2,rr,cc,r,ans,a,b;
    while(scanf("%d%d%d",&n,&m,&d)!=EOF)
    {
		flag = 0;
        memset(mark,0,sizeof(mark));
        for(i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            mark[a][b]=mark[b][a]=1;
        }
        for(i=1;i<=n;i++)
            mark[i][i]=1;//自己可以给自己供电
        for(i=1;i<=n;i++)
            scanf("%d%d",&s[i].st,&s[i].ed);//每个城市可用的区间
        memset(H,-1,sizeof(H));
        memset(Row,0,sizeof(Row));
        cc=0;//列数 n*D+n
		//每个城市D天内每一天都做一列
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=d;j++)
            {
                s2[++cc].num=i;//列对应城市
                s2[cc].day=j;//列对应天
            }
        }
        cc+=n;//城市自身做一列 表示发电一次
        for(i=0;i<=cc;i++)
        {
            S[i]=0;
            U[i]=D[i]=i;
            L[i+1]=i;R[i]=i+1; 
        }
		R[cc]=0;
        size=cc+1;
        rr=0;//行数
		//行，每个城市供电区间[1,D]拆分为不超过D的小区间做行
		//si ei本身就是D以内  因此枚举si ei的所有组合就可以
        for(i=1;i<=n;i++)
        {
            for(i1=1;i1<=d;i1++)//
			{
                for(i2=i1;i2<=d;i2++)
                {
                    s1[++rr].num=i;
                    s1[rr].st=i1;
                    s1[rr].ed=i2;
                }
			}
            s1[++rr].num=i;
            s1[rr].st=0;
            s1[rr].ed=0;
        }
		//看行与列的覆盖关系
        for(i=1;i<=rr;i++)
        {
            for(j=1;j<=cc;j++)
            {
                ans1=s1[i].num;//行代表供电城市
                if(!(s1[i].st>=s[ans1].st && s1[i].ed<=s[ans1].ed) && s1[i].st!=0) continue;//如果行代表区间不包含于ans1城市可用区间 无效
                if(j<=n*d)//列代表某个城市ans2的某天
                {        
                    ans2=s2[j].num;//城市
                    if(s2[j].day>=s1[i].st && s2[j].day<=s1[i].ed && mark[ans1][ans2]) //列代表的天处于行的供电区间且有电线
						Link(i,j);  
                }
                else//列代表一个城市j-nd
                {
                    if(ans1==j-n*d) //发电一次
						Link(i,j);
                }
            }
        }
		Dance(0);
		if(!flag)
			printf("No solution\n\n");
		else
		{
			for(int i = 0;i<ak;i++)
			{
				s4[i].num=s1[OK[i]].num;
				s4[i].st=s1[OK[i]].st;
				s4[i].ed=s1[OK[i]].ed;
			}
			sort(s4,s4+ak);
			for(int i = 0;i<ak;i++)
			{
				printf("%d %d\n",s4[i].st,s4[i].ed);
			}
			printf("\n");
		}
	}
	return 0;
}