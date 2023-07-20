#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <windows.h>
#include <iostream>

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
		fprintf(stderr, "Не возможно выделить %u байт для выражения.\n", sizeof(TREE));
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

TREE *RandomTree(void)
{
	int num = 0;
	TREE *head = NULL;
	printf("Создаем рандомное дерево\n");
	printf("Введите количество элементов дерева: ");
	scanf("%i", &num);
	srand((unsigned int)time(NULL) * 1000);
	for (int i = 0; i < num; i++) AddKey(&head, rand() % 31);
	return head;
}

void Shortest(TREE *head)
{
	printf("\nИщем самое короткую ветку дерева: \n");
	Level *tmp = GetLen(head, 1);
	if (tmp != NULL)
	{
		FindWithPrinting(head, tmp->index->key, 1);
		printf("Саймый маленький уровень: %i там находится число: %i\n", tmp->level, tmp->index->key);
	}
	else printf("У вас нет элементов в дереве.\n");
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	TREE *head = RandomTree();
	DisplayTurn(head, 1);
	Shortest(head);
	system("pause");
	Delete(&head);
	return 1;
}
