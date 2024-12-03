#include "Task12Header.h"

// ������� ��� ��������� ��������� ������� ���������
void generateRandomGraph(int** graph, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j]; // �������������� ��� ������������������ �����
            }
        }
    }
}

// ������� ��� ������ ������� ���������
void printGraphMatrix(int** graph, int size) {
    printf("������� ���������:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%d   ", graph[i][j]);
        }
        printf("\n");
    }
}

// ������� ��� �������������� ������� ��������� � ������ ���������
void convertToAdjacencyList(int** graph, int size) {
    printf("\n������ ���������:\n");
    for (int i = 0; i < size; i++) {
        printf("������� %d: ", i + 1);
        for (int j = 0; j < size; j++) {
            if (graph[i][j] == 1) {
                printf("%d ", j + 1);
            }
        }
        printf("\n");
    }
}

// ������� �������������� ������
void mergeVertices(int** graph, int size, int u, int v) {
    u--; v--; // ������� � ��������� �������
    for (int i = 0; i < size; i++) {
        if (graph[u][i] == 1 || graph[v][i] == 1) {
            graph[u][i] = 1;
            graph[i][u] = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        graph[v][i] = 0;
        graph[i][v] = 0;
    }
    printf("������� %d � %d �������������.\n", u + 1, v + 1);
}

// ������� ���������� �����
void contractEdge(int** graph, int size, int u, int v) {
    if (graph[u - 1][v - 1] == 1) {
        mergeVertices(graph, size, u, v);
        printf("����� ����� ��������� %d � %d �������.\n", u, v);
    }
    else {
        printf("����� ��������� %d � %d ��� �����.\n", u, v);
    }
}

// ������� ����������� �������
int** splitVertex(int** graph, int* size, int v) {
    v--; // ������� � ��������� �������
    int newSize = *size + 1;

    // ���������� �����
    int** newGraph = (int**)realloc(graph, newSize * sizeof(int*)); // ����� �������������� � int**
    if (!newGraph) {
        printf("������ ��������� ������ ��� �����!\n");
        return graph; // ���������� ������ ��������� ��� ���������
    }

    for (int i = 0; i < newSize; i++) {
        int* temp = (int*)realloc(newGraph[i], newSize * sizeof(int)); // ����� �������������� � int*
        if (!temp) {
            printf("������ ��������� ������ ��� ��������!\n");

            // ����������� ��� ���������� ������ ��� ����� �����
            for (int j = 0; j < i; j++) {
                free(newGraph[j]);
            }
            free(newGraph);
            return graph; // ���������� ������ ���������
        }
        newGraph[i] = temp;
    }

    // ������������� ����� ������ � �������
    for (int i = 0; i < newSize; i++) {
        newGraph[newSize - 1][i] = 0;
        newGraph[i][newSize - 1] = 0;
    }

    // ���������� ����� ������� � ���������� ��������
    for (int i = 0; i < *size; i++) {
        if (newGraph[v][i] == 1) {
            newGraph[newSize - 1][i] = 1;
            newGraph[i][newSize - 1] = 1;
        }
    }
    newGraph[v][newSize - 1] = 1;
    newGraph[newSize - 1][v] = 1;

    *size = newSize;
    printf("������� %d ���������� �� ������� %d � %d.\n", v + 1, v + 1, newSize);
    return newGraph; // ���������� ����� ���������
}

// ������� ��� ���������� �������� ��� ������
void performOperations(int** graph, int* size) {
    int v1, v2, choice;

    while (1) {
        printf("\n�������� ��������:\n");
        printf("1 - �������������� ������\n");
        printf("2 - ���������� �����\n");
        printf("3 - ����������� �������\n");
        printf("4 - ����� ������� ���������\n");
        printf("5 - �����\n");
        printf("������� ����� ��������: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("������� ������ ������ ��� ��������������: ");
            scanf("%d %d", &v1, &v2);
            mergeVertices(graph, *size, v1, v2);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 2) {
            printf("������� ������ ������ ��� ���������� �����: ");
            scanf("%d %d", &v1, &v2);
            contractEdge(graph, *size, v1, v2);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 3) {
            printf("������� ����� ������� ��� �����������: ");
            scanf("%d", &v1);
            graph = splitVertex(graph, size, v1);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 4) {
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 5) {
            printf("�� ��������!\n");
            break;
        }
        else {
            printf("������: �������� ����� ��������\n");
        }
    }
}

int startTaskOneTwo() {
    setlocale(LC_ALL, "RUS");

    int size;
    printf("������� ������ �����: ");
    scanf("%d", &size);

    // ������������ ��������� ������ ��� �������
    int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // ��������� ��������� ������� ���������
    generateRandomGraph(graph, size);
    printGraphMatrix(graph, size);
    convertToAdjacencyList(graph, size);

    // ���������� �������� ��� ������
    performOperations(graph, &size);

    // ������������ ������
    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}