#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_DEPRECATE

typedef struct Teacher
{
	int Number;//职工号
	char Name[20];//姓名
	char Title[20];//职称
	char Sex[5];//性别
	char Course[20];//3门讲授课程的名单
	int Score;//教学效果综合评分
	struct Teacher*next;
} TeacherLink, *Pointer;

int choose;//菜单选择项
int menu();//主菜单
int flag = 1;//是否退出体统flag
int n = 1;
void welcome();//欢迎界面
void exitTeacher();//退出程序
Pointer readTeacher();//读取文件
void displayTeacher(Pointer Head);//显示
void insertTeacher(Pointer*Head);//添加
void sortTeacher(Pointer Head);//职工号\教学效果评分排序
void selectTeacher(Pointer Head);//查找
void selectNum(Pointer Head);//教工号查找
void selectName(Pointer Head);//姓名查找
void deleteTeacher(Pointer*Head);//输入职工号删除
void updateTeacher(Pointer*Head);//输入职工号修改
void saveTeacher(Pointer Head);//保存
Pointer maopaoNumber(Pointer l);//职工号
Pointer maopaoScore(Pointer l);//教学效果综合评分
FILE*openfile(char *fileaddress, char *openmode);
void main()//主函数
{
	welcome();//欢迎界面
	Pointer Head = (Pointer)malloc(sizeof(TeacherLink));
	Head->next = NULL;
	Head = readTeacher();
	//Sleep(5000); //睡5s
	do{
		choose = menu();
		switch (choose){
		case 1:
			insertTeacher(&Head);//添加
			break;
		case 2:
			displayTeacher(Head);//显示
			break;
		case 3:
			sortTeacher(Head);//职工号\教学效果评分排序
			break;
		case 4:
			selectTeacher(Head);//教工号\姓名查找
			break;
		case 5:
			deleteTeacher(&Head);//输入职工号删除
			break;
		case 6:
			updateTeacher(&Head);//输入职工号修改
			break;
		case 7:
			saveTeacher(Head);//保存
			break;
		case 8:
			flag = 0;//退出
			break;
		default:
			printf("error！！！您输入的选项有误，请输入选项（1-8）进行操作！！！ \n");
			break;
		}

	} while (flag != 0);
	exitTeacher();
}
void welcome(){
	printf(" ******************************************************************************************** \n");
	printf(" *******************        欢迎使用佳佳酱教师信息管理系统             ********************** \n");
	printf(" ******************************************************************************************** \n");
}
void exitTeacher(){//3s后退出
	for (int i = 3; i>0; i--){
		system("cls");//清除屏幕内容
		printf(" ******************************************************************************************** \n");
		printf(" *******************                 程序将在%d秒后退出                  ********************** \n", i);
		printf(" ******************************************************************************************** \n");
		Sleep(1000); //睡1s
	}
}
//主菜单
int menu(){
	int choose;
	system("pause");
	system("cls");//清除屏幕内容
	printf(" *****************************    欢迎使用佳佳酱学院教学信息管理系统    ***************************** \n");
	printf(" *****************************           1.添 加 教 师 信 息            ***************************** \n");
	printf(" *****************************           2.显 示 教 师 信 息            ***************************** \n");
	printf(" *****************************           3.教 师 信 息 排 序            ***************************** \n");
	printf(" *****************************           4.查 询 教 师 信 息            ***************************** \n");
	printf(" *****************************           5.删 除 教 师 信 息            ***************************** \n");
	printf(" *****************************           6.修 改 教 师 信 息            ***************************** \n");
	printf(" *****************************           7.保 存 教 师 信 息            ***************************** \n");
	printf(" *****************************           8.退 出 管 理 系 统            ***************************** \n");
	printf(" 请输入选项（1-8）进行操作： \n");
	scanf_s("%d", &choose);
	return choose;
}
//读取文件
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
		printf("无记录\n");
	p = p->next;
	while (p != NULL)
	{
		if (!t)
			printf("职工号\t姓名\t职称\t性别\t3门讲授课程的名单\t教学效果综合评分\n");
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
//插入教师信息
void insertTeacher(Pointer*Head)
{
	int num_t;
	Pointer p, q, r;
	printf("请输入职工号：\n");
	scanf("%d", &num_t);
	p = q = *Head;
	p = p->next;
	while (p != NULL)
	{
		if (p->Number == num_t)
		{
			printf("已经有相同职工号:\n");
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
	printf("请输入姓名：\n");
	scanf("%s", r->Name);
	printf("请输入职称：\n");
	scanf("%s", r->Title);
	printf("请输入性别：\n");
	scanf("%s", r->Sex);
	printf("请输入3门讲授课程的名单：\n");
	scanf("%s", r->Course);
	printf("请输入教学效果综合评分：\n");
	scanf("%d", &r->Score);
}
//排序教师信息
void sortTeacher(Pointer Head)
{
	int s;
	Pointer t = NULL;
	printf("请输入需要排序信息\n");
	printf("1---职工号\n");
	printf("2---教学效果综合评分\n");
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
//查找教师信息
void selectTeacher(Pointer Head)
{
	int s;
	printf("请输入查找方式\n");
	printf("1---按照职工号查找\n");
	printf("2---按照姓名查找\n");
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
//查找教师——姓名
void selectName(Pointer Head)
{
	int flag = 1;
	char Name[20];
	Pointer p;
	p = Head;
	printf("请输入您要查找的姓名：\n");
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
		printf("职工号\t姓名\t职称\t性别\t3门讲授课程的名单\t教学效果综合评分\n");
		printf("%d\t", p->Number);
		printf("%s\t", p->Name);
		printf("%s\t", p->Title);
		printf("%s\t", p->Sex);
		printf("%s\t", p->Course);
		printf("%d\t\n", p->Score);
	}
	else
	{
		printf("没有要查询的记录\n");
	}
}
//查找教师——职工号
void selectNum(Pointer Head)
{
	int flag = 1;
	int num_t;
	Pointer p;
	p = Head;
	printf("请输入您要查找的职工号：\n");
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
		printf("职工号\t姓名\t职称\t性别\t3门讲授课程的名单\t教学效果综合评分\n");
		printf("%d\t", p->Number);
		printf("%s\t", p->Name);
		printf("%s\t", p->Title);
		printf("%s\t", p->Sex);
		printf("%s\t", p->Course);
		printf("%d\t\n", p->Score);
	}
	else
	{
		printf("没有要查询的记录\n");
	}
}
//删除教师信息
void deleteTeacher(Pointer*Head)
{
	int flagu = 1;
	int num_t;
	printf("请输入职工号：\n");
	scanf("%d", &num_t);
	Pointer p, q;
	p = q = *Head;
	while (p != NULL && flagu)
	{
		if (p->Number == num_t)
		{
			int t = 0;
			printf("是否要真的删除信息？请输入\n1--是\n0--否\n");
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
		printf("没有找到可以删除的数据\n");
}
//修改教师信息
void updateTeacher(Pointer*Head)
{
	Pointer r;
	int num_t;
	int flagu = 1;
	r = *Head;
	r = r->next;
	printf("请输入职工号：\n");
	scanf("%d", &num_t);
	while (r != NULL && flagu)
	{
		if (r->Number == num_t)
		{
			printf("请输入职工号：\n");
			scanf("%d", &r->Number);
			printf("请输入姓名：\n");
			scanf("%s", r->Name);
			printf("请输入职称：\n");
			scanf("%s", r->Title);
			printf("请输入性别：\n");
			scanf("%s", r->Sex);
			printf("请输入3门讲授课程的名单：\n");
			scanf("%s", r->Course);
			printf("请输入教学效果综合评分：\n");
			scanf("%d", &r->Score);
			flagu = 0;
		}
	}
	if (flagu)
		printf("没有查询到要修改的记录:\n");
}
//保存教师信息
void saveTeacher(Pointer Head)
{
	FILE*fp;
	if ((fp = fopen("d:\\Teacher.txt", "w")) == NULL)
	{
		printf("Can't open the file\n");
	}
	if (n == 0)
	{
		fprintf(fp, "%s", "职工号    姓名    职称    性别    3门讲授课程的名单    教学效果综合评分\n");
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
//按照Number排序
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
//按照Score排序
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