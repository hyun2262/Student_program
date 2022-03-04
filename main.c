#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mem.h>
#include <string.h>
#define MAX 100 // 최대 100명


//구조체 정의
struct STUDENT_INFO{
    char name[20]; //학생명
    int id, kor, eng, math, total; //학번, 국어, 영어, 수학 점수, 합계
    double avr; // 평균
    char grade; //등급
};

typedef struct STUDENT_INFO stu;
int total_cnt = 0; // 구조체 배열수
const int SU = 3; // 과목수

void input_scr(stu *student); // 성적 입력 함수 선언
char input_grade(double avr); // 등급 산정 함수 선언
void print_scr(stu *student, int cnt); // 성적 출력 함수 선언
void sort_scr(stu *student); // 성적 정렬 함수 선언
void search_scr(stu *student); // 성적 검색 함수 선언
void delete_scr(stu *student); // 성적 삭제 함수 선언
void add_scr(stu *student); // 성적 추가 함수 선언
void update_scr(stu *student); // 성적 수정 함수 선언

int main()
{
    stu student[MAX];
    int menu = 0, flag = 0;

    //입력 대상 학생수
    printf("입력할 학생 수: ");
    scanf("%d", &total_cnt);

    if(total_cnt>MAX){
        printf("최대 입력 가능한 학생수는 %d명 입니다. \n", MAX);
        printf("%d명으로 입력 진행합니다.\n", MAX);
        total_cnt = MAX;
    }

    while(!flag){
        printf("1. 성적 입력 \n");
        printf("2. 성적 출력 \n");
        printf("3. 성적 정렬 \n");
        printf("4. 성적 검색 \n");
        printf("5. 성적 삭제 \n");
        printf("6. 성적 추가 \n");
        printf("7. 성적 수정 \n");
        printf("8. 종료 \n");
        printf("메뉴 선택: ");
        scanf("%d", &menu);

        switch(menu){
        case 1:
            input_scr(student);
            printf("** 입력이 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 2:
            print_scr(student, total_cnt);
            printf("** 출력이 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 3:
            sort_scr(student);
            printf("** 정렬이 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 4:
            search_scr(student);
            printf("** 검색이 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 5:
            delete_scr(student);
            printf("** 삭제가 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 6:
            add_scr(student);
            printf("** 추가가 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 7:
            update_scr(student);
            printf("** 수정이 완료되었습니다. ** \n");
            getchar(); getchar();
            system("cls");
            break;
        case 8: flag = 1; break;
        default: printf("다시 입력해주세요. \n");
        }
    }//end of while

    printf("성적 프로그램을 종료합니다. \n");

    return 0;
}
//성적 입력 함수 정의
void input_scr(stu *student){
    int i = 0;

    for(i=0; i<total_cnt; i++){

        printf("%d번째 학생 이름을 입력하세요 : ", i+1);
        scanf("%s", student[i].name);

        //학번 입력받기
        printf("%d번째 학생 학번을 입력하세요(1000~9999) : ", i+1);
        scanf("%d", &student[i].id);

        //점수 입력받기
        printf("%d번째 학생 국어점수를 입력하세요(0~100) : ", i+1);
        scanf("%d", &student[i].kor);
        printf("%d번째 학생 영어점수를 입력하세요(0~100) : ", i+1);
        scanf("%d", &student[i].eng);
        printf("%d번째 학생 수학점수를 입력하세요(0~100) : ", i+1);
        scanf("%d", &student[i].math);

        //총점, 평균 계산
        student[i].total = student[i].kor + student[i].eng + student[i].math;
        student[i].avr = student[i].total / (double)SU;

        //등급 함수 호출
        student[i].grade = input_grade(student[i].avr);
        printf("\n");
    }
    return;
}

// 등급 산정 함수 정의
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
//성적 출력 함수 정의
void print_scr(stu *student, int cnt){
    int i = 0, sum1=0, sum2=0, sum3 =0;

    printf("개별 학생 성적 \n");
    for(i=0; i<cnt; i++){
        if(student[i].total==0) continue;

        printf("%5s (%4d): %4d %4d %4d %8d %5.2lf %3c \n",
               student[i].name, student[i].id, student[i].kor, student[i].eng,
               student[i].math, student[i].total, student[i].avr, student[i].grade);
    }

    printf("과목별 성적 평균 \n");
    for(i=0; i<cnt; i++){
        sum1 += student[i].kor;
        sum2 += student[i].eng;
        sum3 += student[i].math;
    }

    printf("국어 성적 평균 : %.2lf \n", sum1/(double)cnt);
    printf("영어 성적 평균 : %.2lf \n", sum2/(double)cnt);
    printf("수학 성적 평균 : %.2lf \n", sum3/(double)cnt);

    return;
}
//성적 정렬 함수 정의
void sort_scr(stu *student){
    stu cpy_student[total_cnt]; // 복사한 구조체
    stu tempt; // 선택정렬시 담아둘 구조체
    int i, j = 0, sort = 0;

    //구조체 복사
    for(i=0; i<total_cnt; i++){
        memcpy(&cpy_student[i], &student[i], sizeof(student[i]));
    }

    //정렬방식 선택
    printf("정렬 방식 선택 \n1) 오름차순 2) 내림차순 \n");
    scanf("%d", &sort);
    //선택정렬로 성적순 정렬
    if(!(sort-1)){
        //오름차순 정렬
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
        //내림차순 정렬
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

    //정렬된 복사 구조체 출력
    print_scr(cpy_student, total_cnt);

    return;
}
//성적 검색 함수 정의
void search_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;
    //이름 입력
    printf("검색 대상 학생명: ");
    scanf("%s", name);

    //입력된 이름과 같으면 성적 출력
    for(i=0; i<total_cnt; i++){
        if(!strnicmp(name, student[i].name, sizeof(student[i].name))){
            print_scr(&student[i], 1);
            flag = 1;
        }
    }

    //입력된 이름 없는 경우 안내
    if(!flag){
        printf("일치하는 학생이 없습니다. \n");
    }

    return;
}
//성적 삭제 함수 정의
void delete_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;
    //이름 입력
    printf("삭제 대상 학생명: ");
    scanf("%s", name);

    //입력된 이름과 같으면 구조체 초기화
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

    //입력된 이름 없는 경우 안내
    if(!flag){
        printf("일치하는 학생이 없습니다. \n");
    }
    return;
}
//성적 추가 함수 정의
void add_scr(stu *student){
    //인원 추가 가능 여부 확인
    if(total_cnt+1>MAX){
        printf("인원추가가 불가능합니다. (현재 인원: %d)\n", MAX);
    }

    total_cnt++;

    //추가 대상 정보 입력
    printf("추가 대상 학생명: ");
    scanf("%s", student[total_cnt-1].name);
    printf("%s 학번: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].id);
    printf("%s 국어 점수: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].kor);
    printf("%s 영어 점수: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].eng);
    printf("%s 수학 점수: ", student[total_cnt-1].name);
    scanf("%d", &student[total_cnt-1].math);

    //총점, 평균 계산
    student[total_cnt-1].total = student[total_cnt-1].kor + student[total_cnt-1].eng + student[total_cnt-1].math;
    student[total_cnt-1].avr = student[total_cnt-1].total / (double)SU;

    //등급산정 함수 호출
    student[total_cnt-1].grade = input_grade(student[total_cnt-1].avr);

    //추가한 학생 정보 출력
    print_scr(&student[total_cnt-1], 1);

    return;
}
//성적 수정 함수 정의
void update_scr(stu *student){
    char name[20] = "";
    int i = 0, flag = 0;

    //이름 입력
    printf("수정 대상 학생명: ");
    scanf("%s", name);

    //입력된 이름과 같으면 해당 구조체 성적 재입력
    for(i=0; i<total_cnt; i++){
        if(!strnicmp(name, student[i].name, sizeof(student[i].name))){
            printf("%s 국어 점수 (현재 점수: %d): ", student[i].name, student[i].kor);
            scanf("%d", &student[i].kor);
            printf("%s 영어 점수 (현재 점수 : %d): ", student[i].name, student[i].eng);
            scanf("%d", &student[i].eng);
            printf("%s 수학 점수 (현재 점수 : %d): ", student[i].name, student[i].math);
            scanf("%d", &student[i].math);

            //변경된 성적으로 총점, 평균 계산
            student[i].total = student[i].kor + student[i].eng + student[i].math;
            student[i].avr = student[i].total / (double)SU;

            //등급 함수 호출
            student[i].grade = input_grade(student[i].avr);

            //수정한 학생 정보 출력
            print_scr(&student[i], 1);

            flag = 1;
        }
    }

    //입력된 이름 없는 경우 안내
    if(!flag){
        printf("일치하는 학생이 없습니다. \n");
    }

    return;
}
