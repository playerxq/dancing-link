// hdu-3529-重复覆盖.cpp : 定义控制台应用程序的入口点。
//
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
#define CC 32  
#define RR 256  
int n,m;  
int size,ak; 
const int V=RR*CC;  
int U[V],D[V],L[V],R[V];
int S[CC],H[RR],Row[V]; 
int C[V];
bool vis[CC];
void remove(int c)  
{  
    int i;  
    for(i=D[c];i!=c;i=D[i])  
        L[R[i]]=L[i],R[L[i]]=R[i];  
}
void resume(int c)  
{  
    int i;  
    for(i=U[c];i!=c;i=U[i])  
        L[R[i]]=R[L[i]]=i;  
}
int h()  
{  
    int r=0,i,j,k;  
    memset(vis,false,sizeof(vis));  
    for(i=R[0];i;i=R[i]){  
        if(!vis[i]){  
            r++;  
            for(j=D[i];j!=i;j=D[j]){  
                for(k=R[j];k!=j;k=R[k])  
                    vis[C[k]]=true;  
            }  
        }  
    }  
    return r;  
}
void Dance(int k)  
{  
    int min,c,i,j;  
    if(k+h()>=ak) return; 
    if(!R[0]){  
        if(k<ak) ak=k;  
        return ;  
    }  
    for(min=V,i=R[0];i;i=R[i]){  
        if(S[i]<min) min=S[i],c=i;  
    }  
    for(i=D[c];i!=c;i=D[i]){  
        remove(i);  
        for(j=R[i];j!=i;j=R[j])  
            remove(j);  
        Dance(k+1);  
        for(j=L[i];j!=i;j=L[j])  
            resume(j);  
        resume(i);  
    }  
}
void Link(int r,int c)  
{  
    S[c]++;
	C[size]=c; 
	Row[size]=r;
    U[size]=U[c];
	D[U[c]]=size;  
    D[size]=c;
	U[c]=size;  
    if(H[r]==-1)  
        L[size]=R[size]=H[r]=size;  
    else
	{  
        L[size]=L[H[r]];
		R[L[H[r]]]=size;  
        R[size]=H[r];
		L[H[r]]=size;  
    }
	size++;  
}
char str[20][20];  
int dx[]={0,0,1,-1};  
int dy[]={1,-1,0,0};  
int id[20][20];  
int ck[20][20];  
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int nu,num;  
     while(scanf("%d%d",&n,&m)!=EOF)  
     {  
		  for(int i=0;i<n;i++)  
		  {  
			  scanf("%s",str[i]);  
		  }  
		  num=0;  
		  nu=0;  
		  memset(id,0,sizeof(id));  
		  memset(ck,0,sizeof(ck));  
        
		  for(int i=0;i<n;i++)  
		  {  
			for(int j=0;j<m;j++)  
			{  
				if(str[i][j]=='#')  
					id[i][j]=++num;  
				if(str[i][j]=='.')  
					ck[i][j]=++nu;  
			}  
		  }  
		  int c=num;  //c为列的数量  
		  for(int i=0;i<=c;i++)  
          {  
            S[i]=0;
			U[i]=D[i]=i;  
            L[i+1]=i;
			R[i]=i+1;  
          }  
          R[c]=0;  
          size=c+1;  
          memset(H,-1,sizeof(H));  
		  for(int i=0;i<n;i++)  
		  {
			   for(int j=0;j<m;j++)  
			   {  
					if(str[i][j]=='.')  
					{  
						for(int d=0;d<4;d++)  
						{  
							int x=i,y=j;  
							for(;x>-1&&y>-1&&x<n&&y<m&&str[x][y]=='.';x=x+dx[d],y=y+dy[d]);  //朝一个方向一直走直到不为'.'
							if(x>-1&&x<n&&y>-1&&y<m&&str[x][y]=='#')  
								Link(ck[i][j],id[x][y]);  
						}         
					}  
			   } 
		  }
		  ak=m*n;//ak为所选函数  
		  Dance(0);  
		  printf("%d\n",ak);  
      }
}

