#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];   // adjacency matrix: graph[i][j] = 1 means edge i - j
int visited[MAX];      // 1 = already visited, 0 = not visited yet
int n;                 // number of vertices

// Mark all vertices as not visited
void resetVisited() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
}

// ---------------- DFS (uses recursion) ----------------
void dfs(int node) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < n; i++) {
        if (graph[node][i] == 1 && !visited[i]) {
            dfs(i);                  // go deeper first
        }
    }
}

// ---------------- BFS (uses a queue) ----------------
void bfs(int start) {
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;           // put start vertex in the queue

    while (front < rear) {           // repeat until queue is empty
        int node = queue[front++];   // take one vertex from the front
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;   // add neighbors to the back
            }
        }
    }
}

// ---------------- Main ----------------
int main() {
    int edges, u, v, start;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as two vertices (u v), numbered 0 to %d:\n", n - 1);
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;             // undirected graph:
        graph[v][u] = 1;             // add the edge both ways
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("\nDFS Traversal: ");
    resetVisited();
    dfs(start);

    printf("\nBFS Traversal: ");
    resetVisited();
    bfs(start);

    printf("\n");
    return 0;
}