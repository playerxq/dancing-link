// hdu-3149-分治.cpp : 定义控制台应用程序的入口点。
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

#define Maxn 300005

int median(int *a,int *b,int length)

{

    if(length == 1) return a[0] < b[0] ? a[0] : b[0];

    int mid = (length - 1)/2;

    if(a[mid] == b[mid]) return a[mid];

    if(a[mid] < b[mid])

    {

        return median(&a[length - mid -1],b,mid+1);

    }

    else

    {

        return median(a,&b[length - mid -1],mid+1);

    }

}

int a[Maxn],b[Maxn];

int main()

{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;

    int n;

    int A,B,C,D;

    int q;

    int len;

    scanf(" %d",&t);

    while(t--)

    {

        scanf(" %d",&n);

        for(int i=0; i<n; i++) scanf(" %d",&a[i]);

        for(int i=0; i<n; i++) scanf(" %d",&b[i]);

        scanf(" %d",&q);

        for(int i=0; i<q; i++)

        {

            scanf(" %d %d %d %d",&A,&B,&C,&D);

            len = B-A+1;

            int ans = median(a+A,b+C,len);

            printf("%d\n",ans);

        }

    }

    return 0;

}


