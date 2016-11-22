// poj-3076-����-��ȷ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

// poj-3074-����-��ȷ����.cpp : �������̨Ӧ�ó������ڵ㡣
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
using namespace std;
#define RR 750//�յ�λ�ÿ�����չΪ9��  ���81����λ
#define CC 350//��Լ����324
#define V RR*CC
int hashx1[RR],hashx2[RR],hashx[RR],OK[90];//����81��  ��Ϊ81������  ÿ�����Ӷ�Ӧһ��
int U[V],R[V],L[V],D[V];
int C[V],Row[V];
int H[RR],S[CC];
int map[10][10];
int size,r;
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
int get_ans()//�õ�һ���  ����һ����
{
    int i;
    for(i=0;i<81;i++)//�Եõ���ÿһ�� OK[i] hashx1��¼���д������ʵ�� hashx2��¼��ʵ�� hashx��¼ֵ
         map[hashx1[OK[i]]][hashx2[OK[i]]]=hashx[OK[i]];
	return 0;
}
int Dance(int k)
{
	int i,j,Min,c;
	if(R[0]==0)
	{
		get_ans();
		return 1;
	}
	for(Min=RR,i=R[0];i;i=R[i])//ѡȡ��С��1��Ŀ���ڵ���
	{
		if(Min>S[i]) {Min=S[i];c=i;}
	}
	remove(c);
	for(i=D[c];i!=c;i=D[i])//����i���ڵ���ѡ��  ������ϵ�1���ڵ�����ÿ��1���ڵ��в�����ѡ�� ��˽���Щ��remove�� ��ȥ������1���ڵ���
     {
         for(j=R[i];j!=i;j=R[j])
             remove(C[j]);
         OK[k]=Row[i];//��¼ѡ�����
         if(Dance(k+1)) return 1;
         for(j=L[i];j!=i;j=L[j])
             resume(C[j]);
     }
     resume(c);
	 return 0;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	char str[90];
	while(scanf("%s",str+1)!=EOF)
	{
		if(str[1]=='e')
			break;
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
		memset(map,0,sizeof(map));
		r = 0;
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				if(str[(i-1)*9+j]=='.')
					map[i][j]=0;
				else
					map[i][j]=str[(i-1)*9+j]-'0';
			}
		}
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				if(map[i][j]!=0)
				{
					r++;//����һ��
					hashx1[r]=i;
					hashx2[r]=j;
					hashx[r]=map[i][j];//��¼��ֵ
					Link(r,(i-1)*9+j);//(i,j)����һ���� ��Ӧ��(i-1)*9+j
					Link(r,(i-1)*9+map[i][j]+81);//i����map[i][j]
					Link(r,(j-1)*9+map[i][j]+162);//j����map[i][j]
					int g = int((i-1)/3*3+int((j-1)/3))+1;
					Link(r,243+((i-1)/3)*27 + ((j-1)/3)*9+map[i][j]);//g����map[i][j]
				}
				else
				{
					//ö��(i,j)����1:9
					for(int k = 1;k<=9;k++)
					{
						r++;
						hashx1[r]=i;
						hashx2[r]=j;
						hashx[r]=k;//��¼��ֵ
						Link(r,(i-1)*9+j);//(i,j)����һ���� ��Ӧ��(i-1)*9+j
						Link(r,(i-1)*9+k+81);//i����map[i][j]
						Link(r,(j-1)*9+k+162);//j����map[i][j]
						int g = int((i-1)/3*3+int((j-1)/3))+1;
						Link(r,243+(i-1)/3*27 + (j-1)/3*9 + k);//g����map[i][j]
					}
				}
			}
		}
		Dance(0);
		for(int i = 1;i<=9;i++)
		{
			for(int j = 1;j<=9;j++)
			{
				printf("%d",map[i][j]);
			}
		}
		printf("\n");
	}
}




