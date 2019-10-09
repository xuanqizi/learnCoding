#ifndef _ARI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <conio.h>


typedef struct Record {
	int numberOfQuestions;			//��������
	int numberOfSolvedQuestions;	//�ܶ�����
	int numberOfAddQuestions;		//�ӷ�������
	int solvedAdd;					//�ӷ�������
	int numberOfSub;				//����������
	int solvedSub;					//����������
	int numberOfMul;				//�˷�������
	int solvedMul;					//�˷�������
	int numberOfDiv;				//����������
	int solvedDiv;					//����������
	char evaluation[1001];			//��ʦ����
	int level;						//�����Ĺؿ���
}Record;

typedef struct User {				//���Դ洢�û���Ϣ������
	char account[20];				//�˺�
	char password[20];				//����
	char name[10];					//����
	Record record;					//�����¼
	int isTeacher;					//����Ƿ�Ϊ��ʦ
}User;

typedef struct WrongBank {
	char name[10];
	int num1;
	int num2;
	int kind;
}WrongBank;

typedef struct Node {
	User user;
	struct Node *pNext;
}Node;

#define  CLEARBUF \
{\
	int ch;\
		while((ch=getchar())!=EOF&&ch!='\n')\
		{\
		;\
	}\
 } 

extern User user_read;				//ȫ�ֱ������������û���Ϣ

int loginInterface(User* user);		//��¼���棨����ֵΪ��¼�����
int login(User* p);					//��¼(����ֵΪ��¼���)
void enrol();						//ע��
int teacherInterface(User *p);		//��ʦ��¼����ʾ����(����ֵ��ʾ�Ƿ��������)
int studentInterface(User* p);		//ѧ����¼����ʾ����(����ֵ��ʾ�Ƿ��������)
void announce();					//��ʦ��������
Node* studentList();				//����ѧ������
Node* insertList(Node* pEnd, User user);	//������뺯��
void commentStudent();				//����ѧ��
void commentSystem();				//����ϵͳ
void viewRank();					//�鿴ѧ������������
void limitTimeExercise();			//������60s������
void timeExercise();				//��ʱģʽ
void breakThrough();				//����ģʽ
void watchBank();					//�鿴���Ȿ
void exerciseYourself();			//�Բ���ϰ
void checkInfo();					//�鿴��Ϣ
void checkEvaluation();				//�鿴��ʦ����
void checkAnnouncement();			//�鿴����
int setDifficulty();				//������Ŀ�Ѷ�
int recording(int isRight, int kind,int num1, int num2);
void enterBank(char name[], int kind, int num1, int num2);			//�������������
void save();						//����ȫ�ֱ��������޸Ľ��б���
int continueOrNot();				//�ж��û��Ƿ��������
void checkRecord();					//ѧ���鿴�Լ��Ĵ����¼
Node* sort(Node* pHead);			//��ѧ����Ϣ��������������
int checkRepeat(User newUser);		//������û���Ϣ�Ƿ��ظ���0���ظ���1�û����ظ���2�����ظ���
void printErrorSituation(int situation);	//����������
void displayTimeExercise();			//��ʾ��ʱģʽ����
void timeExerciseProcess();			//��ʱģʽ����
void printDifficulty(int n);		//��ʱģʽ�д�ӡ�Ѷ�
void quit();						//�û��Ƴ�ǰ��ʾ����

#endif // !_ARI_H_


