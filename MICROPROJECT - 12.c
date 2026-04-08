#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define INF 9999

int graph[MAX][MAX], n;

// ---------- PRIM'S ALGORITHM ----------
void prim() {
    int selected[MAX] = {0};
    int no_edge = 0;
    int total = 0;

    selected[1] = 1;

    printf("\nPrim's MST:\n");

    while (no_edge < n - 1) {
        int min = INF;
        int x = 0, y = 0;

        for (int i = 1; i <= n; i++) {
            if (selected[i]) {
                for (int j = 1; j <= n; j++) {
                    if (!selected[j] && graph[i][j]) {
                        if (min > graph[i][j]) {
                            min = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        printf("T%d - T%d : %d\n", x, y, graph[x][y]);
        total += graph[x][y];
        selected[y] = 1;
        no_edge++;
    }

    printf("Total Cost = %d\n", total);
}

// ---------- UNION FIND ----------
int parent[MAX];

int find(int i) {
    while (parent[i])
        i = parent[i];
    return i;
}

int unionSet(int i, int j) {
    if (i != j) {
        parent[j] = i;
        return 1;
    }
    return 0;
}

// ---------- KRUSKAL ----------
void kruskal() {
    int total = 0;
    int edge_count = 0;

    for (int i = 1; i <= n; i++)
        parent[i] = 0;

    printf("\nKruskal's MST:\n");

    while (edge_count < n - 1) {
        int min = INF, a = 0, b = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] < min && graph[i][j] != 0) {
                    min = graph[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        int u = find(a);
        int v = find(b);

        if (unionSet(u, v)) {
            printf("T%d - T%d : %d\n", a, b, min);
            total += min;
            edge_count++;
        }

        graph[a][b] = graph[b][a] = INF;
    }

    printf("Total Cost = %d\n", total);
}

// ---------- CONNECTIVITY CHECK ----------
void dfs(int v, int visited[]) {
    visited[v] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[v][i] && graph[v][i] != INF && !visited[i]) {
            dfs(i, visited);
        }
    }
}

void checkConnectivity() {
    int visited[MAX] = {0};

    dfs(1, visited);

    int flag = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            flag = 0;
            break;
        }
    }

    if (flag)
        printf("Graph is Connected\n");
    else
        printf("Graph is DISCONNECTED\n");
}

// ---------- MAIN ----------
int main() {
    int edges, u, v, w, choice;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter u v weight: ");
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }

    while (1) {
        printf("\n1. Prim\n2. Kruskal\n3. Remove Edge\n4. Check Connectivity\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                prim();
                break;

            case 2:
                kruskal();
                break;

            case 3:
                printf("Enter edge to remove (u v): ");
                scanf("%d %d", &u, &v);
                graph[u][v] = graph[v][u] = 0;
                break;

            case 4:
                checkConnectivity();
                break;

            case 5:
                exit(0);
        }
    }
}
