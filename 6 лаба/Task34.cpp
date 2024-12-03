#include "Task34Header.h"


// ������� ��� ��������� ��������� ������� ���������
void generateRandomGraphh(int** graph, int size) {
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
void printGraphMatrixx(int** graph, int size) {
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

// ������� ����������� ������
void unionGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] || graph2[i][j];
        }
    }
}

// ������� ����������� ������
void intersectGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] && graph2[i][j];
        }
    }
}

// ������� ��������� ����� ������
void ringSumGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] ^ graph2[i][j];
        }
    }
}

// ������� ��������� ������������ ������
void cartesianProductGraphs(int** graph1, int size1, int** graph2, int size2, int** result) {
    int size = size1 * size2;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size1; k++) {
                for (int l = 0; l < size2; l++) {
                    int index1 = i * size2 + j;
                    int index2 = k * size2 + l;
                    result[index1][index2] = (i == k && graph2[j][l]) || (j == l && graph1[i][k]);
                }
            }
        }
    }
}

// ������� ��� ���������� �������� ��� ������
void performOperations(int** graph1, int** graph2, int* size1, int* size2) {
    int v1, v2, choice;

    while (1) {
        printf("\n�������� ��������:\n");
        printf("1 - �����������\n");
        printf("2 - �����������\n");
        printf("3 - ��������� �����\n");
        printf("4 - ��������� ������������\n");
        printf("5 - �����\n");
        printf("������� ����� ��������: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            unionGraphs(graph1, graph2, *size1, result);
            printf("\n����������� ������:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 2) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            intersectGraphs(graph1, graph2, *size1, result);
            printf("\n����������� ������:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 3) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            ringSumGraphs(graph1, graph2, *size1, result);
            printf("\n��������� ����� ������:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 4) {
            int sizeProduct = *size1 * *size2;
            int** cartesianResult = (int**)malloc(sizeProduct * sizeof(int*));
            for (int i = 0; i < sizeProduct; i++) cartesianResult[i] = (int*)malloc(sizeProduct * sizeof(int));
            cartesianProductGraphs(graph1, *size1, graph2, *size2, cartesianResult);
            printf("\n��������� ������������ ������:\n");
            printGraphMatrixx(cartesianResult, sizeProduct);
            for (int i = 0; i < sizeProduct; i++) free(cartesianResult[i]);
            free(cartesianResult);
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

int startTaskThreeFour() {
    setlocale(LC_ALL, "RUS");

    int size1, size2;
    printf("������� ������ ������� �����: ");
    scanf("%d", &size1);
    printf("������� ������ ������� �����: ");
    scanf("%d", &size2);

    // ������������ ��������� ������ ��� �������
    int** graph1 = (int**)malloc(size1 * sizeof(int*));
    for (int i = 0; i < size1; i++) {
        graph1[i] = (int*)malloc(size1 * sizeof(int));
    }

    int** graph2 = (int**)malloc(size1 * sizeof(int*));
    for (int i = 0; i < size1; i++) {
        graph2[i] = (int*)malloc(size1 * sizeof(int));
    }

    generateRandomGraphh(graph1, size1);
    generateRandomGraphh(graph2, size2);
    printf("\n���� 1:\n");
    printGraphMatrixx(graph1, size1);
    printf("\n���� 2:\n");
    printGraphMatrixx(graph2, size2);

    performOperations(graph1, graph2, &size1, &size2);

    for (int i = 0; i < size1; i++) free(graph1[i]);
    for (int i = 0; i < size2; i++) free(graph2[i]);
    free(graph1);
    free(graph2);

    return 0;
}