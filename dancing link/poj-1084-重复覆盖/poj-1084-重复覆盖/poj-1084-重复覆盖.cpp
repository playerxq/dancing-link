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

bool ok(int x1, int y1, int x2, int y2)//(x1,y1)起点 (x2,y2)终点的方块
{
    bool flag = true;
    int id; 
    for (int i = y1; i < y2; ++i) {
        id = (x1 - 1) * (2 * n + 1) + i;//上边的火柴号码
        if (!has[id]) {
            flag = false;
            break;
        }
        id = (x2-1) * (2 * n + 1) + i;//下边的火柴号码
        if (!has[id]) {
            flag = false;
            break;
        }
    }
    if (!flag) return false;
    for (int i = x1; i < x2; ++i) {
        id = (i - 1)*(2*n+1) + n + y1;//左边火柴号码
        if (!has[id]) {
            flag = false;
            break;  
        }
        id = (i - 1)*(2*n+1) + n + y2;//右边火柴号码
        if (!has[id]) {
            flag = false;
            break;
        }
    }
    if (!flag) return false;
    return true;
}

void add(int x1, int y1, int x2, int y2, int c)//将(x1,y1):(x2,y2)方块上的火柴都制定到c号块上
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
	//枚举方块左上角起点
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; i + k <= n+1 && j + k <= n+1; ++k) {//k为边长
                if (ok(i, j, i + k, j + k)) {
                    add(i, j, i + k, j + k, cnt);
                    cnt++;//方块号即列号
                }
            }
        }
    }
    totRow = 2 * n * (n + 1);
    totCol = cnt-1;
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
    for (int i = 1; i <= totRow; ++i) {//每个火柴
        for (int j = 1; j <= totCol; ++j) {//每个方块列
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
