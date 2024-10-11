#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>


struct node
{
	char inf[256]; // �������� ����������
	struct node *next; // ������ �� ��������� �������
};

struct node *head = NULL, *last = NULL, *f = NULL;
int dlinna = 0, flag = -1;
void push(void), review(void), del(char *name);
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
		printf("������ ��� ������������� ������\n");
		exit(1);
	}
	printf("������� �������� �������: \n ");
	scanf("%s", s);
	if (*s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	strcpy(p->inf, s);
	p->next = NULL;
	return p;
}

void push(void)
{
	struct node *p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL) // ���� ������ ���, �� ������������� ������
	{
		head = p;
		last = p;
	}
	else if (last != NULL && p != NULL) // ������ ��� ����, �� ��������� � ������
	{
		last->next = p;
		last = p;
	}
	return;
}

char *pop(){
	if(last == NULL) return NULL;
	struct node *temp = head, *prev=NULL;
	char str[256];

	if(temp->next == NULL){
			strcpy(str, last->inf);
			free(last);
			last = NULL;
			head = NULL;
			return str;
		}
	prev = temp;
	temp = temp->next;
	while(true){
		if(temp->next == NULL){
			strcpy(str, temp->inf);
			free(temp);
			prev->next = NULL;
			last = prev;
			return str;
		}
		prev = temp;
		temp = temp->next;
	}

}

/* �������� ����������� ������. */
void review(void)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("���� ����\n");
	}
	while (struc)
	{
		printf("%s; ", struc->inf);
		struc = struc->next;
	}
	return;
}

struct node *find(char *name)
{
	struct node *struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			printf("%s", struc->inf);
			return struc;
		}
		struc = struc->next;
	}
	printf("������� �� ������\n");
	return NULL;
}

void del(char *name)
{
	struct node *struc = head; // ���������, ���������� �� ������ ���������� �� ������
	struct node *prev;// ��������� �� �������������� ���������� �������
	int flag = 0; // ��������� ���������� ���������� �������� � ������
	if (head == NULL) // ���� ������ ������ ����� NULL, �� ������ ����
	{
		printf("������ ����\n");
		return;
	}
	if (strcmp(name, struc->inf) == 0) // ���� ��������� ������� - ������
	{
		flag = 1;
		head = struc->next; // ������������� ������ �� ��������� �������
		free(struc); // ������� ������ �������
		struc = head; // ������������� ��������� ��� ����������� ������
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}
	while (struc) // ������ �� ������ � ����� ���������� ��������
	{
		if (strcmp(name, struc->inf) == 0) // ���� �����, ��
		{
			flag = 1; // ���������� ���������
			if (struc->next) // ���� ��������� ������� �� ��������� � ������
			{
				prev->next = struc->next; // ������ ���������
				free(struc); // ������� �������
				struc = prev->next; // ������������� ��������� ��� �����������

			}
			else // ���� ��������� ������� ��������� � ������
			{
				prev->next = NULL; // �������� ��������� ���������������

				free(struc); // ������� �������
				return;

			}
		}
		else
		{
			prev = struc; // ������������� ��������� ��� ����������� ������
			struc = struc->next;
		}
	}
	if (flag == 0) // ���� ���� = 0, ������ ������ ������� ��
	{
		printf("������� �� ������\n");
		return;
	}
}

int main()
{
	
	setlocale(LC_ALL, "Rus");
	char str1[256];
	while(true){
		system("cls");
		printf("1. �������� �������\n2. ������� ������� � ������� ��������\n3. ���������� ����\n4. ����� �� ���������\n����: ");
		scanf("%d", &flag);
		switch(flag){
		case 1:
				system("cls");
				push();
		break;
		case 2:
				system("cls");
				strcpy(str1, pop());
				printf("%s\n", str1);
				printf("\n��� �������� � ���� ������� ����� ������:");
				getchar();
				getchar();
		break;
		case 3:
				system("cls");
				review();
				printf("\n��� �������� � ���� ������� ����� ������:");
				getchar();
				getchar();
		break;
		case 4:
			return 0;
		}
	}
}