#pragma once //�ߺ� ���̺귯���� ������ �ϳ��� �ν�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STUDENT{
    char name[20]; //�л���
    int id, java, android, kotlin, react, javascript, total; //�й�, ���� ����, �հ�
    double avr; // ���� ���
    char gender[5]; // ����
    char grade; // ���

    struct STUDENT* prev; //struct STUDENT ����Ű�� ������ ����
    struct STUDENT* next; //struct STUDENT ����Ű�� ������ ����
}STUDENT_t;

STUDENT_t* head = NULL; // ���߿��Ḯ��Ʈ ���
STUDENT_t* current = NULL; // ��ȭ�鿡 ǥ�õǴ� ���
const int SU = 5; // �����

char input_grade(double avr);
int check_id(int id);
int input_value(char *subject, int minimum, int maximum);

// head ��� ����
void initialize_student(){
    head = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));
    //head�� ������ �ȳ�
    if(head == NULL){
        puts("�� ������ STUDENT ����ü ���� ����");
        getchar();
    }
    return;
}

// ��� �߰��Ͽ� ������ ��忡 ����
// (ó��-head ���� ��ġ, ������-����� ������ ��� ���� ��ġ)
void append_node(STUDENT_t *data){
    STUDENT_t* p = head; // �ӽ� head ������ ����(head �� ���� ����)

    //next�� NULL�� ���� �̵�(������ ���)
    while(p->next!=NULL){
        p = p->next;
    }

    //������ ��忡 data ����
    p->next = data;

    //�߰��� ��忡 ���� ��� ���� (head ����)
    if(p!=head){
        data->prev = p;
    }

    return;
}

// ��� ���
void print_student(){
    STUDENT_t* p = head; // �ӽ� head ������ ����(head �� ���� ����)

    if(p==NULL){
        puts("����� �����Ͱ� �����ϴ�.");
        return;
    }
    puts("======================================================================");
    puts("�̸�\t�й�\t����\t\t����\t\t����\t���\t���");
    puts("======================================================================");

    //next�� NULL�� ���� �̵�(������ ���)
    while(p->next!=NULL){
        p = p->next;
        printf("%6s \t%4d \t%4s \t%3d %3d %3d %3d %3d \t%3d \t%5.2lf \t%2c\n",
               p->name, p->id, p->gender, p->java, p->android, p->kotlin,
               p->react, p->javascript, p->total, p->avr, p->grade);
    }

    return;
}

// ���� �л� ���� ���� �Է�
STUDENT_t* new_student(){
    STUDENT_t* data = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));
    int flag=0; //�ݺ��� ����

    if(data == NULL){
        puts("�� ������ STUDENT ����ü �Է� ����");
        getchar();
        return NULL;
    }
    //�̸� �Է�
    printf("%12s :", "�̸�");
    scanf_s("%s", data->name, sizeof(data->name));
    getchar();

    //�й� �Է�(�ߺ� Ȯ��)
    while(!flag){
        data->id = input_value("�й�", 1000, 9999);

        if(check_id(data->id)==0){
            flag = 1;
            continue;
        }

        puts("�ߺ��� �й��Դϴ�. �ٽ� �Է����ּ���.");
    }

    //���� �Է�
    printf("%12s : ", "����");
    scanf_s("%s", data->gender, sizeof(data->gender));
    getchar();
    //���� �Է�
    data->java = input_value("JAVA", 0, 100);
    data->android = input_value("ANDROID", 0, 100);
    data->kotlin = input_value("KOTLIN", 0, 100);
    data->react = input_value("REACT", 0, 100);
    data->javascript = input_value("JAVASCRIPT", 0, 100);
    //����, ��� ����
    data->total = data->java + data->android + data->kotlin + data->react + data->javascript;
    data->avr = data->total / (double)SU;
    //��� ����
    data->grade = input_grade(data->avr);

    return data;
}

// �л� ���� ����
void update_student(STUDENT_t *current){

    if(current == NULL){
        puts("");
        getchar();
        return ;
    }

    //���� �Է�
    current->java = input_value("���� JAVA", 0, 100);
    current->android = input_value("���� ANDROID", 0, 100);
    current->kotlin = input_value("���� KOTLIN", 0, 100);
    current->react = input_value("���� REACT", 0, 100);
    current->javascript = input_value("���� JAVASCRIPT", 0, 100);
    //����, ��� ����
    current->total = current->java + current->android + current->kotlin + current->react + current->javascript;
    current->avr = current->total / (double)SU;
    //��� ����
    current->grade = input_grade(current->avr);

    return;
}

// �л� ���� �˻�
STUDENT_t* search_student(){
    STUDENT_t* p = head; // �ӽ� head ������ ����(head �� ���� ����)
    STUDENT_t* data = NULL;
    int id=0;

    printf("�˻���� �й��� �Է����ּ��� (1000~9999) : ");
    scanf("%d", &id);

     while(p->next!=NULL){
            p = p->next;
            if(p->id==id){
                data = p;
                break;
            }
    }

    if(data==NULL){
        printf("�ش��ϴ� �л�(�й�: %d)�� �����ϴ�. \n", id);
        getchar();
        getchar();
    }

    return data;
}

// ��� ���� �Լ�
char input_grade(double avr){
    char grade=0;

    if(avr>=90.0){
        grade = 'A';
    }else if(avr>=80.0){
        grade = 'B';
    }else if(avr>=70.0){
        grade = 'C';
    }else if(avr>=60.0){
        grade = 'D';
    }else{
        grade = 'F';
    }

    return grade;
}

// �й� �ߺ� üũ
int check_id(int id){
    int id_value = 0;
    STUDENT_t* p = head; // �ӽ� head ������ ����(head �� ���� ����)

        //���� ��� �߿� �Էµ� �й��� ���� ���� �ִ��� Ȯ��
        while(p->next!=NULL){
            p = p->next;
            if(p->id==id){
                id_value = p->id;
                break;
            }
        }

    return id_value;
}

// �л� ���� ����
void insert_student(STUDENT_t* data){
    // 1) head�� ���� (�Էµ� ���� ���� ���)
    if(head->next==NULL){
        head->next = data;
        return;
    }

    //2) ó����忡 ���� 3) ��������忡 ����, 4) �߰���忡 ����
    if(current->prev==NULL){
        // ó�� ��忡 ����
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next==NULL){
        // ������ ��忡 ����
        append_node(data);
    }else if(current->prev!=NULL && current->next!=NULL){
        // �߰� ��忡 ����
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("���Կ� �����Ͽ����ϴ�. ���� ���");
        getchar();
        getchar();
    }

    return;
}

// �л� ���� ����
void delete_student(){
    STUDENT_t* p = current;

    // current ��� �����ǹǷ� ����/���� ���� ���� �ʿ�
    if(current->next!=NULL){
        // ���� ����� �߰� ����� �� current�� ���� ���� �̵�
        current = current->next;
    }else if(current->next==NULL && current->prev!=NULL){
        // ��������� ������ ����� �� current�� ���� ���� �̵�
        current = current->prev;
    }else{
        // ��ü ��尡 head�� ������� ���� �� current �ʱ�ȭ
        current = NULL;
    }

    if(p->next!=NULL && p->prev==NULL){
        // ó�� ����� �� ��� ����
        p->next->prev = NULL;
        head->next = p->next;
    }else if(p->next!=NULL && p->prev!=NULL){
        // �߰� ����� �� ���� ����
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }else if(p->next==NULL && p->prev!=NULL){
        // ������ ����� �� ���� ��� ���� ����
        p->prev->next = NULL;
    }else{
        // ��ü ��尡 head�� ������� ���� �� head ���� ����
        head->next = NULL;
    }

    free(p);

    return;
}

// �Է°� ����
int input_value(char *subject, int minimum, int maximum){
    int value = 0, flag = 0;

    while(!flag){
        printf("%12s (%d~%d) : ", subject, minimum, maximum);
        scanf("%d", &value);

        if(value<minimum || value>maximum){
        printf("%s��(��) �ٽ� �Է����ּ���. (%d~%d)", subject, minimum, maximum);
        }

        flag = 1;
    }

    return value;
}

