// dancing link.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void remove(int& c)//��c���ϵ�Ԫ�ض�Ӧ����ȥ��  ��ȥ��c���ϵ�1���ڵ���
{
	L[R[c]]=L[c];
	R[L[c]]=R[c];
	for(int i = D[c];i!=c;i=D[i])
	{
		for(int j = R[i];j!=i;j=R[j])
		{
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			--S[col[j]];//��Ӧ�е�1����1
		}
	}
}
void resume(int& c)//remove�����
{
	for(int i = U[c];i!=c;i=U[i])
	{
		for(int j = L[i];j!=i;j=L[j])
		{
			U[D[j]]=j;
			D[U[j]]=j;
			++S[col[j]];//��Ӧ�е�1����1
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
	remove(idx);//��1���ٵ�һ���Ƴ�
	for(i = D[idx];i!=idx;i=D[idx])//���Ƴ��е�ÿһ����i
	{
		ans[deep++]=Row[i];//��i�����м����
		for(j = R[i];j!=i;j=R[j])//���ղż��������ϵ�1��Ӧ�����Ƴ� ��Ϊi���ڵ����ϵ�1���ڵ����Ѿ���i�м����  ������������Ҳ����������ϵ�1 ��ȥ���������1���ڵ���  ��remove�����
		{
			remove(col[j]);
		}
		if(dfs())
			return true;
		deep--;
		for(j = L[i];j!=i;j=L[j])//�ָ�
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

