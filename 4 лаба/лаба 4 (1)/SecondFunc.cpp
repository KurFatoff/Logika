#include "SecondFunc.h"



struct sNode
{
	int data;
	sNode* left;
	sNode* right;

};


struct sNode* root;
struct sNode* CreateTree(struct sNode* root, struct sNode* r, int data)
{
	if (r == NULL)
	{
		r = (struct sNode*)malloc(sizeof(struct sNode));
		if (r == NULL)
		{
			printf("������ ��������� ������");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data == r->data) { return root; }
	else if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct sNode* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}


void start_noreplies()
{
	int D, start = 1;

	root = NULL;
	printf("��������� ������ (��� ������ ������� '0')\n");
	while (start)
	{
		printf("������� �����: ");
		scanf_s("%d", &D);
		if (D == 0)
		{
			printf("\n�������� ������ ���������!\n������:\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}
	print_tree(root, 0);
}
