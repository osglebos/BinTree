#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <iostream>


struct TREE
{
	int key;
	TREE *left, *right;
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
	while (*T != NULL)
	{
		if ((*T)->key == x)
		{
			T = &(*T)->left;
			break;
		}
		if ((*T)->key > x) T = &(*T)->left;
		else T = &(*T)->right;
	}

	TREE *newEl = new TREE;
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

int CountNumbers(TREE *T, int x)
{
	int res = 0;
	if (T != NULL)
	{
		if (T->key < x) res += CountNumbers(T->right, x);
		if (T->key == x) res++;
		if (T->key >= x) res+= CountNumbers(T->left, x);
	}
	return res;
}

TREE *RandomTree(void)
{
	int num = 0;
	TREE *head = NULL;
	printf("Создаем рандомное дерево\n");
	printf("Укажите количество элементов дерева: ");
	scanf("%i", &num);
	srand((unsigned int)time(NULL) * 1000);
	for (int i = 0; i < num; i++)
		AddKey(&head, rand() % 31);
	return head;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int num = 0;
	TREE *head = RandomTree();
	DisplayTurn(head, 1);
	printf("Введите число для которого стоит посчитать количество: ");
	scanf("%i", &num);
	printf("В дереве находится %i чисел %i.\n",  CountNumbers(head, num), num);
	system("pause");
	Delete(&head);
	return 1;
}

