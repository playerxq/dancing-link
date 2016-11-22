// hdu-5046-�ظ�����.cpp : �������̨Ӧ�ó������ڵ㡣
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
int U[maxnode],D[maxnode],L[maxnode],R[maxnode],C[maxnode],X[maxnode];//x����M�������У�c����M�������У�U��D��L��RΪһ��Ԫ�ص���������ָ��  
int H[N],S[M];//H��ˮƽѭ�������ͷָ�룬S����ÿһ�е�Ԫ�ظ�����Q�洢һ�����ܽ��  
int size,n,m,K;
bool vis[maxnode];  
  
void remove(int c)  //ɾ��һ�У��뾫ȷ���ǵ������ǣ���ȷ����Ҫ��ÿ��ֻ��ĳ�г���һ�Σ����ظ�����Ҫ�����ٵ���ʹ��ÿ�����ٳ���һ��
{ //�ظ����ǵ�removeֻ����ǰ�е�ÿ��Ԫ���Ƴ� ���ı��Ƴ�Ԫ�������е�Ԫ���Ǹ���
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //�ָ�
{  
    for(int i = U[c]; i != c; i = U[i])  
        R[L[i]] = L[R[i]] = i;  
}
int h()  //����һ������
{  
    int i,j,c;  
    memset(vis,0,sizeof(vis));  
    int ans = 0;  
    for(c = R[0] ; c ; c = R[c])  //���ǵ�ǰʣ���ÿ����
    {  
        if(!vis[c])  
        {  
            ans++;  //���ٻ�Ҫһ�� ������c�еĸ������� ���һ�и�������ķ�����ѡ������һ��Ԫ�� ������������Ϊ��  ����Ԫ�����ڵ��б����и��� �п��Ա����
            for(i = D[c]; i != c; i = D[i])  //���ϵ�ÿ��Ԫ��
                for(j = R[i]; j != i; j = R[j])  //Ԫ�����ڵ���
                    vis[C[j]] = true;  //��Ӧ���б��  ˵���Ѿ�������
        }  
    }  
    return ans;  
} 

bool Dance(int dep)  
{  
    if(R[0] == 0)  //û��Ҫ���ǵ�����  ȫ���������  ����
        return dep<=K;  
    if(dep + h() > K)       //A_Star��֦  
        return false;  
  
    int i,j,tmp,c;  
  
    for(tmp=100000,i=R[0]; i; i=R[i])  //��¼1���ٵ��� �к�Ϊc
        if(S[i]<tmp)tmp=S[c=i];  
      
    for(i=D[c]; i!=c; i=D[i])  //������ÿ��Ԫ��
    {  
        remove(i);  //remove(i)��ɾ��c���ϳ�i���������1������i���ڵ�����Ϊ���һ���� ���Ѿ������˵�ǰc�� c��������1����Ҫ�ٿ����� remove�� 
        for(j=R[i]; j!=i; j=R[j])remove(j);  //��i�е�ÿ��1����Ӧ���Ǹ���Ҳ����i���ڵ��и����� ��ô������ϵ�������1Ҳ����Ժ����ļ�����Ӱ�� Ӧremove��
        if(Dance(dep+1))return 1;  
        for(j=L[i]; j!=i; j=L[j])resume(j);//����������ѭ��ԭ������ɾ���ĺ�ԭ����ɾ�����Ȼ�ԭ��  
        resume(i);  
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
