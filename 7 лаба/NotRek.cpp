#include "NotRekHeader.h"

// ��������� ������� ���������
void generateAdjacencyMatrixx(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                int edge = rand() % 2;
                matrix[i][j] = edge;
                matrix[j][i] = edge;
            }
        }
    }
}

// ����� ������� ���������
void printAdjacencyMatrixx(int** matrix, int size) {
    printf("\n������� ���������:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%d   ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ������������� ����� � ������� � �������������� �����
void dfsNonRecursive(int** matrix, int size, int startVertex) {
    int* visited = (int*)malloc(size * sizeof(int)); // ������ ���������� ������
    int* stack = (int*)malloc(size * sizeof(int));   // ���� ��� ������
    int top = -1; // ������ ������� �� ������� �����

    // ������������� ������� ���������� ������
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    // ��������� ��������� ������� � ����
    stack[++top] = startVertex;

    printf("����� � ������� (�������������): ");
    while (top >= 0) {
        int currentVertex = stack[top--]; // ������� ������� �� �����

        // ���� ������� ��� �� ���� ��������
        if (!visited[currentVertex]) {
            printf("%d ", currentVertex+1);
            visited[currentVertex] = 1;

            // �������� � ���� ��� �������, �� ���������� �������
            for (int i = size - 1; i >= 0; i--) { // ��������� � �����, ����� ������� ��� ��� � ����������� ������
                if (matrix[currentVertex][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
    printf("\n");

    free(visited);
    free(stack);
}

int notrekStart() {
    srand(time(NULL));
    int size;

    printf("������� ������ �����: ");
    scanf("%d", &size);

    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    generateAdjacencyMatrixx(matrix, size);
    printAdjacencyMatrixx(matrix, size);

    dfsNonRecursive(matrix, size, 0);

    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
