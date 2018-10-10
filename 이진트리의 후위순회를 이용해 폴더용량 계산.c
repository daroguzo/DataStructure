#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int element;
typedef struct treeNode {	// Ʈ���� ��� ���� ����
	int size;				// ������ �ʵ�
	struct treeNode *left;	// ���� ���� Ʈ���� ���� ��ũ �ʵ�
	struct treeNode *right;	// ������ ���� Ʈ���� ���� ��ũ �ʵ�
} treeNode;

int FolderSize = 0;

// size�� ��Ʈ ����� ������ �ʵ�� �Ͽ� ���ʰ� ������ ���� Ʈ���� �����ϴ� ����
treeNode* makeRootNode(int size, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));
	root->size = size;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}
// ���� Ž�� Ʈ������ Ű ���� x�� ����� ��ġ�� Ž���ϴ� ����
treeNode* searchBST(treeNode* root, int x) {
	treeNode* p;
	p = root;
	while (p != NULL) {
		if (x < p->size) p = p->left;
		else if (x == p->size) return p;
		else p = p->right;
	}
	printf("\n ã�� Ű�� �����ϴ�!");
	return p;
}
// �� ���� ũ�⸦ ����ϱ� ���� ���� ��ȸ ����
int postorder_FolderSize(treeNode* root) {
	if (root) {
		postorder_FolderSize(root->left);
		postorder_FolderSize(root->right);
		FolderSize += root->size;
	}
	return FolderSize;
}
// ���� Ž�� Ʈ���� ���� ��ȸ�ϸ鼭 ����ϴ� ����
void displayInorder(treeNode* root) {
	if (root) {
		displayInorder(root->left);
		printf("%d_", root->size);
		displayInorder(root->right);
	}
}

// ������ p�� ����Ű�� ���� ���Ͽ� ���  x�� �����ϴ� ����
treeNode* insertNode(treeNode *p, int x) {
	treeNode *newNode;
	if (p == NULL) {
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode->size = x;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (x < p->size) p->left = insertNode(p->left, x);
	else if (x > p->size)p->right = insertNode(p->right, x);
	else printf("\n �̹� ���� Ű�� �ֽ��ϴ�! \n");

	return p;
}

// ��Ʈ ������ Ž���Ͽ� Ű ���� ���� ��带 ã�� �����ϴ� ����
void deleteNode(treeNode *root, element size) {
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (p->size != size)) {	// ������ ����� ��ġ Ž��
		parent = p;
		if (size < p->size) p = p->left;
		else p = p->right;
	}

	// ������ ��尡 ���� ���
	if (p == NULL) {
		printf("\n ã�� Ű�� ���� Ʈ���� �����ϴ�!\n");
		return;
	}

	// ������ ��尡 �ܸ� ����� ���
	if (parent != NULL) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}

	// ������ ��尡 �ڽ� ��带 �� �� ���� ���
	else if ((p->left == NULL) && (p->right == NULL)) {
		if (parent->left == p) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p)parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	// ������ ��尡 �ڽ� ��带 �� �� ���� ���
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) {	// ���� ���� Ʈ������ �İ��� ã��
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left == succ) succ_parent->left = succ->left;
		else succ_parent->right = succ->left;
		p->size = succ->size;
		p = succ;
	}
	free(p);
}


void menu() {
	printf("\n*--------------------*");
	printf("\nt1 : Ʈ�� ���");
	printf("\nt2 : ���� ����");
	printf("\nt3 : ���� ����");
	printf("\nt4 : ���� �˻�");
	printf("\nt5 : ����");
	printf("\n*--------------------*");
	printf("\n�޴� �Է� >> ");
}

int main() {
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice;
	int key;

	treeNode* F11 = makeRootNode(13, NULL, NULL);
	treeNode* F10 = makeRootNode(10, NULL, NULL);
	treeNode* F9 = makeRootNode(2, NULL, NULL);
	treeNode* F8 = makeRootNode(0, NULL, NULL);
	treeNode* F7 = makeRootNode(11, F10, F11);
	treeNode* F6 = makeRootNode(7, NULL, NULL);
	treeNode* F5 = makeRootNode(5, NULL, NULL);
	treeNode* F4 = makeRootNode(1, F8, F9);
	treeNode* F3 = makeRootNode(9, F6, F7);
	treeNode* F2 = makeRootNode(3, F4, F5);
	root = makeRootNode(6, F2, F3);

	while (1) {
		menu();
		scanf(" %c", &choice);

		switch (choice - '0') {
		case 1: printf("\t[���� Ʈ�� ���] ");
			displayInorder(root); printf("\n");
			break;

		case 2: printf("\t������ ���ڸ� �Է��ϼ��� :  ");
			scanf(" %d", &key);
			insertNode(root, key);
			break;

		case 3: printf("\t������ ���ڸ� �Է��ϼ��� : ");
			scanf(" %d", &key);
			deleteNode(root, key);
			break;

		case 4: printf("\tã�� ���ڸ� �Է��ϼ��� : ");
			scanf(" %d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf(" \n %d�� ã�ҽ��ϴ�! \n", foundedNode->size);
			else printf("\n ���ڸ� ã�� ���߽��ϴ�. \n");
			break;

		case 5: return 0;

		default: printf("���� �޴��Դϴ�. �޴��� �ٽ� �����ϼ���! \n");
			break;
		}
	}
	getchar();
}