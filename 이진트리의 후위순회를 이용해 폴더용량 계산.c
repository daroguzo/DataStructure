#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int element;
typedef struct treeNode {	// 트리의 노드 구조 정의
	int size;				// 데이터 필드
	struct treeNode *left;	// 왼쪽 서브 트리에 대한 링크 필드
	struct treeNode *right;	// 오른쪽 서브 트리에 대한 링크 필드
} treeNode;

int FolderSize = 0;

// size를 루트 노드의 데이터 필드로 하여 왼쪽과 오른쪽 서브 트리를 연결하는 연산
treeNode* makeRootNode(int size, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));
	root->size = size;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}
// 이진 탐색 트리에서 키 값이 x인 노드의 위치를 탐색하는 연산
treeNode* searchBST(treeNode* root, int x) {
	treeNode* p;
	p = root;
	while (p != NULL) {
		if (x < p->size) p = p->left;
		else if (x == p->size) return p;
		else p = p->right;
	}
	printf("\n 찾는 키가 없습니다!");
	return p;
}
// 각 폴더 크기를 계산하기 위한 후위 순회 연산
int postorder_FolderSize(treeNode* root) {
	if (root) {
		postorder_FolderSize(root->left);
		postorder_FolderSize(root->right);
		FolderSize += root->size;
	}
	return FolderSize;
}
// 이진 탐색 트리를 중위 순회하면서 출력하는 연산
void displayInorder(treeNode* root) {
	if (root) {
		displayInorder(root->left);
		printf("%d_", root->size);
		displayInorder(root->right);
	}
}

// 포인터 p가 가리키는 노드와 비교하여 노드  x를 삽입하는 연산
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
	else printf("\n 이미 같은 키가 있습니다! \n");

	return p;
}

// 루트 노드부터 탐색하여 키 값과 같은 노드를 찾아 삭제하는 연산
void deleteNode(treeNode *root, element size) {
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;

	parent = NULL;
	p = root;
	while ((p != NULL) && (p->size != size)) {	// 삭제할 노드의 위치 탐색
		parent = p;
		if (size < p->size) p = p->left;
		else p = p->right;
	}

	// 삭제할 노드가 없는 경우
	if (p == NULL) {
		printf("\n 찾는 키가 이진 트리에 없습니다!\n");
		return;
	}

	// 삭제할 노드가 단말 노드인 경우
	if (parent != NULL) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}

	// 삭제할 노드가 자식 노드를 한 개 가진 경우
	else if ((p->left == NULL) && (p->right == NULL)) {
		if (parent->left == p) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p)parent->left = child;
			else parent->right = child;
		}
		else root = child;
	}

	// 삭제할 노드가 자식 노드를 두 개 가진 경우
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) {	// 왼쪽 서브 트리에서 후계자 찾기
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
	printf("\nt1 : 트리 출력");
	printf("\nt2 : 문자 삽입");
	printf("\nt3 : 문자 삭제");
	printf("\nt4 : 문자 검색");
	printf("\nt5 : 종료");
	printf("\n*--------------------*");
	printf("\n메뉴 입력 >> ");
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
		case 1: printf("\t[이진 트리 출력] ");
			displayInorder(root); printf("\n");
			break;

		case 2: printf("\t삽입할 숫자를 입력하세요 :  ");
			scanf(" %d", &key);
			insertNode(root, key);
			break;

		case 3: printf("\t삭제할 문자를 입력하세요 : ");
			scanf(" %d", &key);
			deleteNode(root, key);
			break;

		case 4: printf("\t찾을 숫자를 입력하세요 : ");
			scanf(" %d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf(" \n %d를 찾았습니다! \n", foundedNode->size);
			else printf("\n 숫자를 찾지 못했습니다. \n");
			break;

		case 5: return 0;

		default: printf("없는 메뉴입니다. 메뉴를 다시 선택하세요! \n");
			break;
		}
	}
	getchar();
}