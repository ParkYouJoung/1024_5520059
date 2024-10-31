#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	
	int weight[MAX_VERTICES][MAX_VERTICES];  
} GraphType;

int selected[MAX_VERTICES];  // ���õ� ������ ����
int distance[MAX_VERTICES];  // �� ���������� �ּ� �Ÿ�

// �ּ� �Ÿ� ���� ���� ���õ��� ���� ������ ��ȯ�ϴ� �Լ�
int get_min_vertex(int n)
{
	int v = -1, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {  // ���õ��� ���� ù ��° ���� ã��
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;  // ���� ���� �Ÿ� �� ���� ���� ã��
	return v;
}

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g)
{
	g->n = 10;  // ������ ������ 10
	for (int i = 0; i < MAX_VERTICES; i++) {
		selected[i] = FALSE;  
		distance[i] = INF;     
		for (int j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = INF;  // ��� ����ġ ���Ѵ� ����
	}
}


void GenerateGraph(GraphType* g)
{
	int weights[10][10] = {
		{INF, 3, INF, INF, INF, 11, 12, INF, INF, INF },
		{3, INF, 5, 4, 1, 7, 8, INF, INF, INF },
		{INF, 5, INF, 2, INF, INF, 6, 5, INF, INF},
		{INF, 4, 2, INF, 13, INF, INF, 14, INF, 16 },
		{INF, 1, INF, 13, INF, 9, INF, INF, 18, 17 },
		{11, 17, INF, INF, 9, INF, INF, INF, INF, INF },
		{12, 8, 6, INF, INF, INF, INF, 13, INF, INF },
		{INF, INF, 5, 14, INF, INF, 13, INF, INF, 15},
		{INF, INF, INF, INF, 18, INF, INF, INF, INF, 10},
		{INF, INF, INF, 16, 17, INF, INF, 15, 10, INF}
	};

	for (int i = 0; i < g->n; i++)
		for (int j = 0; j < g->n; j++)
			g->weight[i][j] = weights[i][j];  // ����ġ �׷����� ����
}


void FindPrimMST(GraphType* g)
{
	int u, v;
	distance[0] = 0;  
	for (int i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);  
		selected[u] = TRUE;  
		if (distance[u] == INF) return;  // ��� ������ ������� ���� ��� ����
		printf("���� %d �߰�\n", u + 1);  
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v])
				distance[v] = g->weight[u][v];  // ���� ������ �Ÿ� ���� ����
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));  
	graph_init(g);    
	GenerateGraph(g); 
	FindPrimMST(g);   

	free(g);          
	return 0;
}
