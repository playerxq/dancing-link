//��ȫʹ���赸��ģ��n*n���� ���б�߷��������
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

int U[M],D[M],L[M],R[M],L_U[M],L_D[M],R_U[M],R_D[M],C[M],X[M];//L_UΪ���� L_D���� R_U���� R_D����
int H[N],Q[N],S[N];
int n,size;
int map[100][100];
void Link(int r,int c)
{
    L_U[size] = L_D[size] = size;
    R_U[size] = R_D[size] = size;
    if( r != 1 )//���ڵ�һ�� ��Ϊб�߱�ͷ  L_U L_D R_U R_Dֻ��ָ���Լ�����
    {
        int i;
        if(c!=n)//�������һ�� ����R[U[c]]
        {
			//��size���뵽�������λ��  ��U[c]֮��
            i = R[U[c]];//ԭ��U[c]�Ҳ�i ����ʹ��size�ŵ�i�����·�
			//�����������  ��ʱL_D[i]Ӧѭ������ͷ
            R_U[L_D[i]] = size;//��ͷ������ѭ����β��size
            L_D[size] = L_D[i];//ѭ����ͷ��
            L_D[i] = size;//
            R_U[size] = i;//
        }
        if(c!=1)//�������� ������������ ��˴�ʱi��R_DΪָ��б�߱�ͷ
        {
            i = L[U[c]];
            L_U[R_D[i]] = size;//��ͷ������ѭ����β��size��
            R_D[size] = R_D[i];//size�����¾���ԭ��i������ ʵ����ָ��б�߱�ͷ
            R_D[i] = size;
            L_U[size] = i;
        }
    }
	//��size�ŵ�����β��
    C[size] = c;
    U[size] = U[c];
    D[U[c]] = size;
    D[size] = c;
    U[c] = size;
    if(H[r] < 0) H[r] = L[size] = R[size] = size;
    else
    {//�����β��
        L[size] = L[H[r]];
        R[L[H[r]]] = size;
        R[size] = H[r];
        L[H[r]] = size;
    }
    X[size++] = r;//size���ڵ���
}
//ɾ��(h,c)λ�� ������h�� c���Լ�����б�ߵ�ɾ��
void remove(int h,int c)
{
    L[R[c]] = L[c];R[L[c]] = R[c];//��ͷȥ��
    for(int i = D[c]; i!=c; i = D[i])//��c�е�ÿ��Ԫ��
    {
        if(X[i] == h)//�ҵ�(h,c)Ԫ��
        {
            for(int j = L_U[i]; j!=i; j = L_U[j])//���������µ�б�� ����Ӧ���L R U D�Ͽ�
            {
                U[D[j]] = U[j];D[U[j]] = D[j];//�Ͽ�U D
                L[R[j]] = L[j];R[L[j]] = R[j];//�Ͽ�L R
                L_D[R_U[j]] = L_D[j];R_U[L_D[j]] = R_U[j];//�Ͽ�L_D R_U
                S[C[j]]--;
            }
            for(int j = R_U[i]; j!=i; j = R_U[j])//���������ϵ�б��
            {
                U[D[j]] = U[j];D[U[j]] = D[j];
                L[R[j]] = L[j];R[L[j]] = R[j];
                R_D[L_U[j]] = R_D[j];L_U[R_D[j]] = L_U[j];
                S[C[j]]--;
            }
            for(int j = R[i]; j!=i; j = R[j])//ɾ�����г�i�����Ԫ���������е����ӣ�i�ı�����Ϊ������resume��
            {
                U[D[j]] = U[j]; D[U[j]] = D[j];//��ɾ��L R��Ϊresume
                R_D[L_U[j]] = R_D[j];L_U[R_D[j]] = L_U[j];
                L_D[R_U[j]] = L_D[j];R_U[L_D[j]] = R_U[j];
                S[C[j]]--;
            }
        }
        else//����h�е�  ֻ��ɾ��c���ϵ�Ԫ��
        {
            L[R[i]] = L[i];R[L[i]] = R[i];//ֻɾL R��ɾ U D
            L_D[R_U[i]] = L_D[i];R_U[L_D[i]] = R_U[i];
            R_D[L_U[i]] = R_D[i];L_U[R_D[i]] = L_U[i];
        }
    }
	//ɾ����c���ϵ�U D��Ȼ����  Ϊresume
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
        if( S[i] == 0 ) return;//û�н�
        if( S[i] < tmp ) tmp = S[i],c = i;//�ҵ�Ԫ�����ٵ�һ��
    }


    for(int i = D[c]; i!=c; i=D[i])//���������е�ÿ��λ���ϷŻʺ�
    {
        Q[c] = X[i];//����c���϶�Ӧ���м�(x[i],c)λ�÷��ûʺ�
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
	for(i = 0; i<=n; i++)//��ʼ��n�� 
    {
        C[i] = i;
        U[i] = D[i] = i;
        L_U[i] = L_D[i] = i;//��ͷ��б��ָ���Լ�
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