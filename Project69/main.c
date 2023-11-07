#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define MAX_VERTEXS 1000
#define INF 1000

int parent[MAX_VERTEXS];

void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;
    struct Edge edges[MAX_VERTEXS]; 
} GraphType;

void graph_init(GraphType* g) {
    g->n = 0;
}

void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

void min_heap(struct Edge arr[], int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight < arr[smallest].weight)
        smallest = left;

    if (right < n && arr[right].weight < arr[smallest].weight)
        smallest = right;

    if (smallest != i) {
        struct Edge temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        min_heap(arr, smallest, n);
    }
}

void set_min_heap(struct Edge arr[], int n) { //최소 힙 정렬
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heap(arr, i, n);
    }
}

void kruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->n);

    set_min_heap(g->edges, g->n);

    printf("Kruskal MST Algorithm\n");
    while (edge_accepted < (g->n - 1)) {
        e = g->edges[0];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d, %d) Select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        // 선택한 간선을 배열에서 제거
        for (int i = 0; i < g->n - 1; i++) {
            g->edges[i] = g->edges[i + 1];
        }
        
        // 다시 최소 힙으로 정렬
        set_min_heap(g->edges, g->n);
    }
}


int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g); //초기화

	insert_edge(g, 1, 7, 12); //g start end weight
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);

	kruskal(g); 

	free(g);
	return 0;

}