#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <time.h>

struct TREE
{
	int key;
	TREE *left, *right;
};

struct Level
{
	TREE *index;
	int level;
};

void Delete(TREE **T)
{
	if (*T == NULL)
		return;
	Delete(&(*T)->left);
	Delete(&(*T)->right);
	free(*T);
	*T = NULL;
}

void DisplayTurn(TREE *T, int dep)
{
	if (T != NULL)
	{
		if (T->right != NULL)
			DisplayTurn(T->right, dep + 1);
		printf("%*i\n", dep * 3, T->key);
		if (T->left != NULL)
			DisplayTurn(T->left, dep + 1);
	}
}

int AddKey(TREE **T, int x)
{
	TREE *newEl;
	while (*T != NULL)
	{
		if ((*T)->key == x)
		{
			T = &(*T)->left;
			break;
		}
		if ((*T)->key > x)
			T = &(*T)->left;
		else
			T = &(*T)->right;
	}

	newEl = new TREE;
	if (newEl == NULL)
	{
		fprintf(stderr, "Could not allocate %u bytes for the sovature\n", sizeof(TREE));
		return 0;
	}
	newEl->left = *T;
	newEl->right = NULL;
	newEl->key = x;
	*T = newEl;
	return 1;
}

Level *GetLen(TREE *p, int level)
{
	if (p == NULL) return NULL;

	if ((p->left == NULL) && (p->right == NULL))
	{
		Level *tmp = new Level;
		tmp->index = p;
		tmp->level = level;
		return tmp;
	}
	else if ((p->left != NULL) && (p->right == NULL)) return GetLen(p->left, level + 1);
	else if ((p->left == NULL) && (p->right != NULL)) return GetLen(p->right, level + 1);
	else
	{
		Level *left = GetLen(p->left, level + 1);
		Level *right = GetLen(p->right, level + 1);

		if (left->level < right->level) return left;
		else return right;
	}
}

void FindWithPrinting(TREE *T, int x, int dep)
{
	if (T != NULL)
	{
		if (T->key < x)
			FindWithPrinting(T->right, x, dep + 1);
		printf("%*i\n", dep * 3, T->key);
		if (T->key > x)
			FindWithPrinting(T->left, x, dep + 1);
	}
}

int *CreateDessendingList(int num)
{
	printf("Creating random dessending list\n");
	int *list;
	list = new int[num];
	srand((unsigned int)time(NULL) * 1000);
	list[0] = 3000;
	for (int i = 1; i < num; i++)
	{
		int a = rand() % 531;
		list[i] = list[i - 1] - a;
	}
	return list;
}

int *CreateRisingList(int num)
{
	printf("Creating random rising list\n");
	int *list;
	list = new int[num];
	srand((unsigned int)time(NULL) * 1000);
	list[0] = rand() % 5;
	for (int i = 1; i < num; i++)
	{
		int a = rand() % 531;
		list[i] = a + list[i - 1];
	}
	return list;
}

TREE *CreateTree(int *list, int num)
{	
	TREE *head = NULL;	
	for (int i = 0; i < num; i++) printf("list[%3i]: %5i\n", i, list[i]);
	for (int i = 0; i < num; i++) AddKey(&head, list[i]);
	return head;
}

int main(void)
{
	TREE *head=NULL;
	int *list;
	int num = 0;

	printf("Input number of list: ");
	scanf("%i", &num);
	list = CreateRisingList(num);
	head = CreateTree(list, num);
	DisplayTurn(head, 1);
	Delete(&head);

	printf("Input number of list: ");
	scanf("%i", &num);
	list = CreateDessendingList(num);
	head = CreateTree(list, num);
	DisplayTurn(head, 1);
	Delete(&head);

	system("pause");
	return 1;
}
