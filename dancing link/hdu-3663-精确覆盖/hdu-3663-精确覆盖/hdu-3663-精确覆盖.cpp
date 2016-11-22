//��Ϊ��������Ϊ����

//ѡ��һЩ���й���ʱ�����䣬ʹ�����г�����D�������ڶ����Եõ�����
//���Ƿ������������Ǽ�����еķ������䣬����о��Ƿ������䣬���в�ֳ�С����
//��ÿ�����п��Թ��������[si,ei],���Բ��Ϊ������D��С���䣬����si,ei�����[1��5]����˹����Բ��D<=5��16��С���䣨���[1,5],��С[0,0]��
//n�����п��Թ���n*16�У�ÿһ�д�����п��ܵĹ������� (i-1)16+j�д����˵�i������ѡ���j������

//�������ƣ�2�����ƣ�һ����ÿ�����з���һ�Σ�һ����D������������
//ǰn�д���n�����У���ÿ�����б�����ֻ�ܱ�����һ�Σ�������һ�Ρ�֮��ÿ������D�У���ʾ��ÿ���Ƿ�ĳ��������и��ǣ���һ��n*D+n��
//��(i-1)D+j�б�ʾ��i�����е�j�츲�����
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
        ak=k;//ѡ��Ĺ��������Ŀ
        flag=1;//�ҵ�һ������
        return;
    }
    for(Min=RR,i=R[0];i;i=R[i])
        if(Min>S[i]) Min=S[i],c=i;
    remove(c);
    for(i=D[c];i!=c;i=D[i])
    {
        OK[k]=Row[i];//ѡ����к�
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
            mark[i][i]=1;//�Լ����Ը��Լ�����
        for(i=1;i<=n;i++)
            scanf("%d%d",&s[i].st,&s[i].ed);//ÿ�����п��õ�����
        memset(H,-1,sizeof(H));
        memset(Row,0,sizeof(Row));
        cc=0;//���� n*D+n
		//ÿ������D����ÿһ�춼��һ��
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=d;j++)
            {
                s2[++cc].num=i;//�ж�Ӧ����
                s2[cc].day=j;//�ж�Ӧ��
            }
        }
        cc+=n;//����������һ�� ��ʾ����һ��
        for(i=0;i<=cc;i++)
        {
            S[i]=0;
            U[i]=D[i]=i;
            L[i+1]=i;R[i]=i+1; 
        }
		R[cc]=0;
        size=cc+1;
        rr=0;//����
		//�У�ÿ�����й�������[1,D]���Ϊ������D��С��������
		//si ei�������D����  ���ö��si ei��������ϾͿ���
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
		//�������еĸ��ǹ�ϵ
        for(i=1;i<=rr;i++)
        {
            for(j=1;j<=cc;j++)
            {
                ans1=s1[i].num;//�д��������
                if(!(s1[i].st>=s[ans1].st && s1[i].ed<=s[ans1].ed) && s1[i].st!=0) continue;//����д������䲻������ans1���п������� ��Ч
                if(j<=n*d)//�д���ĳ������ans2��ĳ��
                {        
                    ans2=s2[j].num;//����
                    if(s2[j].day>=s1[i].st && s2[j].day<=s1[i].ed && mark[ans1][ans2]) //�д�����촦���еĹ����������е���
						Link(i,j);  
                }
                else//�д���һ������j-nd
                {
                    if(ans1==j-n*d) //����һ��
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