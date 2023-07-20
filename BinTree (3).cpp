#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

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

		if (left->level > right->level) return left;
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

int main(void)
{
	int key, quit = 0, l = 0;
	TREE *head = NULL;

	while (!quit)
	{
		printf("\n\n");
		printf("esc | Exit\n");
		printf("1   | Random tree\n");
		printf("2   | Add number\n");
		printf("3   | Diplay\n");
		printf("4   | Delete\n");
		printf("5   | Longest tree\n\n");
		key = _getch();
		switch (key)
		{
		case 27:
			printf("Exit.\n");
			quit = 1;
			break;

		case '1':
			for (int i = 0; i < 15; i++)
			{
				int l = rand() % 31;
				AddKey(&head, l + 1);
			}
			DisplayTurn(head, 1);
			break;

		case '2':
			printf("Input key: ");
			scanf("%i", &l);
			if (AddKey(&head, l) == 1)
				printf("The key is successfully added");
			else
				printf("The key isn't added");
			break;

		case '3':
			DisplayTurn(head, 1);
			break;

		case '4':
			Delete(&head);
			break;

		case '5':
		{
			Level *tmp = GetLen(head, 1);
			if (tmp != NULL)
			{
				FindWithPrinting(head, tmp->index->key, 1);
				printf("\nMax level is: %i and number is: %i\n", tmp->level, tmp->index->key);
			}
			else printf("Your tree is empty.\n");
		}
		break;

		default:
			printf("Error: %c is not right key", key);
		}
	}
	Delete(&head);
	return 1;
}
