// hdu-4210-数独-精确覆盖.cpp : 定义控制台应用程序的入口点。
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
#define RR 750
#define CC 350
#define V RR*CC
int U[V],R[V],L[V],D[V];
int C[V],Row[V];
int H[RR],S[CC];
int size;
int map[10][10];
int hashx1[RR],hashx2[RR],hashx[RR],OK[90];
int visit[12][12],vis[12][12];
int dir[2][2]={0,1,1,0};
void Link(int r, int c)//建链  插入链表尾
{
	++S[c];
	C[size]=c;
	Row[size]=r;
	U[size]=U[c];
	D[U[c]]=size;
	U[c]=size;
	D[size]=c;
	if(H[r]<0) H[r]=L[size]=R[size]=size;
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
	L[R[c]]=L[c];
	R[L[c]]=R[c];
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
	L[R[c]]=c;
	R[L[c]]=c;
}
int dfs(int step)
{
      int i,j,k,temp,nextx,nexty;
      int ans1,ans2,ans;
      if(step==82) return 1;
      i=(step-1)/9+1;
      j=step-(i-1)*9;
      if(vis[i][j]) 
      {
          return dfs(step+1);
      }
      else
      {
          for(k=0;k<=1;k++)
          {
              nextx=i+dir[k][0];
              nexty=j+dir[k][1];
              if(nextx<=9 && nexty<=9 && vis[nextx][nexty]==0)
              {
                  ans1=map[i][j];
                  ans2=map[nextx][nexty];
                  if(ans1>ans2)
                  {
                     temp=ans1;
                     ans1=ans2;
                     ans2=temp;
                 }
                 if(visit[ans1][ans2]==0)
                 {
                     vis[i][j]=1;
                     vis[nextx][nexty]=1;
                     visit[ans1][ans2]=1;
                     ans=dfs(step+1);
                     if(ans==1) return 1;
                     vis[i][j]=0;
                     vis[nextx][nexty]=0;
                     visit[ans1][ans2]=0;
                 }
             }
         }
         return 0;
     }
}
int check()
{
    int i;
    for(i=0;i<81;i++)
         map[hashx1[OK[i]]][hashx2[OK[i]]]=hashx[OK[i]];
    return dfs(1);
}
int Dance(int k)
{
	int i,j,Min,c;
	if(R[0]==0)
	{
		if(check())
			return 1;
		else return 0;
	}
	for(Min=RR,i=R[0];i;i=R[i])//选取最小的1数目所在的列
         if(Min>S[i]) Min=S[i],c=i;
	remove(c);
	for(i=D[c];i!=c;i=D[i])//假设i所在的行选择  则该行上的1所在的列上每个1所在的行不可能选中 因此将这些列remove掉 即去除列上1所在的行
     {
         for(j=R[i];j!=i;j=R[j])
             remove(C[j]);
         OK[k]=Row[i];//记录选择的行
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
	int i,j,n,k,t=0,r;
     int ans1,ans2,ii,jj,temp;
     char ch1[5],ch2[5];
     while(scanf("%d",&n)!=EOF && n)
     {
         t++;
         for(i=0;i<=324;i++)
         {
             S[i]=0;
             D[i]=U[i]=i;
             L[i+1]=i;
             R[i]=i+1;
         }R[324]=0;
         size=325;
         r=0;
         memset(map,0,sizeof(map));
         memset(H,-1,sizeof(H));
         memset(visit,0,sizeof(visit));
         memset(vis,0,sizeof(vis));
         for(i=0;i<n;i++)
         {
             scanf("%d%s%d%s",&ans1,ch1,&ans2,ch2);
             ii=ch1[0]-'A'+1;
             jj=ch1[1]-'0';
             map[ii][jj]=ans1;
             vis[ii][jj]=1;
 
             ii=ch2[0]-'A'+1;
             jj=ch2[1]-'0';
             map[ii][jj]=ans2;
             vis[ii][jj]=1;
 
             if(ans1>ans2)
             {
                 temp=ans1;
                 ans1=ans2;
                 ans2=temp;
             }
             visit[ans1][ans2]=1;
         }
         for(i=1;i<=9;i++)
         {
             scanf("%s",ch1);
             ii=ch1[0]-'A'+1;
             jj=ch1[1]-'0';
             map[ii][jj]=i;
             vis[ii][jj]=1;
         }
         for(i=1;i<=9;i++)
         {
             for(j=1;j<=9;j++)
             {
                 if(map[i][j]!=0)
                 {
                     r++;
                     hashx1[r]=i;
                     hashx2[r]=j;
                     hashx[r]=map[i][j];
                     Link(r,(i-1)*9+j);
                     Link(r,81+(i-1)*9+map[i][j]);
                     Link(r,162+(j-1)*9+map[i][j]);
                     Link(r,243+((i-1)/3)*27 + ((j-1)/3)*9+map[i][j]);
                 }
                 else
                 {
                     for(k=1;k<=9;k++)
                     {
                         r++;
                         hashx1[r]=i;
                         hashx2[r]=j;
                         hashx[r]=k;
                         Link(r,(i-1)*9+j);
                         Link(r,81+(i-1)*9+k);
                         Link(r,162+(j-1)*9+k);
                         Link(r,243+(i-1)/3*27 + (j-1)/3*9 + k);
                     }
                 }
             }
         }///
         Dance(0);
         printf("Puzzle %d\n",t);
         for(i=1;i<=9;i++)
         {
             for(j=1;j<=9;j++)
                 printf("%d",map[i][j]);
             printf("\n");
         }
     }
}

