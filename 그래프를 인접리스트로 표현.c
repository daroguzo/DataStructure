#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30

// 인접 리스트의 노드 구조를 구조체로 정의
typedef struct graphNode {
	int vertex;
	struct graphNode* link;		// 정점을 나타내는 데이터 필드
} graphNode;					// 다음 인접 정점을 연결하는 링크 필드

// 그래프를 인접 리스트로 표현하기 위한 구조체 정의
typedef struct graphType {
	int n;								// 그래프의 정점 개수
	graphNode* adjList_H[MAX_VERTEX];	// 그래프 정점에 대한 헤드 포인터 배열
}graphType;

// 공백 그래프를 생성하는 연산
void createGraph(graphType *g) {
	int v;
	g->n = 0;							// 그래프의 정점 개수를 0으로 초기화
	for (v = 0; v < MAX_VERTEX; v++) {
		g->adjList_H[v] = NULL;			// 그래프의 정점에 대한 헤드 포인터 배열을 NULL로 초기화
	}
}

// 그래프 g에 정점 v를 삽입하는 연산
void insertVertex(graphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTEX) {
		printf("\n 그래프 정점의 개수를 초과하였습니다!");
		return;
	}
	g->n++;								// 그래프의 정점 개수 n을 하나 증가
}

// 그래프 g에 간선 (u, v)를 삽입하는 연산
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;
	graphNode* ptr;

	// 간선 (u, v)를 삽입하기 위해 정점 u와 정점 v가 현재 그래프에 있는지 확인
	if (u >= g->n || v >= g->n) {
		printf("\n 그래프에 없는 정점입니다!");
		return;
	}
	
	node = (graphNode *)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = NULL;	// 추가할 것

	// 새 노드를 리스트의 마지막에 연결
	if (!(ptr = g->adjList_H[u])) {		// 새 노드가 첫 번째 노드인 경우
		g->adjList_H[u] = node;
		return;
	}
	// 이미 한개 이상의 노드가 있는 경우
	ptr = g->adjList_H[u];
	while (ptr->link) ptr = ptr->link;	// 마지막으로 이동. ptr은 마지막 노드가 된다.
	ptr->link = node;					// 마지막 노드 다음에 새 노드를 연결

	// node->link = g->adjList_H[u];	// 새 노드를 리스트의 첫 번째 노드로 연결
	// g->adjList_H[u] = node;
}

// 그래프 g의 각 정점에 대한 인접 리스트를 출력하는 연산
void print_adgList(graphType* g) {
	int i;
	graphNode* p;
	for (i = 0; i < g->n; i++) {
		printf("\n\t\t정점 %d의 인접 리스트", i);
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
		insertVertex(G1, i);	// G1의 정점 0~3 삽입
	int graph[4][4] = { {0,1,0,1}, {1,0,1,1}, {0,1,0,1}, {1,1,1,0} };
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (graph[i][j] == 1)
				insertEdge(G1, i, j);
	printf("\n G1의 인접 리스트");
	print_adgList(G1);
	printf("\n");

}