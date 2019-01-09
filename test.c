#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_DEPRECATE

typedef struct Teacher
{
	int Number;//ְ����
	char Name[20];//����
	char Title[20];//ְ��
	char Sex[5];//�Ա�
	char Course[20];//3�Ž��ڿγ̵�����
	int Score;//��ѧЧ���ۺ�����
	struct Teacher*next;
} TeacherLink, *Pointer;

int choose;//�˵�ѡ����
int menu();//���˵�
int flag = 1;//�Ƿ��˳���ͳflag
int n = 1;
void welcome();//��ӭ����
void exitTeacher();//�˳�����
Pointer readTeacher();//��ȡ�ļ�
void displayTeacher(Pointer Head);//��ʾ
void insertTeacher(Pointer*Head);//���
void sortTeacher(Pointer Head);//ְ����\��ѧЧ����������
void selectTeacher(Pointer Head);//����
void selectNum(Pointer Head);//�̹��Ų���
void selectName(Pointer Head);//��������
void deleteTeacher(Pointer*Head);//����ְ����ɾ��
void updateTeacher(Pointer*Head);//����ְ�����޸�
void saveTeacher(Pointer Head);//����
Pointer maopaoNumber(Pointer l);//ְ����
Pointer maopaoScore(Pointer l);//��ѧЧ���ۺ�����
FILE*openfile(char *fileaddress, char *openmode);
void main()//������
{
	welcome();//��ӭ����
	Pointer Head = (Pointer)malloc(sizeof(TeacherLink));
	Head->next = NULL;
	Head = readTeacher();
	//Sleep(5000); //˯5s
	do{
		choose = menu();
		switch (choose){
		case 1:
			insertTeacher(&Head);//���
			break;
		case 2:
			displayTeacher(Head);//��ʾ
			break;
		case 3:
			sortTeacher(Head);//ְ����\��ѧЧ����������
			break;
		case 4:
			selectTeacher(Head);//�̹���\��������
			break;
		case 5:
			deleteTeacher(&Head);//����ְ����ɾ��
			break;
		case 6:
			updateTeacher(&Head);//����ְ�����޸�
			break;
		case 7:
			saveTeacher(Head);//����
			break;
		case 8:
			flag = 0;//�˳�
			break;
		default:
			printf("error�������������ѡ������������ѡ�1-8�����в��������� \n");
			break;
		}

	} while (flag != 0);
	exitTeacher();
}
void welcome(){
	printf(" ******************************************************************************************** \n");
	printf(" *******************        ��ӭʹ�üѼѽ���ʦ��Ϣ����ϵͳ             ********************** \n");
	printf(" ******************************************************************************************** \n");
}
void exitTeacher(){//3s���˳�
	for (int i = 3; i>0; i--){
		system("cls");//�����Ļ����
		printf(" ******************************************************************************************** \n");
		printf(" *******************                 ������%d����˳�                  ********************** \n", i);
		printf(" ******************************************************************************************** \n");
		Sleep(1000); //˯1s
	}
}
//���˵�
int menu(){
	int choose;
	system("pause");
	system("cls");//�����Ļ����
	printf(" *****************************    ��ӭʹ�üѼѽ�ѧԺ��ѧ��Ϣ����ϵͳ    ***************************** \n");
	printf(" *****************************           1.�� �� �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           2.�� ʾ �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           3.�� ʦ �� Ϣ �� ��            ***************************** \n");
	printf(" *****************************           4.�� ѯ �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           5.ɾ �� �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           6.�� �� �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           7.�� �� �� ʦ �� Ϣ            ***************************** \n");
	printf(" *****************************           8.�� �� �� �� ϵ ͳ            ***************************** \n");
	printf(" ������ѡ�1-8�����в����� \n");
	scanf_s("%d", &choose);
	return choose;
}
//��ȡ�ļ�
Pointer readTeacher()
{
	Pointer p, team, head;
	char name[20], title[20], sex[5], course[20];
	FILE* fp = openfile("d:\\Teacher.txt", "a+");
	head = (Pointer)malloc(sizeof(TeacherLink));
	team = (Pointer)malloc(sizeof(TeacherLink));
	team->next = NULL;
	p = head;
	p->next = NULL;

	fscanf(fp, "%d%s%s%s%s%d", &(team->Number), name, title, sex, course, &(team->Score));
	strcpy(team->Name, name);
	strcpy(team->Title, title);
	strcpy(team->Sex, sex);
	strcpy(team->Course, course);
	while (!feof(fp))
	{
		p->next = (Pointer)malloc(sizeof(TeacherLink));
		p = p->next;
		p->next = NULL;
		p->Number = team->Number;
		strcpy(p->Name, team->Name);
		strcpy(p->Title, team->Title);
		strcpy(p->Sex, team->Sex);
		strcpy(p->Course, team->Course);
		p->Score = team->Score;
		fscanf(fp, "%d%s%s%s%s%d", &team->Number, name, title, sex, course, &team->Score);
		strcpy(team->Name, name);
		strcpy(team->Title, title);
		strcpy(team->Sex, sex);
		strcpy(team->Course, course);
	}
	//fclose(fp);
	return head;
}
FILE*openfile(char *fileaddress, char *openmode)
{
	FILE *fp;
	fp = fopen(fileaddress, openmode);
	if (!fp)
	{
		printf("File open error!\n");
		exit(0);
	}
	return fp;
}
void displayTeacher(Pointer Head)
{
	Pointer p;
	p = Head;
	int t = 0;
	if (p == NULL)
		printf("�޼�¼\n");
	p = p->next;
	while (p != NULL)
	{
		if (!t)
			printf("ְ����\t����\tְ��\t�Ա�\t3�Ž��ڿγ̵�����\t��ѧЧ���ۺ�����\n");
		t = 1;
		printf("%d\t", p->Number);
		printf("%s\t", p->Name);
		printf("%s\t", p->Title);
		printf("%s\t", p->Sex);
		printf("%s\t", p->Course);
		printf("%d\t\n", p->Score);
		p = p->next;
	}
}
//�����ʦ��Ϣ
void insertTeacher(Pointer*Head)
{
	int num_t;
	Pointer p, q, r;
	printf("������ְ���ţ�\n");
	scanf("%d", &num_t);
	p = q = *Head;
	p = p->next;
	while (p != NULL)
	{
		if (p->Number == num_t)
		{
			printf("�Ѿ�����ְͬ����:\n");
			return;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	r = (Pointer)malloc(sizeof(TeacherLink));
	r->next = NULL;
	if (q == NULL)
		*Head = r;
	else
		q->next = r;
	r->Number = num_t;
	printf("������������\n");
	scanf("%s", r->Name);
	printf("������ְ�ƣ�\n");
	scanf("%s", r->Title);
	printf("�������Ա�\n");
	scanf("%s", r->Sex);
	printf("������3�Ž��ڿγ̵�������\n");
	scanf("%s", r->Course);
	printf("�������ѧЧ���ۺ����֣�\n");
	scanf("%d", &r->Score);
}
//�����ʦ��Ϣ
void sortTeacher(Pointer Head)
{
	int s;
	Pointer t = NULL;
	printf("��������Ҫ������Ϣ\n");
	printf("1---ְ����\n");
	printf("2---��ѧЧ���ۺ�����\n");
	scanf("%d", &s);
	t = Head->next;
	if (s == 1)
	{
		t = maopaoNumber(Head);
		displayTeacher(t);
	}
	else if (s == 2)
	{
		t = maopaoScore(Head);
		displayTeacher(t);
	}
}
//���ҽ�ʦ��Ϣ
void selectTeacher(Pointer Head)
{
	int s;
	printf("��������ҷ�ʽ\n");
	printf("1---����ְ���Ų���\n");
	printf("2---������������\n");
	scanf("%d", &s);
	if (s == 1)
	{
		selectNum(Head);
	}
	else if (s == 2)
	{
		selectName(Head);
	}
}
//���ҽ�ʦ��������
void selectName(Pointer Head)
{
	int flag = 1;
	char Name[20];
	Pointer p;
	p = Head;
	printf("��������Ҫ���ҵ�������\n");
	scanf("%s", Name);
	while (p != NULL && flag)
	{
		if ((strcmp(Name, p->Name)) == NULL)
		{
			flag = 0;
		}
		else
		{
			p = p->next;
		}
	}
	if (flag == 0)
	{
		printf("ְ����\t����\tְ��\t�Ա�\t3�Ž��ڿγ̵�����\t��ѧЧ���ۺ�����\n");
		printf("%d\t", p->Number);
		printf("%s\t", p->Name);
		printf("%s\t", p->Title);
		printf("%s\t", p->Sex);
		printf("%s\t", p->Course);
		printf("%d\t\n", p->Score);
	}
	else
	{
		printf("û��Ҫ��ѯ�ļ�¼\n");
	}
}
//���ҽ�ʦ����ְ����
void selectNum(Pointer Head)
{
	int flag = 1;
	int num_t;
	Pointer p;
	p = Head;
	printf("��������Ҫ���ҵ�ְ���ţ�\n");
	scanf("%d", &num_t);
	while (p != NULL && flag)
	{
		if (p->Number == num_t)
		{
			flag = 0;
		}
		else
		{
			p = p->next;
		}
	}
	if (flag == 0)
	{
		printf("ְ����\t����\tְ��\t�Ա�\t3�Ž��ڿγ̵�����\t��ѧЧ���ۺ�����\n");
		printf("%d\t", p->Number);
		printf("%s\t", p->Name);
		printf("%s\t", p->Title);
		printf("%s\t", p->Sex);
		printf("%s\t", p->Course);
		printf("%d\t\n", p->Score);
	}
	else
	{
		printf("û��Ҫ��ѯ�ļ�¼\n");
	}
}
//ɾ����ʦ��Ϣ
void deleteTeacher(Pointer*Head)
{
	int flagu = 1;
	int num_t;
	printf("������ְ���ţ�\n");
	scanf("%d", &num_t);
	Pointer p, q;
	p = q = *Head;
	while (p != NULL && flagu)
	{
		if (p->Number == num_t)
		{
			int t = 0;
			printf("�Ƿ�Ҫ���ɾ����Ϣ��������\n1--��\n0--��\n");
			scanf("%d", &t);
			if (t)
			{
				if (p == *Head)
				{
					*Head = p->next;
					free(p);
					flagu = 0;
				}
				else
				{
					q->next = p->next;
					free(p);
					flagu = 0;
				}
			}
			else
			{
				break;
			}

		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	if (flagu)
		printf("û���ҵ�����ɾ��������\n");
}
//�޸Ľ�ʦ��Ϣ
void updateTeacher(Pointer*Head)
{
	Pointer r;
	int num_t;
	int flagu = 1;
	r = *Head;
	r = r->next;
	printf("������ְ���ţ�\n");
	scanf("%d", &num_t);
	while (r != NULL && flagu)
	{
		if (r->Number == num_t)
		{
			printf("������ְ���ţ�\n");
			scanf("%d", &r->Number);
			printf("������������\n");
			scanf("%s", r->Name);
			printf("������ְ�ƣ�\n");
			scanf("%s", r->Title);
			printf("�������Ա�\n");
			scanf("%s", r->Sex);
			printf("������3�Ž��ڿγ̵�������\n");
			scanf("%s", r->Course);
			printf("�������ѧЧ���ۺ����֣�\n");
			scanf("%d", &r->Score);
			flagu = 0;
		}
	}
	if (flagu)
		printf("û�в�ѯ��Ҫ�޸ĵļ�¼:\n");
}
//�����ʦ��Ϣ
void saveTeacher(Pointer Head)
{
	FILE*fp;
	if ((fp = fopen("d:\\Teacher.txt", "w")) == NULL)
	{
		printf("Can't open the file\n");
	}
	if (n == 0)
	{
		fprintf(fp, "%s", "ְ����    ����    ְ��    �Ա�    3�Ž��ڿγ̵�����    ��ѧЧ���ۺ�����\n");
		n = 1;
	}
	Pointer p;
	p = Head;
	p = p->next;
	while (p != NULL)
	{
		fprintf(fp, "%d\t", p->Number);
		fprintf(fp, "%s\t", p->Name);
		fprintf(fp, "%s\t", p->Title);
		fprintf(fp, "%s\t", p->Sex);
		fprintf(fp, "%s\t", p->Course);
		fprintf(fp, "%d\t\n", p->Score);
		p = p->next;
	}
	fflush(fp);
	fclose(fp);
}
//����Number����
Pointer maopaoNumber(Pointer l)
{
	Pointer head, ptr, qtr, team;
	team = (Pointer)malloc(sizeof(TeacherLink));
	team->next = NULL;
	int len = 0;
	int i, j;
	head = l;
	ptr = head->next;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	for (i = 0; i<len; i++)
	{
		qtr = head->next;
		ptr = head->next->next;
		for (j = 0; j<len - i - 1; j++)
		{
			if (qtr->Number>ptr->Number)
			{
				team->Number = qtr->Number;
				strcpy(team->Name, qtr->Name);
				strcpy(team->Title, qtr->Title);
				strcpy(team->Sex, qtr->Sex);
				strcpy(team->Course, qtr->Course);
				team->Score = qtr->Score;

				qtr->Number = ptr->Number;
				strcpy(qtr->Name, ptr->Name);
				strcpy(qtr->Title, ptr->Title);
				strcpy(qtr->Sex, ptr->Sex);
				strcpy(qtr->Course, ptr->Course);
				qtr->Score = ptr->Score;

				ptr->Number = team->Number;
				strcpy(ptr->Name, team->Name);
				strcpy(ptr->Title, team->Title);
				strcpy(ptr->Sex, team->Sex);
				strcpy(ptr->Course, team->Course);
				ptr->Score = team->Score;
			}
			qtr = qtr->next;
			ptr = ptr->next;
		}
	}
	return head;
}
//����Score����
Pointer maopaoScore(Pointer l)
{
	Pointer head, ptr, qtr, team;
	team = (Pointer)malloc(sizeof(TeacherLink));
	team->next = NULL;
	int len = 0;
	int i, j;
	head = l;
	ptr = head->next;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	for (i = 0; i<len; i++)
	{
		qtr = head->next;
		ptr = head->next->next;
		for (j = 0; j<len - i - 1; j++)
		{
			if (qtr->Score>ptr->Score)
			{
				team->Number = qtr->Number;
				strcpy(team->Name, qtr->Name);
				strcpy(team->Title, qtr->Title);
				strcpy(team->Sex, qtr->Sex);
				strcpy(team->Course, qtr->Course);
				team->Score = qtr->Score;

				qtr->Number = ptr->Number;
				strcpy(qtr->Name, ptr->Name);
				strcpy(qtr->Title, ptr->Title);
				strcpy(qtr->Sex, ptr->Sex);
				strcpy(qtr->Course, ptr->Course);
				qtr->Score = ptr->Score;

				ptr->Number = team->Number;
				strcpy(ptr->Name, team->Name);
				strcpy(ptr->Title, team->Title);
				strcpy(ptr->Sex, team->Sex);
				strcpy(ptr->Course, team->Course);
				ptr->Score = team->Score;
			}
			qtr = qtr->next;
			ptr = ptr->next;
		}
	}
	return head;
}