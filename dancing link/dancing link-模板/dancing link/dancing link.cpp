// dancing link.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void remove(int& c)//将c列上的元素对应的行去除  即去除c列上的1所在的行
{
	L[R[c]]=L[c];
	R[L[c]]=R[c];
	for(int i = D[c];i!=c;i=D[i])
	{
		for(int j = R[i];j!=i;j=R[j])
		{
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			--S[col[j]];//相应列的1数减1
		}
	}
}
void resume(int& c)//remove逆操作
{
	for(int i = U[c];i!=c;i=U[i])
	{
		for(int j = L[i];j!=i;j=L[j])
		{
			U[D[j]]=j;
			D[U[j]]=j;
			++S[col[j]];//相应列的1数减1
		}
	}
	L[R[c]]=c;
	R[L[c]]=c;
}
bool dfs()
{
	if(R[0]==0)
		return true;
	int i,j,idx,minm=999999;
	for(i = R[0];i!=0;i=R[i])
	{
		if(S[i]<minm)
		{
			minm = S[i];
			idx=i;
		}
	}
	remove(idx);//将1最少的一列移除
	for(i = D[idx];i!=idx;i=D[idx])//对移除列的每一个行i
	{
		ans[deep++]=Row[i];//将i所在行加入解
		for(j = R[i];j!=i;j=R[j])//将刚才加入解的行上的1对应的列移除 因为i所在的行上的1所在的列已经被i行加入解  不能有其他行也含有这个列上的1 故去除这个列上1所在的行  即remove这个列
		{
			remove(col[j]);
		}
		if(dfs())
			return true;
		deep--;
		for(j = L[i];j!=i;j=L[j])//恢复
		{
			resume(col[j]);
		}
	}
	resume(idx);
	return false;
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

