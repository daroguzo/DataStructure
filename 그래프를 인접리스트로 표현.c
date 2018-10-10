#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30

// ���� ����Ʈ�� ��� ������ ����ü�� ����
typedef struct graphNode {
	int vertex;
	struct graphNode* link;		// ������ ��Ÿ���� ������ �ʵ�
} graphNode;					// ���� ���� ������ �����ϴ� ��ũ �ʵ�

// �׷����� ���� ����Ʈ�� ǥ���ϱ� ���� ����ü ����
typedef struct graphType {
	int n;								// �׷����� ���� ����
	graphNode* adjList_H[MAX_VERTEX];	// �׷��� ������ ���� ��� ������ �迭
}graphType;

// ���� �׷����� �����ϴ� ����
void createGraph(graphType *g) {
	int v;
	g->n = 0;							// �׷����� ���� ������ 0���� �ʱ�ȭ
	for (v = 0; v < MAX_VERTEX; v++) {
		g->adjList_H[v] = NULL;			// �׷����� ������ ���� ��� ������ �迭�� NULL�� �ʱ�ȭ
	}
}

// �׷��� g�� ���� v�� �����ϴ� ����
void insertVertex(graphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTEX) {
		printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
		return;
	}
	g->n++;								// �׷����� ���� ���� n�� �ϳ� ����
}

// �׷��� g�� ���� (u, v)�� �����ϴ� ����
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;
	graphNode* ptr;

	// ���� (u, v)�� �����ϱ� ���� ���� u�� ���� v�� ���� �׷����� �ִ��� Ȯ��
	if (u >= g->n || v >= g->n) {
		printf("\n �׷����� ���� �����Դϴ�!");
		return;
	}
	
	node = (graphNode *)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = NULL;	// �߰��� ��

	// �� ��带 ����Ʈ�� �������� ����
	if (!(ptr = g->adjList_H[u])) {		// �� ��尡 ù ��° ����� ���
		g->adjList_H[u] = node;
		return;
	}
	// �̹� �Ѱ� �̻��� ��尡 �ִ� ���
	ptr = g->adjList_H[u];
	while (ptr->link) ptr = ptr->link;	// ���������� �̵�. ptr�� ������ ��尡 �ȴ�.
	ptr->link = node;					// ������ ��� ������ �� ��带 ����

	// node->link = g->adjList_H[u];	// �� ��带 ����Ʈ�� ù ��° ���� ����
	// g->adjList_H[u] = node;
}

// �׷��� g�� �� ������ ���� ���� ����Ʈ�� ����ϴ� ����
void print_adgList(graphType* g) {
	int i;
	graphNode* p;
	for (i = 0; i < g->n; i++) {
		printf("\n\t\t���� %d�� ���� ����Ʈ", i);
		p = g->adjList_H[i];
		while (p) {
			printf(" -> %d", p->vertex);
			p = p->link;
		}
	}
}
void main() {
	int i, j;
	graphType *G1;
	G1 = (graphType *)malloc(sizeof(graphType));
	createGraph(G1);
	for (i = 0; i < 4; i ++)
		insertVertex(G1, i);	// G1�� ���� 0~3 ����
	int graph[4][4] = { {0,1,0,1}, {1,0,1,1}, {0,1,0,1}, {1,1,1,0} };
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (graph[i][j] == 1)
				insertEdge(G1, i, j);
	printf("\n G1�� ���� ����Ʈ");
	print_adgList(G1);
	printf("\n");

}