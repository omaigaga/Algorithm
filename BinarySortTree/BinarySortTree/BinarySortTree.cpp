// BinarySortTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"   
#include "io.h"
#include "math.h" 
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;

/* �������Ķ���������ṹ���� */
typedef  struct BiTNode    /* ���ṹ */
{
	int data;    /* ������� */
	struct BiTNode *lchild, *rchild;    /* ���Һ���ָ�� */
} BiTNode, *BiTree; /**BiTree�ȼ���typedef BiTNode *BiTree*/

					/*���Ҷ���������T���Ƿ����key(�ݹ����)*/
Status Search(BiTree T, int key, BiTree f, BiTree *p)
{
	if (!T)    /*  ���Ҳ��ɹ� */
	{
		*p = f;
		return FALSE;
	}
	else if (key == T->data) /*  ���ҳɹ� */
	{
		*p = T;
		return TRUE;
	}
	else if (key<T->data)
		return Search(T->lchild, key, T, p);  /*  ���������м������� */
	else
		return Search(T->rchild, key, T, p);  /*  ���������м������� */
}

/*  ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ�� */
/*  ����key������TRUE�����򷵻�FALSE */
Status Insert(BiTree *T, int key)
{
	BiTree p, s;
	if (!Search(*T, key, NULL, &p)) /* ���Ҳ��ɹ� */
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s;            /*  ����sΪ�µĸ���� */
		else if (key<p->data)
			p->lchild = s;    /*  ����sΪ���� */
		else
			p->rchild = s;  /*  ����sΪ�Һ��� */
		return TRUE;
	}
	else
		return FALSE;  /*  �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}

/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
Status DeleteBST(BiTree *p)
{
	BiTree q, s;
	if ((*p)->rchild == NULL) /* ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧) */
	{
		q = *p; *p = (*p)->lchild; free(q);
	}
	else if ((*p)->lchild == NULL) /* ֻ���ؽ����������� */
	{
		q = *p; *p = (*p)->rchild; free(q);
	}
	else /* �������������� */
	{
		q = *p; s = (*p)->lchild;
		while (s->rchild) /* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */
		{
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data; /*  sָ��ɾ����ֱ��ǰ��������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */
		if (q != *p)
			q->rchild = s->lchild; /*  �ؽ�q�������� */
		else
			q->lchild = s->lchild; /*  �ؽ�q�������� */
		free(s);
	}
	return TRUE;
}

/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��, */
/* ������TRUE�����򷵻�FALSE�� */
Status Delete(BiTree *T, int key)
{
	if (!*T) /* �����ڹؼ��ֵ���key������Ԫ�� */
		return FALSE;
	else
	{
		if (key == (*T)->data) /* �ҵ��ؼ��ֵ���key������Ԫ�� */
			return DeleteBST(T);
		else if (key<(*T)->data)
			return Delete(&(*T)->lchild, key);
		else
			return Delete(&(*T)->rchild, key);

	}
}

/*�������������*/
void LDR(BiTree T)
{
	if (T != NULL)
	{
		LDR(T->lchild);
		printf("%d ", T->data);
		LDR(T->rchild);
	}
}


#define N 10
void main()
{
	int i, j;
	BiTree T = NULL;

	//��������ͳ�ʼ��SeqList
	int d[N] = { 62,88,58,47,35,73,51,99,37,93 };

	for (i = 0;i<N;i++)
	{
		Insert(&T, d[i]);
	}

	printf("***************��������������(C��)***************\n");
	printf("��ʼ������������\n����������ݣ�");
	LDR(T);

	printf("\n***************ɾ���ڵ�1***************\n");
	Delete(&T, 93);
	printf("ɾ��Ҷ�ڵ�93\n���������");
	LDR(T);

	printf("\n***************ɾ���ڵ�2***************\n");
	Delete(&T, 47);
	printf("ɾ��˫���ӽڵ�47\n���������");
	LDR(T);

	getchar();
}


