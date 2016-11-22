// hdu-2295-�ظ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//�ظ�����Ҫ������0/1������ѡ�����ٵ���ʹÿһ��������һ��1
/*
DLX�ظ����Ƕ��ڵ�ǰ����Ĵ����ǣ�����ǰ��ȥ��������ѡ����ǰ�еĽ�����ܹ����ǵ�����ȫ��ȥ������Щ�������ʱ���Ѿ���������Щ�е�1����˲����ٿ�����Щ���ˣ���
��Ϊ����Ҫÿ�н���һ��1ȥ���ǣ��������ɸ�������˲���Ҫ���ܹ�����ĳһ�е�������ȫ��ȥ����
���remove��resume������д������������ͬ
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
int U[M],D[M],L[M],R[M],C[M],X[M];//x����M�������У�c����M�������У�U��D��L��RΪһ��Ԫ�ص���������ָ��  
int H[N],S[N];//H��ˮƽѭ�������ͷָ�룬S����ÿһ�е�Ԫ�ظ�����Q�洢һ�����ܽ��  
int size,n,m,k;  
double city[N][2];  
double radar[N][2];  
double dis[N][N];       //dis[i][j]��ʾ�״�i��cityj�ľ���  
int mx[N][N];  
bool vis[N];  
  
void remove(int c)  //ɾ��һ�У��뾫ȷ���ǵ������ǣ���ȷ����Ҫ��ÿ��ֻ��ĳ�г���һ�Σ����ظ�����Ҫ�����ٵ���ʹ��ÿ�����ٳ���һ��
{ //�ظ����ǵ�removeֻ����ǰ�е�ÿ��Ԫ���Ƴ� ���ı��Ƴ�Ԫ�������е�Ԫ���Ǹ���
    for(int i = D[c]; i != c; i = D[i])  
        R[L[i]] = R[i], L[R[i]] = L[i];  
}  
  
void resume(int c)  //�ָ�
{  
    for(int i = D[c]; i != c; i = D[i])  
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
        return true;  
    if(dep + h() > k)       //A_Star��֦  
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
bool build(double mid){  //����
    memset(mx,0,sizeof(mx));  
    for(int i=1;i<=n;i++){  //��������
        int flag=0;  
        for(int j=1;j<=m;j++){  //�״�����  ��ѡ��������ʹ��ÿ�����ٱ�һ�и���
            if(dis[j][i] - mid < 1e-8){  //��������
                mx[j][i] = 1;  
                flag=1;  
            }  
        }  
        if(!flag)  //ȫΪ0
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
    size=n+1;  //0Ϊͷ 1:n���� ���нڵ��n+1��ʼ���
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
double solve()  //2�ִ�
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
double Dis(int i, int j)  //�������
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

