#pragma once //중복 라이브러리가 있으면 하나만 인식
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STUDENT{
    char name[20]; //학생명
    int id, java, android, kotlin, react, javascript, total; //학번, 과목 점수, 합계
    double avr; // 점수 평균
    char gender[5]; // 성별
    char grade; // 등급

    struct STUDENT* prev; //struct STUDENT 가리키는 포인터 변수
    struct STUDENT* next; //struct STUDENT 가리키는 포인터 변수
}STUDENT_t;

STUDENT_t* head = NULL; // 이중연결리스트 노드
STUDENT_t* current = NULL; // 현화면에 표시되는 노드
const int SU = 5; // 과목수

char input_grade(double avr);
int check_id(int id);
int input_value(char *subject, int minimum, int maximum);

// head 노드 생성
void initialize_student(){
    head = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));
    //head가 없으면 안내
    if(head == NULL){
        puts("힙 영역에 STUDENT 구조체 생성 실패");
        getchar();
    }
    return;
}

// 노드 추가하여 마지막 노드에 연결
// (처음-head 다음 위치, 마지막-연결된 마지막 노드 다음 위치)
void append_node(STUDENT_t *data){
    STUDENT_t* p = head; // 임시 head 포인터 변수(head 값 고정 목적)

    //next가 NULL인 노드로 이동(마지막 노드)
    while(p->next!=NULL){
        p = p->next;
    }

    //마지막 노드에 data 연결
    p->next = data;

    //추가한 노드에 이전 노드 연결 (head 제외)
    if(p!=head){
        data->prev = p;
    }

    return;
}

// 노드 출력
void print_student(){
    STUDENT_t* p = head; // 임시 head 포인터 변수(head 값 고정 목적)

    if(p==NULL){
        puts("출력할 데이터가 없습니다.");
        return;
    }
    puts("======================================================================");
    puts("이름\t학번\t성별\t\t성적\t\t총점\t평균\t등급");
    puts("======================================================================");

    //next가 NULL인 노드로 이동(마지막 노드)
    while(p->next!=NULL){
        p = p->next;
        printf("%6s \t%4d \t%4s \t%3d %3d %3d %3d %3d \t%3d \t%5.2lf \t%2c\n",
               p->name, p->id, p->gender, p->java, p->android, p->kotlin,
               p->react, p->javascript, p->total, p->avr, p->grade);
    }

    return;
}

// 개별 학생 성적 정보 입력
STUDENT_t* new_student(){
    STUDENT_t* data = (STUDENT_t *)calloc(1, sizeof(STUDENT_t));
    int flag=0; //반복문 조건

    if(data == NULL){
        puts("힙 영역에 STUDENT 구조체 입력 실패");
        getchar();
        return NULL;
    }
    //이름 입력
    printf("%12s :", "이름");
    scanf_s("%s", data->name, sizeof(data->name));
    getchar();

    //학번 입력(중복 확인)
    while(!flag){
        data->id = input_value("학번", 1000, 9999);

        if(check_id(data->id)==0){
            flag = 1;
            continue;
        }

        puts("중복된 학번입니다. 다시 입력해주세요.");
    }

    //성별 입력
    printf("%12s : ", "성별");
    scanf_s("%s", data->gender, sizeof(data->gender));
    getchar();
    //점수 입력
    data->java = input_value("JAVA", 0, 100);
    data->android = input_value("ANDROID", 0, 100);
    data->kotlin = input_value("KOTLIN", 0, 100);
    data->react = input_value("REACT", 0, 100);
    data->javascript = input_value("JAVASCRIPT", 0, 100);
    //총합, 평균 산출
    data->total = data->java + data->android + data->kotlin + data->react + data->javascript;
    data->avr = data->total / (double)SU;
    //등급 산정
    data->grade = input_grade(data->avr);

    return data;
}

// 학생 정보 수정
void update_student(STUDENT_t *current){

    if(current == NULL){
        puts("");
        getchar();
        return ;
    }

    //점수 입력
    current->java = input_value("수정 JAVA", 0, 100);
    current->android = input_value("수정 ANDROID", 0, 100);
    current->kotlin = input_value("수정 KOTLIN", 0, 100);
    current->react = input_value("수정 REACT", 0, 100);
    current->javascript = input_value("수정 JAVASCRIPT", 0, 100);
    //총합, 평균 산출
    current->total = current->java + current->android + current->kotlin + current->react + current->javascript;
    current->avr = current->total / (double)SU;
    //등급 산정
    current->grade = input_grade(current->avr);

    return;
}

// 학생 성적 검색
STUDENT_t* search_student(){
    STUDENT_t* p = head; // 임시 head 포인터 변수(head 값 고정 목적)
    STUDENT_t* data = NULL;
    int id=0;

    printf("검색대상 학번을 입력해주세요 (1000~9999) : ");
    scanf("%d", &id);

     while(p->next!=NULL){
            p = p->next;
            if(p->id==id){
                data = p;
                break;
            }
    }

    if(data==NULL){
        printf("해당하는 학생(학번: %d)이 없습니다. \n", id);
        getchar();
        getchar();
    }

    return data;
}

// 등금 산정 함수
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

// 학번 중복 체크
int check_id(int id){
    int id_value = 0;
    STUDENT_t* p = head; // 임시 head 포인터 변수(head 값 고정 목적)

        //현재 노드 중에 입력된 학번과 같은 값이 있는지 확인
        while(p->next!=NULL){
            p = p->next;
            if(p->id==id){
                id_value = p->id;
                break;
            }
        }

    return id_value;
}

// 학생 정보 삽입
void insert_student(STUDENT_t* data){
    // 1) head에 연결 (입력된 성적 없는 경우)
    if(head->next==NULL){
        head->next = data;
        return;
    }

    //2) 처음노드에 연결 3) 마지막노드에 연결, 4) 중간노드에 연결
    if(current->prev==NULL){
        // 처음 노드에 연결
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next==NULL){
        // 마지막 노드에 연결
        append_node(data);
    }else if(current->prev!=NULL && current->next!=NULL){
        // 중간 노드에 연결
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("삽입에 실패하였습니다. 점검 요망");
        getchar();
        getchar();
    }

    return;
}

// 학생 정보 삭제
void delete_student(){
    STUDENT_t* p = current;

    // current 노드 삭제되므로 이전/다음 노드로 변경 필요
    if(current->next!=NULL){
        // 삭제 대상이 중간 노드일 때 current를 다음 노드로 이동
        current = current->next;
    }else if(current->next==NULL && current->prev!=NULL){
        // 삭제대상이 마지막 노드일 때 current를 이전 노드로 이동
        current = current->prev;
    }else{
        // 전체 노드가 head와 삭제대상 뿐일 때 current 초기화
        current = NULL;
    }

    if(p->next!=NULL && p->prev==NULL){
        // 처음 노드일 때 헤드 연결
        p->next->prev = NULL;
        head->next = p->next;
    }else if(p->next!=NULL && p->prev!=NULL){
        // 중간 노드일 때 양쪽 연결
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }else if(p->next==NULL && p->prev!=NULL){
        // 마지막 노드일 때 이전 노드 연결 해제
        p->prev->next = NULL;
    }else{
        // 전체 노드가 head와 삭제대상 뿐일 때 head 연결 해제
        head->next = NULL;
    }

    free(p);

    return;
}

// 입력값 검증
int input_value(char *subject, int minimum, int maximum){
    int value = 0, flag = 0;

    while(!flag){
        printf("%12s (%d~%d) : ", subject, minimum, maximum);
        scanf("%d", &value);

        if(value<minimum || value>maximum){
        printf("%s을(를) 다시 입력해주세요. (%d~%d)", subject, minimum, maximum);
        }

        flag = 1;
    }

    return value;
}

