﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>

struct node
{
	char inf[256];
	struct node* next;
};


struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, \n", struc->inf);
		struc = struc->next;
	}
	return;
}




/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev_struc = NULL; // указатель на предшествующий элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, head->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		struct node* temp = head;
		head = head->next; // установливаем голову на следующий элемент
		free(temp);  // удаляем первый элемент
	}
	else
	{
		prev_struc = head;
		struc = head->next;
		while (struc) // проход по списку и поиск удаляемого элемента
		{
			if (strcmp(name, struc->inf) == 0) // если нашли, то
			{
				flag = 1;         // выставляем индикатор
				prev_struc->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				break;
			}
			else // если не нашли, то
			{
				prev_struc = struc;
				struc = struc->next; // устанавливаем указатели для продолжения поиска
			}
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}



struct node* pop() {
	if (!head) {
		return nullptr;
	}

	if (!head->next) {
		node* temp = head;
		head = nullptr;
		return temp;
	}

	node* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next;
	}

	node* last = temp->next;
	temp->next = nullptr;
	return last;
}



void printStack() {
	struct node* temp = head;
	printf("Стэк содержит: \n");
	while (temp) {
		printf("Имя элемента - ", temp->inf, "\n");
		temp = temp->next;
	}
	printf("\n");
}


void stack() {
	while (true) {
		printf("\nВыберите предложенное действие: \n");
		printf("1 - Добавление элемента\n");
		printf("2 - Удаление элемента\n");
		printf("3 - Просмотр содержимого списка\n");
		printf("4 - Выход\n");
		printf("Введите номер выбранного действия: ");

		int choice;
		scanf("%d", &choice);

		printf("\n");

		if (choice == 1) {
			spstore();
		}
		else if (choice == 2) {
			struct node* popped = pop();
			if (popped == nullptr) {
				printf("Стэк пуст\n\n");
			}
			else {
				printf("Последний элемент удален.\n");
			}
		}

		else if (choice == 3) {
			review();
		}

		else if (choice == 4) {
			return;
		}

		else {
			printf("Некорректная операция\n\n");
		}
	}
}


int main()
{
	setlocale(LC_ALL, "RUS");
	stack();
	exit(0);
}