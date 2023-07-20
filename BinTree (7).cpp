#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
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
		if ((*T)->key == x) return MININT;
		if ((*T)->key > x) T = &(*T)->left;
		else T = &(*T)->right;
	}

	TREE *newEl = new TREE;
	if (newEl == NULL)
	{
		fprintf(stderr, "Could not allocate %u bytes for the sovature\n", sizeof(TREE));
		return MININT;
	}
	newEl->left = *T;
	newEl->right = NULL;
	newEl->key = x;
	*T = newEl;
	return 1;
}

void inOrderTravers(TREE *T)
{
	if (T->left != NULL) inOrderTravers(T->left);
	printf("(%i)->", T->key);
	if (T->right != NULL) inOrderTravers(T->right);
}

int main(void)
{
	TREE *head = NULL;
	int num;
	printf("Input number os elements: ");
	scanf("%i", &num);
	printf("Create random tree:\n");
	srand((unsigned int)time(NULL) * 1000);
	for (int i = 0; i < num;)
	{
		int l = rand() % 31;
		if (AddKey(&head, l + 1) != MININT) i++;
	}
	DisplayTurn(head, 1);
	printf("In order counting:\n");
	inOrderTravers(head);
	printf("(end)\n");
	Delete(&head);
	system("pause");
	return 1;
}


