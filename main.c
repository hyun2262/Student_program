#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mem.h>
#include <string.h>
#define MAX 100 // �ִ� 100��


//����ü ����
struct STUDENT_INFO{
    char name[20]; //�л���
    int id, kor, eng, math, total; //�й�, ����, ����, ���� ����, �հ�
    double avr; // ���
    char grade; //���
};

typedef struct STUDENT_INFO stu;
int total_cnt = 0; // ����ü �迭��
const int SU = 3; // �����

void input_scr(stu *student); // ���� �Է� �Լ� ����
char input_grade(double avr); // ��� ���� �Լ� ����
void print_scr(stu *student, int cnt); // ���� ��� �Լ� ����
void sort_scr(stu *student); // ���� ���� �Լ� ����
void search_scr(stu *student); // ���� �˻� �Լ� ����
void delete_scr(stu *student); // ���� ���� �Լ� ����
void add_scr(stu *student); // ���� �߰� �Լ� ����
void update_scr(stu *student); // ���� ���� �Լ� ����

int main()
{
    stu student[MAX];
    int menu = 0, flag = 0;

    //�Է� ��� �л���
    printf("�Է��� �л� ��: ");
    scanf("%d", &total_cnt);

    if(total_cnt>MAX){
        printf("�ִ� �Է� ������ �л����� %d�� �Դϴ�. \n", MAX);
        printf("%d������ �Է� �����մϴ�.\n", MAX);
        total_cnt = MAX;
    }

    while(!flag){
        printf("1. ���� �Է� \n");
        printf("2. ���� ��� \n");
        printf("3. ���� ���� \n");
        printf("4. ���� �˻� \n");
        printf("5. ���� ���� \n");
        printf("6. ���� �߰� \n");
        printf("7. ���� ���� \n");
        printf("8. ���� \n");
        printf("�޴� ����: ");
        scanf("%d", &menu);

        switch(menu){
        case 1:
            input_scr(student);
            printf("** �Է��� �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 2:
            print_scr(student, total_cnt);
            printf("** ����� �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 3:
            sort_scr(student);
            printf("** ������ �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 4:
            search_scr(student);
            printf("** �˻��� �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 5:
            delete_scr(student);
            printf("** ������ �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 6:
            add_scr(student);
            printf("** �߰��� �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 7:
            update_scr(student);
            printf("** ������ �Ϸ�Ǿ����ϴ�. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 8: flag = 1; break;
        default: printf("�ٽ� �Է����ּ���. \n");
        }
    }//end of while

    printf("���� ���α׷��� �����մϴ�. \n");

    return 0;
}
//���� �Է� �Լ� ����
void input_scr(stu *student){
    int i = 0;

    for(i=0; i<total_cnt; i++){

        printf("%d��° �л� �̸��� �Է��ϼ��� : ", i+1);
        scanf("%s", student[i].name);

        //�й� �Է¹ޱ�
        printf("%d��° �л� �й��� �Է��ϼ���(1000~9999) : ", i+1);
        scanf("%d", &student[i].id);

        //���� �Է¹ޱ�
        printf("%d��° �л� ���������� �Է��ϼ���(0~100) : ", i+1);
        scanf("%d", &student[i].kor);
        printf("%d��° �л� ���������� �Է��ϼ���(0~100) : ", i+1);
        scanf("%d", &student[i].eng);
        printf("%d��° �л� ���������� �Է��ϼ���(0~100) : ", i+1);
        scanf("%d", &student[i].math);

        //����, ��� ���
        student[i].total = student[i].kor + student[i].eng + student[i].math;
        student[i].avr = student[i].total / (double)SU;

        //��� �Լ� ȣ��
        student[i].grade = input_grade(student[i].avr);
        printf("\n");
    }
    return;
}

// ��� ���� �Լ� ����
char input_grade(double avr){
    char grade = 0;

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
//���� ��� �Լ� ����
void print_scr(stu *student, int cnt){
    int i = 0, sum1=0, sum2=0, sum3 =0;

    printf("���� �л� ���� \n");
    for(i=0; i<cnt; i++){
        if(student[i].total==0) continue;

        printf("%5s (%4d): %4d %4d %4d %8d %5.2lf %3c \n",
               student[i].name, student[i].id, student[i].kor, student[i].eng,
               student[i].math, student[i].total, student[i].avr, student[i].grade);
    }

    printf("���� ���� ��� \n");
    for(i=0; i<cnt; i++){
        sum1 += student[i].kor;
        sum2 += student[i].eng;
        sum3 += student[i].math;
    }

    printf("���� ���� ��� : %.2lf \n", sum1/(double)cnt);
    printf("���� ���� ��� : %.2lf \n", sum2/(double)cnt);
    printf("���� ���� ��� : %.2lf \n", sum3/(double)cnt);

    return;
}
//���� ���� �Լ� ����
void sort_scr(stu *student){
    stu cpy_student[total_cnt]; // ������ ����ü
    stu tempt; // �������Ľ� ��Ƶ� ����ü
    int i, j = 0, sort = 0;

    //����ü ����
    for(i=0; i<total_cnt; i++){
        memcpy(&cpy_student[i], &student[i], sizeof(student[i]));
    }

    //���Ĺ�� ����
    printf("���� ��� ���� \n1) �������� 2) �������� \n");
    scanf("%d", &sort);
    //�������ķ� ������ ����
    if(!(sort-1)){
        //�������� ����
        for(i=0; i<total_cnt-1; i++){
            for(j=i+1; j<total_cnt; j++){
                if(cpy_student[i].total<cpy_student[j].total){
                    memcpy(&tempt, &cpy_student[i], sizeof(cpy_student[i]));
                    memcpy(&cpy_student[i], &cpy_student[j], sizeof(cpy_student[i]));
                    memcpy(&cpy_student[j], &tempt, sizeof(cpy_student[i]));
                }
            }
        }
    }else{
        //�������� ����
        for(i=0; i<total_cnt-1; i++){
            for(j=i+1; j<total_cnt; j++){
                if(cpy_student[i].total>cpy_student[j].total){
                    memcpy(&tempt, &cpy_student[i], sizeof(cpy_student[i]));
                    memcpy(&cpy_student[i], &cpy_student[j], sizeof(cpy_student[i]));
                    memcpy(&cpy_student[j], &tempt, sizeof(cpy_student[i]));
                }
            }
        }
    }

    //���ĵ� ���� ����ü ���
    print_scr(cpy_student, total_cnt);

    return;
}
//���� �˻� �Լ� ����
void search_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;
    //�̸� �Է�
    printf("�˻� ��� �л���: ");
    scanf("%s", name);

    //�Էµ� �̸��� ������ ���� ���
    for(i=0; i<total_cnt; i++){
        if(!strnicmp(name, student[i].name, sizeof(student[i].name))){
            print_scr(&student[i], 1);
            flag = 1;
        }
    }

    //�Էµ� �̸� ���� ��� �ȳ�
    if(!flag){
        printf("��ġ�ϴ� �л��� �����ϴ�. \n");
    }

    return;
}
//���� ���� �Լ� ����
void delete_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;
    //�̸� �Է�
    printf("���� ��� �л���: ");
    scanf("%s", name);

    //�Էµ� �̸��� ������ ����ü �ʱ�ȭ
    for(i=0; i<total_cnt; i++){
        if(!strnicmp(name, student[i].name, sizeof(student[i].name))){
            strcpy(student[i].name, "");
            student[i].id = 0;
            student[i].kor = 0;
            student[i].eng = 0;
            student[i].math = 0;
            student[i].total = 0;
            student[i].avr = 0.0;
            student[i].grade = 0;
            flag = 1;
        }
    }

    //�Էµ� �̸� ���� ��� �ȳ�
    if(!flag){
        printf("��ġ�ϴ� �л��� �����ϴ�. \n");
    }
    return;
}
//���� �߰� �Լ� ����
void add_scr(stu *student){
    //�ο� �߰� ���� ���� Ȯ��
    if(total_cnt+1>MAX){
        printf("�ο��߰��� �Ұ����մϴ�. (���� �ο�: %d)\n", MAX);
    }

    total_cnt++;

    //�߰� ��� ���� �Է�
    printf("�߰� ��� �л���: ");
    scanf("%s", student[total_cnt-1].name);
    printf("%s �й�: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].id);
    printf("%s ���� ����: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].kor);
    printf("%s ���� ����: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].eng);
    printf("%s ���� ����: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].math);

    //����, ��� ���
    student[total_cnt-1].total = student[total_cnt-1].kor + student[total_cnt-1].eng + student[total_cnt-1].math;
    student[total_cnt-1].avr = student[total_cnt-1].total / (double)SU;

    //��޻��� �Լ� ȣ��
    student[total_cnt-1].grade = input_grade(student[total_cnt-1].avr);

    //�߰��� �л� ���� ���
    print_scr(&student[total_cnt-1], 1);

    return;
}
//���� ���� �Լ� ����
void update_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;

    //�̸� �Է�
    printf("���� ��� �л���: ");
    scanf("%s", name);

    //�Էµ� �̸��� ������ �ش� ����ü ���� ���Է�
    for(i=0; i<total_cnt; i++){
        if(!strnicmp(name, student[i].name, sizeof(student[i].name))){
            printf("%s ���� ���� (���� ����: %d): ", student[i].name, student[i].kor);
            scanf("%d", &student[i].kor);
            printf("%s ���� ���� (���� ���� : %d): ", student[i].name, student[i].eng);
            scanf("%d", &student[i].eng);
            printf("%s ���� ���� (���� ���� : %d): ", student[i].name, student[i].math);
            scanf("%d", &student[i].math);

            //����� �������� ����, ��� ���
            student[i].total = student[i].kor + student[i].eng + student[i].math;
            student[i].avr = student[i].total / (double)SU;

            //��� �Լ� ȣ��
            student[i].grade = input_grade(student[i].avr);

            //������ �л� ���� ���
            print_scr(&student[i], 1);

            flag = 1;
        }
    }

    //�Էµ� �̸� ���� ��� �ȳ�
    if(!flag){
        printf("��ġ�ϴ� �л��� �����ϴ�. \n");
    }

    return;
}
