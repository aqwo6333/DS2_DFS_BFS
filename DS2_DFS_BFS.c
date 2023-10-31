#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 50
#define MAX 50

typedef struct GraphType {
	int n;	
	int adj_mat[MAX_VERTEX][MAX_VERTEX];
} GraphType;

typedef struct GraphNode {
	int vertex; 
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType_List {
	int n; 
	GraphNode* adj_list[MAX_VERTEX];
} GraphType_List;


typedef struct Stack {
	int top;
	int data[MAX];
}Stack;

typedef struct Queue {
	int front, rear;
	int data[MAX];
}Queue;

int visited[MAX_VERTEX];

void init_stack(Stack* s) {
	s->top = -1;
}

void init_queue(Queue* q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty_stack(Stack* s) {
	return s->top == -1;
}

int is_empty_queue(Queue* q) {
	return q->front == q->rear;
}

void push(Stack* s, int item) {
	s->data[++(s->top)];
}

int pop(Stack* s) {
	if (s->top == -1) {
		printf("stack is empty");
		return;
	}
	return s->data[(s->top)--];
}

void enqueue(Queue* q, int item) {
	if (q->front == q->rear + 1 % MAX) {
		printf("Queue is full");
		return;
	}
	else {
		 q->rear = (q->rear + 1) % (MAX);
		 q->data[q->rear] = item;
	}

}

int dequeue(Queue* q) {
	if (q->front == q->rear) {
		printf("Queue is empty");
		return;
	}
	return q->data[++(q->front)];
}

void init_graph(GraphType_List* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTEX; v++) {
		g->adj_list[v] = NULL;
	}

}

void insert_vertex(GraphType_List* g, int v) {
	if (((g->n) + 1) > MAX_VERTEX) {
		printf("그래프: 정점 번호 오류");
		return;
	}
	g->n++;
}

void insert_edge(GraphType_List* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void dfs_list(GraphType_List* g, int v, int key) {
	GraphNode* n;
	int node;
	Stack s;
	init_stack(&s);
	push(&s, v);
	for (int i = 0; i < g->n; i++) visited[i] = 0;
	while (!is_emptys(&s)) {
		node = pop(&s);
		if (!visited[node]) {
			visited[node] = 1;
			printf("%d ", node);
			if (node == key) {
				printf("\n탐색 성공 : %d 방문한 노드의 수: %d\n", key, node);
				break;
			}			
			for (n = g->adj_list[node]; n != NULL; n = n->link) {
				if (!visited[n->vertex]) {
					push(&s, n->vertex);
				}
			}
		}
	}
}

void bfs_list(GraphType_List* g, int v, int key) {
	GraphNode* n;
	int node;
	Queue q;
	init_queue(&q);
	enqueue(&q, v);
	for (int i = 0; i < g->n; i++) visited[i] = 0;
	while (!is_emptyq(&q)) {
		node = dequeue(&q);
		if (!visited[node]) {
			visited[node] = 1;
			printf("%d ", node); 
			if (node == key) { 
				printf("\n탐색 성공 : %d 방문한 노드의 수: %d\n", key, node);
				break;
			}
			for (n = g->adj_list[node]; n != NULL; n = n->link) {
				if (!visited[n->vertex]) {
					enqueue(&q, n->vertex);
				}
			}
		}
	}
}

GraphType_List* make_Graph() {
	GraphType_List* g = (GraphType_List*)malloc(sizeof(GraphType_List));
	init_List(g);

	for (int i = 0; i < 11; i++) {
		insert_vertex(g, i);
	}
	int edges[11][7] = {
		{2, 5, 6, 9, -1},  // 0
		{4, 5, 7, 10, -1}, // 1
		{0, 3, 4, -1},     // 2
		{2, 4, 5, -1},     // 3
		{1, 2, 3, 5, 6, 7, -1}, // 4
		{0, 1, 3, 4, -1}, // 5
		{0, 4, 7, 8, -1}, // 6
		{1, 4, 10, -1},   // 7
		{6, 9, 10, -1},    // 8
		{0, 8, -1},        // 9
		{1, 7, 8, -1}      // 10
	};

	for (int i = 0; i < 11; i++) {
		for (int j = 0; edges[i][j] != -1; j++) {
			insert_edge(g, i, edges[i][j]);
		}
	}

	return g;
}


int main(int argc, char* argv[]) {
	GraphType_List* g = makeGraph();

	printf("1. DFS \n2. BFS \n3. Exit \n");
	int menu = 0;
	int start, item;
	while (1) {
		printf("Insert Menu : ");
		scanf_s("%d", &menu);

		switch (menu) {
		case 1:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &start, &item);
			dfs_list(g, start, item);
			break;
		case 2:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &start, &item);
			bfs_list(g, start, item);
			break;
		case 3:
			exit(1);
			break;
		default:
			printf("Insert Error");
			break;
		}

	}

	free(g);

	return 0;
}
