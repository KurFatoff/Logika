#include "Task1Header.h"

#define MAX_NODES 100

// ������� ��� ��������� ��������� ������� ���������
void generateAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                graph[i][j] = 0; // ������� ������
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 2; // ���������
            }
        }
    }
}

// ����� ������� ���������
void printAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    printf("\n������� ���������:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%d   ", graph[i][j]);
        }
        printf("\n");
    }
}

// ����� ����� � ������
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1; // -1 ��������, ��� ������� �� ��������
    }

    // ��������� �������
    dist[start] = 0;
    queue[rear++] = start;

    printf("\n����� ���������� (������� ���������):\n");

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < size; i++) {
            if (graph[current][i] && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                queue[rear++] = i;
            }
        }
    }

    printf("���������� �� ������� %d:\n", start);
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            printf("������� %d->%d: %d\n", start, i, dist[i]);
        }
        else {
            printf("������� %d->%d: ���� �����������\n", start, i);
        }
    }
}

// ���������� ������ ��������� �� ������� ���������
void buildAdjacencyList(int graph[MAX_NODES][MAX_NODES], int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    for (int i = 0; i < size; i++) {
        adjList[i] = (int*)malloc(size * sizeof(int));
        adjSize[i] = 0;
        for (int j = 0; j < size; j++) {
            if (graph[i][j]) {
                adjList[i][adjSize[i]++] = j;
            }
        }
    }
}

// ����� ������ ���������
void printAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    printf("\n������ ���������:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < adjSize[i]; j++) {
            printf("%d ", adjList[i][j]);
        }
        printf("\n");
    }
}

// ����� ����� � ������ (������ ���������)
void bfsAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
    }

    // ��������� �������
    dist[start] = 0;
    queue[rear++] = start;

    printf("\n����� ���������� (������ ���������):\n");

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                queue[rear++] = neighbor;
            }
        }
    }

    printf("���������� �� ������� %d:\n", start);
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            printf("������� %d->%d: %d\n", start, i, dist[i]);
        }
        else {
            printf("������� %d->%d: ���� �����������\n", start, i);
        }
    }
}

int task1Start() {
    int graph[MAX_NODES][MAX_NODES];
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES];
    int size, start;

    printf("������� ���������� ������ ����� (�������� %d): ", MAX_NODES);
    scanf("%d", &size);

    if (size <= 0 || size > MAX_NODES) {
        printf("������������ ���������� ������. ��������� ���������.\n");
        return 1;
    }

    printf("������� ��������� ������� (�� 0 �� %d): ", size - 1);
    scanf("%d", &start);

    if (start < 0 || start >= size) {
        printf("������������ ��������� �������. ��������� ���������.\n");
        return 1;
    }

    // ��������� ������� ���������
    generateAdjacencyMatrix(graph, size);
    printAdjacencyMatrix(graph, size);

    // BFS ������� ���������
    bfsMatrix(graph, size, start);

    // ��������� ������ ���������
    buildAdjacencyList(graph, adjList, adjSize, size);
    printAdjacencyList(adjList, adjSize, size);

    // BFS ������ ���������
    bfsAdjacencyList(adjList, adjSize, size, start);

    for (int i = 0; i < size; i++) {
        free(adjList[i]);
    }

    return 0;
}
