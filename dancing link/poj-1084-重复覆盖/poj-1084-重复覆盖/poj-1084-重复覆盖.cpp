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

const int maxn = 65*6*6*6;
const int oo = 1 << 30;
const int maxrow = 65;
const int maxcol = 6*6*6;
bool mtx[maxrow][maxcol];
int t, n, k, ans;
int has[65];

int totRow, totCol, size;
int L[maxn], R[maxn], U[maxn], D[maxn];
int H[maxn], C[maxn], S[maxn],X[maxn];

bool ok(int x1, int y1, int x2, int y2)//(x1,y1)��� (x2,y2)�յ�ķ���
{
    bool flag = true;
    int id; 
    for (int i = y1; i < y2; ++i) {
        id = (x1 - 1) * (2 * n + 1) + i;//�ϱߵĻ�����
        if (!has[id]) {
            flag = false;
            break;
        }
        id = (x2-1) * (2 * n + 1) + i;//�±ߵĻ�����
        if (!has[id]) {
            flag = false;
            break;
        }
    }
    if (!flag) return false;
    for (int i = x1; i < x2; ++i) {
        id = (i - 1)*(2*n+1) + n + y1;//��߻�����
        if (!has[id]) {
            flag = false;
            break;  
        }
        id = (i - 1)*(2*n+1) + n + y2;//�ұ߻�����
        if (!has[id]) {
            flag = false;
            break;
        }
    }
    if (!flag) return false;
    return true;
}

void add(int x1, int y1, int x2, int y2, int c)//��(x1,y1):(x2,y2)�����ϵĻ���ƶ���c�ſ���
{
    int id;
    for (int i = y1; i < y2; ++i) {
        id = (x1 - 1) * (2 * n + 1) + i;
        mtx[id][c] = 1;
        id = (x2-1) * (2 * n + 1) + i;
        mtx[id][c] = 1;
    }
    for (int i = x1; i < x2; ++i) {
        id = (i - 1)*(2*n+1) + n + y1;
        mtx[id][c] = 1;
        id = (i - 1)*(2*n+1) + n + y2 ;
        mtx[id][c] = 1;
    }
}

void initMtx()
{
    int cnt = 1;
    memset(mtx, 0, sizeof(mtx));
	//ö�ٷ������Ͻ����
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; i + k <= n+1 && j + k <= n+1; ++k) {//kΪ�߳�
                if (ok(i, j, i + k, j + k)) {
                    add(i, j, i + k, j + k, cnt);
                    cnt++;//����ż��к�
                }
            }
        }
    }
    totRow = 2 * n * (n + 1);
    totCol = cnt-1;
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
void Build(int m,int n)
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
void build()
{
    Build(totRow,totCol);
    for (int i = 1; i <= totRow; ++i) {//ÿ�����
        for (int j = 1; j <= totCol; ++j) {//ÿ��������
           if (!mtx[i][j]) continue;
           Link(i,j);
        }
    }
}

void remove(int c)
{
    for (int i = D[c]; i != c; i = D[i]) {
        L[R[i]] = L[i]; R[L[i]] = R[i];
    }
}

void resume(int c)
{
    for (int i = U[c]; i != c; i = U[i]) {
        L[R[i]] = R[L[i]] = i;
    }
}

int h()
{
    bool vis[maxcol];
    memset(vis, false, sizeof(vis));
    int ret = 0;
    for (int i = R[0]; i != 0; i = R[i]) {
        if (!vis[i]) {
            ret++;
            vis[i] = true;
            for (int j = D[i]; j != i; j = D[j]) {
                for (int k = R[j]; k != j; k = R[k]) {
                    vis[C[k]] = true;
                }
            }
        }
    }
    return ret;
}

void dance(int cnt)
{
    if (cnt + h() >= ans) {
        return ;
    }
    if (R[0] == 0) {
        ans = cnt;
        return ;
    }
    int c, Min = oo;
    for (int i = R[0]; i != 0; i = R[i]) {
        if (S[i] < Min) {
            Min = S[i]; c = i;
        }
    }
    for (int i = D[c]; i != c; i = D[i]) {
        remove(i);
        for (int j = R[i]; j != i; j = R[j]) {
            remove(j);
        } 
        dance(cnt + 1);
        
        for (int j = L[i]; j != i; j = L[j]) {
            resume(j);
        }
        resume(i);
    }
    return ; 
}

int main()
{
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%d", &k);
        memset(has, true, sizeof(has));
        int num;
        for (int i = 0; i < k; ++i) {
            scanf("%d", &num);
            has[num] = false;
        }
        initMtx();
        build();
        ans = oo;
        dance(0);
        printf("%d\n", ans);
    }
    return 0;
}
