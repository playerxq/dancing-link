// hdu-2828-�ظ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//n�б���n����  2m�б�ʾÿ�����صĿ���״̬

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
int U[maxnode],D[maxnode],L[maxnode],R[maxnode],C[maxnode],X[maxnode];//x����M�������У�c����M�������У�U��D��L��RΪһ��Ԫ�ص���������ָ��  
int H[M],S[N];//H��ˮƽѭ�������ͷָ�룬S����ÿһ�е�Ԫ�ظ�����Q�洢һ�����ܽ��  
int size,n,m,k;
bool vis[maxnode];  
  
void remove(int c)
{
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //�ָ�
{  
    for(int i = U[c]; i != c; i = U[i])  
        R[L[i]] = L[R[i]] = i;  
}

bool Dance(int dep)  
{  
    if(R[0] == 0)  //û��Ҫ���ǵ�����  ȫ���������  ����
        return 1;  
    int i,j,tmp,c;
    for(tmp=100000,i=R[0]; i; i=R[i])  //��¼1���ٵ��� �к�Ϊc
        if(S[i]<tmp)tmp=S[c=i];  
      
    for(i=D[c]; i!=c; i=D[i])  //������ÿ��Ԫ��
    {  
		if((X[i]&1)&&(vis[X[i]+1])) continue;//�����д��� ż�����ǹ� �����д�����һ�����صĵ�һ��״̬ ����һ��ż����ѡ�� ��ʾ�����Ѿ�ѡ�� ��ȥ
		if((X[i]&1)==0&&(vis[X[i]-1])) continue;
        remove(i);
		vis[X[i]]=1;
        for(j=R[i]; j!=i; j=R[j])remove(j);  //��i�е�ÿ��1����Ӧ���Ǹ���Ҳ����i���ڵ��и����� ��ô������ϵ�������1Ҳ����Ժ����ļ�����Ӱ�� Ӧremove��
        if(Dance(dep+1))return 1;  
        for(j=L[i]; j!=i; j=L[j])resume(j);//����������ѭ��ԭ������ɾ���ĺ�ԭ����ɾ�����Ȼ�ԭ��  
        resume(i);  
		vis[X[i]]=0;
    }  
  
    return 0;  
} 
void Link(int r,int c)  //(r,c)����size�Žڵ�
{  
    ++S[C[size]=c];  //C[size]��size�Žڵ�����������c,����1��Ŀ+1
	//��size���뵱ǰ��c�е�ѭ�������У��������c���� ��cͷ�ڵ��
    D[size]=D[c];  //size�Žڵ����ָ��ָ��ǰ�е���ָ��
    U[D[c]]=size;  //��ǰ����ָ��ڵ��������size�Žڵ�
    U[size]=c;  //
    D[c]=size;  
    if(H[r]<0)H[r]=L[size]=R[size]=size;  //�������ͷ
    else  
    {  
        R[size]=R[H[r]];  //��������ͷH[r]����
        L[R[H[r]]]=size;  
        L[size]=H[r];  
        R[H[r]]=size;  
    }  
    X[size++]=r;  //size�Žڵ�ָ��r��
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
				if(vis[i<<1])//ż��  ��
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

