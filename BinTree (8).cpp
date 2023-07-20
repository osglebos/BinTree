#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

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
		if ((*T)->key > x)
			T = &(*T)->left;
		else
			T = &(*T)->right;
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

void PostOrder(TREE *T)
{
	if (T->left != NULL) PostOrder(T->left);
	if (T->right != NULL) PostOrder(T->right);
	printf("%i\n", T->key);
}

int main(void)
{
	TREE *head = NULL;
	int num;
	printf("Input number os elements: ");
	scanf("%i", &num);
	printf("Create random tree:\n");
	srand((unsigned int)time(NULL) * 1000);
	for (int i = 0; i < num; i++)
	{
		int l = rand() % 31;
		AddKey(&head, l + 1);
	}
	DisplayTurn(head, 1);
	printf("Post order counting:\n");
	PostOrder(head);
	Delete(&head);
	system("pause");
	return 1;
}


