// BinarySortTree.cpp : 定义控制台应用程序的入口点。
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

/* 二叉树的二叉链表结点结构定义 */
typedef  struct BiTNode    /* 结点结构 */
{
	int data;    /* 结点数据 */
	struct BiTNode *lchild, *rchild;    /* 左右孩子指针 */
} BiTNode, *BiTree; /**BiTree等价于typedef BiTNode *BiTree*/

					/*查找二叉排序树T中是否存在key(递归查找)*/
Status Search(BiTree T, int key, BiTree f, BiTree *p)
{
	if (!T)    /*  查找不成功 */
	{
		*p = f;
		return FALSE;
	}
	else if (key == T->data) /*  查找成功 */
	{
		*p = T;
		return TRUE;
	}
	else if (key<T->data)
		return Search(T->lchild, key, T, p);  /*  在左子树中继续查找 */
	else
		return Search(T->rchild, key, T, p);  /*  在右子树中继续查找 */
}

/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status Insert(BiTree *T, int key)
{
	BiTree p, s;
	if (!Search(*T, key, NULL, &p)) /* 查找不成功 */
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s;            /*  插入s为新的根结点 */
		else if (key<p->data)
			p->lchild = s;    /*  插入s为左孩子 */
		else
			p->rchild = s;  /*  插入s为右孩子 */
		return TRUE;
	}
	else
		return FALSE;  /*  树中已有关键字相同的结点，不再插入 */
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
Status DeleteBST(BiTree *p)
{
	BiTree q, s;
	if ((*p)->rchild == NULL) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支) */
	{
		q = *p; *p = (*p)->lchild; free(q);
	}
	else if ((*p)->lchild == NULL) /* 只需重接它的右子树 */
	{
		q = *p; *p = (*p)->rchild; free(q);
	}
	else /* 左右子树均不空 */
	{
		q = *p; s = (*p)->lchild;
		while (s->rchild) /* 转左，然后向右到尽头（找待删结点的前驱） */
		{
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data; /*  s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值） */
		if (q != *p)
			q->rchild = s->lchild; /*  重接q的右子树 */
		else
			q->lchild = s->lchild; /*  重接q的左子树 */
		free(s);
	}
	return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status Delete(BiTree *T, int key)
{
	if (!*T) /* 不存在关键字等于key的数据元素 */
		return FALSE;
	else
	{
		if (key == (*T)->data) /* 找到关键字等于key的数据元素 */
			return DeleteBST(T);
		else if (key<(*T)->data)
			return Delete(&(*T)->lchild, key);
		else
			return Delete(&(*T)->rchild, key);

	}
}

/*二叉树中序遍历*/
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

	//定义数组和初始化SeqList
	int d[N] = { 62,88,58,47,35,73,51,99,37,93 };

	for (i = 0;i<N;i++)
	{
		Insert(&T, d[i]);
	}

	printf("***************二叉排序树查找(C版)***************\n");
	printf("初始化二叉排序树\n中序遍历数据：");
	LDR(T);

	printf("\n***************删除节点1***************\n");
	Delete(&T, 93);
	printf("删除叶节点93\n中序遍历后：");
	LDR(T);

	printf("\n***************删除节点2***************\n");
	Delete(&T, 47);
	printf("删除双孩子节点47\n中序遍历后：");
	LDR(T);

	getchar();
}


