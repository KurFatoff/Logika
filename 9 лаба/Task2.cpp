#include "Task2Header.h"
#include <time.h>

#define MAX_NODES 100

// ������� ��� ��������� ��������� ������� ���������
void generateAdjacencyMatrixx(int graph[MAX_NODES][MAX_NODES], int size) {
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
void printAdjacencyMatrixx(int graph[MAX_NODES][MAX_NODES], int size) {
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

// ����� � ������� (������� ���������)
void dfsMatrix(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int stack[MAX_NODES];
    int top = -1;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1; // -1 ��������, ��� ������� �� ��������
    }

    // ��������� �������
    dist[start] = 0;
    stack[++top] = start;

    printf("\n����� ���������� (������� ���������):\n");

    while (top >= 0) {
        int current = stack[top--];

        for (int i = 0; i < size; i++) {
            if (graph[current][i] && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                stack[++top] = i;
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

// ���������� ������ ���������
void buildAdjacencyListt(int graph[MAX_NODES][MAX_NODES], int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
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
void printAdjacencyListt(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    printf("\n������ ���������:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < adjSize[i]; j++) {
            printf("%d ", adjList[i][j]);
        }
        printf("\n");
    }
}

// ����� � ������� (������ ���������)
void dfsAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int stack[MAX_NODES];
    int top = -1;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
    }

    // ��������� �������
    dist[start] = 0;
    stack[++top] = start;

    printf("\n����� ���������� (������ ���������):\n");

    while (top >= 0) {
        int current = stack[top--];

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                stack[++top] = neighbor;
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

int task2Start() {
    int graph[MAX_NODES][MAX_NODES];
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES];
    int size, start;
    time_t time0, time1;

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

    time0 = clock();
    // ��������� ������� ���������
    generateAdjacencyMatrixx(graph, size);
    printAdjacencyMatrixx(graph, size);

    // DFS ������� ���������
    dfsMatrix(graph, size, start);

    // ��������� ������ ���������
    buildAdjacencyListt(graph, adjList, adjSize, size);
    printAdjacencyListt(adjList, adjSize, size);

    // DFS ������ ���������
    dfsAdjacencyList(adjList, adjSize, size, start);

    time1 = clock();
    printf("\n%f", difftime(time1, time0));

    for (int i = 0; i < size; i++) {
        free(adjList[i]);
    }

    return 0;
}
