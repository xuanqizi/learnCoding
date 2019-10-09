#include "ari.h"

User user_read;

int loginInterface(User* user) {								//chen
	int option = 1;													//ѡ�1Ϊ��¼��2Ϊע��
	int ret = 0;													//����ֵ��0Ϊδ��¼��1Ϊ��¼
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);					//��ȡ��׼�����豸���
	COORD crd = { 0,0 };
	INPUT_RECORD inRec;												//��¼������Ϣ
	DWORD res,mode;
	CONSOLE_CURSOR_INFO cinfo;										//���
	cinfo.bVisible = 0;												//�����Ϊ���ɼ�
	
	printf("--------------------------------------\n");
	printf("��ӭ����Сѧ�����Բ�ϵͳ\n");
	printf("--------------------------------------\n");
	printf("���������ѡ�\n");
	printf("<1>��¼\n\n");
	printf("<2>ע��\n\n");

	
	for (;;) {
		GetConsoleMode(hInput, &mode);										//�������̨ģʽ
		mode |= ENABLE_MOUSE_INPUT;											//�����������
		SetConsoleMode(hInput, mode);
		ReadConsoleInput(hInput, &inRec, 1, &res);							//��ȡ����̨������Ϣ
		if (inRec.EventType == MOUSE_EVENT && inRec.Event.MouseEvent.dwButtonState
			== FROM_LEFT_1ST_BUTTON_PRESSED) {								//����Ϊ���
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 4 &&			//����λ���ڵ�¼��������
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 1;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y ==6 &&		//����λ����ע�ᰴ������
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 2;
				break;
			}
		}
	}

	

	system("cls");
	switch (option) {
		case 2:enrol(); return 0;											//��return 0����break��ע��������µ�¼��
		case 1:return login(user);											//����login()�����ķ���ֵ
	};
}

int login(User* p) {								//chen
	char account[20];
	char password[20];
	FILE *fp = fopen("data.txt", "r");					//�򿪴洢���ݵ��ļ�
	User user;

	printf("----------------------\n");
	printf("         ��¼         \n");
	printf("----------------------\n");
	printf("�����������˺ţ�");
	scanf("%s", account);
	for (;;) {
		if (fread(&user, sizeof(user), 1, fp)) {		//�����ļ�����
			if (!strcmp(account, user.account)) {		//strcmp����ֵΪ0��ʾ�����˺�����˺���ͬ
				printf("�������������룺");
				scanf("%s", password);					//��������
				if (strcmp(password, user.password)) {
					printf("�����������������\n");
					system("pause");
					fclose(fp);
					return 0;
				}
				user_read = user;
				p = &user_read;
				fclose(fp);
				return 1;
			}
		}
		else {											//fread����ֵΪ0�����Ѿ�ȫ����ȡ
			printf("���˺Ų����ڣ�������\n");
			system("pause");
			fclose(fp);
			return 0;
		}
	}
}

void enrol() {										//chen
	FILE* fp = NULL;
	User newUser;
	int isRepeat = 0;
	char input[50];
	
	for (;;) {
		printf("�����������˺ţ�");
		fflush(stdin);								//��ջ�����
		scanf("%s", &input);
		if (strlen(input) > 19) {					//���ַ������ȳ���19���ַ�
			printErrorSituation(4);					//Ҫ���û���������
			system("pause");
			system("cls");
		}
		else {
			strcpy(newUser.account, input);
			break;
		}
	}
	system("cls");
	for (;;) {
		printf("�������������룺");
		fflush(stdin);
		scanf("%s", &input);
		if (strlen(input) > 19) {
			printErrorSituation(5);
			system("pause");
			system("cls");
		}
		else {
			strcpy(newUser.password, input);
			break;
		}
	}
	system("cls");
	printf("����������������");
	scanf("%s", &newUser.name);
	system("cls");
	if (IDYES == MessageBox(NULL, "������ʦ��", "���ȷ��", MB_YESNO)) {
		newUser.isTeacher = 1;
	}
	else {
		newUser.isTeacher = 0;
	}
	system("cls");
	
	newUser.record.numberOfAddQuestions = 0;		//��ʼ�������¼����
	newUser.record.numberOfDiv = 0;
	newUser.record.numberOfMul = 0;
	newUser.record.numberOfQuestions = 0;
	newUser.record.numberOfSolvedQuestions = 0;
	newUser.record.numberOfSub = 0;
	newUser.record.solvedAdd = 0;
	newUser.record.solvedDiv = 0;
	newUser.record.solvedMul = 0;
	newUser.record.solvedSub = 0;
	newUser.record.level = 1;
	newUser.record.evaluation[0] = '\0';
	
	isRepeat = checkRepeat(newUser);					//��ֹ�û����������ظ�
	if (!isRepeat) {
		fp = fopen("data.txt", "a");					//�򿪴洢���ݵ��ļ�
		fwrite(&newUser, sizeof(User), 1, fp);
		printf("ע����ɣ������µ�¼\n");
		fclose(fp);
	}
	else {
		printErrorSituation(isRepeat);
	}
	
	system("pause");
}

int teacherInterface(User *p) {						//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);			//��ȡ��׼������
	INPUT_RECORD inRec;										//�洢�����¼
	DWORD mode;												//�洢����̨ģʽ
	int option = 0;											//��¼�û�ѡ��

	printf("%s��ʦ������\n",user_read.name);
	printf("���������Ҫʹ�õĹ���\n");
	printf("<1>��������\n\n");
	printf("<2>��ѧ����������\n\n");
	printf("<3>��ϵͳ��������\n\n");
	printf("<4>�鿴ѧ������\n\n");
	printf("<5>�˳�\n");

	for (;;) {
		GetConsoleMode(hStdIn, &mode);						//��ȡ����̨ģʽ
		mode |= ENABLE_MOUSE_INPUT;							//�����������
		SetConsoleMode(hStdIn, mode);						//�������̨ģʽ
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);			//��ȡ����̨���뵽inRec
		if (inRec.EventType == MOUSE_EVENT &&				//�ж������λ��
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 2 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 1;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 4 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 15) {
				option = 2;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 6 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 15) {
				option = 3;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 8 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 15) {
				option = 4;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 10 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 5;
				break;
			}
		}

	}
	system("cls");

	switch (option) {
		case 5: return 0;						//<5>�˳�ϵͳ
		case 4: viewRank(); return 1;			//<4>�鿴ѧ������
		case 3: commentSystem(); return 1;		//<3>��ϵͳ��������
		case 2: commentStudent(); return 1;		//<2>��ѧ����������
		case 1: announce(); return 1;			//<1>��������
		default: break;
	}
	
	return 1;
}

int studentInterface(User* p) {					//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);			//��ȡ��׼������
	INPUT_RECORD inRec;										//���Լ�¼�������
	DWORD mode;												//���Դ洢����̨ģʽ
	int option = 0;											//����û�ѡ��

	printf("%sͬѧ�����\n", user_read.name);
	printf("���������Ҫʹ�õĹ���\n");
	printf("<1>�鿴��Ϣ\n\n");
	printf("<2>�Բ���ϰ\n\n");
	printf("<3>�鿴���Ȿ\n\n");
	printf("<4>����ģʽ\n\n");
	printf("<5>��ʱģʽ\n\n");
	printf("<6>����60s\n\n");
	printf("<7>�˳�\n\n");

	for (;;) {
		GetConsoleMode(hStdIn, &mode);						//������̨ģʽ�洢��mode��
		mode |= ENABLE_MOUSE_INPUT;							//����̨ģʽ�趨Ϊ�����������
		SetConsoleMode(hStdIn, mode);						//���ÿ���̨ģʽ
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);			//��ȡ����̨����
		if (inRec.EventType == MOUSE_EVENT &&				//�¼�����Ϊ����¼�
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {		//�¼�Ϊ���������
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 2 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 1;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 4 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 2;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 6 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 3;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 8 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 15) {
				option = 4;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 10 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 5;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 12 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 6;
				break;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 14 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 10) {
				option = 7;
				break;
			}
		}
	}
	system("cls");
	switch (option) {
		case 7: return 0;						//<7>�˳�������0��ʾ����ά��ϵͳ���У�
		case 6: limitTimeExercise(); return 1;	//<6>����60s
		case 5: timeExercise();	return 1;		//<5>��ʱģʽ
		case 4: breakThrough();	return 1;		//<4>����ģʽ
		case 3: watchBank(); return 1;			//<3>�鿴���Ȿ
		case 2: exerciseYourself();	return 1;	//<2>�Բ���ϰ
		case 1: checkInfo(); return 1;			//<1>�鿴��Ϣ
	}
	
	return 1;	
}

void announce() {								//chen
	FILE *fp = fopen("announce.txt", "a");
	char announceText[1001];
	printf("�����빫������(���1000��)��\n");
	scanf("%s", announceText);
	fprintf(fp, "%s\n", announceText);
	fclose(fp);
	system("cls");
}

Node* studentList() {							//chen
	User user;
	Node *pHead = (Node*)malloc(sizeof(Node));
	Node *pEnd = pHead;
	FILE* fp = fopen("data.txt", "r");
	pHead->pNext = NULL;
	while (fread(&user, sizeof(user), 1, fp) == 1) {
		if (user.isTeacher == 0) {					//�����û�������ʦ�����������
			pEnd = insertList(pEnd, user);
		}
	}
	fclose(fp);
	return pHead;
}

Node* insertList(Node* pEnd, User user) {		//chen
	Node* p = (Node*)malloc(sizeof(Node));
	p->user = user;
	p->pNext = NULL;
	pEnd->pNext = p;
	return p;
}

void commentStudent() {							//chen
	char name[10];
	int find = 0;								//����Ƿ��ҵ���Ӧѧ��
	FILE *fp = fopen("data.txt","rt+");			//���ı��������д��
	User user;
	char comment[1001];							//��������

	printf("������Ҫ����ѧ����������");
	scanf("%s", name);

	while (fread(&user, sizeof(user), 1, fp)) {
		if (!strcmp(user.name, name)) {			//strcmp()����ֵΪ0�������ֶ�Ӧ
			find = 1;
			break;
		}
	}
	
	if (find) {
		fseek(fp, -(long)sizeof(User), SEEK_CUR);
		printf("���������\n");
		scanf("%s",user.record.evaluation);
		fwrite(&user, sizeof(user), 1, fp);
		fclose(fp);
		printf("�������\n");
	}
	else {
		printf("δ�ҵ���ѧ��\n");
	}
	system("pause");
	system("cls");

}

void commentSystem() {					//chen
	FILE* fp = fopen("comments.txt","a");
	char commentSystemText[1001];
	printf("����������������������ͽ��飺\n");
	scanf("%s", commentSystemText);
	fprintf(fp, commentSystemText);
	fclose(fp);
	system("cls");
}

void viewRank() {						//chen
	Node* pHead = studentList();		//����ѧ��������������
	Node* p = NULL;
	int rank = 0;
	
	pHead = sort(pHead);				//���������ð������
	printf("����\t����\t������\n");
	for (p = pHead->pNext; p; p = p->pNext) {	//��������
		rank++;
		printf("��%d��\t%s\t%d\n", rank, p->user.name, p->user.record.numberOfQuestions);
	}
	system("pause");
	system("cls");

}

void limitTimeExercise() {				//feng
	int difficulty;//�Ѷ�
	int num1, num2;// ��ʽ�������� 
	int answer;//�� 
	int kind = 1; //��ʽ���� 
	int grades = 0;//��Ϸ�÷� 
	int temp;
	int rest;
	time_t start, end; //��ʱ 
	srand((unsigned)time(NULL));
	//��ӡ��ʾ 
	printf("��ӭ����������60�롱\n");
	printf("�㽫��60���ʱ����д��⣬�����ѡ��1��2��3�����Ѷȣ��������ش���Ŀ��ʱ��ʱ����");

	printf("��ϵͳ������ش���֮�������������ǲ�����ɼ������ͣ�\n");
	system("pause");
	system("cls");
	difficulty = setDifficulty();


	start = time(NULL);   //��ʼ��ʱ 
	end = time(NULL);
	for (; (end - start) < 60; end = time(NULL), kind++) {
		if (kind == 5) kind = 1;
		if (difficulty == 1) {    //�Ѷ�1 
			num1 = rand() % 10 + 1;
			num2 = rand() % 10 + 1;//����һλ�򵥵�����
			printf("С���ѣ��㻹ʣ��%d�롣\n", 60 - (end - start));

			if (num1 < num2) { temp = num1; num1 = num2; num2 = temp; }
			switch (kind) {    //����������������ʽ �����´����¼ 
			case 1:printf("%d + %d = ��\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); if ((num1 + num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 2:printf("%d - %d = ��\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);  if ((num1 - num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 3:printf("%d * %d = ��\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);  if ((num1*num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 4:printf("%d / %d = ��\n", num1, num2); fflush(stdin); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && (num1%num2) == rest, kind, num1, num2);
				if ((num1 / num2) == answer && (num1%num2) == rest) { printf("��ȷ��\n"); grades++;
				} break;
			}
		}
		else if (difficulty == 2) {   //�Ѷ�2 
			num1 = rand() % 101 + 1;
			num2 = rand() % 101 + 1;
			switch (kind) {
			case 1:printf("%d + %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); 
				if ((num1 + num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 2:printf("%d - %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);  
				if ((num1 - num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 3:printf("%d * %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);  
				if ((num1*num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 4:printf("%d / %d = ��\n", num1, num2); fflush(stdin); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && (num1%num2) == rest, kind, num1, num2);
				if ((num1 / num2) == answer && (num1%num2) == rest) { printf("��ȷ��\n"); grades++;
				}
				break;
			}
		}
		else if (difficulty == 3) {   //�Ѷ�3 
			num1 = rand() % 1001 + 1;
			num2 = rand() % 1001 + 1;
			switch (kind) {
			case 1:printf("%d + %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); 
				if ((num1 + num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 2:printf("%d - %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);
				if ((num1 - num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 3:printf("%d * %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);  
				if ((num1*num2) == answer) { printf("��ȷ��\n"); grades++;
				}
				break;
			case 4:printf("%d / %d = ��\n", num1, num2); fflush(stdin); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && (num1%num2) == rest, kind, num1, num2);
				if ((num1 / num2) == answer && (num1%num2) == rest) { printf("��ȷ��\n"); grades++;
				} break;
			}
		}
		system("pause");
		system("cls");
	}
	printf("��Ϸ������С���ѣ���һ�������%d��\n", grades);
	system("pause");
	system("cls");
}

void timeExercise() {					//yu
	clock_t start;
	clock_t end;
	displayTimeExercise();
	start = clock();						//��ʼ��ʱ 
	timeExerciseProcess();
	end = (clock() - start);				//��ʱ���� 
	printf("��ʱΪ%d��\n", end / 1000);

	Sleep(4000);								//��ͣ4�� 
	system("cls");
}

void displayTimeExercise() {			//yu
	int difficulity;
	printf("\n			**************************��ӭ�����ʱ��ϰģʽ************************\n");
	printf("				��ϵͳ����Ϊ���10�������⣬��ɺ���֪������ʱ�䣩\n");
}

void printDifficulty(int n) {
	switch (n) {
	case 1:printf("\n						     ��ǰΪ��ģʽ\n\n\n"); break;
	case 2:printf("\n						     ��ǰΪһ��ģʽ\n\n\n"); break;
	case 3:printf("\n						     ��ǰΪ����ģʽ\n\n\n"); break;
	}
}

void timeExerciseProcess() {			//yu
	int num1, num2;					//num1Ϊ������ĵ�һ������num2Ϊ�ڶ����� 
	int kindrandom;				//���������������ķ��� 
	int answer;						//�û��Ĵ� 
	char kind;						//�������� 
	int shang;						//�������� 
	int yushu;						//���������� 
	int rightcount = 0;			   	//�������� 
	int wrongcount = 0;				//�������� 
	int difficulty = 0;				    //�Ѷ� 
	int i = 0;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;


	printf("\n						    *��ѡ�����׳̶�*\n");
	printf("\n              1------��     2------һ��     3------����\n\n\n");


begin:																			//goto �����ת 
	while (!difficulty) {
		GetConsoleMode(hStdIn, &mode);
		mode |= ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdIn, mode);
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);
		if (inRec.EventType == MOUSE_EVENT &&
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 6) {
				if (inRec.Event.MouseEvent.dwMousePosition.X >= 13 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 23) {
					difficulty = 1;
				}
				else if (inRec.Event.MouseEvent.dwMousePosition.X >= 26 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 36) {
					difficulty = 2;
				}
				else if (inRec.Event.MouseEvent.dwMousePosition.X >= 41 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 51) {
					difficulty = 3;
				}
			}
		}
	}
	CLEARBUF											//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!��� 

	printf("���������ʼ");
	Sleep(2000); 														//�����Ѷ�ѡ�����ͣ2�� 
	system("cls");														//����������� 
	displayTimeExercise();												//���´�ӡ������Ϣ 
	printDifficulty(difficulty);




	for (i = 0; i < 10; i++) {															//10��ѭ������ 


		srand(time(NULL));				//������������� 
		switch (difficulty) {															//�����û������Ѷȣ�����������ķ�Χ�ı� 
		case 1: num1 = rand() % 10, num2 = rand() % 9 + 1; break;
		case 2: num1 = rand() % 90 + 10, num2 = rand() % 100 + 1; break;							//��ֹ������num2��Ϊ0 
		case 3: num1 = rand() % 900 + 100, num2 = rand() % 1000 + 1; break;

		default:

			printf("						*��ѡ�����׳̶�*\n");
			printf("\n				1------��		2------һ��		3------����\n\n\n");
			printf("������Ч�����������������\n");
			goto  begin; 															//������Чָ���ת�Ѷ�ѡ������������� 

		}

		kindrandom = rand() % 4 + 1;														//���������Ŀ���ͣ��Ӽ��˳��� 

		switch (kindrandom) {								//kindrandom������1��ӷ���2�������3��˷���4 �����

		case 1: kind = '+'; break;
		case 2: kind = '-'; break;
		case 3: kind = 'x'; break;
		case 4: kind = '/'; break;

		}


		printf("\n\n��%d�⣺\n\n", i + 1);
		if (kindrandom == 2) {
			if (num1 >= num2)printf("%d - %d =", num1, num2);
			else if (num1 < num2)printf("%d - %d =", num2, num1);						//����ʱ��ֹ��Ϊ���� 
		}
		else printf("%d %c %d =", num1, kind, num2);

		if (kindrandom == 1 || kindrandom == 2 || kindrandom == 3) {
			scanf("%d", &answer);

			CLEARBUF									//���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!��ջ����� 

				if (kindrandom == 1) {															//�ӷ� 
					if (num1 + num2 == answer) {
						rightcount++;															//��������һ 
						printf("��ϲ�㣬����ˣ�\n");
					}

					else {
						wrongcount++;
						printf("����Ŷ��\n");
					}

					Sleep(2000);
					system("cls");															//�����һ�� 
					displayTimeExercise();
					printDifficulty(difficulty);

				}
				else if (kindrandom == 2) {    											//���� 
					if (num1 >= num2) {

						if (num1 - num2 == answer) {
							rightcount++;
							printf("��ϲ�㣬����ˣ�\n");
						}

						else {
							wrongcount++;
							printf("����Ŷ��\n");
						}
						Sleep(2000);
						system("cls");
						displayTimeExercise();
						printDifficulty(difficulty);
					}
					else {
						if (num2 - num1 == answer) {
							rightcount++;
							printf("��ϲ�㣬����ˣ�\n");
						}

						else {
							wrongcount++;
							printf("����Ŷ��\n");
						}
						Sleep(2000);
						system("cls");
						displayTimeExercise();
						printDifficulty(difficulty);
					}
				}
				else if (kindrandom == 3) {												//�˷� 
					if (num1*num2 == answer) {
						rightcount++;
						printf("��ϲ�㣬����ˣ�\n");
					}

					else {
						wrongcount++;
						printf("����Ŷ��\n");
					}

					Sleep(2000);
					system("cls");
					displayTimeExercise();
					printDifficulty(difficulty);

				}
		}
		else if (kindrandom == 4) {												//���� 


			printf("���̣���");
			scanf("%d", &shang);
			if (num1 / num2 == shang)printf("��ϲ�㣬����ˣ�\n");					//���� 


			else printf("����Ŷ��\n");

			CLEARBUF									//��������������������������������������������ջ����� 
				printf(" ......(����)��");
			scanf("%d", &yushu);

			if (num1%num2 == yushu)printf("��ϲ�㣬����ˣ�\n");				//������ 

			else printf("����Ŷ��\n");
			CLEARBUF														//��ջ����� 

				if (num1 / num2 != shang || num1 % num2 != yushu) wrongcount++;
				else rightcount++;
			Sleep(2000);
			system("cls");
			displayTimeExercise();
			printDifficulty(difficulty);

		}
		printf("\n\n");
	}
	printf("������ɴ˴μ�ʱ��ϰ�������%d�������%d��\n�ٽ�������\n", rightcount, wrongcount);
}

void breakThrough() {					//feng
	int i;
	int kind;
	int answer;
	int rest;
	int right;
	int option = 0;
	int num1, num2;
	int temp;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;

	srand((unsigned)time(NULL));
	printf("С���ѣ���ӭ��������ģʽ��");
	printf("��һ���㴳���Ĺؿ����ǵ�%d��\n", user_read.record.level);
	printf("׼�����ˣ���Ϸ�����Ӻ�ʼ��\n");
	Sleep(3000);
	system("cls");
	if (user_read.record.level == 1) {  //��һ�� 
		printf("\n��ӭ������һ�أ�\n");
		for (i = 0; i < 7; i++) {
			right = 0;
			num1 = rand() % 10 + 1;    //��������� 
			num2 = rand() % 10 + 1;
			if (num1 < num2) { temp = num1; num1 = num2; num2 = temp; }
			srand((unsigned)time(NULL)); //���������--�����ɼ��������� 
			kind = rand() % 4 + 1;
			switch (kind) {                                                         //������Ŀ��ʷ                      //������� right��Ϊ1 
			case 1:printf("%d + %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); 
				if ((num1 + num2) != answer) right = 1;  break;
			case 2:printf("%d - %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);  if ((num1 - num2) != answer) right = 1; break;
			case 3:printf("%d * %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);  if ((num1*num2) != answer) right = 1; break;
			case 4:printf("%d / %d = ?\n", num1, num2); fflush(stdin); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && num1%num2 == rest, kind, num1, num2);
				if ((num1 / num2) != answer || num1 % num2 != rest) right = 1; break;
			}
			if (right == 1) {  //����Ĵ���취 
				system("cls");
				printf("����ʧ�ܣ�С���ѣ���Ҫ����ؿ�ʼ������ս��\n\n");
				printf("<��>                                   <��>\n");

				for (;;) {
					GetConsoleMode(hStdIn, &mode);
					mode |= ENABLE_MOUSE_INPUT;
					SetConsoleMode(hStdIn, mode);
					ReadConsoleInput(hStdIn, &inRec, 1, &mode);
					if (inRec.EventType == MOUSE_EVENT &&
						inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
							if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 5) {
								option = 1;
								break;
							}
							else if (inRec.Event.MouseEvent.dwMousePosition.X >= 37 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 42) {
								option = 0;
								break;
							}
						}
					}
				}

				if (option == 0) { system("cls"); break; }   // ���ѡ��0��break 
				else if (option == 1) { i = 0; system("pause"); system("cls"); } //���ѡ��1������i �� right�� 
			}
			else {
				printf("��ȷ��");
				system("pause");
				system("cls");
			}

		}
		if (right == 0) user_read.record.level++;
	}
	if (user_read.record.level == 2) {  //��2�� 
		printf("��ӭ�����ڶ��أ�\n");
		for (i = 0; i < 7; i++) {
			right = 0;
			num1 = rand() % 101 + 1;    //��������� 
			num2 = rand() % 10 + 1;
			if (num1 < num2) { temp = num1; num1 = num2; num2 = temp; }
			srand((unsigned)time(NULL)); //���������--�����ɼ��������� 
			kind = rand() % 4 + 1;
			switch (kind) {                                                         //������Ŀ��ʷ   //������� right��Ϊ1 
			case 1:printf("%d + %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); if ((num1 + num2) != answer) right = 1;  break;
			case 2:printf("%d - %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);  if ((num1 - num2) != answer) right = 1; break;
			case 3:printf("%d * %d = ?\n", num1, num2); fflush(stdin); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);  if ((num1*num2) != answer) right = 1; break;
			case 4:printf("%d / %d = ?\n", num1, num2); fflush(stdin); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && num1%num2 == rest, kind, num1, num2);
				if ((num1 / num2) != answer || num1 % num2 != rest) right = 1; break;
			}
			if (right == 1) {  //����Ĵ���취 
				system("cls");
				printf("����ʧ�ܣ�С���ѣ���Ҫ����ؿ�ʼ������ս��\n\n");
				printf("<��>                                   <��>\n");
				for (;;) {
					GetConsoleMode(hStdIn, &mode);
					mode |= ENABLE_MOUSE_INPUT;
					SetConsoleMode(hStdIn, mode);
					ReadConsoleInput(hStdIn, &inRec, 1, &mode);
					if (inRec.EventType == MOUSE_EVENT &&
						inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
							if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 5) {
								option = 1;
								break;
							}
							else if (inRec.Event.MouseEvent.dwMousePosition.X >= 37 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 42) {
								option = 0;
								break;
							}
						}
					}
				}
				if (option == 0) { system("cls"); break; }  // ���ѡ��0��break 
				else if (option == 1) { i = 0; system("pause"); system("cls"); } //���ѡ��1������i �� right�� 

			}
			else {
				printf("��ȷ��");
				system("pause");
				system("cls");
			}

		}
		if (right == 0) user_read.record.level++;
	}
	if (user_read.record.level == 3) {  //��3�� 
		printf("��ӭ���������أ�\n");
		for (i = 0; i < 7; i++) {
			right = 0;
			num1 = rand() % 101 + 1;    //��������� 
			num2 = rand() % 101 + 1;
			if (num1 < num2) { temp = num1; num1 = num2; num2 = temp; }
			srand((unsigned)time(NULL)); //���������--�����ɼ��������� 
			kind = rand() % 4 + 1;
			switch (kind) {                                                         //������Ŀ��ʷ         //������� right��Ϊ1 
			case 1:printf("%d + %d = ?\n", num1, num2); scanf("%d", &answer);
				recording((num1 + num2) == answer, kind, num1, num2); 
				if ((num1 + num2) != answer) right = 1;  break;
			case 2:printf("%d - %d = ?\n", num1, num2); scanf("%d", &answer);
				recording((num1 - num2) == answer, kind, num1, num2);
				if ((num1 - num2) != answer) right = 1; break;
			case 3:printf("%d * %d = ?\n", num1, num2); scanf("%d", &answer);
				recording((num1*num2) == answer, kind, num1, num2);
				if ((num1*num2) != answer) right = 1; break;
			case 4:printf("%d / %d = ?\n", num1, num2); scanf("%d%d", &answer, &rest);
				recording((num1 / num2) == answer && num1%num2 == rest, kind, num1, num2);
				if ((num1 / num2) != answer || num1 % num2 != rest) right = 1; break;
			}
			if (right == 1) {  //����Ĵ���취 
				system("cls");
				printf("����ʧ�ܣ�С���ѣ���Ҫ����ؿ�ʼ������ս��\n\n");
				printf("<��>                                   <��>\n");

				for (;;) {
					GetConsoleMode(hStdIn, &mode);
					mode |= ENABLE_MOUSE_INPUT;
					SetConsoleMode(hStdIn, mode);
					ReadConsoleInput(hStdIn, &inRec, 1, &mode);
					if (inRec.EventType == MOUSE_EVENT &&
						inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
							if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 5) {
								option = 1;
								break;
							}
							else if (inRec.Event.MouseEvent.dwMousePosition.X >= 37 &&
								inRec.Event.MouseEvent.dwMousePosition.X < 42) {
								option = 0;
								break;
							}
						}
					}
				}

				if (option == 0) { system("cls"); break; }   // ���ѡ��0��break 
				else if (option == 1) { i = 0; system("pause"); system("cls"); } //���ѡ��1������i �� right��
			}
			else {
				printf("��ȷ��");
				system("pause");
				system("cls");
			}

		}
		if (right == 0) {
			printf("С���ѣ������ս�Ѿ���ɡ�");
			system("pause");
			system("cls");
		}
	}
}

void watchBank() {						//feng
	FILE *fp;
	WrongBank wbank[100] = { NULL,0,0,0 };//�������������ŵĽṹ�� 
	int i;//�������� 
	fp = fopen("�����.txt", "r"); // ���ļ� 
	for (i = 0; !feof(fp); i++) {
		fread(&wbank[i], sizeof(WrongBank), 1, fp);   //һ��һ�����������¼���ṹ���У�ֱ������ 
	}
	fclose(fp);//�ر��ļ� 
	printf("����������������⣺\n");
	for (i = 0; i < 50; i++) {
		if (strcmp(user_read.name, wbank[i].name) == 0) {   //���������ȫ�ֱ�������������¼����һ��   
			switch (wbank[i].kind) {                          //��ӡ 
			case 1:printf("%d + %d=%d\n", wbank[i].num1, wbank[i].num2, wbank[i].num1 + wbank[i].num2); break;
			case 2:printf("%d - %d=%d\n", wbank[i].num1, wbank[i].num2, wbank[i].num1 - wbank[i].num2); break;
			case 3:printf("%d x %d=%d\n", wbank[i].num1, wbank[i].num2, wbank[i].num1*wbank[i].num2); break;
			case 4:printf("%d / %d=%d������%d\n", wbank[i].num1, wbank[i].num2,
				wbank[i].num1 / wbank[i].num2, wbank[i].num1%wbank[i].num2); break;
			}
		}
	}
	system("pause");
	system("cls");
}

void exerciseYourself() {				//chen
	int difficulty = 0;					//�Ѷ�ֵ
	int num1 = 0, num2 = 0;
	int kind = 0;						//���ͣ�1/2/3/4�ֱ�����/��/��/��
	int continueExercising = 1;			//����Ƿ��������
	int answer = 0;						//�洢ѧ������Ĵ�
	int standardAnswer = 0;				//��׼��
	int reminder = 0;					//��Ϊ���������¼ѧ������������
	char sign;							//��ʾ�����
	int isRight = 0;					//�����Ŀ�Ƿ�����
	int temp = 0;						//��ʱ�洢����
	int isNumber = 0;					//����û�������Ƿ�Ϊ����
	
	difficulty = setDifficulty();
	while (continueExercising) {
		isNumber = 0;						//���Ƿ��������±��Ϊ��ʹ�ܽ���ѭ��
		isRight = 0;						//���Ƿ���ȷ���±��Ϊ����
		srand(time(NULL));					//���������
		num1 = rand() % (int)pow(10, difficulty) + 1;	//ȡ��������Ѷ�1Ϊ10���ڣ��Ѷ�2Ϊ100���ڣ��Ѷ�3Ϊ1000���ڣ�				
		num2 = rand() % (int)pow(10, difficulty) + 1;
		if (kind == 2 && num1 < num2) {					//������ָ������
			temp = num1;
			num1 = num2;
			num2 = temp;
		}
		kind = (rand() % 4) + 1;				//ȡ1-4֮��������
		switch (kind) {							//���������
			case 4: sign = '/'; standardAnswer = num1 / num2; break;
			case 3: sign = '*'; standardAnswer = num1 * num2; break;
			case 2: sign = '-'; standardAnswer = num1 - num2; break;
			case 1: sign = '+'; standardAnswer = num1 + num2; break;
		}
		while (!isNumber) {
			printf("��Ŀ��   %d  %c  %d  =  ?\n", num1, sign, num2);
			if (kind == 4) {					//�����ĿΪ����
				printf("�̣�");
				fflush(stdin);					//��ջ�����
				isNumber = scanf("%d", &answer);
				getchar();						//����û�����Ļس�
				if (!isNumber) {
					printErrorSituation(3);		//���������Ϣ����������֣�
					system("pause");
					system("cls");
					continue;
				}
				printf("������");	
				fflush(stdin);
				isNumber = scanf("%d", &reminder);
				getchar();
				if (answer == standardAnswer && reminder == num1 % num2) {	//���̺���������ȷ
					isRight = 1;				//����Ϊ��ȷ
				}
			}
			else {
				printf("�𰸣�");
				fflush(stdin);
				isNumber = scanf("%d", &answer);	
				getchar();
				if (answer == standardAnswer) {			//����������ͬ
					isRight = 1;						//����Ϊ����
				}
			}
			if (!isNumber) {				//�ж��Ƿ�Ϊ����
				printErrorSituation(3);		//���������Ϣ����������֣�
				system("pause");
				system("cls");
			}
		}
		if (isRight) {
			printf("�ش���ȷ��\n");
			system("pause");
		}
		else {
			printf("���ź����ش������ȷ���ǣ�");
			if (kind == 4) {
				printf("�̣�%d  ������%d\n", standardAnswer, (num1%num2));
			}
			else {
				printf("%d\n", standardAnswer);
			}
			system("pause");
		}
		recording(isRight, kind, num1, num2);
		continueExercising = continueOrNot();
	}
}

void checkInfo() {						//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;
	int option = 0;
	
	printf("��ѡ����Ҫ�鿴������\n\n");
	printf("<1>����\n\n");
	printf("<2>��ʦ����\n\n");
	printf("<3>�鿴���˼�¼\n\n");

	while (!option) {
		GetConsoleMode(hStdIn, &mode);						
		mode |= ENABLE_MOUSE_INPUT;							
		SetConsoleMode(hStdIn, mode);						
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);
		if (inRec.EventType == MOUSE_EVENT &&
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 2 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 5) {
				option = 1;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 4 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 5) {
				option = 2;
			}
			else if (inRec.Event.MouseEvent.dwMousePosition.Y == 6 &&
				inRec.Event.MouseEvent.dwMousePosition.X < 5) {
				option = 3;
			}
		}
	}

	system("cls");

	switch (option) {
		case 3: checkRecord(); break;
		case 2: checkEvaluation(); break;
		case 1: checkAnnouncement(); break;
	}
}

void checkEvaluation() {					//chen
	printf("%sͬѧ����ʦ�����������:\n",user_read.name);
	printf("%s\n", user_read.record.evaluation);
	system("pause");
	system("cls");
}

void checkAnnouncement() {					//chen
	FILE* fp = fopen("announce.txt", "r");
	int find = 0;
	char announce[1001];

	while (fscanf(fp,"%s",announce)!=EOF){
		find++;
		printf("%s", announce);
		printf("\n");
	}
	if (find == 0) {
		printf("��ǰû�й��档\n");
	}
	system("pause");
	system("cls");
}

int setDifficulty() {						//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;
	int option = 0;
	
	printf("��ѡ��������Ҫ����Ŀ�Ѷȣ�\n\n");
	printf("<1>         <2>          <3>\n");

	while (!option) {
		GetConsoleMode(hStdIn, &mode);
		mode |= ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdIn, mode);
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);
		if (inRec.EventType == MOUSE_EVENT &&
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
				if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 3) {
					option = 1;
				}
				else if (inRec.Event.MouseEvent.dwMousePosition.X >= 11 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 17) {
					option = 2;
				}
				else if (inRec.Event.MouseEvent.dwMousePosition.X >= 25 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 29) {
					option = 3;
				}
			}
		}
	}
	printf("��ѡ���˵�%d�����Ѷ�\n", option);
	system("pause");
	system("cls");
	return option;
}

int recording(int isRight, int kind,int num1,int num2) {	//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;
	int option = 0;
	
	user_read.record.numberOfQuestions++;				//������+1
	switch (kind) {
		case 4:user_read.record.numberOfDiv++; break;
		case 3:user_read.record.numberOfMul++; break;
		case 2:user_read.record.numberOfSub++; break;
		case 1:user_read.record.numberOfAddQuestions++; break;
	}
	if (isRight) {
		user_read.record.numberOfSolvedQuestions++;		//������+1
		switch (kind) {
			case 4:user_read.record.solvedDiv++; break;
			case 3:user_read.record.solvedMul++; break;
			case 2:user_read.record.solvedSub++; break;
			case 1:user_read.record.solvedAdd++; break;
		}
		return 0;
	}
	else {
		system("cls");
		printf("Ҫ������������������\n\n");
		printf("<��>                    <��>");
		for (;;) {
			GetConsoleMode(hStdIn, &mode);
			mode |= ENABLE_MOUSE_INPUT;
			SetConsoleMode(hStdIn, mode);
			ReadConsoleInput(hStdIn, &inRec, 1, &mode);
			if (inRec.EventType == MOUSE_EVENT &&
				inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
					if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
						inRec.Event.MouseEvent.dwMousePosition.X < 3) {
						option = 1;
						break;
					}
					else if (inRec.Event.MouseEvent.dwMousePosition.X >= 21 &&
						inRec.Event.MouseEvent.dwMousePosition.X < 30) {
						option = 0;
						break;
					}
				}
			}
		}
		if (option) {
			enterBank(user_read.name, kind, num1, num2);
		}
		return option;
	}
}

void enterBank(char name[], int kind, int num1, int num2) {		//feng
	FILE *fp;
	WrongBank wbank;   //�������������ṹ�嵱�� 
	wbank.kind = kind;
	wbank.num1 = num1;
	wbank.num2 = num2;
	strcpy(wbank.name, name);
	fp = fopen("�����.txt", "a");    //���ļ� 
	fwrite(&wbank, sizeof(WrongBank), 1, fp);   //��Ӽ�¼ 
	fclose(fp);   //end 
}

void save() {					//chen
	FILE *fp = fopen("data.txt", "rt+");			//�򿪴洢���ݵ��ı��������д��
	User user;										//�½�һ���ֲ�����user�����Ա��������ļ�
	while (fread(&user, sizeof(user), 1, fp)) {
		if (!strcmp(user.name, user_read.name)) {	//strcmp()����ֵΪ0�������ֶ�Ӧ
			break;
		}
	}
	fseek(fp, -(long)sizeof(User), SEEK_CUR);		//��ָ��fp��λ�����õ���ǰλ�õ�ǰһҳ������Ӧ�û�֮ǰ��
	fwrite(&user_read, sizeof(User), 1, fp);
	fclose(fp);
}

int continueOrNot() {											//chen
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD mode;

	system("cls");
	printf("����Ҫ����������\n\n");
	printf("<��>               <��>\n");
	for (;;) {
		GetConsoleMode(hStdIn, &mode);
		mode |= ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdIn, mode);
		ReadConsoleInput(hStdIn, &inRec, 1, &mode);
		if (inRec.EventType == MOUSE_EVENT &&
			inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (inRec.Event.MouseEvent.dwMousePosition.Y == 2) {
				if (inRec.Event.MouseEvent.dwMousePosition.X >= 0 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 6) {
					system("cls");
					return 1;
				}
				else if (inRec.Event.MouseEvent.dwMousePosition.X >= 17 &&
					inRec.Event.MouseEvent.dwMousePosition.X < 22) {
					system("cls");
					return 0;
				}
			}
		}
	}
}

void checkRecord() {										//chen
	printf("��������¼���£�\n");
	printf("����������%d\n",user_read.record.numberOfQuestions);
	printf("����ȷ����%d\n", user_read.record.numberOfSolvedQuestions);
	if (user_read.record.numberOfSolvedQuestions == 0) {
		printf("����ȷ��0.00%%\n");
	}
	else {
		printf("����ȷ�ʣ�%.2lf%%\n",
			user_read.record.numberOfSolvedQuestions *100.0 / user_read.record.numberOfQuestions);
	}
	printf("�ӷ���������%d\t\t", user_read.record.numberOfAddQuestions);
	printf("�ӷ���ȷ������%d\n", user_read.record.solvedAdd);
	printf("������������%d\t\t", user_read.record.numberOfSub);
	printf("������ȷ������%d\n", user_read.record.solvedSub);
	printf("�˷���������%d\t\t", user_read.record.numberOfMul);
	printf("�˷���ȷ������%d\n", user_read.record.solvedMul);
	printf("������������%d\t\t", user_read.record.numberOfDiv);
	printf("������ȷ������%d\n", user_read.record.solvedDiv);
	system("pause");
	system("cls");
}

Node* sort(Node* pHead) {						//chen
	Node* p = pHead->pNext;
	Node* q = pHead->pNext;
	User temp;
	for (p; p->pNext; p = p->pNext) {
		for (q = pHead->pNext; q->pNext; q = q->pNext) {
			if (q->user.record.numberOfQuestions < q->pNext->user.record.numberOfQuestions) {
				temp = q->pNext->user;
				q->pNext->user = q->user;
				q->user = temp;
			}
		}
	}
	return pHead;
}

int checkRepeat(User newUser) {
	FILE *fp = fopen("data.txt", "r");								//�򿪴洢���ݵ��ļ�
	User user;

	for (;;) {
		if (fread(&user, sizeof(user), 1, fp)) {
			if (!strcmp(newUser.account, user.account)) {			//���Ѵ�����ͬ�û���
				return 1;											//����1
			}
			else if (!strcmp(newUser.name, user.name)) {			//���Ѵ�����ͬ����
				return 2;											//����2
			}
		}
		else {
			return 0;												//����0����ʾ���ظ���
		}
	}
}

void printErrorSituation(int situation) {						//chen
	switch (situation) {
		case 5:printf("�趨�����볤�ȳ���20���ַ���������\n"); break;
		case 4:printf("�趨���˺ų��ȳ���20���ַ���������\n"); break;
		case 3:printf("������Ĳ������֣�����������\n"); break;
		case 2:printf("���Ѿ�ӵ��һ���˺��ˣ��벻Ҫ�ظ�ע��\n"); break;
		case 1:printf("���û����Ѵ��ڣ��벻Ҫ�ظ�ע��\n"); break;
		default: break;
	}
}

void quit() {
	printf("����������������������       %%%%%%%%%%%\n");
	printf("������������������������   %%%%/\\%%%%/\\%%%%,\n");
	printf("����������������������   %%%%%%%%/c ''J/ %%%%%%%,\n");
	printf("�� %.����������������     %%%%%%%%/ d��b \\%%%%%%%%% \n");
	printf("�� `%%.�������� _��   %%%%%%%%%%%%%%|����_��|%%%%%%%%%%%%% \n");
	printf("����`%%������.-����`'~-'`%%%%%%%%%%(=_Y_=)%%%%%%%%%%%%%%     ~~~  �ټ�\n");
	printf("���� //����.������ `.�� `%%%%%%%%%%%% \\7/%%%%%%%%%%%____\n");
	printf("���� //����.������ `.����  %%%%%%%%\\7/%%%%%%%%____ \n");
	printf("����((����/����,�� ;������`  %%%%%%%%%%____)))\n");
	printf("����`.`--����,��, ,����_,`-._%%%%%%%_`-,\n");
	printf("\n������3����˳���");
	Sleep(3000);
}

