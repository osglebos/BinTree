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
		DisplayTurn(T->right, dep + 1);
		printf("%*i\n", dep * 3, T->key);
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

TREE *RandomTree(void)
{
	TREE *head = NULL;
	int num;
	printf("Input number os elements: ");
	scanf("%i", &num);
	printf("Creating random tree:\n");
	srand((unsigned int)time(NULL) * 1000);

	for (int i = 0; i < num;)
		if (AddKey(&head, rand() % 100) != MININT) 
			i++;

	DisplayTurn(head, 1);
	return head;
}

int CountLeaves(TREE *T)
{ 
	int res = 0;
	if (T->left != NULL) res += CountLeaves(T->left);
	if (T->right != NULL) res += CountLeaves(T->right);
	if (res == 0) 
	{
		printf("%i is leaf\n", T->key);
		res = 1;
	}
	return res;
}

int main(void)
{
	TREE *head = RandomTree();

	printf("Counting leaves of the tree:\n");
	printf("There is %i leaves.\n", CountLeaves(head));

	Delete(&head);
	system("pause");
	return 1;
}
