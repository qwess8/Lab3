#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>


struct node
{
	char inf[256]; // полезная информация
	int pr;
	struct node *next; // ссылка на следующий элемент
};

struct node *head = NULL, *last = NULL, *f = NULL;
int dlinna = 0, flag = -1;
void spstore(void), review(void), del(char *name);
char find_el[256], str[256];
struct node *find(char *name);
struct node *get_struct(void);

struct node *get_struct(void)
{
	struct node *p = NULL;
	char s[256];
	int t;
	if ((p = (node*)malloc(sizeof(struct node))) == NULL)
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}
	printf("Введите название объекта: \n ");
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);
	printf("Введите приоритет: \n ");
	scanf("%i", &(p->pr));
	p->next = NULL;
	return p;
}

void spstore(void)
{
	struct node *p = NULL, *temp = head;
	p = get_struct();
	if (head == NULL && p != NULL) // если списка нет, то устанавливаем голову
	{
		head = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		if(p->pr > temp->pr){
			p->next = temp;
			head = p;
			return;
		}
		while(true){
			if(temp->next==NULL || p->pr > temp->next->pr){
				p->next = temp->next;
				temp->next = p;
				return;
			}
			temp = temp->next;
		}
	}
	return;
}

/* Просмотр содержимого списка. */
void review(void)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("%s, %d; ", struc->inf, struc->pr);
		struc = struc->next;
	}
	return;
}

struct node *find(char *name)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			printf("%s, %d ", struc->inf, struc->pr);
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

void del(char *name)
{
	struct node *struc = head; // указатель, проходящий по списку установлен на начало
	struct node *prev;// указатель на предшествующий удаляемому элемент
	int flag = 0; // индикатор отсутствия удаляемого элемента в списке
	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}
	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc); // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}
	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1; // выставляем индикатор
			if (struc->next) // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc); // удаляем элемент
				struc = prev->next; // устанавливаем указатель для продолжения

			}
			else // если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего

				free(struc); // удаляем элемент
				return;

			}
		}
		else
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}
	if (flag == 0) // если флаг = 0, значит нужный элемент не
	{
		printf("Элемент не найден\n");
		return;
	}
}

int main()
{
	
	setlocale(LC_ALL, "Rus");
	while(flag!=5){
		system("cls");
		printf("1. Добавить элемент\n2. Удалить элемент\n3. Найти элемент\n4. Отобразить список\n5. Выйти из программы\nВвод: ");
		scanf("%d", &flag);
		if(flag == 1){
			system("cls");
			spstore();
		}
		else if(flag == 2){
			system("cls");
			printf("Введите название нужного элемента:");
			scanf("%s", str);
			del(str);
		}
		else if(flag == 3){
			system("cls");
			printf("Введите название нужного элемента:");
			scanf("%s", str);
			find(str);
			printf("\nДля возврата к меню введите любой символ:");
			getchar();
			getchar();
		}
		else if(flag == 4){
			system("cls");
			review();
			printf("\nДля возврата к меню введите любой символ:");
			getchar();
			getchar();
		}
	}

	getchar();
	return 0;
}